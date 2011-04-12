
#include "util.h"

void wait(unsigned int milliseconds)
{
    clock_t goal = milliseconds + clock();
    while (goal > clock());
}
