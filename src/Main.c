#include "tm4c123gh6pm.h"
#include "UART.h"
#include "GPS_Reciever.h"
#include "GPIO.h"
#include "Systick.h"

int main(void)
{
    GPIO_PortF_Init();
    UART0_PORTA_Init();
    UART1_PORTB_Init();
    LED_init();
    Switches_init();
    SysTick_Init();
    const int length = 300;
    char buffer[length]; 
    const int L = 3;
    const int W = 2;
    double coordinates[L][W];
    double distance =0;
    int i = 0 ;         
    while (1)                   
    { UART0_TRANSMIT_CHAR('1');
GPS_Start(&distance,coordinates,buffer,i);
    UART0_TRANSMIT_CHAR('c');
    char output_buffer[10];
    UART0_TRANSMIT_CHAR('d');
UART0_TRANSMIT_CHAR('\n');
UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/1000) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/100) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/10) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/1) % 10) + 48);
UART0_TRANSMIT_CHAR('.');
UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*10)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*100)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*1000)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*10000)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*100000)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*1000000)) % 10) + 48);
UART0_TRANSMIT_CHAR(' ');
UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/1000) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/100) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/10) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/1) % 10) + 48);
UART0_TRANSMIT_CHAR('.');
UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*10)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*100)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*1000)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*10000)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*100000)) % 10) + 48);
UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*1000000)) % 10) + 48);

UART0_TRANSMIT_CHAR('\n');
}

}
