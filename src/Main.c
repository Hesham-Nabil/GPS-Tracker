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
{
   SysTick_Init();
   GPIO_PortF_Init();
   UART0_PORTA_Init();
   UART1_PORTB_Init();
   EepromInit();
   LED_init();
   Switches_init();
   I2C_Init();
   LCD_1602_I2C_Init();
   const int length = 300;
   double coordinates[3][2];
   double distance = 0;
   char buffer[length];
   char LCD_output_buffer[16] = {};
   char output_buffer[16] = {};
   int fr_part = 0;
   int int_part = 0;
   int gps_loop_counter = 0;
   int address = 0;
   int block = 0;
   int flag = 0;
   double rec = 0;
   while (1)
   {
      LED_OFF();
      LED_RED_ON();
      if (SW1_Input() == '1')
      {
         flag = 1;
         break;
      }
      while (flag)
      {
         LED_OFF();
         LED_Green_ON();
         GPS_Start(&distance, coordinates, buffer, gps_loop_counter);
         /////////////Displaying Distance///////////////
         LCD_1602_I2C_Write("Calculating..  ");
         delay(100);
         LCD_DISPLAY_FLOAT(distance);
         delay(100);

         ///////////////Saving Distance/////////////////
         LCD_1602_I2C_Write("Saving..  ");
         delay(100);
         if (address < 16)
         {
            EepromWrite(coordinates[0][0] * 100000, address, block);
            EepromWrite(coordinates[0][1] * 100000, ++address, block);
            EepromWrite(coordinates[1][0] * 100000, ++address, block);
            EepromWrite(coordinates[1][1] * 100000, ++address, block);
            address++;
         }
         else if (block < 32)
         {
            block++;
            address = 0;
         }
         else
         // break;
         // if (SW2_Input == 1)
         {
            for (int j; j < block; j++)
            {
               for (int i = 0; i < address; i++)
               {
                  rec = EepromRead(i, j) / 100000.0;
                  int_part = ((int)rec);
                  fr_part = (rec - (int)rec) * 1000000;
                  sprintf(output_buffer, "(%d.%d,", int_part, fr_part);
                  UART0_TRANSMIT_DATA(LCD_output_buffer,9);
                  rec = EepromRead(++i, j) / 100000.0;
                  int_part = ((int)rec);
                  fr_part = (rec - (int)rec) * 100000;
                  sprintf(output_buffer, "-%d.%d)", int_part, fr_part);
                  UART0_TRANSMIT_DATA(LCD_output_buffer,10);
                  Uart0_Transmit_CHAR('\n');
               }
            }
            flag = 0;
            break;
         }
      }
   }