# 📊 Benchmark de Desempenho de Algoritmos (LLM Comparison)

Uma *suite* de testes de desempenho desenvolvida em **C++17** e **Python** para mensurar, analisar e comparar a eficiência de execução do código gerado por diferentes Modelos de Linguagem (*Large Language Models*): **Grok**, **Gemini** e **ChatGPT (GPT)**.

O projeto avalia o tempo de execução de algoritmos clássicos sob diferentes complexidades computacionais e gera automaticamente análises estatísticas e gráficos comparativos.

---

## 🛠️ Estrutura do Projeto

```text
.
├── IA's/
│   ├── calculos.h / calculos.cpp  # Funções de regressão linear e taxa de crescimento
│   ├── gemini.h / gemini.cpp      # Algoritmos implementados pelo Gemini
│   ├── gpt.h / gpt.cpp            # Algoritmos implementados pelo ChatGPT
│   └── grok.h / grok.cpp          # Algoritmos implementados pelo Grok
├── main.cpp                       # Orquestrador dos benchmarks e exportação para CSV
├── visualizar_dados.py            # Script Python para geração dos gráficos
└── resultados/                    # Diretório gerado para armazenar o CSV e os gráficos PNG
```

---

## 🧪 Algoritmos Avaliados

1. **Avaliação de Polinômio ($O(n)$)**
   * Medição do tempo de execução do cálculo polinomial para graus entre **100 e 500.000**.
   * **Métrica**: Inclinação da reta de regressão linear em segundos por grau ($s/\text{grau}$).

2. **Sequência de Fibonacci ($O(n)$)**
   * Cálculo iterativo do $n$-ésimo termo da sequência para entradas $N$ variando de **1 a 2.000.000**.
   * **Métrica**: Inclinação da reta de regressão linear em segundos por iteração ($s/\text{iteração}$).

3. **Torre de Hanói ($O(2^n)$)**
   * Resolução recursiva do problema para $N$ discos variando de **1 a 25**.
   * **Métrica**: Taxa de crescimento exponencial.

---

## 💻 Pré-requisitos

* **Compilador C++17** com suporte à biblioteca `<filesystem>` (ex: `g++`, `clang++` ou `MSVC`).
* **Python 3.8+**
* Bibliotecas Python necessárias:
  * `pandas`
  * `matplotlib`
  * `seaborn`

Para instalar as dependências do Python, execute:

```bash
pip install pandas matplotlib seaborn
```

---

## 🚀 Como Executar

### 1. Compilar e Executar o Benchmark (C++)

Compile todos os arquivos do projeto utilizando a flag do C++17 e otimização de código (`-O2`):

```bash
g++ -std=c++17 -O2 main.cpp IA's/grok.cpp IA's/gemini.cpp IA's/gpt.cpp IA's/calculos.cpp -o benchmark
```

Execute o binário gerado:

```bash
./benchmark
```

*O programa medirá os tempos com `std::chrono::high_resolution_clock`, exibirá os resultados no terminal e criará o arquivo `resultados/resultados_benchmark.csv`.*

### 2. Gerar Visualizações Gráficas (Python)

Após gerar o arquivo CSV, execute o script em Python para criar os gráficos comparativos:

```bash
python visualizar_dados.py
```

Os gráficos em formato PNG serão salvos automaticamente na pasta `resultados/`:
* `Polinomio.png`
* `Fibonacci.png`
* `Torre_de_Hanoi.png`

---

## 📁 Arquivos Gerados

* **`resultados/resultados_benchmark.csv`**: Tabela contendo os tempos exatos de execução (em segundos) para cada valor de entrada $N$ em cada IA.
* **`resultados/*.png`**: Gráficos ilustrando o desempenho temporal dos algoritmos à medida que a entrada escala.
