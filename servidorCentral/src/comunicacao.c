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

void TrataClienteTCP(int socketCliente) {
	char buffer[16];
	int tamanhoRecebido;

	if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
		printf("Erro no recv()\n");

	while (tamanhoRecebido > 0) {
		if(send(socketCliente, buffer, tamanhoRecebido, 0) != tamanhoRecebido)
			printf("Erro no envio - send()\n");
		
		if((tamanhoRecebido = recv(socketCliente, buffer, 16, 0)) < 0)
			printf("Erro no recv()\n");
	}
}



void* recebeDistribuido() {
  
  /* 1. Cria variáveis necessárias para o socket */
  int socketServidor; // Descritor do arquivo - servidor
	int socketCliente; // Descritor do arquivo - cliente
	struct sockaddr_in addrServidor; // Struct de endereço - servidor
	struct sockaddr_in addrCliente; // Struct de endereço - cliente
	unsigned short portaServidor = 11130; // Endereço de Porta do Servidor
	unsigned int clienteLen; // Tamanho do Endereço do cliente
  int maxClientes = 10; // Máximo de Clientes até que uma conexão seja rejeitada

  /* 2. Abrir o Socket (Criar a pilha de dados) */
  if((socketServidor = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
	  printf("falha no socker do Servidor\n");

  /* 3. Montar a estrutura sockaddr_in (Definir o endereço, como porta e IP)*/
  memset(&addrServidor, 0, sizeof(addrServidor)); // Zerando a estrutura de dados
  addrServidor.sin_family = AF_INET;
  addrServidor.sin_addr.s_addr = htonl(INADDR_ANY);
  addrServidor.sin_port = htons(portaServidor);

  /* 4. Realizar o bind (associar o endereço ao socket em si)*/
	if(bind(socketServidor, (struct sockaddr *) &addrServidor, sizeof(addrServidor)) < 0)
		printf("Falha no Bind\n");

  /* 5. Implementar o listen (começar a receber dados no IP e porta via socket)*/
  if(listen(socketServidor, maxClientes) < 0) 
		printf("Falha no Listen\n");

  /* 6. Começa o loop para escutar/receber as mensagens no socket */
	while(1) {

    /* 7. Cria conexão de socket com o cliente para aceitar mensagens */
		clienteLen = sizeof(clienteAddr);
		if((socketCliente = accept(socketServidor, (struct sockaddr *) &clienteAddr, &clienteLen)) < 0)
			printf("Falha no Accept\n");
		
    /* 8. Printa o endereço do cliente*/
		printf("Conexão do Cliente %s\n", inet_ntoa(clienteAddr.sin_addr));
		
    /* 9. Chama função de tratamento do cliente (possui um loop infinito) */
		TrataClienteTCP(socketCliente);

    /* 10. Fecha conexão de socket com o cliente */
		close(socketCliente);
	}

  /* 11. Fecha conexão do próprio socket do servidor */
	close(socketServidor);


















  while (1) {
	  unsigned int len = sizeof(client);
	  int clientid = accept(serverid, (struct sockaddr*) &client, &len);

    printf("Conexão do Cliente %s\n", inet_ntoa(client.sin_addr));
    char buffer[16];
	  int size = recv(clientid, buffer, 16, 0);

    if (size < 0) {
      exit(0);
    }
    
    buffer[15] = '\0';

		int command;
		sscanf(buffer, "%d", &command);

    trataSensores(command);
		
		close(clientid);
  }

	close(serverid);
}

// }

DHT22 leDHT() {
  struct sockaddr_in client;

  DHT22 dht22;
  dht22.temperature = 0;
  dht22.humidity = 0;

  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1) {
    return dht22;
  }

  // unsigned short servidorPorta = 11130;

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(SERVER_DISTRIBUTED_IP);
  client.sin_port = htons(SERVER_DISTRIBUTED_PORT);
  
  if (connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0) {
    return dht22;
  }
  
  char buf[2];
  snprintf(buf, 2, "%d", 2);
  int size = strlen(buf);
  if (send(socketid, buf, size, 0) != size) {
    close(socketid);
    return dht22;
  }

  char buffer[16];
  int size_rec = recv(socketid, buffer, 16, 0);
  if (size_rec < 0) {
    close(socketid);
    return dht22;
  }
    
  buffer[15] = '\0';

  int command;
  double temperature;
  double humidity;
  sscanf(buffer, "%d %lf %lf", &command, &temperature, &humidity);
  // printf("TEMP: %lf\nUMID: %lf\n", temperature, humidity);
  dht22.temperature = temperature;
  dht22.humidity = humidity;

  close(socketid);

  return dht22;
}

void leTempUmidade() {
	while (1) {
    DHT22 dht22 = leDHT();

    printf("temp: %f -- umidade: %f\n\n", dht22.temperature, dht22.humidity);

    sleep(1);
  }

}


int enviaDistribuido(int item, int status, unsigned short int porta) {
  
  struct sockaddr_in client;
  
  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1) {
    printf("error\n");

    exit(0);
  }
  
  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr(SERVER_DISTRIBUTED_IP);
  client.sin_port = htons(porta);

  if (connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0) {
    printf("error\n");
    exit(0);
  }

  char buf[7];
  snprintf(buf, 7, "%d %d %d", 1, item, status);
  int size = strlen(buf);
  if (send(socketid, buf, size, 0) != size) {
    printf("error\n");
    exit(0);
  }

  char buffer[16];
  int size_rec = recv(socketid, buffer, 16, 0);
  if (size_rec < 0) {
    printf("error\n");
    exit(0);
  }

  buffer[15] = '\0';

  int res;
  sscanf(buffer, "%d", &res);

  close(socketid);

  return res;
}