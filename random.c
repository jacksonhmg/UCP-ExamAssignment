#include<stdlib.h>
#include<time.h>
#include"random.h"

/*call this function just ONCE at the beginning of your program before using the random number generator */
void initRandom()
{
    srand(time(NULL));
}

/* Will return random integer between *low* and *high* inclusive.
   If the low is larger than the high, it will return -1 instead.
   In theory, it still works with negative *low* and *high* (as long as low is not larger than high), but for this assignment you will most likely not need the negative number.
   Please ensure you call initRandom function once before starting using this function. */
int random(int low, int high)
{
    int number = -1;

    if(low <= high)
    {
        number = (rand() % (high-low+1)) + low;
    }

    return number;
}