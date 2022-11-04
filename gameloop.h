#include "struct.h"

#ifndef GAMELOOP_H
#define GAMELOOP_H

void printMap(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, simInfo* simInfo);
void loop(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, simInfo* simInfo);
void rotateChar(antStruct* ant1, int choice);
void moveAnt(antStruct* antToMove, antStruct* antToCheck, simInfo* simsInfo);

#endif