#include <iostream>
#include <fstream>
#include <chrono>
#include "hanoi.h"

using namespace std;

template <typename Func>
long double medir_tempo_medio_log(Func func, int n, int origens, int destino, int auxiliar,ofstream &log);

template <typename Func>
long double medir_tempo_medio(Func func, int n, int origens, int destino, int auxiliar);

int main(int argc, char* argv[])
/*
    Argumentos:
        [1]: first instance size
        [2]: number of instances
        [3]: size dif between neighbouring instances
        [4]: 0 will not execute logging. 1 will

*/
{
    bool to_log=(1==stoi(argv[4]));
    int min,number_of_instances,step;
    min=stoi(argv[1]);
    number_of_instances=stoi(argv[2]); 
    step=stoi(argv[3]);
    ofstream csv("HanoiData.csv");//creates and open .csv with name : HanoiRecursive.csv
    ofstream log("log.txt");
    csv << "instanceSZ,time_custom,time_grok,time_gemini,time_gpt\n";
    for(int i=min;i<number_of_instances*step+min;i+=step)
    {
        long double t_rec;
        long double t_grok;
        long double t_gemini;
        long double t_gpt;
        if(to_log){
            t_rec=medir_tempo_medio_log(hanoiRecLog,i,1,2,3,log);
            t_grok=medir_tempo_medio_log(hanoiGrokLog,i,1,2,3,log);
            t_gemini=medir_tempo_medio_log(hanoiGeminiLog,i,1,2,3,log);
            t_gpt=medir_tempo_medio_log(hanoiGPTLog,i,1,2,3,log);
        }else{
            t_rec=medir_tempo_medio(hanoiRec,i,1,2,3);
            t_grok=medir_tempo_medio(hanoiGrok,i,1,2,3);
            t_gemini=medir_tempo_medio(hanoiGemini,i,1,2,3);
            t_gpt=medir_tempo_medio(hanoiGPT,i,1,2,3);
        }
            //writes the following line in the .csv : HanoiRecursive,i,duration
        
        csv << i << ","
        << t_rec << ","
        << t_grok << ","
        << t_gemini << ","
        << t_gpt;
        if(i+step<number_of_instances*step+min)
            csv<< "\n";
    }
    //closes .csv
    return 0;
}

template <typename Func>
long double medir_tempo_medio_log(Func func, int n, int origens, int destino, int auxiliar,ofstream &log) {
    long double tempo_total = 0.0;

    for (int i = 0; i < 3; ++i) {
        auto inicio = std::chrono::high_resolution_clock::now();
        
        // Roda a função com os parametros
        func(n, origens, destino, auxiliar,log);
        
        auto fim = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<long double, std::nano> duracao = fim - inicio;
        tempo_total += duracao.count();
    }

    return tempo_total / 3.0; // Retorna a média em ns
}
template <typename Func>
long double medir_tempo_medio(Func func, int n, int origens, int destino, int auxiliar) {
    long double tempo_total = 0.0;

    for (int i = 0; i < 3; ++i) {
        auto inicio = std::chrono::high_resolution_clock::now();
        
        // Roda a função com os parametros
        func(n, origens, destino, auxiliar);
        
        auto fim = std::chrono::high_resolution_clock::now();
        
        std::chrono::duration<long double, std::nano> duracao = fim - inicio;
        tempo_total += duracao.count();
    }

    return tempo_total / 3.0; // Retorna a média em ns
}