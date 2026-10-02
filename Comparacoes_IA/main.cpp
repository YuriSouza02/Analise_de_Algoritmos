#include <iostream>
#include <vector>
#include <chrono>
#include <iomanip>
#include <fstream>
#include <filesystem> // Biblioteca do C++17 para manipulação de pastas

// Importando os serviços essenciais
#include "IA's/grok.h"
#include "IA's/gemini.h"
#include "IA's/gpt.h"
#include "IA's/calculos.h"

using namespace std;
using namespace std::chrono;

int main()
{
    cout << "Iniciando orquestracao de benchmarks. Aguarde..." << endl;
    cout << fixed << setprecision(10);

    // =========================================
    // SERVIÇO: POLINÔMIO
    // =========================================
    vector<double> poli_x;
    for (int i = 100; i <= 500000; i += 25000)
        poli_x.push_back(i);

    vector<double> p_grok, p_gemini, p_gpt;
    double x_val = 1.05;

    for (auto n : poli_x)
    {
        vector<double> coeffs(n, 1.0);

        auto start = high_resolution_clock::now();
        polinomio_grok(coeffs, x_val);
        p_grok.push_back(duration<double>(high_resolution_clock::now() - start).count());

        start = high_resolution_clock::now();
        polinomio_gemini(coeffs, x_val);
        p_gemini.push_back(duration<double>(high_resolution_clock::now() - start).count());

        start = high_resolution_clock::now();
        polinomio_gpt(coeffs, x_val);
        p_gpt.push_back(duration<double>(high_resolution_clock::now() - start).count());
    }

    cout << "\n--- Inclinacao da Reta: POLINOMIO O(n) ---" << endl;
    cout << "Grok:   " << calcularInclinacao(poli_x, p_grok) << " s/grau" << endl;
    cout << "Gemini: " << calcularInclinacao(poli_x, p_gemini) << " s/grau" << endl;
    cout << "GPT:    " << calcularInclinacao(poli_x, p_gpt) << " s/grau" << endl;

    // =========================================
    // SERVIÇO: FIBONACCI
    // =========================================
    vector<double> fib_x;
    for (int i = 1; i <= 2000000; i += 100000)
        fib_x.push_back(i);

    vector<double> f_grok, f_gemini, f_gpt;

    for (auto n : fib_x)
    {
        auto start = high_resolution_clock::now();
        fibonacci_grok(n);
        f_grok.push_back(duration<double>(high_resolution_clock::now() - start).count());

        start = high_resolution_clock::now();
        fibonacci_gemini(n);
        f_gemini.push_back(duration<double>(high_resolution_clock::now() - start).count());

        start = high_resolution_clock::now();
        fibonacci_gpt(n);
        f_gpt.push_back(duration<double>(high_resolution_clock::now() - start).count());
    }

    cout << "\n--- Inclinacao da Reta: FIBONACCI O(n) ---" << endl;
    cout << "Grok:   " << calcularInclinacao(fib_x, f_grok) << " s/iteracao" << endl;
    cout << "Gemini: " << calcularInclinacao(fib_x, f_gemini) << " s/iteracao" << endl;
    cout << "GPT:    " << calcularInclinacao(fib_x, f_gpt) << " s/iteracao" << endl;

    // =========================================
    // SERVIÇO: TORRE DE HANÓI
    // =========================================
    vector<double> hanoi_x;
    for (int i = 1; i <= 25; i += 1)
        hanoi_x.push_back(i);

    vector<double> h_grok, h_gemini, h_gpt;

    for (auto n : hanoi_x)
    {
        auto start = high_resolution_clock::now();
        hanoi_grok(n, 'A', 'C', 'B');
        h_grok.push_back(duration<double>(high_resolution_clock::now() - start).count());

        start = high_resolution_clock::now();
        hanoi_gemini(n, 'A', 'C', 'B');
        h_gemini.push_back(duration<double>(high_resolution_clock::now() - start).count());

        start = high_resolution_clock::now();
        hanoi_gpt(n, 'A', 'C', 'B');
        h_gpt.push_back(duration<double>(high_resolution_clock::now() - start).count());
    }

    cout << "\n--- Inclinacao Logaritmica: HANOI O(2^n) ---" << endl;
    cout << "Grok:   " << calcularInclinacaoExponencial(hanoi_x, h_grok) << " (crescimento)" << endl;
    cout << "Gemini: " << calcularInclinacaoExponencial(hanoi_x, h_gemini) << " (crescimento)" << endl;
    cout << "GPT:    " << calcularInclinacaoExponencial(hanoi_x, h_gpt) << " (crescimento)" << endl;

    // =========================================
    // EXPORTAÇÃO DE DADOS PARA CSV
    // =========================================
    cout << "\nExportando dados para CSV..." << endl;

    std::filesystem::create_directories("resultados");

    ofstream arquivo_csv("resultados/resultados_benchmark.csv");

    if (arquivo_csv.is_open())
    {
        arquivo_csv << "Benchmark,Input_N,Tempo_Grok(s),Tempo_Gemini(s),Tempo_GPT(s)\n";

        for (size_t i = 0; i < poli_x.size(); ++i)
            arquivo_csv << "Polinomio," << poli_x[i] << "," << p_grok[i] << "," << p_gemini[i] << "," << p_gpt[i] << "\n";

        for (size_t i = 0; i < fib_x.size(); ++i)
            arquivo_csv << "Fibonacci," << fib_x[i] << "," << f_grok[i] << "," << f_gemini[i] << "," << f_gpt[i] << "\n";

        for (size_t i = 0; i < hanoi_x.size(); ++i)
            arquivo_csv << "Torre_de_Hanoi," << hanoi_x[i] << "," << h_grok[i] << "," << h_gemini[i] << "," << h_gpt[i] << "\n";

        arquivo_csv.close();
        cout << "Arquivo 'resultados/resultados_benchmark.csv' gerado com sucesso!" << endl;
    }
    else
    {
        cerr << "Erro ao tentar criar o arquivo CSV dentro da pasta 'resultados'!" << endl;
    }

    cout << "Sucesso! Pipeline concluida. Use o Python para gerar os graficos." << endl;

    return 0;
}