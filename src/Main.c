#include "PortsDef.h"
#include "UART.h"
#include "GPS_Reciever.h"


char GPS_data[80];
int main(void)
{
    GPIO_PortF_Init();
    UART0_PORTA_Init();
    UART1_PORTB_Init();
    LED_init();
    double coordinates[300][2] = {};                                //this line should be written in main before GPS_Start() should be called
    double Distance = 0;                                            //this line should be written in main before GPS_Start() should be called
    int i = 0;
    char buffer[10] = {};                                           //initialize a buffer with size very very big to be certain that the data is recieved
    while (1)
    {
        GPS_Start(&Distance, coordinates, &buffer, i);


    }
}
