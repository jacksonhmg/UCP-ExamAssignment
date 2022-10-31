#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "setup.h"
#include "color.h"
#include "newSleep.h"

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
                printf("%c",topMap[i][j]);
                if(colChck) /* reset for next iteration*/
                {
                    setBackground("reset");
                }
        }
        printf("\n"); /*new line after each row to show 2d array effect*/
    }
}



void loop(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, simInfo* simsInfo)
{
    int counter = 0;
    printMap(topMap, underMap, ant1, ant2, simsInfo);
    while(counter < simsInfo->steps)
    {
        topMap[ant1->r][ant1->c] = ' ';
        topMap[ant2->r][ant2->c] = ' ';
        if(underMap[ant1->r][ant1->c] == 'G' || underMap[ant1->r][ant1->c] == 'R' || underMap[ant1->r][ant1->c] == 'B')
        {
            underMap[ant1->r][ant1->c] = ' ';
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
        else if(underMap[ant1->r][ant1->c] == ' ')
        {
            underMap[ant1->r][ant1->c] = 'R';
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
        topMap[ant1->r][ant1->c] = ant1->dir;
        topMap[ant2->r][ant2->c] = ant2->dir;
        /*newSleep(1);
        printMap(topMap, underMap, ant1, ant2, nR, nC);*/
        topMap[ant1->r][ant1->c] = ' ';
        topMap[ant2->r][ant2->c] = ' ';
        if(ant1->dir == '^')
        {
            if(ant1->r > 2)
            {
                ant1->r --;
            }
        }
        else if(ant1->dir == 'v')
        {
            if(ant1->r < simsInfo->nR - 2)
            {
                ant1->r ++;
            }
        }
        else if(ant1->dir == '>')
        {
            if(ant1->c < simsInfo->nC - 2)
            {
                ant1->c ++;
            }
        }
        else if(ant1->dir == '<')
        {
            if(ant1->c > 2)
            {
                ant1->c --;
            }
        }
        topMap[ant1->r][ant1->c] = ant1->dir;
        topMap[ant2->r][ant2->c] = ant2->dir;
        newSleep(simsInfo->sleep);
        printMap(topMap, underMap, ant1, ant2, simsInfo);
        counter++;
    }
}


int setupGame(int argc, char* argv[]) 
{ /*used for initialising command line input, organising map setup, initialising game loop, everything set up wise*/
    char** topMap;
    char** underMap;
    antStruct* ant1 = (antStruct*)malloc(sizeof(antStruct));
    antStruct* ant2 = (antStruct*)malloc(sizeof(antStruct));
    simInfo* simsInfo = (simInfo*)malloc(sizeof(simInfo));

    int check,i,j;

    check = readMapFile(&underMap,simsInfo,ant1,ant2,argc,argv);

    simsInfo->steps = atoi(argv[2]);
    simsInfo->sleep = atof(argv[3]);


    topMap = (char**)calloc((simsInfo->nR),sizeof(char*));
    for(i=0;i<(simsInfo->nR);i++)
    {
        topMap[i] = (char*)calloc((simsInfo->nC), sizeof(char));
    }
    for(i=0;i<(simsInfo->nR);i++)
    {
        topMap[i][(simsInfo->nC)-1] = '*';
    }
    for(i=0;i<(simsInfo->nR);i++)
    {
        topMap[i][0] = '*';
    }
    for(i=0;i<(simsInfo->nC);i++)
    {
        topMap[0][i] = '*';
    }
    for(i=0;i<(simsInfo->nC);i++)
    {
        topMap[(simsInfo->nR)-1][i] = '*';
    }
    
    for(i=0;i<(simsInfo->nR);i++)
    {
        for(j=0;j<(simsInfo->nC);j++)
        {
            if(topMap[i][j] == 0)
            {
                topMap[i][j] =  ' '; /*create empty space look*/
            }
        }
    }

    topMap[ant1->r][ant1->c] = ant1->dir;
    topMap[ant2->r][ant2->c] = ant2->dir;

    if(check)
    {
        loop(topMap, underMap, ant1, ant2, simsInfo);
    }


    for(i = 0; i < simsInfo->nR; i++)
    {
        free(underMap[i]);
    }
    free(underMap);
    for(i = 0; i < simsInfo->nR; i++)
    {
        free(topMap[i]);
    }
    free(topMap);
    free(ant1);
    free(ant2);
    free(simsInfo);
    return 0;
}

int readMapFile(char*** underMap, simInfo* simsInfo, antStruct* ant1, antStruct* ant2, int argc, char* argv[])
{
    int nRead, check, lilchecker, counter, i, j, ch, colcounter, rowcounter;

    FILE* f1 = fopen(argv[1], "r");
    check = 1;
    counter = 1;
    if(argc != 4)
    {
        printf("Please run in the format of: './ant mapfile.txt step_number sleep_timer \n");
        check = 0;
    }
    if(f1 == NULL)
    {
        perror("Error opening f1");
    }
    nRead = fscanf(f1, "%d %d", &(simsInfo->nR), &(simsInfo->nC));
    simsInfo->nR +=2; /* increase so that if a user enters map size (5,5) they mean the size inside the borders. so technically map needs to be (7,7) */
    simsInfo->nC +=2;

    if(simsInfo->nR < 7 || simsInfo->nC < 7) /*7 because the inside can't be smaller than 5 and 7 is the number of whole array including border*/
    {
        printf("Map size too small!\n");
        check = 0;
    }

    *underMap = (char**)calloc((simsInfo->nR),sizeof(char*));
    for(i=0;i<(simsInfo->nR);i++)
    {
        (*underMap)[i] = (char*)calloc((simsInfo->nC), sizeof(char));
    }
    for(i=0;i<(simsInfo->nR);i++)
    {
        (*underMap)[i][(simsInfo->nC)-1] = '*';
    }
    for(i=0;i<(simsInfo->nR);i++)
    {
        (*underMap)[i][0] = '*';
    }
    for(i=0;i<(simsInfo->nC);i++)
    {
        (*underMap)[0][i] = '*';
    }
    for(i=0;i<(simsInfo->nC);i++)
    {
        (*underMap)[(simsInfo->nR)-1][i] = '*';
    }
    
    for(i=0;i<(simsInfo->nR);i++)
    {
        for(j=0;j<(simsInfo->nC);j++)
        {
            if((*underMap)[i][j] == 0)
            {
                (*underMap)[i][j] =  ' '; /*create empty space look*/
            }
        }
    }

    rowcounter = 1;
    colcounter = 1;

    do
    {
        lilchecker = 1;
        if(counter == 1)
        {
            nRead = fscanf(f1, "%d %d %c ", &(ant1->r), &(ant1->c), &(ant1->dir));
            ant1->r ++; /* increase numbers like described before with map size increases. 
            now user can enter (0,0) and have it mean the top left corner INSIDE the borders */
            ant1->c ++;
            counter++;
        }
        else if(counter == 2)
        {
            nRead = fscanf(f1, "%d %d %c ", &(ant2->r), &(ant2->c), &(ant2->dir));
            ant2->r ++;
            ant2->c ++;
            counter++;
        }
        else
        {
            /*if(fgets(str, *(nC) * 2, f1) != NULL)
            {
                printf("%s \n", str);
            }
            else
            {
                lilchecker = 0;
            }*/

            ch = fgetc(f1);

            if(ch != EOF)
            {
                if((char)ch == ' ')
                {
                    colcounter ++;
                }
                if((char)ch == '\n')
                {
                    rowcounter ++;
                    colcounter = 1;
                }
                if((char)ch == '1')
                {
                    (*underMap)[rowcounter][colcounter] = 'G';
                }
            }
            else
            {
                lilchecker = 0;
                printf("\n");
            }

        }
        
    } while (nRead != EOF && lilchecker == 1);
    


    if(simsInfo->nR < 2 || simsInfo->nC < 2 || ant1->r < 1 || ant1->c < 1 || ant2->r < 1 || ant2->c < 1) /*numbers are higher than 0 because of the addition done above*/
    {
        printf("Cannot enter negative numbers!\n");
        check = 0;
    }

    if(ant1->r > simsInfo->nR - 2 || ant1->c > simsInfo->nC - 2)
    {
        printf("Ant1 position placed outside of map area!\n");
        check = 0;
    }
    if(ant2->r > simsInfo->nR - 2 || ant2->c > simsInfo->nC - 2)
    {
        printf("Ant2 position placed outside of map area!\n");
        check = 0;
    }

    fclose(f1);
    return check;
}