#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gameloop.h"
#include "color.h"
#include "newSleep.h"
#include "random.h"

void printMap(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, simInfo* simsInfo)
{
    int i,j,colChck;
    system("clear");
    for(i=0;i<(simsInfo->nR);i++)
    {
        for(j=0;j<(simsInfo->nC);j++)
        {
                colChck = 0;
                if(underMap[i][j] == 'G')
                {
                    setBackground("green");
                    colChck = 1;
                }
                if(underMap[i][j] == 'R')
                {
                    setBackground("red");
                    colChck = 1;
                }
                if(underMap[i][j] == 'B')
                {
                    setBackground("blue");
                    colChck = 1;
                }
                printf("%c",topMap[i][j]);
                if(colChck) /* reset for next iteration*/
                {
                    setBackground("reset");
                }
        }
        printf("\n"); /*new line after each row to show 2d array effect*/
    }
}

void rotateChar(antStruct* ant1, int choice)
{
    if(choice == 0) /* anti clockwise choice */
    {
        if(ant1->dir == '^')
        {
            ant1->dir = '<';
        }
        else if(ant1->dir == 'v')
        {
            ant1->dir = '>';
        }
        else if(ant1->dir == '>')
        {
            ant1->dir = '^';
        }
        else if(ant1->dir == '<')
        {
            ant1->dir = 'v';
        }
    }
    if(choice == 1)
    {
        if(ant1->dir == '^')
        {
            ant1->dir = '>';
        }
        else if(ant1->dir == 'v')
        {
            ant1->dir = '<';
        }
        else if(ant1->dir == '>')
        {
            ant1->dir = 'v';
        }
        else if(ant1->dir == '<')
        {
            ant1->dir = '^';
        }
    }
}

void moveAnt(antStruct* antToMove, antStruct* antToCheck, simInfo* simsInfo)
{
    if(antToMove->dir == '^')
    {
        if(antToMove->r > 1 && !(antToCheck->r == antToMove->r -1 && antToCheck->c == antToMove->c))
        {
            antToMove->r --;
        }
    }
    else if(antToMove->dir == 'v')
    {
        if(antToMove->r < simsInfo->nR - 2  && !(antToCheck->r == antToMove->r + 1 && antToCheck->c == antToMove->c))
        {
            antToMove->r ++;
        }
    }
    else if(antToMove->dir == '>')
    {
        if(antToMove->c < simsInfo->nC - 2  && !(antToCheck->r == antToMove->r && antToCheck->c == antToMove->c + 1))
        {
            antToMove->c ++;
        }
    }
    else if(antToMove->dir == '<')
    {
        if(antToMove->c > 1  && !(antToCheck->r == antToMove->r && antToCheck->c == antToMove->c - 1))
        {
            antToMove->c --;
        }
    }
}

void loop(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, simInfo* simsInfo)
{
    int counter, randomSel;
    counter = 0;
    printMap(topMap, underMap, ant1, ant2, simsInfo);
    while(counter < simsInfo->steps)
    {
        topMap[ant1->r][ant1->c] = ' ';
        topMap[ant2->r][ant2->c] = ' ';
        if(underMap[ant1->r][ant1->c] == 'G' || underMap[ant1->r][ant1->c] == 'R' || underMap[ant1->r][ant1->c] == 'B')
        {
            underMap[ant1->r][ant1->c] = ' ';
            rotateChar(ant1, 0);
        }
        else if(underMap[ant1->r][ant1->c] == ' ')
        {
            underMap[ant1->r][ant1->c] = 'R';
            rotateChar(ant1, 1);
        }

        if(underMap[ant2->r][ant2->c] == 'G' || underMap[ant2->r][ant2->c] == 'R' || underMap[ant2->r][ant2->c] == 'B')
        {
            underMap[ant2->r][ant2->c] = ' ';
        }
        else if(underMap[ant2->r][ant2->c] == ' ')
        {
            underMap[ant2->r][ant2->c] = 'B';
        }

        randomSel = myRandom(0,3);
        if(randomSel == 0)
        {
            ant2->dir = '>';
        }
        else if(randomSel == 1)
        {
            ant2->dir = 'v';
        }
        else if(randomSel == 2)
        {
            ant2->dir = '<';
        }
        else if(randomSel == 3)
        {
            ant2->dir = '^';
        }

        moveAnt(ant1,ant2,simsInfo);
        moveAnt(ant2,ant1,simsInfo);

        topMap[ant1->r][ant1->c] = ant1->dir;
        topMap[ant2->r][ant2->c] = ant2->dir;
        newSleep(simsInfo->sleep);
        printMap(topMap, underMap, ant1, ant2, simsInfo);
        counter++;
    }
}