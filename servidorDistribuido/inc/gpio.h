#ifndef GPIO_H_
#define GPIO_H_

#include <wiringPi.h>
#include <stdio.h>    
#include <softPwm.h>
#include <unistd.h>
#include "leJSON.h"


typedef struct statusgeral {
char id[25];
int L_01;
int L_02;
int AC;
int PR;
int AL_BZ;
int SPres;
int SFum;
int SJan;
int SPor;
int SC_IN;
int SC_OUT;
int DHT22;
char IP[15];
int PORTA;
}StatusGeral;


void ativaDesativaDispositivo(const char* str);
void desativaDispositivos();
void* handleGPIO(); //handle sensor state changes

#endif /* GPIO_H_ */