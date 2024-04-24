#include "tm4c123gh6pm.h"
#include "option2_embedded_project"
void RGBLED_Init(void){
SYSCTL_RCGCGPIO_R	|= PF_mask;
while((SYSCTL_RCGCGPIO_R & 0x20)==0)
GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_CR_R   |= 0x0E;
GPIO_PORTF_AMSEL_R &= ~PF123_mask;
GPIO_PORTF_AFSEL_R &= ~PF123_mask;
GPIO_PORTF_PCTL_R &= ~ 0x0000FFF0;
GPIO_PORTF_DIR_R |= PF123_mask;
GPIO_PORTF_DEN_R |= PF123_mask;
GPIO_PORTF_DATA_R &= ~PF123_mask;
}


void SW1_Init(void){

GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
GPIO_PORTF_CR_R   |= PF_SW1_mask;
GPIO_PORTF_AMSEL_R &= ~PF_SW1_mask;
GPIO_PORTF_AFSEL_R &= ~PF_SW1_mask;
GPIO_PORTF_PCTL_R &= ~ 0x000F0000;
GPIO_PORTF_DIR_R &= ~ PF_SW1_mask;
GPIO_PORTF_DEN_R |= PF_SW1_mask;             
GPIO_PORTF_PUR_R &= ~PF_SW1_mask;	
}




unsigned char SW1_Input(void){           //function to dedicate if SW1 is pressed
return GPIO_PORTF_DATA_R & PF_SW1_mask;           
}


void LEDs_output(unsigned char data){       //function to set the color of the LED
	
GPIO_PORTF_DATA_R &= ~ 0x0E;
GPIO_PORTF_DATA_R |= data;
}	


unsigned char button_in1;
unsigned char button_in0;
unsigned char led_color;

 


int main(){
RGBLED_Init();                        //initializing LEDs 
SW1_Init();                           //initializing  SW1 in port F

		

while(1){
button_in1 = SW1_Input() ;	
if ( button_in1 == PF_SW1_mask){                         //if we press on switch 1 
break;
}	

UART_FR_RXFE = 1 ;                                  //stop receiving data from UART 

led_color = 0x02;                                //the color would be red
LEDs_output(led_color);

//describtion : if SW1 is pressed the Red LED will turn on and we will recieve no more data from the GPS

}
