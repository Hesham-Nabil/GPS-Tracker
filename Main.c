#include "tm4c123gh6pm.h"
#include "UART.h"
#include "GPS_Receiver.c"

char GPS_data[80];

int main(void)
{
    UART_Init();
    while (1){

        while (!check_logname()); //wait for desired log name
        getGpsData();

    }
    return 0;
}
