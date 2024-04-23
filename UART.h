#ifndef UART
#define UART
void UART_Init(void);
bool UART0_data_available(void);
char UART0_read_data(void);
#endif
