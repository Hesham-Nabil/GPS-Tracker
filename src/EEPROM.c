#include "EEPROM.h"
#include "Commands.h"
#include "Systick.h"
#include "UART.h"
int EepromTry()
{
	SetBit(SYSCTL_RCGCEEPROM_R, 0); 											// ACTIVATE CLOCK "PAGE559"
	delay(10);																	// delay 100ms

	while (GetBit(EEPROM_EEDONE_R, 0))
		;															 			// WAIT TILL  working bit cleared
	if ((GetBit(EEPROM_EESUPP_R, 3)) | (GetBit(EEPROM_EESUPP_R, 2))) 			// page 567 PRETERY ERETRY BITS CHECK
	{

		return 0;
	}
	return 1;
}
void EepromRecovery()
{
	SetBit(EEPROM_EESUPP_R, 0); 												//set  start bit

	while (GetBit(EEPROM_EEDONE_R, 0))											//wait till done bit equals 1
		;
}

void EepromInit()
{
	int Success = 0;															// declare variable called success
	Success = EepromTry();														//if eeprom initialized without problems it will be 1

	if (Success)   																//if eeprom initialized successfully, return back to main else recover the problem
		;
	else
		EepromRecovery();
}
int EepromRead(unsigned short int Address, unsigned short int Block)
{
	EEPROM_EEBLOCK_R = Block; 													// Block number 0-->31
	EEPROM_EEOFFSET_R = Address;												//address number 0-->15
	while (GetBit(EEPROM_EEDONE_R, 0))											// wait till done bit equals 1
		;
	return EEPROM_EERDWR_R; 													//return data from this register
}
void EepromWrite(int data, unsigned short int Address, unsigned short int Block)
{
	EEPROM_EEBLOCK_R = Block;	 												// block number 0-31
	EEPROM_EEOFFSET_R = Address; 												// address number 0-15
	EEPROM_EERDWR_R = data;  													// write data in this register
	while (GetBit(EEPROM_EEDONE_R, 0))											//wait till done bit equals 1
		;
}