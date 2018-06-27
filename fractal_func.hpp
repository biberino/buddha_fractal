#ifndef FRAC_FUNC_GUARD
#define FRAC_FUNC_GUARD
#include <complex>
#include <vector>

inline std::complex<float> mandelbrot(std::complex<float> z, std::complex<float> c)
{
    return (z * z) + c;
}

inline std::complex<float> mandelbrot_neg(std::complex<float> z, std::complex<float> c)
{
    return (z * z) - c;
}

inline std::complex<float> auge(std::complex<float> z, std::complex<float> c)
{
    return (z * std::conj(z)) + c;
}

inline std::complex<float> schaedel(std::complex<float> z, std::complex<float> c)
{
    return (z * std::conj(z)) - c;
}

inline std::complex<float> antenne_4_pol(std::complex<float> z, std::complex<float> c)
{
    return ((z + c) / (std::complex<float>(0, 1) + c * pow(z, 3)));
}

inline std::complex<float> batman(std::complex<float> z, std::complex<float> c)
{
    return ((z + c) / (std::complex<float>(0, 1) + c * pow(z, 2)));
}

inline std::complex<float> z_hoch_z_plus(std::complex<float> z, std::complex<float> c)
{
    return (pow(z,z)) + c;
}

inline std::complex<float> z_hoch_z_minus(std::complex<float> z, std::complex<float> c)
{
    return (pow(z,z)) - c;
}


std::vector<std::complex<float> (*)(std::complex<float>, std::complex<float>)> fractals;

void setup_fractals()
{
    fractals.push_back(mandelbrot);
    fractals.push_back(mandelbrot_neg);
    fractals.push_back(auge);
    fractals.push_back(schaedel);
    fractals.push_back(antenne_4_pol);
    fractals.push_back(batman);
    fractals.push_back(z_hoch_z_plus);
    fractals.push_back(z_hoch_z_minus);
}

#endif // !FRAC_FUNC_GUARD