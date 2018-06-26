#include <iostream>
#include <complex>
#include <fstream>
#include <thread>
#include <string>
#include "BuddhaCalculator.hpp"
#include "fractal_func.hpp"
#include "time.hpp"

int chunk_counter = 0;

void post_processing(std::vector<std::vector<int>> &matrix, int max_value)
{
    std::string out = "out" + std::to_string(chunk_counter) + ".pgm";
    std::ofstream f(out, std::ios_base::out | std::ios_base::binary | std::ios_base::trunc);

    int maxColorValue = 255;
    f << "P5\n"
      << matrix.size() << " " << matrix[0].size() << "\n"
      << maxColorValue << "\n";
    // std::endl == "\n" + std::flush
    // we do not want std::flush here.
    //TODO: optimize file output
    std::cout << "Writing to File..." << '\n';
    for (size_t y = 0; y < matrix[0].size(); y++)
    {
        char buffer[matrix.size()];
        for (size_t x = 0; x < matrix.size(); x++)
        {
            float transformed_pixel = log((float)matrix[x][y]);
            float transformed_max_value = log((float)max_value);
            //linear scaling
            buffer[x] = (char)((transformed_pixel / transformed_max_value) * 255.0f);
        }
        f.write(buffer, matrix.size());
    }
}

void worker(BuddhaCalculator *b, int id, int num_points)
{
    std::cout << "Worker " << id << " started." << '\n';
    b->calcPoints(num_points);
}

struct options
{
    int num_threads;
    int seconds;
    int max_iter;
    bool opt_ok = false;
    int chunck_size;
};

options parse_options(int argc, char const *argv[])
{
    options retVal;
    if (argc != 5)
    {
        return retVal;
    }
    retVal.num_threads = std::atoi(argv[1]);
    retVal.seconds = std::atoi(argv[2]);
    retVal.max_iter = std::atoi(argv[3]);
    retVal.chunck_size = std::atoi(argv[4]);
    retVal.opt_ok = true;
    return retVal;
}

void calc_chunk(std::vector<BuddhaCalculator> *buddha, int num_threads, int points_per_chunk,
                std::vector<std::vector<int>> *matrix, int *max_hit_count_combined)
{
    std::vector<std::thread> threads;
    for (size_t i = 0; i < num_threads; i++)
    {
        threads.push_back(std::thread(worker, &((*buddha)[i]), i, points_per_chunk));
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
    std::cout << "Chunk: " << chunk_counter << " fertig." << '\n';

    //Zusammenführen

    for (size_t i = 0; i < (*matrix).size(); i++)
    {
        for (size_t j = 0; j < (*matrix)[0].size(); j++)
        {
            int sum = 0;

            for (size_t k = 0; k < num_threads; k++)
            {
                sum += (*buddha)[k]._pixel_counter_array[i][j];
            }

            (*matrix)[i][j] = sum;

            if (*max_hit_count_combined < sum)
            {
                *max_hit_count_combined = sum;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    options opt = parse_options(argc, argv);

    if (!opt.opt_ok)
    {
        std::cout << "Usage: buddha <num_threads> <time in seconds> <Max Iteration> <chunk size>" << '\n';
        return 1;
    }

    const int num_threads = opt.num_threads;
    // const int points_per_thread = opt.points_per_thread;
    const int scale = 10;
    const float axis_scale = 6.0f;
    const int points_per_chunk = opt.chunck_size;

    BuddhaParam params;
    params.pixel_width = 1440 * scale;
    params.pixel_height = 900 * scale;
    params.x_axis_min = -1.0f * axis_scale;
    params.x_axis_max = 1.0f * axis_scale;
    params.y_axis_min = -1.0f * axis_scale;
    params.y_axis_max = 1.0f * axis_scale;
    params.max_iter = opt.max_iter;
    params.func = auge;

    std::vector<BuddhaCalculator> buddha;

    for (size_t i = 0; i < num_threads; i++)
    {
        buddha.push_back(BuddhaCalculator(params));
    }

    std::vector<std::vector<int>> matrix;
    matrix.resize(params.pixel_width, std::vector<int>(params.pixel_height, 0));
    int max_hit_count_combined = 0;
    time_meassure t1;
    t1.start();
    while (t1.stop() < opt.seconds)
    {
        calc_chunk(&buddha, num_threads, points_per_chunk, &matrix, &max_hit_count_combined);
        post_processing(matrix, max_hit_count_combined);
    }

    return 0;
}