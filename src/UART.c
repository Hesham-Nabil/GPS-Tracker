#include "tm4c123gh6pm.h"
#include "Commands.h"

void UART0_PORTA_Init()
{                                                                           // function to initialize UART
  SetBit(SYSCTL_RCGCUART_R, 0);                                             // activate UART0
  while ((GetBit(SYSCTL_PRUART_R, 0) == 0))
    ;                                                                       // waiting for UART0 activation
  SetBit(SYSCTL_RCGCGPIO_R, 0);                                             // activate PORT A
  while ((SYSCTL_PRGPIO_R & 0x1) == 0)
    ;                                                                       // waiting for port A activation
  ClearBit(UART0_CTL_R, 0);                                                 // disabling UART while initializing
  UART0_IBRD_R = 104;                                                       // IBRD=int(16000000/(16*9600)) = int (104.16667) (divider for frequency)
  UART0_FBRD_R = 11;                                                        // FBRD int(0.16667 * 64 +0.5)
  UART0_LCRH_R = 0x0070;                                                    // bit 4,5 are set to 11, which corresponds to an 8-bit word length, bit 6 is set to 1 enabling the FIFO for the UART RX & TX
  UART0_IM_R |= (1 << 4);                                                   // To mask RX page 924
  NVIC_EN0_R |= (1 << 5);                                                   // Uart0 IRQ = 5 
  UART0_CTL_R = 0x0301;                                                     // enable RXE, TXE and UART 001100000001
  SetReg(GPIO_PORTA_AFSEL_R, 0x03);                                         // enable alt function PA0 (), PA1 (),as UART RX and TX
  ClearReg(GPIO_PORTA_AMSEL_R, 0x03);                                       // disable analog function on PA0, PA1
  GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;        // UART for PAO, PA1
  SetReg(GPIO_PORTA_DEN_R, 0x03);                                           // enable digital I/O on PA0, PA1
}
void UART1_PORTB_Init()
{                                                                           // function to initialize UART1
  SetBit(SYSCTL_RCGCUART_R, 1);                                             // activate UART1
  while ((GetBit(SYSCTL_PRUART_R, 1) == 0))
    ;                                                                       // waiting for UART1 activation
  SetBit(SYSCTL_RCGCGPIO_R, 1);                                             // activate PORT B
  while ((SYSCTL_PRGPIO_R & 0x2) == 0)
    ;                                                                       // waiting for port B activation
  ClearBit(UART1_CTL_R, 0);                                                 // disabling UART while initializing
  UART1_IBRD_R = 104;                                                       // IBRD=int(16000000/(16*9600)) = int (104.16667) (divider for frequency)
  UART1_FBRD_R = 11;                                                        // FBRD int(0.16667 * 64 +0.5)
  UART1_LCRH_R = 0x0070;                                                    // bit 4,5 are set to 11, which corresponds to an 8-bit word length, bit 6 is set to 1 enabling the FIFO for the UART RX & TX
  UART1_CTL_R = 0x0301;                                                     // enable RXE, TXE and UART 001100000001
  SetReg(GPIO_PORTB_AFSEL_R, 0x03);                                         // enable alt function PB0 (), PB1 (),as UART RX and TX
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R & 0xFFFFFF00) + 0x00000011;        // UART for PBO, PB1
  SetReg(GPIO_PORTB_DEN_R, 0x03);                                           // enable digital I/O on PB0, PB1
  ClearReg(GPIO_PORTB_AMSEL_R, 0x03);                                       // disable analog function on PB0, PB1
}

int UART0_RECIEVE_CHAR(char *destination)
{
  int i;
  for (i = 0; i < 10000; i++)                                               // For Loop to avoid stuck in the loop if nothing was received
  {
    if ((UART0_FR_R & 0x10) == 0)                                           // Check if FIFO is full.
    {
      *destination = (char)(UART0_DR_R & 0xFF);                             // Store received byte.
      return (int)1;                                                        // Return success.
    }
  }
  return (int)0;                                                            //Return Fail
}

int UART1_RECIEVE_CHAR(char *destination)
{
  int i;
  for (i = 0; i < 10000; i++)                                               // For Loop to avoid stuck in the loop if nothing was received
  {
    if ((UART1_FR_R & 0x10) == 0)                                           // Check if FIFO is full.
    {
      *destination = (char)(UART1_DR_R & 0xFF);                             // Store received byte.
      return (int)1;                                                        // Return success.
    }
  }
  return (int)0;                                                            //Return Fail
}

void UART0_RECIEVE_DATA(char *buffer, int length)
{

  for (int i = 0; i < length; i++)                                          // for loop to fill the buffer
  {
    if (UART0_RECIEVE_CHAR(buffer + i))                                     // if the receiving success it will save the char in the buffer element
      continue;
    else
    {
      i--;                                                                  // if failed, return to the element that was failed
    }
  }
}

void UART1_RECIEVE_DATA(char *buffer, int length)
{

  for (int i = 0; i < length; i++)                                          // for loop to fill the buffer
  {
    if (UART1_RECIEVE_CHAR(buffer + i))                                     // if the receiving success it will save the char in the buffer element
      continue;
    else
    {
      i--;                                                                  // if failed, return to the element that was failed
    }
  }
}

void UART0_TRANSMIT_CHAR(char data)
{                                                                           // UART0 function to send data
  while (UART0_FR_R & 0X020)
    ;                                                                       // wait until the buffer becomes empty to send data on the buffer
  UART0_DR_R = data;                                                        // write data on the buffer
}



void UART1_TRANSMIT_CHAR(char data)
{                                                                           // UART1 function to send data
  if (UART1_FR_R & 0X020 != 0)
    ;                                                                       // wait until the buffer becomes empty to send data on the buffer
  UART1_DR_R = data;                                                        // write data on the buffer
}

void UART0_TRANSMIT_DATA(char *data, int length)
{
  for (int j = 0; j < length; j++)                                          // For loop to transmit String through UART0  
    UART0_TRANSMIT_CHAR(data[j]);
}

void UART1_TRANSMIT_DATA(char *data, int length)
{
  for (int j = 0; j < length; j++)                                          // For loop to transmit String through UART1 
    UART1_TRANSMIT_CHAR(data[j]);
}


