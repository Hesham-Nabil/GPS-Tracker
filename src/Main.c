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
    while (1)
    { UART0_RECIEVE_DATA(&buffer,length);
      delay(20);
      for(int i =0 ; i<length;i++){
      UART0_TRANSMIT_CHAR(buffer[i]);
      }
     memset(buffer,0,length);
    
    }
}
