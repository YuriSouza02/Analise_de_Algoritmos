#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <string>
#include <algorithm> 

using namespace std;
using namespace std::chrono;

/*
 * ==============================================================================
 * METODO 1 - HORNER ITERATIVO (Original)
 * ==============================================================================
 * FUNÇÃO DE COMPLEXIDADE DE TEMPO EQUACIONADA:
 * f(n) = 6n + 6
 * - Inicialização (double p = a[n]): 1 leitura + 1 atribuição = 2 OPs
 * - Setup do laço (int i = n - 1): 1 subtração + 1 atribuição = 2 OPs (1 vez)
 * - Teste de parada (i >= 0): 1 comparação x (n + 1) vezes = n + 1 OPs
 * - Decremento (i--): 1 decremento x n vezes = n OPs
 * - Corpo do laço (p = a[i] + x * p): 1 leitura + 1 mult + 1 soma + 1 atrib = 4 OPs x n vezes = 4n OPs
 * - Instrução de retorno (return p): 1 operação de controle = 1 OP
 *
 * COMPLEXIDADE DE TEMPO (BIG-O): O(n) - Linear
 * COMPLEXIDADE DE ESPAÇO (BIG-O): O(1) - Constante (Usa memória estática local)
 * ==============================================================================
 */
double avaliarIterativoOriginal(int n, const vector<int>& a, int x) {
    double p = a[n]; 
    for (int i = n - 1; i >= 0; i--) {
        p = a[i] + x * p; 
    }
    return p;
}

/*
 * ==============================================================================
 * METODO 2 - HORNER RECURSIVO (Original)
 * ==============================================================================
 * FUNÇÃO DE COMPLEXIDADE DE TEMPO EQUACIONADA:
 * f(n) = 7n + 3
 * - Teste do caso base (if i == n): 1 comparação x (n + 1) chamadas = n + 1 OPs
 * - Caso base executado (return a[n]): 1 leitura + 1 retorno = 2 OPs (1 vez)
 * - Passo recursivo (return a[i] + x * avaliar(... i + 1 ...)): 
 * 1 adição de índice ('i+1') + 1 chamada + 1 leitura ('a[i]') + 1 multiplicação + 
 * 1 adição + 1 retorno = 6 OPs por nível recursivo x n vezes = 6n OPs
 *
 * COMPLEXIDADE DE TEMPO (BIG-O): O(n) - Linear
 * COMPLEXIDADE DE ESPAÇO (BIG-O): O(n) - Linear (Devido aos 'n+1' frames na Call Stack)
 * ==============================================================================
 */
double avaliarRecursivoOriginal(int i, int n, const vector<int>& a, int x) {
    if (i == n) {
        return a[n];
    }
    return a[i] + x * avaliarRecursivoOriginal(i + 1, n, a, x); 
}

/*
 * ==============================================================================
 * METODO 3 - POLINOMIO GEMINI
 * ==============================================================================
 * FUNÇÃO DE COMPLEXIDADE DE TEMPO EQUACIONADA:
 * f(n) = 7n + 13
 * - Inicialização (resultado = 0.0): 1 atribuição = 1 OP
 * - Setup do iterador (auto it = coeffs.rbegin()): 1 leitura de método + 1 atribuição = 2 OPs
 * - Teste do laço (it != coeffs.rend()): (1 leitura de método + 1 comparação) = 2 OPs x (n + 2) vezes = 2n + 4 OPs
 * - Incremento do iterador (++it): 1 incremento x (n + 1) vezes = n + 1 OPs
 * - Corpo do laço (resultado * x + (*it)): 1 mult + 1 leitura + 1 soma + 1 atrib = 4 OPs x (n + 1) vezes = 4n + 4 OPs
 * - Instrução de retorno: 1 operação de controle = 1 OP
 *
 * COMPLEXIDADE DE TEMPO (BIG-O): O(n) - Linear
 * COMPLEXIDADE DE ESPAÇO (BIG-O): O(1) - Constante
 * ==============================================================================
 */
double polinomio_gemini(const std::vector<double> &coeffs, double x) {
    double resultado = 0.0;
    for (auto it = coeffs.rbegin(); it != coeffs.rend(); ++it) {
        resultado = resultado * x + (*it);
    }
    return resultado;
}

/*
 * ==============================================================================
 * METODO 4 - POLINOMIO GPT
 * ==============================================================================
 * FUNÇÃO DE COMPLEXIDADE DE TEMPO EQUACIONADA:
 * f(n) = 6n + 13
 * - Inicialização (resultado = 0.0): 1 atribuição = 1 OP
 * - Setup do índice (int i = size() - 1): 1 leitura + 1 cast + 1 subtração + 1 atribuição = 4 OPs
 * - Teste de parada (i >= 0): 1 comparação x (n + 2) vezes = n + 2 OPs
 * - Decremento (--i): 1 decremento x (n + 1) vezes = n + 1 OPs
 * - Corpo do laço (resultado * x + coeffs[i]): 1 mult + 1 leitura por índice + 1 soma + 1 atrib = 4 OPs x (n + 1) vezes = 4n + 4 OPs
 * - Instrução de retorno: 1 operação de controle = 1 OP
 *
 * COMPLEXIDADE DE TEMPO (BIG-O): O(n) - Linear
 * COMPLEXIDADE DE ESPAÇO (BIG-O): O(1) - Constante
 * ==============================================================================
 */
double polinomio_gpt(const std::vector<double> &coeffs, double x) {
    double resultado = 0.0;
    for (int i = static_cast<int>(coeffs.size()) - 1; i >= 0; --i) {
        resultado = resultado * x + coeffs[i];
    }
    return resultado;
}

/*
 * ==============================================================================
 * METODO 5 - POLINOMIO GROK
 * ==============================================================================
 * FUNÇÃO DE COMPLEXIDADE DE TEMPO EQUACIONADA:
 * f(n) = 6n + 10
 * - Validação (if coeffs.empty()): 1 leitura de método + 1 comparação = 2 OPs
 * - Inicialização (double res = coeffs.back()): 1 leitura de método + 1 atribuição = 2 OPs
 * - Setup do índice (int i = size() - 2): 1 leitura + 1 cast + 1 subtração + 1 atribuição = 4 OPs
 * - Teste de parada (i >= 0): 1 comparação x (n + 1) vezes = n + 1 OPs
 * - Decremento (--i): 1 decremento x n vezes = n OPs
 * - Corpo do laço (res * x + coeffs[i]): 1 mult + 1 leitura + 1 soma + 1 atrib = 4 OPs x n vezes = 4n OPs
 * - Instrução de retorno: 1 operação de controle = 1 OP
 *
 * COMPLEXIDADE DE TEMPO (BIG-O): O(n) - Linear
 * COMPLEXIDADE DE ESPAÇO (BIG-O): O(1) - Constante
 * ==============================================================================
 */
double polinomio_grok(const std::vector<double> &coeffs, double x) {
    if (coeffs.empty())
        return 0.0;
    double res = coeffs.back();
    for (int i = (int)coeffs.size() - 2; i >= 0; --i)
        res = res * x + coeffs[i];
    return res;
}

int main() {
    int x = 1;     
    double x_double = 1;
    const int REPETICOES = 1000; 

    vector<int> instancias = {1000, 2000, 3000, 4000, 5000, 10000, 15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 55000, 60000, 65000, 70000, 75000, 80000, 85000, 90000, 95000, 100000};
    
    ofstream csvIterativo("iterativo_original.csv");
    ofstream csvRecursivo("recursivo_original.csv");
    ofstream csvGemini("polinomio_gemini.csv");
    ofstream csvGpt("polinomio_gpt.csv");
    ofstream csvGrok("polinomio_grok.csv");

    csvIterativo << "metodo,n,mediana_microssegundos\n";
    csvRecursivo << "metodo,n,mediana_microssegundos\n";
    csvGemini << "metodo,n,mediana_microssegundos\n";
    csvGpt << "metodo,n,mediana_microssegundos\n";
    csvGrok << "metodo,n,mediana_microssegundos\n";

    cout << "Iniciando os testes coletando a MEDIANA de " << REPETICOES << " repeticoes..." << endl;

    for (int n : instancias) {
        vector<int> coeficientes_int(n + 1, 1);
        vector<double> coeficientes_double(n + 1, 1.0);

        vector<long long> temposIter; temposIter.reserve(REPETICOES);
        vector<long long> temposRec;  temposRec.reserve(REPETICOES);
        vector<long long> temposGemini; temposGemini.reserve(REPETICOES);
        vector<long long> temposGpt;  temposGpt.reserve(REPETICOES);
        vector<long long> temposGrok; temposGrok.reserve(REPETICOES);

        for (int r = 0; r < REPETICOES; r++) {
            // --- TESTE DO ITERATIVO ORIGINAL ---
            auto inicioIter = high_resolution_clock::now();
            double resIter = avaliarIterativoOriginal(n, coeficientes_int, x);
            auto fimIter = high_resolution_clock::now();
            temposIter.push_back(duration_cast<microseconds>(fimIter - inicioIter).count());

            // --- TESTE DO RECURSIVO ORIGINAL ---
            auto inicioRec = high_resolution_clock::now();
            double resRec = avaliarRecursivoOriginal(0, n, coeficientes_int, x);
            auto fimRec = high_resolution_clock::now();
            temposRec.push_back(duration_cast<microseconds>(fimRec - inicioRec).count());

            // --- TESTE GEMINI ---
            auto inicioGemini = high_resolution_clock::now();
            double resGemini = polinomio_gemini(coeficientes_double, x_double);
            auto fimGemini = high_resolution_clock::now();
            temposGemini.push_back(duration_cast<microseconds>(fimGemini - inicioGemini).count());

            // --- TESTE GPT ---
            auto inicioGpt = high_resolution_clock::now();
            double resGpt = polinomio_gpt(coeficientes_double, x_double);
            auto fimGpt = high_resolution_clock::now();
            temposGpt.push_back(duration_cast<microseconds>(fimGpt - inicioGpt).count());

            // --- TESTE GROK ---
            auto inicioGrok = high_resolution_clock::now();
            double resGrok = polinomio_grok(coeficientes_double, x_double);
            auto fimGrok = high_resolution_clock::now();
            temposGrok.push_back(duration_cast<microseconds>(fimGrok - inicioGrok).count());
            
            (void)resIter; (void)resRec; (void)resGemini; (void)resGpt; (void)resGrok;
        }

        sort(temposIter.begin(), temposIter.end());
        sort(temposRec.begin(), temposRec.end());
        sort(temposGemini.begin(), temposGemini.end());
        sort(temposGpt.begin(), temposGpt.end());
        sort(temposGrok.begin(), temposGrok.end());

        long long medIter = temposIter[REPETICOES / 2];
        long long medRec = temposRec[REPETICOES / 2];
        long long medGemini = temposGemini[REPETICOES / 2];
        long long medGpt = temposGpt[REPETICOES / 2];
        long long medGrok = temposGrok[REPETICOES / 2];

        csvIterativo << "iterativo_original," << n << "," << medIter << "\n";
        csvRecursivo << "recursivo_original," << n << "," << medRec << "\n";
        csvGemini << "gemini," << n << "," << medGemini << "\n";
        csvGpt << "gpt," << n << "," << medGpt << "\n";
        csvGrok << "grok," << n << "," << medGrok << "\n";
    }

    csvIterativo.close();
    csvRecursivo.close();
    csvGemini.close();
    csvGpt.close();
    csvGrok.close();

    cout << "Todos os arquivos CSV baseados na MEDIANA foram gerados com sucesso!" << endl;
    return 0;
}