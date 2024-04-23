#ifndef UART
#define UART
void UART0_Init();
void UART1_Init();
char UART1_data_available();
char UART1_read_data();
char UART0_data_available();
char UART0_read_data();
#endif
