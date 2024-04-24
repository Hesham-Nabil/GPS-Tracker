#ifndef UART
#define UART
void UART0_PORTA_Init();
void UART1_PORTB_Init();
bool UART1_data_available();
char UART1_read_data();
bool UART0_data_available();
char UART0_read_data();
#endif
