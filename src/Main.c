#include "tm4c123gh6pm.h"
#include "UART.h"
#include "GPS_Reciever.h"
#include "GPIO.h"
#include "Math_Functions.h"
#include "Systick.h"
#include "EEPROM.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "LCD.h"
#include "i2c.h"
#include "Commands.h"
int flag;
void UART0_IRQHandler()
{
  int max_block = EepromRead(15, 31);
  int max_address = EepromRead(14, 31);
  double memRead = 0;
  int fr_part = 0;
  int int_part = 0;
  char output_buffer[22] = {};
  char points_buffer[22]={};
  SetBit(UART0_ICR_R, 4);
  char x;
  UART0_RECIEVE_CHAR(&x);
  if (x == 'u' || x == 'U')
  {
    LCD_1602_I2C_Write("Sending..  ");
    delay(100);
    for (int j = max_block; j >= 0; j--)
    {
      for (int i = max_address; i >= 0; i--)
      {
        if (i % 2 == 0)
        {
          continue;
        }

        memRead = EepromRead(--i, j) /100000.0;
        floatToString(memRead, points_buffer, 10);
       sprintf(output_buffer ,"(%s,", points_buffer);
        UART0_TRANSMIT_DATA(output_buffer,22 );
        memRead = EepromRead(++i, j) / 100000.0;
        i--;
        floatToString(memRead, points_buffer, 10);
        sprintf(output_buffer, "%s),", points_buffer);
        UART0_TRANSMIT_DATA(output_buffer, 22);
        UART0_TRANSMIT_CHAR('\n');
      }
      max_address = 15;
    }
    LCD_1602_I2C_Write("Done...  ");
    delay(100);
    flag = 0;
  }
}
int main(void)
{
  UART0_PORTA_Init();
  SysTick_Init();
  GPIO_PortF_Init();
  UART1_PORTB_Init();
  EepromInit();
  LED_init();
  Switches_init();
  I2C_Init();
  LCD_1602_I2C_Init();
  const int length = 300;
  double coordinates[2][2];
  double distance = 0;
  char buffer[length];
  char LCD_output_buffer[16] = {};
  char output_buffer[16] = {};
  int Mem_Address;
  int Mem_Block;
  int gps_loop_counter = 0;
  int counter =0;
  flag = 0;

  UART0_IFLS_R = 0;
  __asm(
      "cpsie i");
    
   while (1)
   {  
     LED_OFF();
    LED_RED_ON();
    if (SW1_Input() == 1)
    {
      flag = 1;
      LED_OFF();
      LED_Green_ON();
      Mem_Address = 0;
      Mem_Block = 0;
      distance=0;
      counter=0;
    }
    while (flag)
    {
      EepromWrite(Mem_Address, 14, 31);
      EepromWrite(Mem_Block, 15, 31);
      GPS_Start(&distance, coordinates, buffer, gps_loop_counter,counter);
      counter++;
      //    /////////////Displaying Distance///////////////
      LCD_1602_I2C_Write("Distance..  ");
      delay(100);
      LCD_DISPLAY_FLOAT(distance);
      delay(100);
  //     ///////////////Saving Distance/////////////////

      LCD_1602_I2C_Write("Saving..  ");
      delay(100);
      if (Mem_Address < 16 && SW2_Input() == 0) //& SW2_Input() == 1
      {
        if (Mem_Block == 31 && (Mem_Address == 14))
        {
          flag = 0;
          break;
        }
        EepromWrite(coordinates[0][0] * 100000, Mem_Address, Mem_Block);
        EepromWrite(Mem_Address, 14, 31);
        EepromWrite(coordinates[0][1] * 100000, ++Mem_Address, Mem_Block);
        EepromWrite(Mem_Address, 14, 31);
        EepromWrite(coordinates[1][0] * 100000, ++Mem_Address, Mem_Block);
        EepromWrite(Mem_Address, 14, 31);
        EepromWrite(coordinates[1][1] * 100000, ++Mem_Address, Mem_Block);
        EepromWrite(Mem_Address, 14, 31);
        Mem_Address++;
      }
      else if (Mem_Block < 32 && SW2_Input() == 0)
      {
        Mem_Block++;
        Mem_Address = 0;
        EepromWrite(Mem_Block, 15, 31);
      }
      else
      {
        flag = 0;
        break;
      }
    }
  }
}
