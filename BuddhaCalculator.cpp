#include "BuddhaCalculator.hpp"
#include <limits>
#include <iostream>

#include "time.hpp"

BuddhaCalculator::BuddhaCalculator(conf_data param,
                                   std::vector<std::complex<double> (*)(std::complex<double>, std::complex<double>)> func_array)
{
    std::srand(static_cast<unsigned int>(time(0)));
    _param = param;
    std::cout << "Allokiere Speicher für Worker: " << (param.pixel_height * param.pixel_width * 4) / 1024 << " KBytes." << '\n';
    _pixel_counter_array.resize(param.pixel_width, std::vector<int>(param.pixel_height, 0));

    _height_const = _param.pixel_height / (_param.y_axis_max - _param.y_axis_min);
    _width_const = _param.pixel_width / (_param.x_axis_max - _param.x_axis_min);
    _func = func_array[param.func_indentifier];

    std::cout << "Allokiere Speicher für Hitbuffer: " << (sizeof(std::complex<double>) * _param.max_iter) / 1024 << "KBytes" << '\n';
    _hit_buffer.resize(_param.max_iter, std::complex<double>(0, 0));
}

BuddhaCalculator::~BuddhaCalculator()
{
}

void BuddhaCalculator::calcPoints(int sec)
{
    time_meassure ellapsed_time;
    ellapsed_time.start();

    

    while (ellapsed_time.stop() < sec)
    {

        for (size_t i = 0; i < _param.chunck_min_points; i++)
        {
            _number_of_valid_values = 0; //for hitbuffer

            double r1 = _param.real_min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (_param.real_max - _param.real_min)));
            double r2 = _param.im_min + static_cast<double>(rand()) / (static_cast<double>(RAND_MAX / (_param.im_max - _param.im_min)));
            std::complex<double> c(r1, r2);
            std::complex<double> z(0, 0);
            //optimierung
            //TODO SPeicherplatz vorher allokieren, wächst mit Anzahl Max Iterationen
            //oder mit array arbeiten, wobei immer ein nullptr vorgeschoben wird

            bool in_set = true;

            for (size_t j = 0; j < _param.max_iter; j++)
            {

                z = _func(z, c);
                _hit_buffer[_number_of_valid_values] = z;
                _number_of_valid_values++;

                if (((z.real() * z.real()) + (z.imag() * z.imag())) > _param.bailout_squared)
                {
                    //punkt liegt nicht in der Menge, geil!

                    in_set = false;
                    break;
                }
            }

            if (_param.anti)
            {
                if (in_set)
                {
                    //hitbuffer übernehmen
                    for (int i=0;i < _number_of_valid_values; i++)
                    {
                        add_number(_hit_buffer[i]);
                    }
                }
            }
            else
            {
                if (!in_set)
                {
                    //z = std::complex<double>(0, 0);

                    //hitbuffer übernehmen
                    for (int i=0;i < _number_of_valid_values; i++)
                    {
                        add_number(_hit_buffer[i]);
                    }

                    //eigentliche Pfadberechnung
                    for (size_t j = _number_of_valid_values; j < _param.max_iter; j++)
                    {

                        z = _func(z, c);

                        if (!isComplexOK(z))
                        {
                            break;
                        }

                        //Zahl, wenn darstellbar, in Pixelarray eintragen
                        add_number(z);
                    }
                    //std::cout << std::endl;
                }
            }
        }
    }
}

void BuddhaCalculator::resetState()
{

    _undepictable_count = 0;
    _depictable_count = 0;
    _max_hit_count = 0;
    for (size_t i = 0; i < _pixel_counter_array.size(); i++)
    {
        for (size_t j = 0; j < _pixel_counter_array[0].size(); j++)
        {
            _pixel_counter_array[i][j] = 0;
        }
    }
}

inline bool BuddhaCalculator::isComplexOK(std::complex<double> number)
{

    if (number.real() < std::numeric_limits<double>::max() && number.real() > (-1 * std::numeric_limits<double>::max()))
    {
        if (number.imag() < std::numeric_limits<double>::max() && number.imag() > (-1 * std::numeric_limits<double>::max()))
        {
            return true;
        }
    }
    return false;
}

inline Point_int BuddhaCalculator::complexToPoint(std::complex<double> number)
{
    Point_int retVal;
    retVal.x = std::round((number.real() - _param.x_axis_min) * _width_const);
    retVal.y = std::round(((_param.y_axis_min - number.imag()) * _height_const) + _param.pixel_height);
    //std::cout << number << " ---> " << retVal.x << "  " << retVal.y << '\n';
    return retVal;
}

inline void BuddhaCalculator::add_number(std::complex<double> n)
{
    Point_int pixel = complexToPoint(n);
    if ((pixel.x < _param.pixel_width && pixel.x >= 0) &&
        (pixel.y < _param.pixel_height && pixel.y >= 0))
    {
        int new_value = ++_pixel_counter_array[pixel.x][pixel.y];
        _depictable_count++;

        if (_max_hit_count < new_value)
        {
            _max_hit_count = new_value;
        }
    }
    else
    {
        _undepictable_count++;
    }
}
