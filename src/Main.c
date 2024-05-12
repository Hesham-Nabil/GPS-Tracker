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
#include "Commands.h"

// acknowledge
//       double memRead = 0;
//       int fr_part = 0;
//       int int_part = 0;
//       for (int j; j < Mem_Block; j++)
//       {
//          for (int i = 0; i < Mem_Address; i++)
//          {
//             memRead = EepromRead(i, j) / 100000.0;
//             int_part = ((int)memRead);
//             fr_part = (memRead - (int)memRead) * 100000;
//             sprintf(output_buffer, "(%d.%d,", int_part, fr_part);
//             UART0_TRANSMIT_DATA(output_buffer, 9);
//             memRead = EepromRead(++i, j) / 100000.0;
//             int_part = ((int)memRead);
//             fr_part = (memRead - (int)memRead) * 100000;
//             sprintf(output_buffer, "-%d.%d)", int_part, fr_part);
//             UART0_TRANSMIT_DATA(output_buffer, 10);
//             UART0_TRANSMIT_CHAR('\n');
//          }
//       }
//    }
// }

int main(void)
{
   SysTick_Init();
   GPIO_PortF_Init();
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
 int Mem_Address;
 int Mem_Block;
   int gps_loop_counter = 0;
   int flag = 0;
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
      }
      while (flag)
      {
         EepromWrite(Mem_Address, 14, 31);
         EepromWrite(Mem_Block, 15, 31);
         GPS_Start(&distance, coordinates, buffer, gps_loop_counter);
         /////////////Displaying Distance///////////////
         LCD_1602_I2C_Write("Calculating..  ");
         delay(100);
         LCD_DISPLAY_FLOAT(distance);
         delay(100);
         ///////////////Saving Distance/////////////////
         LCD_1602_I2C_Write("Saving..  ");
         delay(100);
         if (Mem_Address < 16) //& SW2_Input() == 1
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
         else if (Mem_Block < 32)
         {
            Mem_Block++;
            Mem_Address = 0;
            EepromWrite(Mem_Block, 15, 31);
         }
         else
         {  int max_block=EepromRead(15,31);
            int max_address=EepromRead(14,31);
            double memRead = 0;
            int fr_part = 0;
            int int_part = 0;
            for (int j; j < max_block; j++)
            {
               for (int i = 0; i < max_address; i++)
               {
                  memRead = EepromRead(i, j) / 100000.0;
                  int_part = ((int)memRead);
                  fr_part = (memRead - (int)memRead) * 100000;
                  sprintf(output_buffer, "(%d.%d,", int_part, fr_part);
                  UART0_TRANSMIT_DATA(output_buffer, 9);
                  memRead = EepromRead(++i, j) / 100000.0;
                  int_part = ((int)memRead);
                  fr_part = (memRead - (int)memRead) * 100000;
                  sprintf(output_buffer, "-%d.%d)", int_part, fr_part);
                  UART0_TRANSMIT_DATA(output_buffer, 10);
                  UART0_TRANSMIT_CHAR('\n');

                  flag = 0;
                  break;
               }
            }
         }
      }
   }
}
// double memRead = 0;
//          int fr_part = 0;
//          int int_part = 0;
// memRead = EepromRead(i, j) / 100000.0;
//                int_part = ((int)memRead);
//                fr_part = (memRead - (int)memRead) * 1000000;
//                sprintf(output_buffer, "(%d.%d,", int_part, fr_part);
//                UART0_TRANSMIT_DATA(LCD_output_buffer, 9);
//                memRead = EepromRead(++i, j) / 100000.0;
//                int_part = ((int)memRead);
//                fr_part = (memRead - (int)memRead) * 100000;
//                sprintf(output_buffer, "-%d.%d)", int_part, fr_part);
//                UART0_TRANSMIT_DATA(LCD_output_buffer, 10);
//                Uart0_Transmit_CHAR('\n');