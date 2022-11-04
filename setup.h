#include "struct.h"

#ifndef SETUP_H
#define SETUP_H

int setupGame(int argc, char* argv[]);
int readMapFile(char*** underMap, simInfo* simsInfo, antStruct* ant1, antStruct* ant2, int argc, char* argv[]);
void printMap(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, simInfo* simInfo);
void loop(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, simInfo* simInfo);
void setup2dArray(char*** map, simInfo* simsInfo);

#endif