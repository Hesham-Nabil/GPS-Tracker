#ifndef UART
#define UART
void UART0_Init();
void UART1_Init();
bool UART1_data_available();
char UART1_read_data();
bool UART0_data_available();
char UART0_read_data();
#endif
