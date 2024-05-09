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
   int fr_part = 0;
   int int_part = 0;
   int gps_loop_counter = 0;
   int address = 0;
   int block = 0;

   while (1)
   {
      GPS_Start(&distance, coordinates, buffer, gps_loop_counter);

      /////////////Displaying Distance///////////////
      LCD_1602_I2C_Write("Calculating..  ");
      delay(100);

      int_part = ((int)distance);
      fr_part = (distance - (int)distance) * 1000;
      sprintf(LCD_output_buffer, "%d.%d", int_part, fr_part);
      LCD_1602_I2C_Write(LCD_output_buffer);
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
         break;
   }
}