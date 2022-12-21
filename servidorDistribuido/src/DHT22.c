#include "DHT22.h"
#include <time.h>

#define MAX_TIMINGS 85 // Takes 84 state changes to transmit data
//------------------------------------------------------------------------------------
static int durn(struct timespec t1, struct timespec t2)
{
    return (((t2.tv_sec - t1.tv_sec) * 1000000) + ((t2.tv_nsec - t1.tv_nsec) / 1000)); // elapsed microsecs
}
//------------------------------------------------------------------------------------
int data[5];
float Temp = 0;
float Hum = 0;
int Valid = 0;
const char *Fetchdht(int pin)
{
    struct timespec st, cur;
    int uSec = 0;
    int Toggles = 0;
    int BitCnt = 0;
    int lastState = HIGH;
    char *retorno = malloc(35);

    data[0] = data[1] = data[2] = data[3] = data[4] = 0;

    pinMode(pin, OUTPUT);
    digitalWrite(pin, HIGH);
    delay(10);
    digitalWrite(pin, LOW);
    delay(18);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);

    // Read data from sensor.
    for (Toggles = 0; (Toggles < MAX_TIMINGS) && (uSec < 255); Toggles++)
    {

        clock_gettime(CLOCK_REALTIME, &st);
        while ((digitalRead(pin) == lastState) && (uSec < 255))
        {
            clock_gettime(CLOCK_REALTIME, &cur);
            uSec = durn(st, cur);
        };

        lastState = digitalRead(pin);

        // First 2 state changes are sensor signaling ready to send, ignore them.
        // Each bit is preceeded by a state change to mark its beginning, ignore it too.
        if ((Toggles > 2) && (Toggles % 2 == 0))
        {
            // Each array element has 8 bits.  Shift Left 1 bit.
            data[BitCnt / 8] <<= 1;
            // A State Change > 35 µS is a '1'.
            if (uSec > 35)
                data[BitCnt / 8] |= 0x00000001;

            BitCnt++;
        }
    }

    // Read 40 bits. (Five elements of 8 bits each)  Last element is a checksum.
    if ((BitCnt >= 40) && (data[4] == ((data[0] + data[1] + data[2] + data[3]) & 0xFF)))
    {
        Valid = 1;
        Hum = (float)((data[0] << 8) + data[1]) / 10.0;
        Temp = (float)((data[2] << 8) + data[3]) / 10.0;
        if (data[2] & 0x80)
            Temp *= -1; // Negative Sign Bit on.
        // Convert to Fahrenheit

        sprintf(retorno, "Hum: %.2f Temp: %.2f", Hum, Temp);
    }
    else
    { // Data Bad, use cached values.
        Valid = 0;
        Hum = 0.0;
        Temp = 0.0;
        strcpy(retorno, "");
    }
    //  printf("%s pino:%d\n",retorno, pin);
    return retorno;
}
//------------------------------------------------------------------------------------