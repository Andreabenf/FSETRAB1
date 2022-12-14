#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

typedef struct {
  float temperature;
  float humidity;
} DHT22;

#define SERVER_DISTRIBUTED_IP "192.168.1.133"
#define SERVER_CENTRAL_PORT 10030
#define SERVER_DISTRIBUTED_PORT 11130

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
} StatusGeral;

void acionaDistribuido();
void *recebeDistribuido();
void leTempUmidade();
int enviaDistribuido(int item, int status, unsigned short int porta);

#endif /* COMUNICACAO_H_ */