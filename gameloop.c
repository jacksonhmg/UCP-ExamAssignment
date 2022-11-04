#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gameloop.h"
#include "color.h"
#include "newSleep.h"
#include "random.h"

void printMap(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, simInfo* simsInfo)
{ /* used in each loop iteration for printing out the topMap */
    int i,j,colChck;
    system("clear"); /* clear terminal before each print */
    for(i=0;i<(simsInfo->nR);i++)
    {
        for(j=0;j<(simsInfo->nC);j++)
        {
                colChck = 0;
                if(underMap[i][j] == 'G')
                { /* if underMap has 'G' anywhere thats because its meant to be green in that position on the topMap */
                    setBackground("green");
                    colChck = 1;
                }
                if(underMap[i][j] == 'R')
                { /* if underMap has 'R' anywhere thats because its meant to be red in that position on the topMap */
                    setBackground("red");
                    colChck = 1;
                }
                if(underMap[i][j] == 'B')
                { /* if underMap has 'B' anywhere thats because its meant to be blue in that position on the topMap */
                    setBackground("blue");
                    colChck = 1;
                }
                printf("%c",topMap[i][j]);
                if(colChck) /* reset for next iteration */
                {
                    setBackground("reset");
                }
        }
        printf("\n"); /*new line after each row to show 2d array effect*/
    }
}

void rotateChar(antStruct* ant1, int choice)
{ /* rotates the ant1 according to the choice */
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
    if(choice == 1) /* clockwise choice */
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
{ /* used for both ants. After determining a new direction, attempt to move in that direction */
    /* antToMove is the ant you are wanting to move. antToCheck is the other ant, to ensure they don't collide */
    if(antToMove->dir == '^')
    {
        if(antToMove->r > 1 && !(antToCheck->r == antToMove->r -1 && antToCheck->c == antToMove->c)) /* if its not at the top of the area inside the border and the other ant isn't where its about to move to */
        {
            antToMove->r --; /* move up */
        }
    }
    else if(antToMove->dir == 'v')
    {
        if(antToMove->r < simsInfo->nR - 2  && !(antToCheck->r == antToMove->r + 1 && antToCheck->c == antToMove->c)) /* if its not at the bottom of the area inside the border and the other ant isn't where its about to move to */
        {
            antToMove->r ++; /* move down */
        }
    }
    else if(antToMove->dir == '>')
    {
        if(antToMove->c < simsInfo->nC - 2  && !(antToCheck->r == antToMove->r && antToCheck->c == antToMove->c + 1)) /* if its not at the most-right of the area inside the border and the other ant isn't where its about to move to */
        {
            antToMove->c ++; /* move right */
        }
    }
    else if(antToMove->dir == '<')
    {
        if(antToMove->c > 1  && !(antToCheck->r == antToMove->r && antToCheck->c == antToMove->c - 1)) /* if its not at the most-left of the area inside the border and the other ant isn't where its about to move to */
        {
            antToMove->c --; /* move left */
        }
    }
}

void loop(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, simInfo* simsInfo)
{
    int counter, randomSel;
    counter = 0;
    printMap(topMap, underMap, ant1, ant2, simsInfo); /* initial print of starting map */
    while(counter < simsInfo->steps) /* continue to loop until you've used the amount of steps determined in command line */
    {
        topMap[ant1->r][ant1->c] = ' '; /* remove previous positions of ant1 and ant2 */
        topMap[ant2->r][ant2->c] = ' ';
        if(underMap[ant1->r][ant1->c] == 'G' || underMap[ant1->r][ant1->c] == 'R' || underMap[ant1->r][ant1->c] == 'B') /* if ant1 is on a coloured space */
        {
            underMap[ant1->r][ant1->c] = ' '; /* clear the colour from that coloured space */
            rotateChar(ant1, 0); /* rotate ant1 anti clockwise due to being on a coloured space */
        }
        else if(underMap[ant1->r][ant1->c] == ' ') /* if ant1 is on a clear space */
        {
            underMap[ant1->r][ant1->c] = 'R'; /* make the previously clear space into a red space */
            rotateChar(ant1, 1); /* rotate ant1 clockwise due to being on a clear space*/
        }

        if(underMap[ant2->r][ant2->c] == 'G' || underMap[ant2->r][ant2->c] == 'R' || underMap[ant2->r][ant2->c] == 'B') /* if ant2 is on a coloured space */
        {
            underMap[ant2->r][ant2->c] = ' '; /* clear the colour from that coloured space */
        }
        else if(underMap[ant2->r][ant2->c] == ' ') /* if ant2 is on a clear space */
        {
            underMap[ant2->r][ant2->c] = 'B'; /* make that previously clear space into a blue space */
        }

        randomSel = myRandom(0,3); /* choose a random number between 0-3 (4 options) */
        /* change direction depening on that random selection */
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

        /* now that the new direction of the ants have been decided, move them according to their new direction */
        moveAnt(ant1,ant2,simsInfo); 
        moveAnt(ant2,ant1,simsInfo);

        /* now print this new position and direction of the ants onto the map */
        topMap[ant1->r][ant1->c] = ant1->dir;
        topMap[ant2->r][ant2->c] = ant2->dir;
        newSleep(simsInfo->sleep); /* sleep delay before printing */
        printMap(topMap, underMap, ant1, ant2, simsInfo);
        counter++; /* incremement counter */
    }
}