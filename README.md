# FSE-Trabalho2

## Execução

Há 1 servidor central e 2 servidores distribuídos. Sendo assim, o programa será executado para cada um dos 3 servidores, em terminais separados.

Para compilar o código de um servidor, execute no diretório raiz (diretório servidorCentral ou servidorDistribuido) o comando

```
make
```

Para o servidor central, agora basta executar:
```
bin/bin
```

Para os servidores distribuídos, o comando deve receber o arquivo de configuração. Por exemplo, para o servidor distribuído do andar térreo, seria:
```
bin/bin configuracao_andar_terreo.json
```

## Comandos

* Para encerrar um programa, utilize as teclas `Ctrl + C`
* Utilize `Ctrl + Z` para abrir um segundo menu, para ativar ou desativar os dispositivos (lâmpadas, ar condicionado, etc.)

