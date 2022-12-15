#ifndef LEJSON_H_
#define LEJSON_H_

typedef struct jsonconf {
    int portaDistribuido;
    char ipCentral[230];
    char id[230];
int SPres;
int SFum;
int SJan;
int SPor;
int SC_IN;
int SC_OUT;
int L_01;
int L_02;
int AC;
int PR;
int AL_BZ;
char IP[15];
int PORTA;
    
} JSONConfig;



JSONConfig leJSONConfig(const char* nomeArquivo, const int minhaporta);
int *getDispositivosEntrada();
int getQtdeDispositivosEntrada();
int getQtdeDispositivosSaida();
int *getDispositivosSaida();
int getPorta();
JSONConfig getConfig();


#endif /* LEJSON_H_ */