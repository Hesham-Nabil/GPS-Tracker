#include "GPIO.h"
#include "tm4c123gh6pm.h"
#include "Commands.h"
void GPIO_PortF_Init()
{
	SetBit(SYSCTL_RCGCGPIO_R, 5); 							// SET BIT OF PORT CLOCK
	while ((SYSCTL_PRGPIO_R & 0x20) == 0)
		;													// WAIT TILL CLOCK WORKS PROPERLY
	GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;						// UNLOCK PORT F
	SetReg(GPIO_PORTF_CR_R, 0XFF);							// SET CR (1111111)
	ClearReg(GPIO_PORTF_AMSEL_R, 0XFF); 					// CLEAR AMSEL REG
	ClearReg(GPIO_PORTF_AFSEL_R, 0XFF); 					// CLEAR AFSEL REG
	SetReg(GPIO_PORTF_DEN_R, 0XFF);							// SET ALL BITS TO DIGITAL
	ClearAll(GPIO_PORTF_PCTL_R);							// CLEAR ALL PCTL BITS
	ClearReg(GPIO_PORTF_DIR_R, 0XFF);						// CLEAR DIR REG
	ClearReg(GPIO_PORTF_PUR_R, 0XFF);						// CLEAR PUR REG
	ClearReg(GPIO_PORTF_DATA_R, 0xFF);						// CLEAR DATA REG
}

void LED_init()
{
	SetReg(GPIO_PORTF_DEN_R, 0X0E); 						// DIGITAL ENABLE  3 LEDS
	SetReg(GPIO_PORTF_DIR_R, 0x0E); 						// MAKE THEM OUTPUT
}
void Switches_init()
{
	SetReg(GPIO_PORTF_DEN_R, 0X11);	  						// DIGITAL ENABLE OF THE SWITCHES
	ClearReg(GPIO_PORTF_DIR_R, 0x11); 						// SET THEM AS INPUTS
	SetReg(GPIO_PORTF_PUR_R, 0X11);	  						// SET PULL UP RESISTANCE
}
void LED_ON()
{
	SetReg(GPIO_PORTF_DATA_R, 0X0E); 						// ON LEDS
}
void LED_RED_ON()
{
	SetBit(GPIO_PORTF_DATA_R,1); 							// RED LED On
}
void LED_Green_ON()
{
	SetBit(GPIO_PORTF_DATA_R,3); 							// Green LED On
}
void LED_Blue_ON()
{
	SetBit(GPIO_PORTF_DATA_R,2); 							// Blue LED On
}
void LED_OFF()
{
	ClearReg(GPIO_PORTF_DATA_R, 0X0E); 						// OFF LEDS
}
unsigned char SW1_Input()
{
	return (InvertBit((GetBit(GPIO_PORTF_DATA_R, 4)), 0)); // GET THE INPUT INVERTED OF THE SW1 TO MAKE IF PRESSED 1
}
unsigned char SW2_Input()
{
	return (InvertBit((GetBit(GPIO_PORTF_DATA_R, 0)), 0)); // GET THE INPUT INVERTED OF THE SW2 TO MAKE IF PRESSED 1
}
