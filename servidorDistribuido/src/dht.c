#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define MAX_TIMINGS 100
#define MAX_STACK 5
#define DEBUG 1
#define WAIT_TIME 2000


uint8_t dht_pin = 7;  // default GPIO 20 (wiringPi 28)


int data[5] = {0, 0, 0, 0, 0};
float temperature = -1;
float humidity = -1;

int read_dht_data() {
    
    uint8_t laststate = HIGH;
    uint8_t counter = 0;
    uint8_t j = 0, i;

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    pinMode(dht_pin, OUTPUT);
    digitalWrite(dht_pin, LOW);
    delay(18);

    pinMode(dht_pin, INPUT);

    for (i = 0; i < MAX_TIMINGS; i++) {
        counter = 0;
        while (digitalRead(dht_pin) == laststate) {
            counter++;
            delayMicroseconds(1);
            if (counter == 255) {
                break;
            }
        }
        laststate = digitalRead(dht_pin);

        if (counter == 255)
            break;

        if ((i >= 4) && (i % 2 == 0)) {
            data[j / 8] <<= 1;
            if (counter > 16)
                data[j / 8] |= 1;
            j++;
        }
    }

    if ((j >= 40) &&
        (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF))) {
        float h = (float)((data[0] << 8) + data[1]) / 10;
        if (h > 100) {
            h = data[0]; 
        }
        float c = (float)(((data[2] & 0x7F) << 8) + data[3]) / 10;
        if (c > 125) {
            c = data[2]; 
        }
        if (data[2] & 0x80) {
            c = -c;
        }
        // float f = c * 1.8f + 32;
        humidity = h;
        temperature = c;
        if (DEBUG) printf( "read_dht_data() Humidity = %.1f %% Temperature = %.1f *C\n", humidity, temperature);

        return 0;
    }
    else {
        if (DEBUG) printf( "read_dht_data() Data not good, skip\n" );
		temperature = humidity = -1;
		return 1;

        // printf("Erro ao ler temperatura e humidade. Realizando nova leitura\n");
        // delay(100);
        // if (count != MAX_STACK)
        //     read_dht_data(temperature, humidity, count + 1);
        // else
        // {
        //     humidity *= 1;
        //     temperature *= 1;
        //     printf("Não é possível ler o sensor DHT22\nUtlizando valor da leitura anterior\n");
        // }
    }
}


float leTemperatura() {	
	int done = 0;

	while (!done) {
		done = !read_dht_data();
		delay(WAIT_TIME); 
	}
  return temperature;
}

float leUmidade() {
	int done = 0;

	while (!done) {
		done = !read_dht_data();
		delay(WAIT_TIME); 
	}

  return humidity;

}

