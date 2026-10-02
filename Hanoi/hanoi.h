#ifndef HANOI_H
#define HANOI_H

#include <fstream>
#include <iostream>
using namespace std;

//custom
void hanoiRecLog(int n, int origem, int destino, int auxiliar,ofstream &log);
void hanoiRec(int n, int origem, int destino, int auxiliar);
void MoveDisco(int discN, int origPegN, int destPegN,ofstream &log);
//gpt
void hanoiGPT(int n, int origem, int destino, int auxiliar);
void hanoiGPTLog(int n, int origem, int destino, int auxiliar, ofstream &log);
// grok
void hanoiGrok(int n, int origem, int destino, int auxiliar);
void hanoiGrokLog(int n, int origem, int destino, int auxiliar,ofstream &log);

//gemini
void hanoiGeminiLog(int n, int origem, int destino, int auxiliar, ofstream &log);
void hanoiGemini(int n, int origem, int destino, int auxiliar);


#endif