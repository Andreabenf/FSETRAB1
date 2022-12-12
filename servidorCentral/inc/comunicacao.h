#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

typedef struct {
  float temperature;
  float humidity;
} DHT22;

#define SERVER_DISTRIBUTED_IP "127.0.0.1"
#define SERVER_CENTRAL_PORT 10030
#define SERVER_DISTRIBUTED_PORT 11130


void acionaDistribuido();
void *recebeDistribuido();
void leTempUmidade();
int enviaDistribuido(int item, int status, unsigned short int porta);

#endif /* COMUNICACAO_H_ */