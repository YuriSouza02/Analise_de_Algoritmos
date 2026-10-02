#include "hanoi.h"

//custom
void hanoiRecLog(int n, int origem, int destino, int auxiliar,ofstream &log)
{
    if(n==1)
        MoveDisco(n,origem,destino,log);
    else
    {
        hanoiRecLog(n-1,origem,auxiliar,destino,log);
        MoveDisco(n,origem,destino,log);
        hanoiRecLog(n-1,auxiliar,destino,origem,log);
    }
}
void hanoiRec(int n, int origem, int destino, int auxiliar)
{
    if(n==1)
        return;
    else
    {
        hanoiRec(n-1,origem,auxiliar,destino);
        hanoiRec(n-1,auxiliar,destino,origem);
    }
}

//gpt
void hanoiGPT(int n, int origem, int destino, int auxiliar)
{
    if (n <= 0)
        return;

    // Move n-1 discos da origem para o auxiliar
        if (n <= 1)
        return;
    hanoiGPT(n - 1, origem, auxiliar, destino);
    hanoiGPT(n - 1, auxiliar, destino, origem);
}
void hanoiGPTLog(int n, int origem, int destino, int auxiliar, ofstream &log)
{
    if (n <= 0)
        return;

    // Move n-1 discos da origem para o auxiliar
    hanoiGPTLog(n - 1, origem, auxiliar, destino, log);

    // Move o maior disco para o destino
    log << "Mover disco " << n
        << " da torre " << origem
        << " para a torre " << destino << endl;

    // Move n-1 discos do auxiliar para o destino
    hanoiGPTLog(n - 1, auxiliar, destino, origem, log);
}

// grok
void hanoiGrok(int n, int origem, int destino, int auxiliar)
{
    if (n == 0)
        return;
    hanoiGrok(n - 1, origem, auxiliar, destino);
    hanoiGrok(n - 1, auxiliar, destino, origem);
}
void hanoiGrokLog(int n, int origem, int destino, int auxiliar,ofstream &log)
{
    if (n <= 0) {
        return;
    }

    if (n == 1) {
        log << "Mover disco 1 de " << origem 
            << " para " << destino << std::endl;
        return;
    }

    // Passo 1: mover n-1 discos para o pino auxiliar
    hanoiGrokLog(n - 1, origem, auxiliar, destino, log);

    // Passo 2: mover o disco n para o destino
    log << "Mover disco " << n 
        << " de " << origem << " para " << destino << std::endl;

    // Passo 3: mover n-1 discos do auxiliar para o destino
    hanoiGrokLog(n - 1, auxiliar, destino, origem, log);
}


//gemini
void hanoiGeminiLog(int n, int origem, int destino, int auxiliar, ofstream &log) {
    // Caso base: se não houver discos para mover, interrompe a execução
    if (n <= 0) {
        return;
    }

    // Passo 1: Move n-1 discos da origem para o auxiliar, usando o destino como suporte
    hanoiGeminiLog(n - 1, origem, auxiliar, destino, log);

    // Passo 2: Move o disco atual da origem para o destino e grava no arquivo
    if (log.is_open()) {
        log << "Mover disco " << n << " de " << origem << " para " << destino << "\n";
    }

    // Passo 3: Move os n-1 discos do auxiliar para o destino, usando a origem como suporte
    hanoiGeminiLog(n - 1, auxiliar, destino, origem, log);
}
void hanoiGemini(int n, int origem, int destino, int auxiliar)
{
    if (n == 0)
        return;
    hanoiGemini(n - 1, origem, auxiliar, destino);
    hanoiGemini(n - 1, auxiliar, destino, origem);
}

void MoveDisco(int discN, int origPegN, int destPegN,ofstream &log)
{
    log<<"Move disc number "<<discN<<" from peg number "<<origPegN<<" to peg number "<<destPegN<<" ."<<endl;
}