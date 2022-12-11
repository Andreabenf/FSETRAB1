#include "gpio.h"
#include "comunicacao.h"



void ativaDesativaDispositivo(int item, int status) {
  //used to set a device, such as a lamp, on or off
  printf("Alterando estado da gpio %d\n", item);
  
  int wiringPIpin = item;
  pinMode(wiringPIpin, OUTPUT);
  digitalWrite(wiringPIpin, status);
}

void presAndarUm(void) {
  char* message = "1";
  enviaCentral(message);
  printf("Presença primeiro andar\n");
}

void fumacaAndarUm(void) {
  char* message = "2";
  enviaCentral(message);
  printf("Fumaça primeiro andar\n");
}

void Janela1(void) {
  char* message = "3";
  enviaCentral(message);
  printf("Janela 101 primeiro andar\n");
}

void Janela2(void) {
  char* message = "4";
  enviaCentral(message);
  printf("Janela 102 primeiro andar\n");
}

void presencaTerreo(void) {
  printf("Presenca Terreo\n");
  char* message = "5";
  enviaCentral(message);
}

void fumacaTerreo(void) {
  char* message = "6";
  enviaCentral(message);
  printf("Fumaca Terreo\n");
}

void janelaT01(void) {
  char* message = "7";
  enviaCentral(message);
  printf("Janela T01 Terreo\n");
}

void janelaT02(void) {
  char* message = "8";
  enviaCentral(message);
  printf("Janela T02 Terreo \n");

}

void portaEntrada(void) {
  char* message = "9";
  enviaCentral(message);
  printf("Sensor porta de entrada\n");

}


void* handleGPIO() {
  /*
    Used to interact with all sensors
  */

  // looping through all sensors and using wiringPiISR to interact with them, also attaching
  // the handler functions which will be called upon any changes 

  int *portasDispositivosEntrada =  getDispositivosEntrada();
  int qtdeDispositivosEntrada = getQtdeDispositivosEntrada();
  int gpioPort;
  int wiringPIpin;

  for(int i =0; i < qtdeDispositivosEntrada ; i++){
      gpioPort = portasDispositivosEntrada[i];
      wiringPIpin = gpioPort;
      pinMode(wiringPIpin, OUTPUT);
      switch (gpioPort)


      {
        case config.SPres:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, presAndarUm);
         break;
        case config.SFum:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, fumacaAndarUm);
         break;
        case config.SJan:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, Janela1);
         break;
        case config.SPor:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, Janela2);
         break;
        case config.SC_IN:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, presencaTerreo);
         break;
        case config.SC_OUT:
         wiringPiISR(wiringPIpin, INT_EDGE_BOTH, fumacaTerreo);
         break;
        
      default:
        break;
      }
     
  }

  for(;;) {
    sleep(1);
  }
}

void desativaDispositivos() {

  int *portasDispositivosSaida =  getDispositivosSaida();
  int qtdeDispositivosSaida = getQtdeDispositivosSaida();
  int wiringPIpin;

  for (size_t i = 0; i < qtdeDispositivosSaida; i++)
  {
    wiringPIpin = portasDispositivosSaida[i];
    pinMode(wiringPIpin, OUTPUT);
    digitalWrite(wiringPIpin, LOW);
  }

}