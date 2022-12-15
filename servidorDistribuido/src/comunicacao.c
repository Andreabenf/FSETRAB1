#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "dht.h"
#include "gpio.h"

void *recebeCentral(void *porta)
{

  int this_port = *((int *)porta);

  struct sockaddr_in server, client;

  int serverid = socket(AF_INET, SOCK_STREAM, 0);

  memset(&server, '0', sizeof(server));

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(this_port);

  bind(serverid, (struct sockaddr *)&server, sizeof(server));

  if (listen(serverid, 10) == -1)
  {
    printf("ERROR");
    exit(1);
  }

  while (1)
  {
    unsigned int len = sizeof(client);
    int clientid = accept(serverid, (struct sockaddr *)&client, &len);

    char buffer[6];
    int size = recv(clientid, buffer, 6, 0);

    if (size < 0)
    {
      printf("ERROR");
      exit(1);
    }

    printf("mensagemrecebida: '%s'\n", buffer);

    ativaDesativaDispositivo(buffer);
    close(clientid);
  }

  close(serverid);
}

void enviaCentral(char *message)
{

  struct sockaddr_in client;

  int socketid = socket(AF_INET, SOCK_STREAM, 0);
  if (socketid == -1)
  {
    printf("Falha ao criar socket\n");
    exit(1);
  }

  client.sin_family = AF_INET;
  client.sin_addr.s_addr = inet_addr("192.168.1.103");
  client.sin_port = htons(11130);

  while (connect(socketid, (struct sockaddr *)&client, sizeof(client)) < 0)
  {
    printf("Erro ao tentar conectar com o servidor, tentando novamente\n");
    sleep(1);
  }

  int size = strlen(message);
  if (send(socketid, message, size, 0) != size)
  {
    printf("Error: falha no envio\n");
    exit(1);
  }
  close(socketid);
}