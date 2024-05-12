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

/// Global Variables ////////////////

////////////////////////////////////

void UART0_Handler()
{
   UART0_TRANSMIT_CHAR('1');
   if (GetBit(UART0_MIS_R, 4))
   {
      UART0_TRANSMIT_CHAR('2');
      SetBit(UART0_ICR_R, 4);
      char d;
      UART0_RECIEVE_CHAR(&d);
      if (d == 'U' | 'u')
      {
         UART0_TRANSMIT_CHAR('a');
      }
   }
}
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
   UART0_PORTA_Init();
   ///////////////////////////Enabling Interrupts/////////////////////
   SetBit(UART0_IM_R, 4);                                // enable interrupt for PA0
   NVIC_EN0_R |= (1 << 5);                               // Enable interrupt number 0 (UART0)
   NVIC_PRI1_R |= (NVIC_PRI0_R & 0xFFFF00FF) | (1 << 5); // Set priority level 1 for UART0 interrupt
   GPIO_PORTA_IS_R = ~0X03;
   GPIO_PORTA_IBE_R = ~0X03;
   GPIO_PORTA_IEV_R = ~0X03;
   GPIO_PORTA_IM_R = ~0X03;
   NVIC_PRI0_R |= (1 << 6);
   NVIC_EN0_R |= 1;
   UART0_IFLS_R = 0;
   __asm(
       "cpsie i");
   // must be written in assembly            // Enable interrupts globally
   ///////////////////////////////////////////////////////////////////
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

   int gps_loop_counter = 0;
   int flag = 0;
   while (1)
   {
      UART0_TRANSMIT_CHAR('b');
   }

   //    LED_OFF();
   //    LED_RED_ON();
   //    if (SW1_Input() == 1)
   //    {
   //       flag = 1;
   //       LED_OFF();
   //       LED_Green_ON();
   //       int Mem_Address = 0;
   //       int Mem_Block = 0;
   //    }
   //    while (flag)
   //    {

   //       GPS_Start(&distance, coordinates, buffer, gps_loop_counter);
   //       /////////////Displaying Distance///////////////
   //       LCD_1602_I2C_Write("Calculating..  ");
   //       delay(100);
   //       LCD_DISPLAY_FLOAT(distance);
   //       delay(100);

   //       ///////////////Saving Distance/////////////////
   //       LCD_1602_I2C_Write("Saving..  ");
   //       delay(100);
   //       if (Mem_Address < 16)
   //       {
   //          EepromWrite(coordinates[0][0] * 100000, Mem_Address, Mem_Block);
   //          EepromWrite(coordinates[0][1] * 100000, ++Mem_Address, Mem_Block);
   //          EepromWrite(coordinates[1][0] * 100000, ++Mem_Address, Mem_Block);
   //          EepromWrite(coordinates[1][1] * 100000, ++Mem_Address, Mem_Block);
   //          Mem_Address++;
   //       }
   //       else if (Mem_Block < 32)
   //       {
   //          Mem_Block++;
   //          Mem_Address = 0;
   //       }
   //       else
   //          break;
   //    }
   // }
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