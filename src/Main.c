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
    while (1)
    {
        if (SW1_Input() == 1)
        {
            LED_ON();
        }
        LED_OFF();
    }
}
