#ifndef CONF_REAGER_GUARD
#define CONF_REAGER_GUARD
#include <string>

struct conf_data
{
    int pixel_width = 14400; // x Auflösung in Pixel
    int pixel_height = 9000;
    float x_axis_min = -2.0f;
    float x_axis_max = 2.0f;
    float y_axis_min = -2.0f;
    float y_axis_max = 2.0f; // y Auflösung in Pixel
    float real_min = -4.0f;  // untere Schranke für Zufällige C, realanteil
    float real_max = 4.0f;   // obere Schranke für Zufällige C, realanteil
    float im_min = -4.0f;    // untere Schranke für Zufällige C, imaginär
    float im_max = 4.0f;     // obere Schranke für Zufällige C, imaginär
    int max_iter = 50000;    // maximale Iteration pro Punkt
    int bailout_squared = 4; // quadrierter Abstand zum Ursprung ab dem ein Punkt nicht mehr zur Menge gehört
    //int number_points;                                                     // anzahl Punkte die berechnet werden
    //std::complex<float> (*func)(std::complex<float>, std::complex<float>); // Funktion zur Berechnung eines iterationsschritts
    int func_indentifier = 0; // wählt Fraktalgleichung aus
    bool zwilling = false;
    float koppl = 0.0f;

    int chunck_size = 10000;
    int seconds = 100;
    int num_threads = 2;
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