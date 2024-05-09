#ifndef EEPROM
#define EEPROM
#include "tm4c123gh6pm.h"
void EepromInit();
int EepromRead(unsigned short int Address,unsigned short int Block);
void EepromWrite(int data, unsigned short int Address,unsigned short int Block);
#endif