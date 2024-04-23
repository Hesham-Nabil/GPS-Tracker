#include "tm4c123gh6pm.h"
#include "UART.h"
#include "GPS_Receiver.c"

int main(void)
{
    UART_Init();
    while (1){

        while (!check_logname()); //wait for desired log name


    }
    return 0;
}
