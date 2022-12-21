#ifndef COMUNICACAO_H_
#define COMUNICACAO_H_

void* recebeCentral(void *porta);
void enviaCentral(char *message);
int changeAlarme(void);
#endif /* COMUNICACAO_H_ */