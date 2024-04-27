#ifndef UART
#define UART
void UART0_PORTA_Init();
void UART1_PORTB_Init();
char UART0_RECIEVE_CHAR();
void UART0_TRANSMIT_CHAR(char data);
char UART1_RECIEVE_CHAR();
void UART1_TRANSMIT_CHAR(char data);
void UART0_RECIEVE_DATA(char* buffer);
#endif
