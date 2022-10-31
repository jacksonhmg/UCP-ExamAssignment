#define _DEFAULT_SOURCE /* <-- Do NOT forget to define this */
#include <time.h>
#include "newSleep.h"

void newSleep(float sec)
{
	struct timespec ts;
	ts.tv_sec = (int) sec;
	ts.tv_nsec = (sec - ((int) sec)) * 1000000000;
	nanosleep(&ts,NULL);
}