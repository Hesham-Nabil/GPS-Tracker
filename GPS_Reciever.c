#include "UART.h"

char check_logname(){
    char i=0;
    char[] logname = "$GPRMC,";
    while (i<7){
        if (logname[i] != UART0_read_data()){
            i=0;
            break;
        }
        i++;
    }
    return i;
}
