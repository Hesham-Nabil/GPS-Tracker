#include "EEPROM.h"
#include "Commands.h"
#include "Systick.h"
#include "UART.h"
int EepromTry()
{  SetBit(SYSCTL_RCGCEEPROM_R ,0); // ACTIVATE CLOCK "PAGE559"
	delay(10); // delay 100ms
	UART0_TRANSMIT_CHAR('1');
	while(GetBit(EEPROM_EEDONE_R,0));//estana l7d ma el working bit cleared
		if((GetBit(EEPROM_EESUPP_R,3))  |(GetBit(EEPROM_EESUPP_R,2))) //page 567 PRETERY ERETRY BITS CHECK
		{ UART0_TRANSMIT_CHAR('2');

			return 0;
		}
		UART0_TRANSMIT_CHAR('3');
	SetBit(SYSCTL_SREEPROM_R,0) ;//Page 334 to reset software of eeprom
	delay(10);
	SYSCTL_SREEPROM_R = 0;
	while(GetBit(EEPROM_EEDONE_R,0));
	UART0_TRANSMIT_CHAR('4');
		if((GetBit(EEPROM_EESUPP_R,3))  |(GetBit(EEPROM_EESUPP_R,2))) //page 567 PRETERY ERETRY BITS CHECK
		{UART0_TRANSMIT_CHAR('5');
			return 0;
		}
		return 1;
}
void EepromRecovery()
{
	SetBit(EEPROM_EESUPP_R,0);//start bit
	UART0_TRANSMIT_CHAR('6');
while(GetBit(EEPROM_EEDONE_R,0));
}

void EepromInit()
{
	int Success=0;
	Success = EepromTry();

	if(Success)UART0_TRANSMIT_CHAR('7');
	else
		EepromRecovery();
}
char EepromRead(unsigned short int Address,unsigned short int Block)
{
	int data;
	EEPROM_EEBLOCK_R = Block;//Block number
	EEPROM_EEOFFSET_R = Address;
	data = EEPROM_EERDWR_R;
	while(GetBit(EEPROM_EEDONE_R,0));
	return data;
}
void EepromWrite(char data, unsigned short int Address,unsigned short int Block)
{
	EEPROM_EEBLOCK_R = Block;//0-31
	EEPROM_EEOFFSET_R =  Address; //0-15
	EEPROM_EERDWR_R = data; 	
	while(GetBit(EEPROM_EEDONE_R,0));
}