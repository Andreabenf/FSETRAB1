# Trabalho 1 
# Fundamento de Sistemas Embarcados
### Aluno: André Aben Athar de Freitas
### Matrícula: 170056155
Este trabalho tem por objetivo a criação de um sistema distribuído de automação predial para monitoramento e acionamento de sensores e dispositivos de um prédio com múltiplas salas. O sistema deve ser desenvolvido para funcionar em um conjunto de placas Raspberry Pi com um servidor central responsável pelo controle e interface com o usuário e servidores distribuídos para leitura e acionamento dos dispositivos. Dentre os dispositivos envolvidos estão o monitoramento de temperatura e umidade, sensores de presença, sensores de fumaça, sensores de contagem de pessoas, sensores de abertura e fechamento de portas e janelas, acionamento de lâmpadas, aparelhos de ar-condicionado, alarme e aspersores de água em caso de incêndio.


A solução apresentada foi feita utilizando a linguagem C.
### Execução
1. Clone o repositório nas placas que serão utilizadas.

2. Decida em qual placa ficará o ServidorCentral
3. Rode:
```
$ ifconfig
```
4. Pegue a rede local e coloque nos arquivos de configuração dentro da pasta de Servidor distribuido:
```
exemplo: "ip_servidor_central": "192.168.1.134"
```
5. Após isso, faça o mesmo porém com a chave "ip_servidor_distribuido" em suas respectivas placas de servidores distribuídos. 

6. Pronto! agora é necessário compilar cada projeto.


```
$ cd servidorDistribuido
$ make

$ cd servidorCentral
$ make
```

7. primeiro rode o servidor Central:

```
$ cd servidorCentral
$ bin/bin
```

7. Depois em terminais diferentes, rode os servidores Distribuídos passando o arquivo de configuração e qual porta ele rodará:

```
$ cd servidorDistribuido
$ bin/bin configuracao1-3.json 10122
```
8. Projeto rodando!


# Resumo de features:

| Requisito | Feito? | Como fazer |
| -------- | -------- | -------- |
| Manter conexão com o servidor distribuído (TCP/IP)    |  YES    | Possível ver no inicio da programa    |
| Interface com Estado das entradas | YES | Aperte '1' para sempre atualizar o estado das entradas |
| Interface com Estado das Saídas | YES | Aperte '1' para sempre atualizar o estado das saídas |
| Interface com Valor da temperatura e umidade | YES | Aperte '1' para sempre atualizar o estado da temperatura e humidade |
|  Contador de Ocupação | YES/NO | No estado possui apenas a quantidade por sala |
| Mecanismo na interface para acionar manualmente lâmpadas, aparelhos de ar-condicionado e projetores das salas | YES | Aperte '2', escolha a sala e ligue ou desligue de acordo com os códigos |
| Acionamento do sistema de alarme | YES | Aperte '4' para ligar ou desligar o modo Alarme |
| Acionamento de alarme de incêncio ao detectar presença de fumaça | YES | Acione um detector de fumaça e o alarme de todas as salas acenderão |
| Manter log | YES/NO | O log existe, mas está em TXT |
| Manter os valores de temperatura e umidade atualizados a cada 2 segundos | YES | - |
| Acionar Lâmpadas, aparelhos de Ar-Condicionado e projetores | YES |Aperte '2', escolha a sala e ligue ou desligue de acordo com os códigos |
| Sensores de presença e abertura de portas/janelas (push) | YES | Acione os sensores e veja as respostas dependendo do modo alarme |
| Sensores de fumaça (push) | YES | Acione os sensores e veja as respostas dependendo do modo alarme |
| Efetuar a contagem de pessoas entrando e saindo da sala para controle de ocupação | YES | Veja o estado individual de cada sala no menu central |
| Servidores distribuídos deve ser iniciada conforme o arquivo descrição JSON | YES | - |
| Ligar tudo de todos os andares | YES | Digite '3' depois 1 |
| Desligar tudo de todos os andares | YES | Digite '3' depois 0 |
| Desligar tudo de um andar | YES | Digite '2' escolha o andar e digite T_OFF |
| Ligar tudo de um andar | YES | Digite '2' escolha o andar e digite T_ON |
| Ao acionar o sistema de alarme, deve haver uma verificação se o sensores que ativam o alarme estão ligado | NO | - |




