#include "EEPROM.h"
#include "Commands.h"
#include "Systick.h"

int EepromTry()
{  SetBit(SYSCTL_RCGCEEPROM_R ,0); // ACTIVATE CLOCK "PAGE559"
	delay(10); // delay 100ms
	while(GetBit(EEPROM_EEDONE_R,0));//estana l7d ma el working bit cleared
		if((GitBit(EEPROM_EESUPP_R,3))  |(GitBit(EEPROM_EESUPP_R,2))) //page 567 PRETERY ERETRY BITS CHECK
		{
			return 0;
		}
	SetBit(SYSCTL_SREEPROM_R,0) ;//Page 334 to reset software of eeprom
	while(Getbit(SYSCTL_PREEPROM_R,0)^0X00) ; //PAGE 422,539
	while(GetBit(EEPROM_EEDONE_R,0));
	
		if((GitBit(EEPROM_EESUPP_R,3))  |(GitBit(EEPROM_EESUPP_R,2))) //page 567 PRETERY ERETRY BITS CHECK
		{
			return 0;
		}
		return 1;
}
void EepromRecovery()
{
	SetBit(EEPROM_EESUPP_R,0);//start bit
while(GetBit(EEPROM_EEDONE_R,0));
}

void EepromInit()
{
	int Success=0;
	Success = EepromTry();
	if(Success);
	else
		EepromRecovery();
}
int EepromRead(unsigned short int Address,unsigned short int Block)
{
	int data;
	EEPROM_EEBLOCK_R = Block;//Block number
	EEPROM_EEOFFSET_R = Address;
	data = EEPROM_EERDWR_R;
	while(GetBit(EEPROM_EEDONE_R,0));
	return data;
}
void EepromWrite(float data, unsigned short int Address,unsigned short int Block)
{
	EEPROM_EEBLOCK_R = Block;//0-31
	EEPROM_EEOFFSET_R =  Address; //0-15
	EEPROM_EERDWR_R = data; 
	while(GetBit(EEPROM_EEDONE_R,0));
}