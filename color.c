#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"color.h"

void setForeground(char * color)
{
    if(strcmp(color, "black") == 0)
    {
        printf("\033[30m");
    }
    else if(strcmp(color, "red") == 0)
    {
        printf("\033[31m");
    }
    else if(strcmp(color, "green") == 0)
    {
        printf("\033[32m");
    }
    else if(strcmp(color, "yellow") == 0)
    {
        printf("\033[33m");
    }
    else if(strcmp(color, "blue") == 0)
    {
        printf("\033[34m");
    }
    else if(strcmp(color, "magenta") == 0)
    {
        printf("\033[35m");
    }
    else if(strcmp(color, "cyan") == 0)
    {
        printf("\033[36m");
    }
    else if(strcmp(color, "white") == 0)
    {
        printf("\033[37m");
    }
    else if(strcmp(color, "reset") == 0)
    {
        printf("\033[39m");
    }
}

void setBackground(char * color)
{
    if(strcmp(color, "black") == 0)
    {
        printf("\033[40m");
    }
    else if(strcmp(color, "red") == 0)
    {
        printf("\033[41m");
    }
    else if(strcmp(color, "green") == 0)
    {
        printf("\033[42m");
    }
    else if(strcmp(color, "yellow") == 0)
    {
        printf("\033[43m");
    }
    else if(strcmp(color, "blue") == 0)
    {
        printf("\033[44m");
    }
    else if(strcmp(color, "magenta") == 0)
    {
        printf("\033[45m");
    }
    else if(strcmp(color, "cyan") == 0)
    {
        printf("\033[46m");
    }
    else if(strcmp(color, "white") == 0)
    {
        printf("\033[47m");
    }
    else if(strcmp(color, "reset") == 0)
    {
        printf("\033[49m");
    }
}