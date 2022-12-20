#ifndef TDHT22_H
#define TDHT22_H

#include <wiringPi.h>
//------------------------------------------------------------------------------------
typedef struct TSenData
{
    float Temp;
    float Hum;
    int Valid;
};
//------------------------------------------------------------------------------------
const char *Fetchdht(int pin);
//------------------------------------------------------------------------------------
#endif // TDHT22_H