#include "gpio.h"
#include "comunicacao.h"

void ativaDesativaDispositivo(int item, int status)
{
  // used to set a device, such as a lamp, on or off
  printf("Alterando estado da gpio %d\n", item);
  int wiringPIpin = item;
  pinMode(wiringPIpin, OUTPUT);
  digitalWrite(wiringPIpin, status);
}

void SensorPresenca(void)
{
  JSONConfig configjson = getConfig();
  int pin = configjson.SPres;
  int estado = digitalRead(pin);
  if (estado)
  {
    enviaCentral("Presença acionado\n");
    printf("Presença acionado\n");
  }
  else
  {
    printf("Presença desligado\n");
  }
}

void SensorFumaca(void)
{
  JSONConfig configjson = getConfig();
  int pin = configjson.SFum;
  int estado = digitalRead(pin);
  if (estado)
  {
    enviaCentral("Fumaça detectada\n");
    printf("Fumaça detectada\n");
  }
  else
  {
    printf("Fumaça desligada\n");
  }
}

void Janela1(void)
{
  JSONConfig configjson = getConfig();
  int pin = configjson.SJan;
  int estado = digitalRead(pin);
  if (estado)
  {
    enviaCentral("Janela 1! abriu\n");
    printf("Janela 1! abriu\n");
  }
  else
  {
    printf("Janela 1! feshow\n");
  }
}

void Janela2(void)
{
  JSONConfig configjson = getConfig();
  int pin = configjson.SPor;
  int estado = digitalRead(pin);
  if (estado)
  {
    enviaCentral("Janela 2! abriu\n");
    printf("Janela 2! abriu\n");
  }
  else
  {
    printf("Janela 2! feshow\n");
  }
}

void SensorEntrada(void)
{
  JSONConfig configjson = getConfig();
  int pin = configjson.SC_IN;
  int estado = digitalRead(pin);
  if (estado)
  {
    enviaCentral("Entrou!\n");
    printf("Entrou!\n");
  }
  else
  {
  }
}

void SensorSaida(void)
{
  JSONConfig configjson = getConfig();
  int pin = configjson.SC_OUT;
  int estado = digitalRead(pin);
  if (estado)
  {
    enviaCentral("Saiu");
    printf("Saiu!\n");
  }
  else
  {
  }
}

void *handleGPIO()
{
  /*
    Used to interact with all sensors
  */

  // looping through all sensors and using wiringPiISR to interact with them, also attaching
  // the handler functions which will be called upon any changes

  int *portasDispositivosEntrada = getDispositivosEntrada();
  int qtdeDispositivosEntrada = getQtdeDispositivosEntrada();
  int gpioPort;
  int wiringPIpin;
  JSONConfig configjson = getConfig();

  for (int i = 0; i < qtdeDispositivosEntrada; i++)
  {
    gpioPort = portasDispositivosEntrada[i];
    wiringPIpin = gpioPort;
    pinMode(wiringPIpin, OUTPUT);

    if (configjson.SPres == gpioPort)
    {
      // printf("%d\n", configjson.SPres);
      wiringPiISR(wiringPIpin, INT_EDGE_BOTH, SensorPresenca);
    }

    if (configjson.SFum == gpioPort)
    {
      // printf("%d\n", configjson.SFum);
      wiringPiISR(wiringPIpin, INT_EDGE_BOTH, SensorFumaca);
    }

    if (configjson.SJan == gpioPort)
    {
      // printf("%d\n", configjson.SJan);
      wiringPiISR(wiringPIpin, INT_EDGE_BOTH, Janela1);
    }

    if (configjson.SPor == gpioPort)
    {
      // printf("%d\n", configjson.SPor);
      wiringPiISR(wiringPIpin, INT_EDGE_BOTH, Janela2);
    }

    if (configjson.SC_IN == gpioPort)
    {
      // printf("%d\n", configjson.SC_IN);
      wiringPiISR(wiringPIpin, INT_EDGE_BOTH, SensorEntrada);
    }

    if (configjson.SC_OUT == gpioPort)
    {
      // printf("\n%d", configjson.SC_OUT);
      wiringPiISR(wiringPIpin, INT_EDGE_BOTH, SensorSaida);
    }
  }

  for (;;)
  {
    sleep(1);
  }
}

void desativaDispositivos()
{

  int *portasDispositivosSaida = getDispositivosSaida();
  int qtdeDispositivosSaida = getQtdeDispositivosSaida();
  int wiringPIpin;

  for (size_t i = 0; i < qtdeDispositivosSaida; i++)
  {
    wiringPIpin = portasDispositivosSaida[i];
    pinMode(wiringPIpin, OUTPUT);
    digitalWrite(wiringPIpin, LOW);
  }
}