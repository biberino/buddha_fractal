#ifndef CONF_REAGER_GUARD
#define CONF_REAGER_GUARD
#include <string>

struct conf_data
{
    int pixel_width = 14400; // x Auflösung in Pixel
    int pixel_height = 9000;
    double x_axis_min = -2.0f;
    double x_axis_max = 2.0f;
    double y_axis_min = -2.0f;
    double y_axis_max = 2.0f; // y Auflösung in Pixel
    double real_min = -4.0f;  // untere Schranke für Zufällige C, realanteil
    double real_max = 4.0f;   // obere Schranke für Zufällige C, realanteil
    double im_min = -4.0f;    // untere Schranke für Zufällige C, imaginär
    double im_max = 4.0f;     // obere Schranke für Zufällige C, imaginär
    int max_iter = 50000;    // maximale Iteration pro Punkt
    int bailout_squared = 4; // quadrierter Abstand zum Ursprung ab dem ein Punkt nicht mehr zur Menge gehört
    //int number_points;                                                     // anzahl Punkte die berechnet werden
    //std::complex<double> (*func)(std::complex<double>, std::complex<double>); // Funktion zur Berechnung eines iterationsschritts
    int func_indentifier = 0; // wählt Fraktalgleichung aus
    bool zwilling = false;
    double koppl = 0.0f;

    int chunck_min_points = 20;
    int chunck_time_seconds = 100;
    int seconds = 100;
    int num_threads = 2;
    bool save_raw_result = false;
    bool anti = false;
};

class ConfReader
{
  private:
    /* data */
  public:
    ConfReader();
    ~ConfReader();

    conf_data readConf(std::string path);
};

#endif // !CONF_REAGER_GUARD