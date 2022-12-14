#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dht.h"
#include "gpio.h"

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

void* recebeCentral(void *porta) {

  int this_port = *((int *) porta);

  struct sockaddr_in server, client;

	int serverid = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server, '0', sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(this_port);

	bind(serverid, (struct sockaddr*) &server, sizeof(server));

	if (listen(serverid, 10) == -1) {
		printf("ERROR");
		exit(1);
	}

  while(1) {
    printf("recebendo...");
	  unsigned int len = sizeof(client);
	  int clientid = accept(serverid, (struct sockaddr*) &client, &len);
    
    char buffer[16];
	  int size = recv(clientid, buffer, 16, 0);

    if (size < 0) {
      printf("ERROR");
      exit(1);
    }

    buffer[15] = '\0';
		
    int command;
    sscanf(buffer, "%d", &command);

    // 1 means turning on a lamp or ar condicioner
    if (command == 1) {
      int item;
      int status;
      sscanf(buffer, "%d %d %d", &command, &item, &status);
      printf("Requisicao para alterar estado do dispositivo %d\n", item);
      ativaDesativaDispositivo(item, status);
      char buf[2];
      snprintf(buf, 2, "%d", 1);
      
      
    }

    // 2 means temperature and humidity reading
    if (command == 2) {
      printf("Coletando dadossss de temperatura e humidade\n");
      while(1){

      read_dht_data();
      };
      // char buf[16];
      // snprintf(buf, 16, "%d %4.2f %4.2f", 2, leTemperatura(),leUmidade());
      // int size = strlen(buf);
      // printf("Enviando dados de temperatura e humidade para o servidor central\n");
      // if (send(clientid, buf, size, 0) != size) {
      //   printf("Error: Send failed\n");
      // }
    }
    // TrataClienteTCP(clientid);
		close(clientid);
  }

	close(serverid);
}


void enviaCentral(char *message) {
  
	struct sockaddr_in client;

  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1) {
    printf("Falha ao criar socket\n");
    exit(1);
  }

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr("192.168.1.103");
  client.sin_port = htons(11130);

  while(connect(socketid, (struct sockaddr*) &client, sizeof(client)) < 0){
    printf("Erro ao tentar conectar com o servidor, tentando novamente\n");
    sleep(1);
  }

  int size = strlen(message);
  if (send(socketid, message, size, 0) != size) {
		printf("Error: falha no envio\n");
    exit(1);
  }
  close(socketid);
}