#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

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


#include "leJSON.h"
#include "comunicacao.h"
#include "gpio.h"

pthread_t comunicacao;
pthread_t gpio;

JSONConfig configs;

void encerraPrograma() {
    printf("Encerrando...\n");
    exit(0);
}

void inicializaPrograma(const char * filename) {

    if (wiringPiSetup() == -1) {
		printf("Failed to initialize wiringPi\n");
		exit(1);
    }
    configs = leJSONConfig(filename);

    desativaDispositivos();
}

void trata_SIGINT(int signum) {
    encerraPrograma();
}

int main(int argc, const char * argv[]) {
   
   signal(SIGINT, trata_SIGINT);

    if (argc >= 2){
		inicializaPrograma(argv[1]);
	}
	else{
		printf("O arquivo de configuracao precisa ser passado como parametro\n");
		return -1;
	}
    printf("busco amigos");
    int porta = getPorta();

    pthread_create(&comunicacao, NULL, recebeCentral, &porta);
    pthread_create(&gpio, NULL, handleGPIO, NULL);
    
    pthread_join(comunicacao, NULL);
    pthread_join(gpio, NULL);
	
    return 0;
}