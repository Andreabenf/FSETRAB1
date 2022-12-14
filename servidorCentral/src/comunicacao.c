#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>

#include "comunicacao.h"
#include "menu.h"
#include "cJSON.h"

StatusGeral dispositivos[10];
int num_dispositivos = 0;

StatusGeral* getDispositivos()
{

  return dispositivos;
}
int getNumDispositivos()
{

  return num_dispositivos;
}

void TrataClienteTCP(int socketCliente)
{
  /* 1. Declara variáveis para tratamento do cliente */
  int bufferSize = 550;
  char buffer[bufferSize];
  int tamanhoRecebido, command;

  /* 2. Limpa buffer para garantir a leitura de mensagens novas */
  memset(buffer, '\0', sizeof(buffer));

  /* 3. Obtém tamanho da mensagem recebida */
  if ((tamanhoRecebido = recv(socketCliente, buffer, bufferSize, 0)) < 0)
    printf("Erro no recv()\n");

  // printf("Mensagem: '%s'\n", buffer);

  /*---------------- Processa JSON ----------------------*/
  cJSON *body = cJSON_Parse(buffer);

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

  id = cJSON_GetObjectItemCaseSensitive(body, "id");
  L_01 = cJSON_GetObjectItemCaseSensitive(body, "L_01");
  L_02 = cJSON_GetObjectItemCaseSensitive(body, "L_02");
  AC = cJSON_GetObjectItemCaseSensitive(body, "AC");
  PR = cJSON_GetObjectItemCaseSensitive(body, "PR");
  AL_BZ = cJSON_GetObjectItemCaseSensitive(body, "AL_BZ");
  SPres = cJSON_GetObjectItemCaseSensitive(body, "SPres");
  SFum = cJSON_GetObjectItemCaseSensitive(body, "SFum");
  SJan = cJSON_GetObjectItemCaseSensitive(body, "SJan");
  SPor = cJSON_GetObjectItemCaseSensitive(body, "SPor");
  SC_IN = cJSON_GetObjectItemCaseSensitive(body, "SC_IN");
  SC_OUT = cJSON_GetObjectItemCaseSensitive(body, "SC_OUT");
  DHT22 = cJSON_GetObjectItemCaseSensitive(body, "DHT22");

  // if (cJSON_IsString(id) && (id->valuestring != NULL)) {
  //   printf("id: '%s'\n", id->valuestring);
  // } else {
  //   printf("Se fudeu\n");
  // }

  // printf("id: '%s'\n", id->valuestring);
  // printf("L_01: '%d'\n", L_01->valueint);
  // printf("L_02: '%d'\n", L_02->valueint);
  // printf("AC: '%d'\n", AC->valueint);
  // printf("PR: '%d'\n", PR->valueint);
  // printf("AL_BZ: '%d'\n", AL_BZ->valueint);
  // printf("SPres: '%d'\n", SPres->valueint);
  // printf("SFum: '%d'\n", SFum->valueint);
  // printf("SJan: '%d'\n", SJan->valueint);
  // printf("SPor: '%d'\n", SPor->valueint);
  // printf("SC_IN: '%d'\n", SC_IN->valueint);
  // printf("SC_OUT: '%d'\n", SC_OUT->valueint);
  // printf("DHT22: '%d'\n", DHT22->valueint);

  /*---------------- Termina JSON ----------------------*/

  /* 4. Transfere dado do buffer pra variável do comando */
  // sscanf(buffer, "%d", &command);

  // /* 5. Trata os sensores */
  // trataSensores(command);
  int found = 0;
  for (int i = 0; i < num_dispositivos; i++)
  {
    if (strcmp(id->valuestring, dispositivos[i].id)==0)
    {
      dispositivos[i].L_01 = L_01->valueint;
      dispositivos[i].L_02 = L_02->valueint;
      dispositivos[i].AC = AC->valueint;
      dispositivos[i].PR = PR->valueint;
      dispositivos[i].AL_BZ = AL_BZ->valueint;
      dispositivos[i].SPres = SPres->valueint;
      dispositivos[i].SFum = SFum->valueint;
      dispositivos[i].SJan = SJan->valueint;
      dispositivos[i].SPor = SPor->valueint;
      dispositivos[i].SC_IN = SC_IN->valueint;
      dispositivos[i].SC_OUT = SC_OUT->valueint;
      dispositivos[i].DHT22 = DHT22->valueint;
      found = 1;
    }
  }
  if (!found)
  {
    num_dispositivos++;
    strcpy(dispositivos[num_dispositivos].id, id->valuestring);
    dispositivos[num_dispositivos].L_01 = L_01->valueint;
    dispositivos[num_dispositivos].L_02 = L_02->valueint;
    dispositivos[num_dispositivos].AC = AC->valueint;
    dispositivos[num_dispositivos].PR = PR->valueint;
    dispositivos[num_dispositivos].AL_BZ = AL_BZ->valueint;
    dispositivos[num_dispositivos].SPres = SPres->valueint;
    dispositivos[num_dispositivos].SFum = SFum->valueint;
    dispositivos[num_dispositivos].SJan = SJan->valueint;
    dispositivos[num_dispositivos].SPor = SPor->valueint;
    dispositivos[num_dispositivos].SC_IN = SC_IN->valueint;
    dispositivos[num_dispositivos].SC_OUT = SC_OUT->valueint;
    dispositivos[num_dispositivos].DHT22 = DHT22->valueint;
  }
}

void *recebeDistribuido()
{
  /* 1. Cria variáveis necessárias para o socket */
  int socketServidor;                   // Descritor do arquivo - servidor
  int socketCliente;                    // Descritor do arquivo - cliente
  struct sockaddr_in addrServidor;      // Struct de endereço - servidor
  struct sockaddr_in addrCliente;       // Struct de endereço - cliente
  unsigned short portaServidor = 11130; // Endereço de Porta do Servidor
  unsigned int clienteLen;              // Tamanho do Endereço do cliente
  int maxClientes = 10;                 // Máximo de Clientes até que uma conexão seja rejeitada

  /* 2. Abrir o Socket (Criar a pilha de dados) */
  if ((socketServidor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    printf("falha no socker do Servidor\n");

  /* 3. Montar a estrutura sockaddr_in (Definir o endereço, como porta e IP)*/
  memset(&addrServidor, 0, sizeof(addrServidor)); // Zerando a estrutura de dados
  addrServidor.sin_family = AF_INET;
  addrServidor.sin_addr.s_addr = htonl(INADDR_ANY);
  addrServidor.sin_port = htons(portaServidor);

  /* 4. Realizar o bind (associar o endereço ao socket em si)*/
  if (bind(socketServidor, (struct sockaddr *)&addrServidor, sizeof(addrServidor)) < 0)
    printf("Falha no Bind\n");

  /* 5. Implementar o listen (começar a receber dados no IP e porta via socket)*/
  if (listen(socketServidor, maxClientes) < 0)
    printf("Falha no Listen\n");

  /* 6. Começa o loop para escutar/receber as mensagens no socket */
  while (1)
  {

    /* 7. Cria conexão de socket com o cliente para aceitar mensagens */
    clienteLen = sizeof(addrCliente);
    if ((socketCliente = accept(socketServidor, (struct sockaddr *)&addrCliente, &clienteLen)) < 0)
      printf("Falha no Accept\n");

    /* 8. Printa o endereço do cliente*/
    // printf("Conexão do Cliente %s\n", inet_ntoa(addrCliente.sin_addr));

    /* 9. Chama função de tratamento do cliente (possui um loop infinito) */
    TrataClienteTCP(socketCliente);

    /* 10. Fecha conexão de socket com o cliente */
    close(socketCliente);
  }

  /* 11. Fecha conexão do próprio socket do servidor */
  close(socketServidor);
}

int enviaDistribuido(int item, int status, unsigned short int porta)
{
  printf("Ate aqii foi");
  /* 1. Cria variáveis necessárias para o socket */
  // int socketCliente; // Descritor do arquivo - cliente
  // struct sockaddr_in addrServidor; // Struct de endereço - servidor
  // unsigned short portaPraOndeEnvia = 10121; // Endereço de Porta do Servidor
  // char *IP_Servidor = SERVER_DISTRIBUTED_IP;
  // char *mensagem = "1 1 1";
  // unsigned int tamanhoMensagem;

  // /* 2. Abrir o Socket (Criar a pilha de dados) */
  // if((socketCliente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
  //   printf("falha no socket do Servidor\n");

  // /* 3. Montar a estrutura sockaddr_in (Definir o endereço, como porta e IP)*/
  // memset(&addrServidor, 0, sizeof(addrServidor)); // Zerando a estrutura de dados
  // addrServidor.sin_family = AF_INET;
  // addrServidor.sin_addr.s_addr = htonl(IP_Servidor);
  // addrServidor.sin_port = htons(portaPraOndeEnvia);

  // /* 4. Realizar o connect (associar o endereço do servidor ao socket em si)*/
  // if(connect(socketCliente, (struct sockaddr *) &addrServidor, sizeof(addrServidor)) < 0)
  // 	printf("Erro no connect()\n");

  // tamanhoMensagem = strlen(mensagem);

  // /* 5. Enviar dado para o distribuído */
  // if(send(socketCliente, mensagem, tamanhoMensagem, 0) != tamanhoMensagem)
  //   printf("Erro no envio: numero de bytes enviados diferente do esperado\n");

  // /* 6. Fecha conexão do próprio socket do servidor */
  // close(socketCliente);

  return 1;
}