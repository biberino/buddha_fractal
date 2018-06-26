#ifndef FRAC_FUNC_GUARD
#define FRAC_FUNC_GUARD
#include <complex>

inline std::complex<float> mandelbrot(std::complex<float> z, std::complex<float> c)
{
    return (z * z) + c;
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
    return ((z + c) / (std::complex<float>(0,1) + c * pow(z, 3)));
}

#endif // !FRAC_FUNC_GUARD