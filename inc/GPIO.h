#ifndef GPIO
#define GPIO
void GPIO_PortF_Init();
void LED_init();
void Switches_init();
void LED_ON();
void LED_OFF();
unsigned char SW1_Input();
unsigned char SW2_Input();
void LED_Blue_ON();
void LED_Green_ON();
void LED_RED_ON();
#endif
