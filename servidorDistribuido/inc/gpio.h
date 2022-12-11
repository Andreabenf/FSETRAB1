#ifndef GPIO_H_
#define GPIO_H_

#include <wiringPi.h>
#include <stdio.h>    
#include <softPwm.h>
#include <unistd.h>
#include "leJSON.h"


void ativaDesativaDispositivo(int item, int status);
void desativaDispositivos();
void* handleGPIO(); //handle sensor state changes

#endif /* GPIO_H_ */