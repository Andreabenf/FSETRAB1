#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

typedef struct {
  float temperature;
  float humidity;
} DHT22;

#define SERVER_CENTRAL_PORT 11130

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
  char DHT22[35];
  char IP[15];
  int PORTA;
  int qtdPessoas;
} StatusGeral;

void acionaDistribuido();
void *recebeDistribuido();
void leTempUmidade();
int enviaDistribuido(int item, const char* str);
StatusGeral *getDispositivos();
int getNumDispositivos();
StatusGeral getDispositivo(int num);
char * verificaOnOff(int estadoSensorAparelho);

#endif /* COMUNICACAO_H_ */