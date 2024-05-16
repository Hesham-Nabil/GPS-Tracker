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
int flag;                                                                   // global variable to be used in the interrupt
void UART0_IRQHandler()                                                     //uart0 interrupt
{
  int max_block = EepromRead(15, 31);                                       //load the block reached from EEPROM
  int max_address = EepromRead(14, 31);                                     //load the address reached from EEPROM
  double memRead = 0;
  char output_buffer[22] = {};
  char points_buffer[22] = {};
  SetBit(UART0_ICR_R, 4);                                                   //clear interrupt
  char x;
  UART0_RECIEVE_CHAR(&x);                                                   //Recieve Char From uart0
  if (x == 'u' || x == 'U')                                                 //check if U or u was sent
  {
    LCD_1602_I2C_Write("Sending..  ");                                      //display 'Sending' on LCD
    delay(100);
    for (int j = max_block; j >= 0; j--)                                    //loop to read the EEPROM
    {
      for (int i = max_address; i >= 0; i--)
      {
        if (i % 2 == 0)                                                     // if the U was sent before the latitude was saved so neglect the longitude of this point
        {
          continue;
        }
        memRead = EepromRead(--i, j) / 100000.0;                            //read the integer longitude from EEPROM and divide with 100000 to get the decimal part
        floatToString(memRead, points_buffer, 10);                          //change th float to string to be transmitted through the uart0
        sprintf(output_buffer, "(%s,", points_buffer);                      //make the buffer string to be "(longitude"
        UART0_TRANSMIT_DATA(output_buffer, 22);                             // send the string through uart0
        memRead = EepromRead(++i, j) / 100000.0;                            //read the integer latitude from EEPROM and divide with 100000 to get the decimal part
        i--;
        floatToString(memRead, points_buffer, 10);                          // change float to string
        sprintf(output_buffer, "%s),", points_buffer);                      //make buffer string ,latitude),
        UART0_TRANSMIT_DATA(output_buffer, 22);                             // send the strng through UART0
        UART0_TRANSMIT_CHAR('\n');                                          // SEND NEW LINE
      }
      max_address = 15;                                                     //max address to loop the other blocks
    }
    LCD_1602_I2C_Write("Done...  ");                                        //display 'DONE' on LCD
    delay(100);
    flag = 0;                                                               //turn off tiva
  }
}
int main(void)
{
  UART0_PORTA_Init();                                                       //intialize Uart0
  SysTick_Init();                                                           //initialize Systick
  GPIO_PortF_Init();                                                        //initialize PortF
  UART1_PORTB_Init();                                                       //initialize UART1
  EepromInit();                                                             //initialize EEPROM
  LED_init();                                                               //initialize LEDS
  Switches_init();                                                          //initialize Swiches
  I2C_Init();                                                               //Initialize I2C
  LCD_1602_I2C_Init();                                                      //Initialize LCD
  const int length = 300;                                                   //Buffer Length for gps start 
  double coordinates[2][2];                                                 //Array for Gps start
  double distance = 0;                                                      //Distance variable =0
  char buffer[length];                                                      //Buffer array to fill with data from GPS
  int Mem_Address;                                                          // variable for memory EEPROM address
  int Mem_Block;                                                            //variable for EEPROM block
  int gps_loop_counter = 0;                                                 //Gps counter
  int counter = 0;                                                          //Counter for calling Gps Start
  flag = 0;                                                                 //Flag on or off program
  UART0_IFLS_R = 0;                                                         //to make the interrupt from 1 char
  __asm(
      "cpsie i");                                                           //global interrupt
  while (1)
  {
    LED_OFF();                                                              // turn off LEDs
    LED_RED_ON();                                                           // Red LED on TO indicate the tiva is off
    if (SW1_Input() == 1)                                                   //if the switch is pressed
    {
      flag = 1;                                                             //flag =1 indicates that the tiva works
      LED_OFF();                                                            //red LED off
      LED_Green_ON();                                                       //Green LED on to indicate the tiva is on
      Mem_Address = 0;                                                      //reset memory address variable
      Mem_Block = 0;                                                        //reset memory block variable
      distance = 0;                                                         //resets distance
      counter = 0;                                                          //resets the counter calling gps start
    }
    while (flag)                                                            //while the flag equals 1 means while the tiva works
    {
      EepromWrite(Mem_Address, 14, 31);                                     //save the current address at block 32 address 15 in EEPROM
      EepromWrite(Mem_Block, 15, 31);                                       //save the current block at block 32 address 16 in EEPROM
      GPS_Start(&distance, coordinates, buffer, gps_loop_counter, counter); //Call GPS start
      counter++;                                                            //increment the counter for calling the Gps Start
      LCD_1602_I2C_Write("Distance..  ");                                   //Display "distance" on LCD
      delay(100);
      LCD_DISPLAY_FLOAT(distance);                                          //DISPLAY THE distance on LCD
      delay(100);
      LCD_1602_I2C_Write("Saving..  ");                                     //Display Saving on LCD
      delay(100);
      if (Mem_Address < 16 )                                                // check that the address always less than 16
      {
        if (Mem_Block == 31 && (Mem_Address == 14))                         //if memory block =32 and memory address=15 break and donot save the coordinate to avoid overwriting the address and block
        {
          flag = 0;                                                         //flag =0 to turn off tiva
          break;                                                            //break to turn off tiva
        }
        EepromWrite(coordinates[0][0] * 100000, Mem_Address, Mem_Block);    //save the coordinate after multiplying by 1000000 as EEPROM save as integer
        EepromWrite(Mem_Address, 14, 31);                                   // Save current address
        EepromWrite(coordinates[0][1] * 100000, ++Mem_Address, Mem_Block);  //save the coordinate after multiplying by 1000000 as EEPROM save as integer
        EepromWrite(Mem_Address, 14, 31);                                   // Save current address
        EepromWrite(coordinates[1][0] * 100000, ++Mem_Address, Mem_Block);  //save the coordinate after multiplying by 1000000 as EEPROM save as integer
        EepromWrite(Mem_Address, 14, 31);                                   // Save current address
        EepromWrite(coordinates[1][1] * 100000, ++Mem_Address, Mem_Block);  //save the coordinate after multiplying by 1000000 as EEPROM save as integer
        EepromWrite(Mem_Address, 14, 31);                                   // Save current address
        Mem_Address++;                                                      //increment the address
      }
      else if (Mem_Block < 32 )                                             //if address go beyond 15 increment the block
      {
        Mem_Block++;                                                        //increment the block
        Mem_Address = 0;                                                    // return address back to zero to loop again 
        EepromWrite(Mem_Block, 15, 31);                                     // save current block
      }
      else
      {
        flag = 0;                                                           //if the EEPROM is full turn off tiva 
        break;                                                              //break to turn off tiva
      }
    }
  }
}
