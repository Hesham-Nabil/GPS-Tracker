#include "tm4c123gh6pm.h"
#define PF123_mask 0xE
#define PF_mask 0x20

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

UART0_PORTA_Init();                   //initailizing UART0
	
	

NVIC_PRI2_R |= 0x00002000;     // set priorty 1 to UART0   (NVIC_PRI2_R is the reg for UART and in segment 1)
NVIC_EN0_R = 0x00000020;      // enable interrupts for UART0 (UART 0 enalble reg is EN0 and the bit is the fifth one)
	
	
__asm {
    cpsie i
}
while (1) {
}
}
