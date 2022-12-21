// #include <curses.h>
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

#include "menu.h"
#include "comunicacao.h"

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
    printf("    L_01    | Lâmpada 01 da Sala  |      %s\n", verificaOnOff(chosen.L_01));
    printf("    L_02    | Lâmpada 02 da Sala  |      %s\n", verificaOnOff(chosen.L_02));
    printf("    AC      | Ar-Condicionado     |      %s\n", verificaOnOff(chosen.AC));
    printf("    PR      | Projetor Multimídia |      %s\n", verificaOnOff(chosen.PR));
    printf("    AL_BZ   | Alarme              |      %s\n", verificaOnOff(chosen.AL_BZ));
    printf("    T_ON    | Liga tudo na sala   |      %s\n", verificaOnOff(chosen.AL_BZ));
    printf("    T_OFF   | Desliga tudo na sala|      %s\n\n");

    scanf("%s", &comando);
    if (strcmp(comando, "L_01") == 0 || strcmp(comando, "L_02") == 0 || strcmp(comando, "AC") == 0 || strcmp(comando, "PR") == 0 || strcmp(comando, "AL_BZ") == 0 || strcmp(comando, "T_ON") == 0 || strcmp(comando, "T_OFF") == 0)
    {
      enviaDistribuido(i, comando);
      sleep(1);
      scan = 0;
    }

    __fpurge(stdin);
    printf("leu: %s\n\n", comando);

  } while (scan);
}

void menuAtivaDesativaGERAL()
{

  system("clear");
  int i = -1;
  do
  {
    printf("Digite 0 para DESLIGAR TODOS OS ANDARES\n");
    printf("Digite 1 para ligar TODOS OS ANDARES\n");
    scanf("%d", &i);

  } while (i != 0 && i != 1);

  if (i)
  {
    printf("Ligando todos os andares...\n");
  }
  else
  {

    printf("Desligando todos os andares...\n");
  }
  for (int j = 0; j <= getNumDispositivos() - 1; j++)
  {
    enviaDistribuido(j, i ? "T_ON" : "T_OFF");
  }

  sleep(1);
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
    printf("Digite 2 para entrar no quadro de comandos POR SALA\n");
    printf("Digite 3 para desligar ou ligar TODAS AS SALAS\n");
    printf("Digite 4 para desativar ou ativar o MODO ALARME\n");

    scanf("%d", &i);
    if (i == 2)
    {
      menuAtivaDesativa();
    }
    if (i == 3)
    {
      menuAtivaDesativaGERAL();
    }
    if (i == 4)
    {
      changeAlarme();
    }
    i = 0;

    __fpurge(stdin);
  } while (menuon);
}
