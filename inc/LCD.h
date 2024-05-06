#ifndef _LCD_
#define _LCD_

#define SET_LCD_DATA GPIO_PORTD_DIR_R
#define SET_LCD_INST GPIO_PORTE_DIR_R
#define LCD_DATA GPIO_PORTD_DATA_R
#define LCD_INST GPIO_PORTE_DATA_R
#define En 0 //En pin
#define RW 1 //RW pin
#define RS 2 //RS pin
#define LCD_DATA_PIN (0xff)
#define LCD_INST_PIN ((1<<En)|(1<<RW)|(1<<RS))
#define LCD_DISPLAY_ON (0x0d)
#define LCD_FSET_8B2L5X10D (0x3f)
#define LCD_CLR (0x01)
#define LCD_HOME (0x02)

void lcd_en(void);
void lcd_inst(char d); //for sending instructions ex: clear display, change cursor, etc.
void lcd_portD_DATA_init(void);
void lcd_portE_INST_init(void);
void lcd_init(void); //lcd initialization: 8 data pins in port D & first 3 pins in port E
void lcd_data(char d); //display one character
void lcd_str(const char *d); //display string

#endif
