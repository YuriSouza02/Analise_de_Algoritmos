#include "gemini.h"

double polinomio_gemini(const std::vector<double> &coeffs, double x)
{
    double resultado = 0.0;
    for (auto it = coeffs.rbegin(); it != coeffs.rend(); ++it)
    {
        resultado = resultado * x + (*it);
    }
    return resultado;
}

long long fibonacci_gemini(int n)
{
    if (n <= 1)
        return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++)
    {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

void hanoi_gemini(int n, char origem, char destino, char auxiliar)
{
    if (n == 0)
        return;
    hanoi_gemini(n - 1, origem, auxiliar, destino);
    hanoi_gemini(n - 1, auxiliar, destino, origem);
}