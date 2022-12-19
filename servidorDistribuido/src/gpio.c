#include "gpio.h"
#include "comunicacao.h"
#include "cJSON.h"
#include "DHT22.h"

StatusGeral geral;
const char *printcofing()
{
  const cJSON *id = NULL;
  const cJSON *L_01 = NULL;
  const cJSON *L_02 = NULL;
  const cJSON *AC = NULL;
  const cJSON *PR = NULL;
  const cJSON *AL_BZ = NULL;
  const cJSON *SPres = NULL;
  const cJSON *SFum = NULL;
  const cJSON *SJan = NULL;
  const cJSON *SPor = NULL;
  const cJSON *SC_IN = NULL;
  const cJSON *SC_OUT = NULL;
  const cJSON *DHT22 = NULL;
  const cJSON *IP = NULL;
  const cJSON *PORTA = NULL;
  const cJSON *QTDPESSOAS = NULL;

  cJSON *body = cJSON_CreateObject();

  char *stringmeu = Fetchdht();
    if(strlen(stringmeu)>5){
      strcpy(geral.DHT22,stringmeu);
      // printf("maior %s\n",stringmeu);
    }
// char stringmeu[35];
// strcpy(stringmeu,Fetchdht());
// printf(stringmeu);
  id = cJSON_CreateString(geral.id);
  IP = cJSON_CreateString(geral.IP);
  L_01 = cJSON_CreateNumber(geral.L_01);
  L_02 = cJSON_CreateNumber(geral.L_02);
  AC = cJSON_CreateNumber(geral.AC);
  PR = cJSON_CreateNumber(geral.PR);
  AL_BZ = cJSON_CreateNumber(geral.AL_BZ);
  SPres = cJSON_CreateNumber(geral.SPres);
  SFum = cJSON_CreateNumber(geral.SFum);
  SJan = cJSON_CreateNumber(geral.SJan);
  SPor = cJSON_CreateNumber(geral.SPor);
  SC_IN = cJSON_CreateNumber(geral.SC_IN);
  SC_OUT = cJSON_CreateNumber(geral.SC_OUT);
  DHT22 = cJSON_CreateString(geral.DHT22);
  PORTA = cJSON_CreateNumber(geral.PORTA);
  QTDPESSOAS = cJSON_CreateNumber(geral.qtdPessoas);

  cJSON_AddItemToObject(body, "id", id);
  cJSON_AddItemToObject(body, "L_01", L_01);
  cJSON_AddItemToObject(body, "L_02", L_02);
  cJSON_AddItemToObject(body, "AC", AC);
  cJSON_AddItemToObject(body, "PR", PR);
  cJSON_AddItemToObject(body, "AL_BZ", AL_BZ);
  cJSON_AddItemToObject(body, "SPres", SPres);
  cJSON_AddItemToObject(body, "SFum", SFum);
  cJSON_AddItemToObject(body, "SJan", SJan);
  cJSON_AddItemToObject(body, "SPor", SPor);
  cJSON_AddItemToObject(body, "SC_IN", SC_IN);
  cJSON_AddItemToObject(body, "SC_OUT", SC_OUT);
  cJSON_AddItemToObject(body, "DHT22", DHT22);
  cJSON_AddItemToObject(body, "PORTA", PORTA);
  cJSON_AddItemToObject(body, "IP", IP);
  cJSON_AddItemToObject(body, "QTDPESSOAS", QTDPESSOAS);

  char *finaltring = cJSON_Print(body);
  // sprintf(finaltring, "{\"id\": \"%s\",\n\"L_01: \"%d\",\n\"L_02\": \"%d\",\n\"AC\": \"%d\",\n\"PR\": \"%d\",\n\"AL_BZ\": \"%d\",\n\"SPres\": \"%d\",\n\"SFum\": \"%d\",\n\"SJan\": \"%d\",\n\"SPor\": \"%d\",\n\"SC_IN\": \"%d\",\n\"SC_OUT\": \"%d\",\n\"DHT22\": \"%d\"}",
  //         geral.id, geral.L_01, geral.L_02, geral.AC, geral.PR, geral.AL_BZ, geral.SPres, geral.SFum, geral.SJan, geral.SPor, geral.SC_IN, geral.SC_OUT, geral.DHT22);
      // printf("%s\n",finaltring);

  return finaltring;
}
void ativaDesativaDispositivo(const char *str)
{
  JSONConfig configjson = getConfig();
  printf("aqui chegou assi: %s\n\n", str);
  int estado;
  int pin;
  if (strstr(str, "L_01") != NULL)
  {

    printf("leu L_01\n");
    pin = configjson.L_01;
    estado = digitalRead(pin);
    geral.L_01=!estado;
  }
  if (strstr(str, "L_02") != NULL)
  {
    printf("leu L_02\n");
    pin = configjson.L_02;
    estado = digitalRead(pin);
    geral.L_02=!estado;
  }
  if (strstr(str, "AC") != NULL)
  {
    printf("leu AC\n");
    pin = configjson.AC;
    estado = digitalRead(pin);
    geral.AC=!estado;
  }
  if (strstr(str, "PR") != NULL)
  {
    printf("leu PR\n");
    pin = configjson.PR;
    estado = digitalRead(pin);
    geral.PR=!estado;
  }
  if (strstr(str, "AL_BZ") != NULL)
  {
    printf("leu AL_BZ\n");
    pin = configjson.AL_BZ;
    estado = digitalRead(pin);
    geral.AL_BZ=!estado;
  }
   
  printf("Alterando estado da gpio %d\n", pin);
  pinMode(pin, OUTPUT);
  digitalWrite(pin, !estado);

  char *jsonstring = printcofing();
  
  enviaCentral(jsonstring);
  free(jsonstring);

}

void SensorPresenca(void)
{
  JSONConfig configjson = getConfig();
  int pin = configjson.SPres;
  int estado = digitalRead(pin);
  geral.SPres = estado;
  char *jsonstring = printcofing();
  enviaCentral(jsonstring);
  free(jsonstring);
  if (estado)
  {
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
  geral.SFum = estado;
  char *jsonstring = printcofing();
  enviaCentral(jsonstring);
  free(jsonstring);
  if (estado)
  {
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
  geral.SJan = estado;
  char *jsonstring = printcofing();
  enviaCentral(jsonstring);
  free(jsonstring);
  if (estado)
  {
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
  geral.SPor = estado;
  char *jsonstring = printcofing();
  enviaCentral(jsonstring);
  free(jsonstring);
  if (estado)
  {
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
  geral.SC_IN = estado;
   
  
  if (estado)
  {
    printf("Entrou!\n");
    geral.qtdPessoas+=1;
  }
  char *jsonstring = printcofing();
  enviaCentral(jsonstring);
  free(jsonstring);
}

void SensorSaida(void)
{
  JSONConfig configjson = getConfig();
  int pin = configjson.SC_OUT;
  int estado = digitalRead(pin);
  geral.SC_OUT = estado;
  
  if (estado)
  {
    printf("Saiu!\n");
    if(geral.qtdPessoas>=1)
    geral.qtdPessoas-=1;
  }
 char *jsonstring = printcofing();
  enviaCentral(jsonstring);
  free(jsonstring);
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
  JSONConfig configjson = getConfig();
  strcpy(geral.id, configjson.id);
  strcpy(geral.IP, configjson.IP);
  geral.L_01 = 0;
  geral.L_02 = 0;
  geral.AC = 0;
  geral.PR = 0;
  geral.AL_BZ = 0;
  geral.SPres = 0;
  geral.SFum = 0;
  geral.SJan = 0;
  geral.SPor = 0;
  geral.SC_IN = 0;
  geral.qtdPessoas = 0;
  geral.SC_OUT = 0;
  strcpy(geral.DHT22, Fetchdht());
  geral.PORTA = configjson.PORTA;
  int *portasDispositivosSaida = getDispositivosSaida();
  int qtdeDispositivosSaida = getQtdeDispositivosSaida();
  int wiringPIpin;

  for (size_t i = 0; i < qtdeDispositivosSaida; i++)
  {
    wiringPIpin = portasDispositivosSaida[i];
    pinMode(wiringPIpin, OUTPUT);
    digitalWrite(wiringPIpin, LOW);
  }
  char *jsonstring = printcofing();
  enviaCentral(jsonstring);
}