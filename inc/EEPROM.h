#ifndef EEPROM
#define EEPROM
#include "tm4c123gh6pm.h"
void EepromInit();
char EepromRead(unsigned short int Address,unsigned short int Block);
void EepromWrite(char data, unsigned short int Address,unsigned short int Block);
#endif