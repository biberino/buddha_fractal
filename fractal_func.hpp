#ifndef FRAC_FUNC_GUARD
#define FRAC_FUNC_GUARD
#include <complex>
#include <vector>

inline std::complex<double> mandelbrot(std::complex<double> z, std::complex<double> c)
{
    return (z * z) + c;
}

inline std::complex<double> mandelbrot_neg(std::complex<double> z, std::complex<double> c)
{
    return (z * z) - c;
}

inline std::complex<double> auge(std::complex<double> z, std::complex<double> c)
{
    return (z * std::conj(z)) + c;
}

inline std::complex<double> schaedel(std::complex<double> z, std::complex<double> c)
{
    return (z * std::conj(z)) - c;
}

inline std::complex<double> antenne_4_pol(std::complex<double> z, std::complex<double> c)
{
    return ((z + c) / (std::complex<double>(0, 1) + c * pow(z, 3)));
}

inline std::complex<double> batman(std::complex<double> z, std::complex<double> c)
{
    return ((z + c) / (std::complex<double>(0, 1) + c * pow(z, 2)));
}

inline std::complex<double> z_hoch_z_plus(std::complex<double> z, std::complex<double> c)
{
    return (pow(z, z)) + c;
}

inline std::complex<double> z_hoch_z_minus(std::complex<double> z, std::complex<double> c)
{
    return (pow(z, z)) - c;
}

inline std::complex<double> biber_schaedel(std::complex<double> z, std::complex<double> c)
{
    std::complex<double> a = z * std::conj(z);
    std::complex<double> b = c;
    return (std::abs(a) * std::abs(b) * ((std::sqrt(std::pow(a + b, 2) + std::complex<double>(1, 0)) / (std::abs(a + b))))) + std::complex<double>(-1, 0);
}

std::vector<std::complex<double> (*)(std::complex<double>, std::complex<double>)> fractals;

void setup_fractals()
{
    fractals.resize(20, nullptr);
    fractals[0] = mandelbrot;
    fractals[1] = mandelbrot_neg;
    fractals[2] = auge;
    fractals[3] = schaedel;
    fractals[4] = antenne_4_pol;
    fractals[5] = batman;
    fractals[6] = z_hoch_z_plus;
    fractals[7] = z_hoch_z_minus;
    fractals[8] = biber_schaedel;
}

#endif // !FRAC_FUNC_GUARD