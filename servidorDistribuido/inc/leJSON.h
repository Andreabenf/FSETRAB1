#ifndef LEJSON_H_
#define LEJSON_H_

typedef struct jsonconf {
    int portaDistribuido;
    char ipCentral[13];
int SPres;
int SFum;
int SJan;
int SPor;
int SC_IN;
int SC_OUT;
    
} JSONConfig;

JSONConfig leJSONConfig(const char* nomeArquivo);
int *getDispositivosEntrada();
int getQtdeDispositivosEntrada();
int getQtdeDispositivosSaida();
int *getDispositivosSaida();
int getPorta();


#endif /* LEJSON_H_ */