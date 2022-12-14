#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "leJSON.h"
#include "cJSON.h"

JSONConfig config;
cJSON *live_info;

int qtdeDispositivosEntrada;
int dispositivosEntrada[7];
int qtdeDispositivosSaida;
int dispositivosSaida[5];


JSONConfig leJSONConfig(const char * nomeArquivo, const int minhaporta) {


    const cJSON *item = NULL;
    const cJSON *outputs = NULL;
    const cJSON *inputs = NULL;
    const cJSON *nomeAndar = NULL;

    // Abrindo arquivo JSON
    char json_buffer[2200];

    FILE *arq = fopen(nomeArquivo,"r");
    fread(json_buffer, 2200, 1, arq);
	  fclose(arq);
    cJSON *live_info = cJSON_Parse(json_buffer);
    if (live_info == NULL)
    {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL)
        {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return config;
    }
    config.portaDistribuido= minhaporta;
    nomeAndar = cJSON_GetObjectItemCaseSensitive(live_info, "nome");
    printf("Analisando \"%s\"\n", nomeAndar->valuestring);
    cJSON *ip_json = cJSON_GetObjectItemCaseSensitive(live_info, "ip_servidor_central");
    strcpy(config.ipCentral, ip_json->valuestring);

    cJSON *ip_serv_dist = cJSON_GetObjectItemCaseSensitive(live_info, "ip_servidor_distribuido");
    char str[10];
    sprintf(str, "%s:%d",ip_serv_dist->valuestring, minhaporta);
    strcpy(config.id, str);
    printf("IP: %s e Porta: %s\n", config.ipCentral, config.id);
    inputs = cJSON_GetObjectItemCaseSensitive(live_info, "inputs");

    qtdeDispositivosEntrada = 0;
    cJSON_ArrayForEach(item, inputs)
    {

        cJSON *tag = cJSON_GetObjectItemCaseSensitive(item, "tag");
        cJSON *gpio = cJSON_GetObjectItemCaseSensitive(item, "gpio");
        cJSON *sigla = cJSON_GetObjectItemCaseSensitive(item, "sigla");
        cJSON *status = cJSON_GetObjectItemCaseSensitive(item, "status");

        printf("%s na gpio %d\n", tag->valuestring, gpio->valueint);


        dispositivosEntrada[qtdeDispositivosEntrada] = gpio->valueint;
        qtdeDispositivosEntrada += 1;

        if(strcmp(sigla->valuestring,"SPres")==0)
           config.SPres = gpio->valueint;

        if(strcmp(sigla->valuestring,"SFum")==0)
           config.SFum = gpio->valueint;

        if(strcmp(sigla->valuestring,"SJan")==0)
           config.SJan = gpio->valueint;

        if(strcmp(sigla->valuestring,"SPor")==0)
           config.SPor = gpio->valueint;

        if(strcmp(sigla->valuestring,"SC_IN")==0)
           config.SC_IN = gpio->valueint;
           
        if(strcmp(sigla->valuestring,"SC_OUT")==0)
           config.SC_OUT = gpio->valueint;
        
    }


    outputs = cJSON_GetObjectItemCaseSensitive(live_info, "outputs");

    qtdeDispositivosSaida = 0;
    cJSON_ArrayForEach(item, outputs)
    {

        cJSON *tag = cJSON_GetObjectItemCaseSensitive(item, "tag");
        cJSON *gpio = cJSON_GetObjectItemCaseSensitive(item, "gpio");

        printf("%s na gpio %d\n", tag->valuestring, gpio->valueint);

        

        dispositivosSaida[qtdeDispositivosSaida] = gpio->valueint;
        qtdeDispositivosSaida += 1;
    }


    return config;

}

int *getDispositivosEntrada(){
  return dispositivosEntrada;
}

JSONConfig getConfig(){
   return config;
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
  return config.portaDistribuido;
}
