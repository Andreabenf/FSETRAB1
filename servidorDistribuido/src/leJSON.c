#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "leJSON.h"
#include "cJSON.h"

JSONConfig config;

int qtdeDispositivosEntrada;
int dispositivosEntrada[7];
int qtdeDispositivosSaida;
int dispositivosSaida[5];


JSONConfig leJSONConfig(const char* nomeArquivo) {


    const cJSON *item = NULL;
    const cJSON *outputs = NULL;
    const cJSON *inputs = NULL;
    const cJSON *nomeAndar = NULL;

    // Abrindo arquivo JSON
    char json_buffer[2200];

    FILE *arq = fopen(nomeArquivo,"r");
    fread(json_buffer, 2200, 1, arq);
	  fclose(arq);
    cJSON *devices = cJSON_Parse(json_buffer);
    if (devices == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return config;
    }

    nomeAndar = cJSON_GetObjectItemCaseSensitive(devices, "nome");
    printf("Analisando \"%s\"\n", nomeAndar->valuestring);
    cJSON *ip_json = cJSON_GetObjectItemCaseSensitive(devices, "ip_servidor_central");
    strcpy(config.ipCentral, ip_json->valuestring);

    cJSON *porta_json = cJSON_GetObjectItemCaseSensitive(devices, "porta_servidor_distribuido");
    config.portaDistribuido = porta_json->valueint;

    printf("IP: %s e Porta: %d\n", config.ipCentral, config.portaDistribuido);

    inputs = cJSON_GetObjectItemCaseSensitive(devices, "inputs");

    qtdeDispositivosEntrada = 0;
    cJSON_ArrayForEach(item, inputs)
    {

        cJSON *tag = cJSON_GetObjectItemCaseSensitive(item, "tag");
        cJSON *gpio = cJSON_GetObjectItemCaseSensitive(item, "gpio");

        printf("%s na gpio %d\n", tag->valuestring, gpio->valueint);

        dispositivosEntrada[qtdeDispositivosEntrada] = gpio->valueint;
        qtdeDispositivosEntrada += 1;
    }


    outputs = cJSON_GetObjectItemCaseSensitive(devices, "outputs");

    qtdeDispositivosSaida = 0;
    cJSON_ArrayForEach(item, outputs)
    {

        cJSON *tag = cJSON_GetObjectItemCaseSensitive(item, "tag");
        cJSON *gpio = cJSON_GetObjectItemCaseSensitive(item, "gpio");

        printf("%s na gpio %d\n", tag->valuestring, gpio->valueint);

        if(strcmp(tag->valuestring,"SPres"))
           config.SPres = gpio->valueint;
        if(strcmp(tag->valuestring,"SFum"))
           config.SFum = gpio->valueint;
        if(strcmp(tag->valuestring,"SJan"))
           config.SJan = gpio->valueint;
        if(strcmp(tag->valuestring,"SPor"))
           config.SPor = gpio->valueint;
        if(strcmp(tag->valuestring,"SC_IN"))
           config.SC_IN = gpio->valueint;
        if(strcmp(tag->valuestring,"SC_OUT"))
           config.SC_OUT = gpio->valueint;
        

        dispositivosSaida[qtdeDispositivosSaida] = gpio->valueint;
        qtdeDispositivosSaida += 1;
    }


    return config;

}

int *getDispositivosEntrada(){
  return dispositivosEntrada;
}

int getQtdeDispositivosEntrada(){
  return qtdeDispositivosEntrada;
}

int getQtdeDispositivosSaida(){
  return qtdeDispositivosSaida;
}

int *getDispositivosSaida(){
  return dispositivosSaida;
}

int getPorta(){
  return 10130;
}
