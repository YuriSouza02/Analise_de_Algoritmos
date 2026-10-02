cmake_minimum_required(VERSION 3.15)
project(AIBenchmark)

# Define o padrão C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Cria o executável apontando para a subpasta "IA's"
add_executable(benchmark_run 
    main.cpp 
    "IA's/calculos.cpp" 
    "IA's/grok.cpp" 
    "IA's/gemini.cpp" 
    "IA's/gpt.cpp"
)