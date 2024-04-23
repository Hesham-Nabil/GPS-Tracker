#include "UART.h"

char check_logname(void){
    char i=0;
    char logname[] = "$GPRMC,";
    while (i<7){
        if (logname[i] != UART0_read_data()){
            i=0;
            break;
        }
        i++;
    }
    return i;
}

void getGpsData(void){
    char data = UART0_read_data();
    char i = 0;
    while (data!='*'){
        GPS_data[i] = data;
        data = UART0_read_data();

        if(i>=80) break;

        i++;
    }
}
