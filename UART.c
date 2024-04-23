#include "PortsDef.h"
#include <stdbool.h>
#include "Commands.h"
void UART_Init(void){          // function to initialize UART
	SetBit(SYSCTL_RCGCUART_R,0);       //activate UART0
	while(( GetBit(SYSCTL_RCGCUART_R,0)==0));  //waiting for UART0 activation
	//SYSCTL_RCGCGPIO_R |= 0x1;               activate PORT A
	//while((SYSCTL_RCGCGPIO_R & 0x1)==0) ;   waiting for port A activation
	
ClearBit(UART0_CTL_R,0)  ;                 //disabling UART while initializing

//setting baudrate 	
UART0_IBRD_R = 520; // IBRD=int(80000000/(16*9600)) = int (520.8333) (divider for frequency)
UART0_FBRD_R = 53; // FBRD int(0.8333 * 64 +0.5) 
UART0_LCRH_R = 0x0070; // bit 4,5 are set to 11 (binary), which corresponds to an 8-bit word length.
	                     //bit 6 is set to 1 (binary) enabling the FIFO mode for the UART receiver and transmitter

UART0_CTL_R = 0x0301; // enable RXE, TXE and UART 001100000001
SetReg(GPIO_PORTA_AFSEL_R ,0x03); // enable alt function PA0, PA1 ,
                            //Enable AFSEL for UART pins during initialization to configure them for their alternate function as UART RX and TX pins.
GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R&0xFFFFFF00)+0x00000011; //UART for PAO, PA1 
SetReg(GPIO_PORTA_DEN_R,0x03); // enable digital I/O on PA0, PA1
ClearReg(GPIO_PORTA_AMSEL_R ,0x03); // disable analog function on PA0, PA1
}	
//function to  check if there is data recieved from GPS
bool UART0_data_available(void){   
return ((UART0_FR_R & UART_FR_RXFE) ? 1 : 0 ); //if RXFE(Receive FIFO Empty) bit is clear, indicating data has been received so we send 1(true)
}	                                         // if RXFE is set so there is no data available then we send 0(false)
//function to read the data provided by the GPS
char UART0_read_data(void){       // note that the data of the type <char>
while(!(UART0_FR_R & UART_FR_RXFE));  // check if RXFE is empty(0) so the data is avialable  
return (char)(UART0_DR_R & 0xFF);   // we are ANDing the first 8 bits in data reg with 0xFF so we are sending the first 8 bits
}	
