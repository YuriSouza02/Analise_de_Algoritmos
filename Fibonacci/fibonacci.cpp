#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <unordered_map>

using namespace std;
using namespace std::chrono;

/**
 * Fibonacci recursivo com buffer (memoization) usando vetor.
 * Complexidade: O(n) tempo, O(n) espaço.
 */
long long fib_rec_buffer(int n, vector<long long>& memo) {
    if (n <= 2) return 1;
    
    if (memo[n] != -1) {
        return memo[n];
    }
    
    memo[n] = fib_rec_buffer(n-1, memo) + fib_rec_buffer(n-2, memo);
    return memo[n];
}

long long fibonacci_rec_buffer(int n) {
    vector<long long> memo(n + 1, -1);
    return fib_rec_buffer(n, memo);
}

/**
 * Fibonacci iterativo manual.
 * Estratégia: acumula os dois últimos valores em cada iteração.
 * Complexidade: O(n) tempo, O(1) espaço.
 */
long long fib_iter_manual(int n) {
    if (n == 1) return 1;
    else if (n == 2) return 1;
    else {
        long long f1 = 1;  // F(n-2)
        long long f2 = 1;  // F(n-1)
        long long f;
        for (int i = 3; i <= n; ++i) {
            f = f1 + f2;
            f1 = f2;
            f2 = f;
        }
        return f;
    }
}

/**
 * Fibonacci recursivo manual.
 * Estratégia: divisão clássica F(n) = F(n-1) + F(n-2).
 * Complexidade: O(2^n) tempo, O(n) espaço (pilha de chamadas).
 * Extremamente ineficiente para n > 40.
 */
long long fib_rec_manual(int n) {
    if (n == 1) return 1;
    else if (n == 2) return 1;
    else return fib_rec_manual(n-1) + fib_rec_manual(n-2);
}

// FUNÇÕES GERADAS POR IAs (TODAS ITERATIVAS)
long long fibonacci_gemini(int n) {
    if (n <= 1) return n;
    long long a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

long long fibonacci_gpt(int n) {
    if (n <= 1) return n;
    long long anterior = 0, atual = 1;
    for (int i = 2; i <= n; ++i) {
        long long proximo = anterior + atual;
        anterior = atual;
        atual = proximo;
    }
    return atual;
}

long long fibonacci_grok(int n) {
    if (n <= 0) return 0;
    if (n == 1) return 1;
    long long a = 0, b = 1;
    for (int i = 2; i <= n; ++i) {
        long long c = a + b;
        a = b;
        b = c;
    }
    return b;
}

template<typename Func>
double medir_tempo_medio(Func f, int n, int repeticoes) {
    long long total_ns = 0;
    volatile long long resultado;
    for (int r = 0; r < repeticoes; ++r) {
        auto inicio = high_resolution_clock::now();
        resultado = f(n);
        auto fim = high_resolution_clock::now();
        total_ns += duration_cast<nanoseconds>(fim - inicio).count();
    }
    return static_cast<double>(total_ns) / repeticoes;
}

int main() {
    const int REPETICOES = 10;

    // Verificação de corretude
    cout << "Verificando os 15 primeiros valores:\n";
    cout << "n\tIterativo\tRecursivo\tRecBuffer\tGemini\tGPT\tGrok\tEsperado\n";
    cout << "--------------------------------------------------------------------------------\n";
    vector<int> esperado = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610};
    for (int i = 1; i <= 15; ++i) {
        cout << i << "\t"
             << fib_iter_manual(i) << "\t\t"
             << fib_rec_manual(i) << "\t\t"
             << fibonacci_rec_buffer(i) << "\t\t"
             << fibonacci_gemini(i) << "\t"
             << fibonacci_gpt(i) << "\t"
             << fibonacci_grok(i) << "\t"
             << esperado[i-1] << "\n";
    }

    // Pontos de teste - para TODOS os métodos
    // ns_pequenos: para a tabela comparativa
    vector<int> ns_pequenos = {10, 15, 20, 25, 28, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
    
    // ns_medios: para recursivo com buffer
    vector<int> ns_medios = {1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000,
                             15000, 20000, 25000, 30000, 35000, 40000, 45000, 50000, 
                             60000, 70000, 80000, 90000, 100000};
    
    // ns_grandes: para métodos iterativos
    vector<int> ns_grandes = {50000, 100000, 150000, 200000, 250000, 300000, 350000, 400000,
                              450000, 500000, 550000, 600000, 650000, 700000, 750000, 
                              800000, 850000, 900000, 950000, 1000000};

    // Abrir arquivos CSV separados
    ofstream csv_iter("fib_iter.csv");
    ofstream csv_rec("fib_rec.csv");
    ofstream csv_rec_buffer("fib_rec_buffer.csv");
    ofstream csv_gemini("fib_gemini.csv");
    ofstream csv_gpt("fib_gpt.csv");
    ofstream csv_grok("fib_grok.csv");

    string cabecalho = "metodo,n,duracao_nanossegundos\n";
    csv_iter << cabecalho;
    csv_rec << cabecalho;
    csv_rec_buffer << cabecalho;
    csv_gemini << cabecalho;
    csv_gpt << cabecalho;
    csv_grok << cabecalho;

    // 1. Medir recursivo clássico (n pequenos)
    cout << "\nMedindo Recursivo Clássico O(2^n)...\n";
    for (int n : ns_pequenos) {
        double tempo = medir_tempo_medio(fib_rec_manual, n, REPETICOES);
        csv_rec << "fib_rec_manual," << n << "," << tempo << "\n";
        cout << "n=" << n << " -> Recursivo Clássico: " << tempo << " ns\n";
    }

    // 2. Medir métodos iterativos também para n pequenos (para a tabela)
    cout << "\nMedindo métodos iterativos para n PEQUENOS (para tabela)...\n";
    for (int n : ns_pequenos) {
        double tempo_iter = medir_tempo_medio(fib_iter_manual, n, REPETICOES);
        double tempo_gem = medir_tempo_medio(fibonacci_gemini, n, REPETICOES);
        double tempo_gpt = medir_tempo_medio(fibonacci_gpt, n, REPETICOES);
        double tempo_grok = medir_tempo_medio(fibonacci_grok, n, REPETICOES);
        double tempo_rec_buf = medir_tempo_medio(fibonacci_rec_buffer, n, REPETICOES);
        
        csv_iter << "fib_iter_manual," << n << "," << tempo_iter << "\n";
        csv_gemini << "fib_gemini," << n << "," << tempo_gem << "\n";
        csv_gpt << "fib_gpt," << n << "," << tempo_gpt << "\n";
        csv_grok << "fib_grok," << n << "," << tempo_grok << "\n";
        csv_rec_buffer << "fib_rec_buffer," << n << "," << tempo_rec_buf << "\n";
        
        cout << "n=" << n << " -> Iter: " << tempo_iter << " ns | RecBuffer: " << tempo_rec_buf 
             << " ns | Gem: " << tempo_gem << " ns | GPT: " << tempo_gpt << " ns | Grok: " << tempo_grok << " ns\n";
    }

    // 3. Medir recursivo com buffer para n médios
    cout << "\nMedindo Recursivo com Buffer para n MÉDIOS...\n";
    for (int n : ns_medios) {
        double tempo = medir_tempo_medio(fibonacci_rec_buffer, n, REPETICOES);
        csv_rec_buffer << "fib_rec_buffer," << n << "," << tempo << "\n";
        cout << "n=" << n << " -> Recursivo Buffer: " << tempo << " ns\n";
    }

    // 4. Medir métodos iterativos para n grandes
    cout << "\nMedindo métodos iterativos para n GRANDES...\n";
    for (int n : ns_grandes) {
        double tempo_iter = medir_tempo_medio(fib_iter_manual, n, REPETICOES);
        double tempo_gem = medir_tempo_medio(fibonacci_gemini, n, REPETICOES);
        double tempo_gpt = medir_tempo_medio(fibonacci_gpt, n, REPETICOES);
        double tempo_grok = medir_tempo_medio(fibonacci_grok, n, REPETICOES);
        
        csv_iter << "fib_iter_manual," << n << "," << tempo_iter << "\n";
        csv_gemini << "fib_gemini," << n << "," << tempo_gem << "\n";
        csv_gpt << "fib_gpt," << n << "," << tempo_gpt << "\n";
        csv_grok << "fib_grok," << n << "," << tempo_grok << "\n";
        
        cout << "n=" << n << " -> Iter: " << tempo_iter << " ns | Gem: " << tempo_gem 
             << " ns | GPT: " << tempo_gpt << " ns | Grok: " << tempo_grok << " ns\n";
    }

    csv_iter.close();
    csv_rec.close();
    csv_rec_buffer.close();
    csv_gemini.close();
    csv_gpt.close();
    csv_grok.close();
    
    cout << "\nCSVs gerados com TODOS os métodos para TODOS os n!\n";
    cout << "  - fib_iter.csv (iterativo manual)\n";
    cout << "  - fib_rec.csv (recursivo clássico)\n";
    cout << "  - fib_rec_buffer.csv (recursivo com buffer)\n";
    cout << "  - fib_gemini.csv\n";
    cout << "  - fib_gpt.csv\n";
    cout << "  - fib_grok.csv\n";
    cout << "\nAgora execute: python3 plot_fibonacci.py\n";

    return 0;
}