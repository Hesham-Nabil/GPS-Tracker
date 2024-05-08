#include "tm4c123gh6pm.h"
#include "UART.h"
#include "GPS_Reciever.h"
#include "GPIO.h"
#include "Systick.h"
#include "EEPROM.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LCD.h"
#include "i2c.h"

int main(void)
{   SysTick_Init();
    GPIO_PortF_Init();
    UART0_PORTA_Init();
    UART1_PORTB_Init();
    EepromInit();
    LED_init();
    Switches_init();
    I2C_Init();
    LCD_1602_I2C_Init();
    float x = 332.19;
    int y = ( x - (int) x )*100;
    float i = 720.75;
    int j = ( i - (int) i )*100;
    char buffer[17]={};
    while (1) {
    sprintf(buffer ,"latitude=%d.%d°", (int)i ,j);
    LCD_1602_I2C_Write(buffer);
    delay(100);
    sprintf(buffer ,"longitude=%d.%d°", (int)x ,y);
    LCD_1602_I2C_Write(buffer);
    delay(100);
    LCD_1602_I2C_Write("Embedded Project ");
    delay(100);
    LCD_1602_I2C_Write("GPS Tracker ");
    delay(100);
    }                  
 }



// { UART0_RECIEVE_CHAR(&x);
//     EepromWrite(x,0,0);
//   UART0_TRANSMIT_CHAR(EepromRead(0,0));
//   UART0_TRANSMIT_CHAR(EepromRead(0,1));
//   UART0_TRANSMIT_CHAR(EepromRead(0,2));
//   UART0_TRANSMIT_CHAR('1');
//   delay(1000); 
//   UART0_RECIEVE_CHAR(&x);
//     EepromWrite(x,0,1);
//   UART0_TRANSMIT_CHAR(EepromRead(0,0));
//   UART0_TRANSMIT_CHAR(EepromRead(0,1));
//   UART0_TRANSMIT_CHAR(EepromRead(0,2));
//   UART0_TRANSMIT_CHAR('2');
//   delay(1000); 
//   UART0_RECIEVE_CHAR(&x);
//     EepromWrite(x,0,2);
//     UART0_TRANSMIT_CHAR(EepromRead(0,0));
//   UART0_TRANSMIT_CHAR(EepromRead(0,1));
//   UART0_TRANSMIT_CHAR(EepromRead(0,2));
//   UART0_TRANSMIT_CHAR('3');
//   delay(1000); 




//  const int length = 4;
   //  char buffer[length]; 
   //  const int L = 3;
   //  const int W = 2;
   //  double coordinates[L][W];
   //  double distance =0;
   //  int i = 0 ;  
   //  char x ;    
   //  char y ; 
   //  char z;
   //  char f;

//UART0_TRANSMIT_CHAR('1');
// GPS_Start(&distance,coordinates,buffer,i);
//     UART0_TRANSMIT_CHAR('c');
//     char output_buffer[10];
//     UART0_TRANSMIT_CHAR('d');
// UART0_TRANSMIT_CHAR('\n');
// UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/1000) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/100) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/10) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/1) % 10) + 48);
// UART0_TRANSMIT_CHAR('.');
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*10)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*100)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*1000)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*10000)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*100000)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*1000000)) % 10) + 48);
// UART0_TRANSMIT_CHAR(' ');
// UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/1000) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/100) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/10) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/1) % 10) + 48);
// UART0_TRANSMIT_CHAR('.');
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*10)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*100)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*1000)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*10000)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*100000)) % 10) + 48);
// UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*1000000)) % 10) + 48);

// UART0_TRANSMIT_CHAR('\n'); 