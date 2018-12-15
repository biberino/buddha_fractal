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
    double x_axis_min;
    double x_axis_max;
    double y_axis_min;
    double y_axis_max;        // y Auflösung in Pixel
    double real_min = -4.0f;  // untere Schranke für Zufällige C, realanteil
    double real_max = 4.0f;   // obere Schranke für Zufällige C, realanteil
    double im_min = -4.0f;    // untere Schranke für Zufällige C, imaginär
    double im_max = 4.0f;     // obere Schranke für Zufällige C, imaginär
    int max_iter;            // maximale Iteration pro Punkt
    int bailout_squared = 4; // quadrierter Abstand zum Ursprung ab dem ein Punkt nicht mehr zur Menge gehört
    //int number_points;                                                     // anzahl Punkte die berechnet werden
    std::complex<double> (*func)(std::complex<double>, std::complex<double>); // Funktion zur Berechnung eines iterationsschritts
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
    std::complex<double> (*_func)(std::complex<double>, std::complex<double>);

    double _width_const;
    double _height_const;

    inline bool isComplexOK(std::complex<double> number);
    inline void add_number(std::complex<double> n);

    inline Point_int complexToPoint(std::complex<double> number);

  public:
    int _undepictable_count = 0;
    int _depictable_count = 0;
    std::vector<std::vector<int>> _pixel_counter_array;
    int _max_hit_count = 0;
    std::vector<std::complex<double>> _hit_buffer;
    int _number_of_valid_values = 0;
    BuddhaCalculator(conf_data param,
                     std::vector<std::complex<double> (*)(std::complex<double>, std::complex<double>)> func_array);
    /** 
     * @brief  Berechnet sec Sekunden lang Punkte und speichert deren Abdrücke
     * @note  
     * @retval None
     */
    void calcPoints(int sec);

    void resetState();
    ~BuddhaCalculator();
};

#endif // !BUDDHA_CALC_GUARD
