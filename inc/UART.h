#ifndef UART
#define UART
void UART0_PORTA_Init();
void UART1_PORTB_Init();
int  UART0_RECIEVE_CHAR(char* destination);
int  UART1_RECIEVE_CHAR(char *destination);
void UART0_TRANSMIT_CHAR(char data);
void UART1_TRANSMIT_CHAR(char data);
void UART1_RECIEVE_DATA(char* buffer);
void UART0_RECIEVE_DATA(char* buffer);
#endif
