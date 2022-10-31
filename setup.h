#include "struct.h"

#ifndef SETUP_H
#define SETUP_H

int setupGame(int argc, char* argv[]);
int readMapFile(char*** underMap, int* nR, int* nC, antStruct* ant1, antStruct* ant2, int argc, char* argv[]);
void printMap(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, int nR, int nC);
void loop(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, int nR, int nC);

#endif