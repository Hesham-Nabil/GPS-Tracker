#include "PortsDef.h"
#include "Commands.h"
// if 80MHZ not 16MHZ
////////********SYSTICK timer INITALIZATION******////////
void SysTick_Init(void){
NVIC_ST_CTRL_R = 0;                                   // 1) disable SysTick during setup
NVIC_ST_RELOAD_R = 0x00FFFFFF;                        // 2) maximum reload value
NVIC_ST_CURRENT_R = 0;                                // 3) any write to CURRENT clears it
NVIC_ST_CTRL_R = 0x00000005;                          // 4) enable SysTick with core clock
	                                                // 101  CLK_SRC=1,INTEN =0 for no interrupt,ENABLE=1
}
///////******wait in unit of 80MHZ (12.5ns)*****////////
void SysTick_Wait(unsigned long delay){
NVIC_ST_RELOAD_R = delay-1;                           //number of counts
NVIC_ST_CURRENT_R = 0;                                //any value written to current clears
while((NVIC_ST_CTRL_R&0x00010000)==0);                //wait for flag	
}
//////******DEALY fn wait for delay in seconds*******/////////
void delay(unsigned long delay){
unsigned long i;
for(i=0; i<delay; i++){
SysTick_Wait(800000);                                 // wait 10ms >>800000*12.5ns
}
}
