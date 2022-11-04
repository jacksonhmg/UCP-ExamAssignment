#include "setup.h"
#include "random.h"

int main(int argc, char* argv[])
{
    initRandom(); /* used for initialsing ability to use "myRandom" function in random.c file */
    setupGame(argc, argv);
    
    return 0;
}