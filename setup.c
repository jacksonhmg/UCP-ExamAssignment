#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "setup.h"
#include "color.h"


void printMap(char** topMap, char** underMap, antStruct* ant1, antStruct* ant2, int nR, int nC)
{
    int i,j,colChck;
    for(i=0;i<(nR);i++)
    {
        for(j=0;j<(nC);j++)
        {
                colChck = 0;
                if(underMap[i][j] == '1')
                {
                    setBackground("green");
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


int setupGame(int argc, char* argv[]) 
{ /*used for initialising command line input, organising map setup, initialising game loop, everything set up wise*/
    char** topMap;
    char** underMap;
    antStruct* ant1 = (antStruct*)malloc(sizeof(antStruct));
    antStruct* ant2 = (antStruct*)malloc(sizeof(antStruct));

    int nR,nC,check,i,j;

    check = readMapFile(&underMap,&nR,&nC,ant1,ant2,argc,argv);




    topMap = (char**)calloc((nR),sizeof(char*));
    for(i=0;i<(nR);i++)
    {
        topMap[i] = (char*)calloc((nC), sizeof(char));
    }
    for(i=0;i<(nR);i++)
    {
        topMap[i][(nC)-1] = '*';
    }
    for(i=0;i<(nR);i++)
    {
        topMap[i][0] = '*';
    }
    for(i=0;i<(nC);i++)
    {
        topMap[0][i] = '*';
    }
    for(i=0;i<(nC);i++)
    {
        topMap[(nR)-1][i] = '*';
    }
    
    for(i=0;i<(nR);i++)
    {
        for(j=0;j<(nC);j++)
        {
            if(topMap[i][j] == 0)
            {
                topMap[i][j] =  ' '; /*create empty space look*/
            }
        }
    }


    for(i=0;i<(nR);i++)
    {
        for(j=0;j<(nC);j++)
        {
                printf("%c",topMap[i][j]);
        }
        printf("\n"); /*new line after each row to show 2d array effect*/
    }



    printMap(topMap, underMap, ant1, ant2, nR, nC);


    for(i = 0; i < nR; i++)
    {
        free(underMap[i]);
    }
    free(underMap);
    for(i = 0; i < nR; i++)
    {
        free(topMap[i]);
    }
    free(topMap);
    free(ant1);
    free(ant2);
    return 0;
}

int readMapFile(char*** underMap, int* nR, int* nC, antStruct* ant1, antStruct* ant2, int argc, char* argv[])
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
    nRead = fscanf(f1, "%d %d", &(*nR), &(*nC));
    *nR +=2; /* increase so that if a user enters map size (5,5) they mean the size inside the borders. so technically map needs to be (7,7) */
    *nC +=2;

    if(*nR < 7 || *nC < 7) /*7 because the inside can't be smaller than 5 and 7 is the number of whole array including border*/
    {
        printf("Map size too small!\n");
        check = 0;
    }

    *underMap = (char**)calloc((*nR),sizeof(char*));
    for(i=0;i<(*nR);i++)
    {
        (*underMap)[i] = (char*)calloc((*nC), sizeof(char));
    }
    for(i=0;i<(*nR);i++)
    {
        (*underMap)[i][(*nC)-1] = '*';
    }
    for(i=0;i<(*nR);i++)
    {
        (*underMap)[i][0] = '*';
    }
    for(i=0;i<(*nC);i++)
    {
        (*underMap)[0][i] = '*';
    }
    for(i=0;i<(*nC);i++)
    {
        (*underMap)[(*nR)-1][i] = '*';
    }
    
    for(i=0;i<(*nR);i++)
    {
        for(j=0;j<(*nC);j++)
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
        char str[*(nC) * 2];
        if(counter == 1)
        {
            nRead = fscanf(f1, "%d %d %c ", &(ant1->r), &(ant1->c), &(ant1->dir));
            counter++;
        }
        else if(counter == 2)
        {
            nRead = fscanf(f1, "%d %d %c ", &(ant2->r), &(ant2->c), &(ant2->dir));
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
                    (*underMap)[rowcounter][colcounter] = '1';
                }
            }
            else
            {
                lilchecker = 0;
                printf("\n");
            }

        }
        
    } while (nRead != EOF && lilchecker == 1);
    



    for(i=0;i<(*nR);i++)
    {
        for(j=0;j<(*nC);j++)
        {
                printf("%c",(*underMap)[i][j]);
        }
        printf("\n"); /*new line after each row to show 2d array effect*/
    }


    if(nR < 2 || nC < 2 || ant1->r < 1 || ant1->c < 1 || ant2->r < 1 || ant2->c < 1) /*numbers are higher than 0 because of the addition done above*/
    {
        printf("Cannot enter negative numbers!\n");
        check = 0;
    }

    if(ant1->r > nR - 2 || ant1->c > nC - 2)
    {
        printf("Ant1 position placed outside of map area!\n");
        check = 0;
    }
    if(ant2->r > nR - 2 || ant2->c > nC - 2)
    {
        printf("Ant2 position placed outside of map area!\n");
        check = 0;
    }



    fclose(f1);
    return check;

    /* int nRead, int1, int2, xR, xC, check;
    // char c1;
    // FILE* f1 = fopen(argv[1], "r");
    // check = 1;
    // if(f1 == NULL)
    // {
    //     perror("Error opening f1");
    // }
    // nRead = fscanf(f1, "%d %d ", &map2->nR, &map2->nC);
    // map2->nR += 2; /* increase so that if a user enters map size (5,5) they mean the size inside the borders. so technically map needs to be (7,7) 
    // map2->nC += 2;
    

    // if(map2->nR < 7 || map2->nC < 7) /*7 because the inside can't be smaller than 5 and 7 is the number of whole array including border
    // {
    //     printf("Map size too small!\n");
    //     check = 0;
    // }


    // do
    // {
    //     nRead = fscanf(f1, "%d %d %c ", &int1, &int2, &c1);
    //     if(nRead != EOF)
    //     {
    //         if(c1 == 'P')
    //         {
    //             map2->pR = int1 + 1; /* increase numbers like described before with map size increases. 
    //             now user can enter (0,0) and have it mean the top left corner INSIDE the borders
    //             map2->pC = int2 + 1;
    //         }
    //         if(c1 == 'G')
    //         {
    //             map2->gR = int1 + 1;
    //             map2->gC = int2 + 1;
    //         }
    //         if(c1 == 'X')
    //         {
    //             xR = int1 + 1;
    //             xC = int2 + 1;
    //             if(xR > map2->nR - 2 || xC > map2->nC - 2)
    //             {
    //                 printf("X position placed outside of map area!\n");
    //                 check = 0;
    //             }
    //             if(xR < 1 || xC < 1)
    //             {
    //                 printf("Cannot enter negative numbers!\n");
    //                 check = 0;
    //             }
    //         }
    //     }
    // } while (nRead != EOF);
    
    // if(map2->nR < 2 || map2->nC < 2 || map2->pR < 1 || map2->pC < 1 || map2->gR < 1 || map2->gC < 1) /*numbers are higher than 0 because of the addition done above
    // {
    //     printf("Cannot enter negative numbers!\n");
    //     check = 0;
    // }

    // if(map2->pR > map2->nR - 2 || map2->pC > map2->nC - 2)
    // {
    //     printf("Player position placed outside of map area!\n");
    //     check = 0;
    // }
    // if(map2->gR > map2->nR - 2 || map2->gC > map2->nC - 2)
    // {
    //     printf("Goal position placed outside of map area!\n");
    //     check = 0;
    // }
    
    // fclose(f1);

    // return check; */
}