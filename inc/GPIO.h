#ifndef GPIO
#define GPIO
void GPIO_PortF_Init();
void GPIO_PortE_Init();
void LED_init();
void Switches_init();
void LED_ON();
void LED_OFF();
unsigned char SW1_Input();
unsigned char SW2_Input();
#endif
