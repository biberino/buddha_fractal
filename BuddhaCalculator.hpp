#ifndef BUDDHA_CALC_GUARD
#define BUDDHA_CALC_GUARD
#include <complex>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "ConfReader.hpp"

//obsolet
struct BuddhaParam
{
    int pixel_width; // x Auflösung in Pixel
    int pixel_height;
    float x_axis_min;
    float x_axis_max;
    float y_axis_min;
    float y_axis_max;        // y Auflösung in Pixel
    float real_min = -4.0f;  // untere Schranke für Zufällige C, realanteil
    float real_max = 4.0f;   // obere Schranke für Zufällige C, realanteil
    float im_min = -4.0f;    // untere Schranke für Zufällige C, imaginär
    float im_max = 4.0f;     // obere Schranke für Zufällige C, imaginär
    int max_iter;            // maximale Iteration pro Punkt
    int bailout_squared = 4; // quadrierter Abstand zum Ursprung ab dem ein Punkt nicht mehr zur Menge gehört
    //int number_points;                                                     // anzahl Punkte die berechnet werden
    std::complex<float> (*func)(std::complex<float>, std::complex<float>); // Funktion zur Berechnung eines iterationsschritts
};

struct Point_int
{
    int x;
    int y;
};

class BuddhaCalculator
{
  private:
    conf_data _param;
    std::complex<float> (*_func)(std::complex<float>, std::complex<float>);

    float _width_const;
    float _height_const;

    inline bool isComplexOK(std::complex<float> number);
    inline void add_number(std::complex<float> n);

    inline Point_int complexToPoint(std::complex<float> number);

  public:
    int _undepictable_count = 0;
    int _depictable_count = 0;
    std::vector<std::vector<int>> _pixel_counter_array;
    int _max_hit_count = 0;
    BuddhaCalculator(conf_data param,
                     std::vector<std::complex<float> (*)(std::complex<float>, std::complex<float>)> func_array);
    /** 
     * @brief  Berechnet num_points Punkte und speichert deren Abdrücke
     * @note  
     * @retval None
     */
    void calcPoints(int num_points);
    ~BuddhaCalculator();
};

#endif // !BUDDHA_CALC_GUARD
