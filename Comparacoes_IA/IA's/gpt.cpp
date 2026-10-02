#include "gpt.h"

double polinomio_gpt(const std::vector<double> &coeffs, double x)
{
    double resultado = 0.0;
    for (int i = static_cast<int>(coeffs.size()) - 1; i >= 0; --i)
    {
        resultado = resultado * x + coeffs[i];
    }
    return resultado;
}

long long fibonacci_gpt(int n)
{
    if (n <= 1)
        return n;
    long long anterior = 0, atual = 1;
    for (int i = 2; i <= n; ++i)
    {
        long long proximo = anterior + atual;
        anterior = atual;
        atual = proximo;
    }
    return atual;
}

void hanoi_gpt(int n, char origem, char destino, char auxiliar)
{
    if (n <= 1)
        return;
    hanoi_gpt(n - 1, origem, auxiliar, destino);
    hanoi_gpt(n - 1, auxiliar, destino, origem);
}