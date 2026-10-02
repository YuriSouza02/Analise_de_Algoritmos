#include "calculos.h"
#include <cmath>

double calcularInclinacao(const std::vector<double> &x, const std::vector<double> &y)
{
    size_t n = x.size();
    if (n != y.size() || n == 0)
        return 0.0;

    double somaX = 0, somaY = 0, somaXY = 0, somaX2 = 0;

    for (size_t i = 0; i < n; ++i)
    {
        somaX += x[i];
        somaY += y[i];
        somaXY += x[i] * y[i];
        somaX2 += x[i] * x[i];
    }

    double numerador = (n * somaXY) - (somaX * somaY);
    double denominador = (n * somaX2) - (somaX * somaX);

    return (denominador != 0) ? (numerador / denominador) : 0.0;
}

double calcularInclinacaoExponencial(const std::vector<double> &x, const std::vector<double> &y)
{
    std::vector<double> log_y(y.size());
    for (size_t i = 0; i < y.size(); ++i)
    {
        log_y[i] = std::log(y[i] > 0 ? y[i] : 1e-9);
    }
    return calcularInclinacao(x, log_y);
}