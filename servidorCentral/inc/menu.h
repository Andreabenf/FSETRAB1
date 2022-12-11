#ifndef MENU_H_
#define MENU_H_

typedef struct aparelhosStr {
    int lampadaT01;
    int lampadaT02;
    int lampadaCorrTerreo;
    int arCondicionadoTerreo;
    int aspersores;

    int lampada101;
    int lampada102;
    int lampadaCorrAndar;
    int arCondicionadoAndar;
} Aparelhos;

typedef struct sensuaires {
    int presencaTerreo;
    int fumacaTerreo;
    int janelaT1;
    int janelaT2;
    int portaTerreo;

    int presencaAndar;
    int fumacaAndar;
    int janela101;
    int janela102;
} Sensores;




void* menuFunc();
void mostraMenu();
void menuAtivaDesativa();
void atualizaDispositivo(int dispNum, int novoStatus, int serv);
void trataSensores(int comando);



#endif /* MENU_H_ */