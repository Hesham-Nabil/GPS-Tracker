#include "tm4c123gh6pm.h"
#define PF123_mask 0xE
#define PF_mask 0x20
#define SYSTEM_CLOCK 16000000

void initPortF(void)     //Initializing port F
{

SYSCTL_RCGCGPIO_R	|= PF_mask;             //port F clock enable
while((SYSCTL_RCGCGPIO_R & 0x20)==0)      // Delay until the clock is initialized
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;       // Unlock port F commit register
GPIO_PORTF_CR_R   |= 0x1F;               // Allow changes to port F (two switches and LEDs)
GPIO_PORTF_AMSEL_R = 0x00;       // Disable analog function
GPIO_PORTF_AFSEL_R = 0x0;       // GPIO clear bit PCTL to act as port
GPIO_PORTF_PCTL_R = 0x0;       //Disable alternate functiom
GPIO_PORTF_DIR_R |= PF123_mask;          //PF 321 output
GPIO_PORTF_DEN_R |= 0x1F;          //Enable digital pins PF0 >> PF4 and switches
GPIO_PORTF_DATA_R &= ~PF123_mask;        //Initialize LEDs to be off
GPIO_PORTF_PUR_R = 0x11;             //enable pull up on switches
}


void UART0_Handler(void) {
    if (UART0_MIS_R & 0x10) { // Bit 4 corresponds to RX interrupt
        char receivedChar = UART0_DR_R;                                   // Read the received data
        
        
        // Check if the received character is 'U'
        if (receivedChar == 'U') {
            //condition        <<<<<<
        }
    }
}





int main(){
initPortF();
UART0_PORTA_Init();                   //initailizing UART0
	
	

NVIC_PRI2_R |= 0x00002000;     // set priorty 1 to UART0   (NVIC_PRI2_R is the reg for UART and in segment 1)
NVIC_EN0_R = 0x00000020;      // enable interrupts for UART0 (UART 0 enalble reg is EN0 and the bit is the fifth one)
	
	
__asm {
    cpsie i
}
while (1) {
}
}