#include "tm4c123gh6pm.h"
#include "UART.h"
#include "GPS_Reciever.h"

char GPS_data[80];

int main(void)
{ while(1)
{
int main(void)
{
    GPIO_PortF_Init();
    UART0_PORTA_Init();
    UART1_PORTB_Init();
    Switches_init();
    LED_init();
    //double coordinates[300][2];       //this line should be written in main before GPS_Start() should be called
    //double Distance=0;                //this line should be written in main before GPS_Start() should be called
    //int i = 0;    

    char buffer[500]={};                //initialize a buffer with size very very big to be certain that the data is recieved 
    char test;
    while (1)
    {   
    
    if ( UART1_RECIEVE_CHAR( &test))
    {
        for (int i = 0; i < 1000; i++);
        UART0_TRANSMIT_CHAR(test);
    }
    }
    return 0;
}
}
    return 0;
}
