// #include <curses.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "menu.h"
#include "comunicacao.h"


Sensores sensores;
Aparelhos aparalhos;

void mostraMenu()
{

  system("clear");
  printaDispositivos();
}

void menuAtivaDesativa()
{

  system("clear");
  int i = -1;
  do
  {
    printf("Qual sala deseja controlar?\nDigite um numero de 0 a %d\n", getNumDispositivos() - 1);
    scanf("%d", &i);

  } while (i < 0 || i > getNumDispositivos() - 1);

  StatusGeral chosen = getDispositivo(i);

  char comando[7];
  int scan = 1;
  do
  {
    system("clear");
    printf("\n  Qual dos dispositivos deseja ativar/desativar? Digite o código respectivo\n\n");
    printf("   CODIGO   |     DISPOSITIVO     |   STATUS ATUAL\n");
    printf("------------|---------------------|------------------\n");
    printf("                    SALA  %d      \n", i);
    printf("------------|---------------------|------------------\n");
    printf("     L_01   | Lâmpada 01 da Sala  |      %s\n", verificaOnOff(chosen.L_01));
    printf("     L_02   | Lâmpada 02 da Sala  |      %s\n", verificaOnOff(chosen.L_02));
    printf("     AC     | Ar-Condicionado     |      %s\n", verificaOnOff(chosen.AC));
    printf("     PR     | Projetor Multimídia |      %s\n", verificaOnOff(chosen.PR));
    printf("     AL_BZ  | Alarme              |      %s\n\n", verificaOnOff(chosen.AL_BZ));

    scanf("%s", &comando);
    if (strcmp(comando, "L_01") == 0 || strcmp(comando, "L_02") == 0 || strcmp(comando, "AC") == 0 || strcmp(comando, "PR") == 0 || strcmp(comando, "AL_BZ") == 0)
    {
      scan = 0;
    }

    __fpurge(stdin);
    printf("leu: %s\n\n",comando );

  } while (scan);
enviaDistribuido(i,comando);

}


void *menuFunc()
{
  int menuon = 1;
  int i;
  do
  {
    mostraMenu();
    __fpurge(stdin);
    printf("Digite 1 para atualizar o quadro\n");
    printf("Digite 2 para entrar no quadro de comandos\n");
    scanf("%d", &i);
    if (i == 2)
    {
      menuAtivaDesativa();
    }
    i = 0;

    __fpurge(stdin);
  } while (menuon);
}

