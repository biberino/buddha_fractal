#include "BuddhaCalculator.hpp"
#include <limits>
#include <iostream>

BuddhaCalculator::BuddhaCalculator(conf_data param,
                                   std::vector<std::complex<float> (*)(std::complex<float>, std::complex<float>)> func_array)
{
    std::srand(static_cast<unsigned int>(time(0)));
    _param = param;
    _pixel_counter_array.resize(param.pixel_width, std::vector<int>(param.pixel_height, 0));
    std::cout << _pixel_counter_array.size() << '\n';
    _height_const = _param.pixel_height / (_param.y_axis_max - _param.y_axis_min);
    _width_const = _param.pixel_width / (_param.x_axis_max - _param.x_axis_min);
    _func = func_array[param.func_indentifier];
}

BuddhaCalculator::~BuddhaCalculator()
{
}

void BuddhaCalculator::calcPoints(int num_points)
{

    for (size_t i = 0; i < num_points; i++)
    {
        //TODO: random funktioniert nicht
        float r1 = _param.real_min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (_param.real_max - _param.real_min)));
        float r2 = _param.im_min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (_param.im_max - _param.im_min)));
        std::complex<float> c(r1, r2);
        std::complex<float> z(0, 0);
        //optimierung
        std::vector<std::complex<float>> hit_buffer;
        bool in_set = true;

        for (size_t j = 0; j < _param.max_iter; j++)
        {

            z = _func(z, c);
            hit_buffer.push_back(z);

            if (((z.real() * z.real()) + (z.imag() * z.imag())) > _param.bailout_squared)
            {
                //punkt liegt nicht in der Menge, geil!

                in_set = false;
                break;
            }
        }

        if (!in_set)
        {
            //z = std::complex<float>(0, 0);

            //hitbuffer übernehmen
            for (auto var : hit_buffer)
            {
                add_number(var);
            }

            //eigentliche Pfadberechnung
            for (size_t j = hit_buffer.size(); j < _param.max_iter; j++)
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

inline bool BuddhaCalculator::isComplexOK(std::complex<float> number)
{

    if (number.real() < std::numeric_limits<float>::max() && number.real() > (-1 * std::numeric_limits<float>::max()))
    {
        if (number.imag() < std::numeric_limits<float>::max() && number.imag() > (-1 * std::numeric_limits<float>::max()))
        {
            return true;
        }
    }
    return false;
}

inline Point_int BuddhaCalculator::complexToPoint(std::complex<float> number)
{
    Point_int retVal;
    retVal.x = std::round((number.real() - _param.x_axis_min) * _width_const);
    retVal.y = std::round(((_param.y_axis_min - number.imag()) * _height_const) + _param.pixel_height);
    //std::cout << number << " ---> " << retVal.x << "  " << retVal.y << '\n';
    return retVal;
}

inline void BuddhaCalculator::add_number(std::complex<float> n)
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
