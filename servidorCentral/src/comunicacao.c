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

  void* recebeDistribuido() {

  struct sockaddr_in server, client;

	int serverid = socket(AF_INET, SOCK_STREAM, 0);

	memset(&server, '0', sizeof(server));

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	server.sin_port = htons(11130);

	bind(serverid, (struct sockaddr*) &server, sizeof(server));

	if (listen(serverid, 10) == -1) {
    exit(0);
	}

  while (1) {
	  unsigned int len = sizeof(client);
	  int clientid = accept(serverid, (struct sockaddr*) &client, &len);

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