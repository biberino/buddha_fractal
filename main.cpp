#include <iostream>
#include <complex>
#include <fstream>
#include <thread>
#include <string>
#include <ctime>
#include <iomanip>
#include <sys/stat.h>
#include "ConfReader.hpp"
#include "BuddhaCalculator.hpp"
#include "fractal_func.hpp"
#include "time.hpp"
#include "save_raw.hpp"

int chunk_counter = 0;

void post_processing(std::vector<std::vector<int>> &matrix, int max_value, conf_data *params)
{
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::ostringstream os;
    os << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ":   Chunk:" << chunk_counter << " Fraktal: " << std::to_string(params->func_indentifier) << ".pgm";
    std::string out = os.str(); //"out" + std::to_string(chunk_counter) + ".pgm";
    std::ofstream f(out, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

    int maxColorValue = 255;
    f << "P5\n"
      << matrix.size() << " " << matrix[0].size() << "\n"
      << maxColorValue << "\n";
    // std::endl == "\n" + std::flush
    // we do not want std::flush here.
    //TODO: optimize file output
    std::cout << "Exportiere Bild..." << '\n';
    std::cout << "Allokiere Speicher für Bildexport: " << matrix.size() / 1024 << "KByte" << '\n';
    for (size_t y = 0; y < matrix[0].size(); y++)
    {
        char buffer[matrix.size()];
        for (size_t x = 0; x < matrix.size(); x++)
        {
            double transformed_pixel = log((double)matrix[x][y]);
            double transformed_max_value = log((double)max_value);
            //linear scaling
            buffer[x] = (char)((transformed_pixel / transformed_max_value) * 255.0f);
        }
        f.write(buffer, matrix.size());
    }
}

void worker(BuddhaCalculator *b, int id, int sec)
{
    //std::cout << "Worker " << id << " started." << '\n';
    b->calcPoints(sec);
}

struct options
{
    std::string raw_input_file = "";
};

options parse_options(int argc, char const *argv[])
{

    options retVal;
    if (argc != 2)
    {
        return retVal;
    }

    retVal.raw_input_file = argv[1];

    return retVal;
}

void calc_chunk(std::vector<BuddhaCalculator> *buddha, int num_threads, int chunck_time_sec,
                std::vector<std::vector<int>> *matrix, int *max_hit_count_combined)
{
    std::vector<std::thread> threads;
    for (size_t i = 0; i < num_threads; i++)
    {
        threads.push_back(std::thread(worker, &((*buddha)[i]), i, chunck_time_sec));
    }

    for (size_t i = 0; i < num_threads; i++)
    {
        threads[i].join();
        /**
        std::cout << "***********************" << '\n';
        std::cout << "MAX HIT COUNT: " << (*buddha)[i]._max_hit_count << '\n';
        std::cout << "UNDEPICTABLE COUNT: " << (*buddha)[i]._undepictable_count << '\n';
        std::cout << "DEPICTABLE COUNT: " << (*buddha)[i]._depictable_count << '\n';
        **/
    }
    chunk_counter++;
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::cout << std::put_time(&tm, "%d-%m-%Y %H-%M-%S") << ":   Chunk: " << chunk_counter << " fertig." << '\n';

    //Zusammenführen

    for (size_t i = 0; i < (*matrix).size(); i++)
    {
        for (size_t j = 0; j < (*matrix)[0].size(); j++)
        {
            //int sum = 0;

            for (size_t k = 0; k < num_threads; k++)
            {
                (*matrix)[i][j] += (*buddha)[k]._pixel_counter_array[i][j];
            }

            //(*matrix)[i][j] = sum;

            if (*max_hit_count_combined < (*matrix)[i][j])
            {
                *max_hit_count_combined = (*matrix)[i][j];
            }
        }
    }

    for (size_t k = 0; k < num_threads; k++)
    {
        (*buddha)[k].resetState();
    }
}

int main(int argc, char const *argv[])
{
    options opt = parse_options(argc, argv);

    setup_fractals();
    ConfReader conf_reader;
    conf_data params = conf_reader.readConf("conf.json");

    std::vector<BuddhaCalculator> buddha;

    for (size_t i = 0; i < params.num_threads; i++)
    {
        buddha.push_back(BuddhaCalculator(params, fractals));
    }

    std::vector<std::vector<int>> matrix;
    matrix.resize(params.pixel_width, std::vector<int>(params.pixel_height, 0));
    int max_hit_count_combined = 0;

    if (opt.raw_input_file != "")
    {
        struct stat buffer;
        if (stat(opt.raw_input_file.c_str(), &buffer) == 0)
        {
            std::cout << "Lese Ergebnissdatei ein..." << '\n';
            read_raw_data(opt.raw_input_file, matrix, params);
        }
    }

    std::cout << "Beginne Berechnung" << '\n';

    time_meassure t1;
    t1.start();
    while (t1.stop() < params.seconds)
    {
        calc_chunk(&buddha, params.num_threads, params.chunck_time_seconds, &matrix, &max_hit_count_combined);
        post_processing(matrix, max_hit_count_combined, &params);

        if (params.save_raw_result)
        {
            if (opt.raw_input_file != "")
            {
                dump_raw_data(opt.raw_input_file, matrix, params);
            }
        }
    }

    return 0;
}
