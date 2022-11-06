#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "setup.h"
#include "gameloop.h"

int setupGame(int argc, char* argv[]) 
{ /*initialises the game, including structs, maps and begins loop. also controls freeing*/
    char** topMap; /* topMap means the map visible that has the characters and colours printed */
    char** underMap; /* underMap means the map that holds where the colours are */
    antStruct* ant1 = (antStruct*)malloc(sizeof(antStruct));
    antStruct* ant2 = (antStruct*)malloc(sizeof(antStruct));
    simInfo* simsInfo = (simInfo*)malloc(sizeof(simInfo)); /* used for holding information about the simulation (map size, simulation steps, sleep length)*/

    int check,i;

    check = readMapFile(&underMap,simsInfo,ant1,ant2,argc,argv);

    if(check) /* if all the inputs from the file were valid */
    {
        setup2dArray(&topMap, simsInfo); /* creates topMap in accordance with read in variables */
        
        topMap[ant1->r][ant1->c] = ant1->dir; /* set up ants on topMap */
        topMap[ant2->r][ant2->c] = ant2->dir;

        loop(topMap, underMap, ant1, ant2, simsInfo); /* begin loop */

        /*once loop finished, begin freeing variables*/
        for(i = 0; i < simsInfo->nR; i++) /* the freeing of the map is put inside the if(check) statement because they're only malloc'd if check is true */
        {
            free(topMap[i]);
        }
        free(topMap);
        for(i = 0; i < simsInfo->nR; i++)
        {
            free(underMap[i]);
        }
        free(underMap);
    }
    /* below is malloc'd no matter what */
    free(ant1); 
    free(ant2);
    free(simsInfo);
    return 0;
}

void setup2dArray(char*** map, simInfo* simsInfo)
{ /* used twice. once for each of the maps (topMap, underMap) */
    int i,j;
    *map = (char**)calloc((simsInfo->nR),sizeof(char*));
    for(i=0;i<(simsInfo->nR);i++)
    {
        (*map)[i] = (char*)calloc((simsInfo->nC), sizeof(char));
    }
    for(i=0;i<(simsInfo->nR);i++)
    { /* create borders */
        (*map)[i][(simsInfo->nC)-1] = '*';
    }
    for(i=0;i<(simsInfo->nR);i++)
    { /* create borders */
        (*map)[i][0] = '*';
    }
    for(i=0;i<(simsInfo->nC);i++)
    { /* create borders */
        (*map)[0][i] = '*';
    }
    for(i=0;i<(simsInfo->nC);i++)
    { /* create borders */
        (*map)[(simsInfo->nR)-1][i] = '*';
    }
    
    for(i=0;i<(simsInfo->nR);i++)
    {
        for(j=0;j<(simsInfo->nC);j++)
        {
            if((*map)[i][j] == 0)
            {
                (*map)[i][j] =  ' '; /*create empty space look*/
            }
        }
    }
}

int readMapFile(char*** underMap, simInfo* simsInfo, antStruct* ant1, antStruct* ant2, int argc, char* argv[])
{
    int nRead, check, lilchecker, counter, ch, colcounter, rowcounter;

    FILE* f1 = fopen(argv[1], "r");
    check = 1;
    counter = 1;
    if(argc != 4)
    { /* if command line arguments did not meet required format */
        printf("Please run in the format of: './ant mapfile.txt step_number sleep_timer' \n");
        check = 0;
    }
    if(f1 == NULL)
    { /* if file cannot be opened */
        perror("Error opening f1");
        check = 0;
        free(f1); /* have to free it, if you try fclose(f1) when its null, you get an error */
    }
    else if(f1 != NULL)
    {
        nRead = fscanf(f1, "%d %d", &(simsInfo->nR), &(simsInfo->nC)); /* read in first two variables as map rows and columns */
        simsInfo->nR +=2; /* increase so that if a user enters map size (5,5) they mean the size inside the borders. so technically map needs to be (7,7) */
        simsInfo->nC +=2;

        if(simsInfo->nR < 7 || simsInfo->nC < 7) /*7 because the inside can't be smaller than 5 and 7 is the number of whole array including border*/
        {
            printf("Map size too small!\n");
            check = 0;
        }

        simsInfo->steps = atoi(argv[2]); /* simulation steps */
        simsInfo->sleep = atof(argv[3]); /* sleep (delay between each step) length*/

        rowcounter = 1; /* these track where the f1 pointer is "at" in the map. so because we begin addressing the area inside the map with the map file, technically we begin by addressing (1,1) of the overall 2d array (top left corner inside border) */
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

                /* now that map size and ant positions have been declared, validate all of them before initialising and setting up the map */
                if(simsInfo->nR < 2 || simsInfo->nC < 2 || ant1->r < 1 || ant1->c < 1 || ant2->r < 1 || ant2->c < 1 || simsInfo->steps < 0 || simsInfo->sleep < 0) /* some numbers are higher than 0 because of the addition done above */
                {
                    printf("Cannot enter negative numbers!\n");
                    check = 0;
                }
                if(ant1->r > simsInfo->nR - 2 || ant1->c > simsInfo->nC - 2) 
                { /* only need to address when its larger than map size. (0,0) is considered within border (see discussion previously) and anything less than that is negative which is addressed directly above */
                    printf("Ant1 position placed outside of map area!\n");
                    check = 0;
                }
                if(ant2->r > simsInfo->nR - 2 || ant2->c > simsInfo->nC - 2)
                { /* only need to address when its larger than map size. (0,0) is considered within border (see discussion previously) and anything less than that is negative which is addressed directly above */
                    printf("Ant2 position placed outside of map area!\n");
                    check = 0;
                }

                if(check)
                {
                    setup2dArray(underMap, simsInfo); /* to ensure map is not created if file inputs are invalid */
                }
            }
            else
            {
                ch = fgetc(f1); /* address each character */

                if(ch != EOF)
                {
                    if((char)ch == ' ') 
                    { /* as we move through each row, if there is a space between two characters then we know we've moved onto the next column (see map files, there are spaces between each column) */
                        colcounter ++;
                    }
                    if((char)ch == '\n')
                    { /* once we reach the \n character, we know we've reached the end of the row and that we're about to drop to the next row AND start from column 1 again*/
                        rowcounter ++;
                        colcounter = 1;
                    }
                    if((char)ch == '1')
                    { /* if we've found a '1' within the file, we know this is meant to be initialised as a green floor */
                        (*underMap)[rowcounter][colcounter] = 'G'; /* i use letters labelling each colour to easily understand */
                    }
                }
                else
                {
                    lilchecker = 0;
                }
            }
            
        } while (nRead != EOF && lilchecker == 1 && check == 1);

        fclose(f1);
    }
    return check;
}