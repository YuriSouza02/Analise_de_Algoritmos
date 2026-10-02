#include "grok.h"

double polinomio_grok(const std::vector<double> &coeffs, double x)
{
    if (coeffs.empty())
        return 0.0;
    double res = coeffs.back();
    for (int i = (int)coeffs.size() - 2; i >= 0; --i)
        res = res * x + coeffs[i];
    return res;
}

long long fibonacci_grok(int n)
{
    if (n <= 0)
        return 0;
    if (n == 1)
        return 1;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i)
    {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void hanoi_grok(int n, char origem, char destino, char auxiliar)
{
    if (n == 0)
        return;
    hanoi_grok(n - 1, origem, auxiliar, destino);
    hanoi_grok(n - 1, auxiliar, destino, origem);
}