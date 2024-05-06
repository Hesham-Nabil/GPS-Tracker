#include "tm4c123gh6pm.h"
#include "Systick.h"
#include "LCD.h"

void lcd_en(void){
    LCD_INST |= (1<<En);
    delay(1);
    LCD_INST &= ~(1<<En);
}

void lcd_inst(char d){
    LCD_INST &= ~(1<<En);
    LCD_INST &= ~(1<<RW);
    LCD_INST &= ~(1<<RS);
    LCD_DATA = d;
    lcd_en();
}

void lcd_portD_DATA_init(void){
    SYSCTL_RCGCGPIO_R |= 0x08;
    while ((SYSCTL_PRGPIO_R & 0x08)==0);
    GPIO_PORTD_AMSEL_R &= ~LCD_DATA_PIN;
    GPIO_PORTD_PCTL_R  &= ~0xFFFFFFFF;
    GPIO_PORTD_AFSEL_R &= ~LCD_DATA_PIN;
    GPIO_PORTD_DIR_R   |= LCD_DATA_PIN;
    GPIO_PORTD_DEN_R   |= LCD_DATA_PIN;
    GPIO_PORTD_DATA_R  &= ~LCD_DATA_PIN;
}

void lcd_portE_INST_init(void){
    SYSCTL_RCGCGPIO_R |= 0x10;
    while ((SYSCTL_PRGPIO_R & 0x10)==0);
    GPIO_PORTE_AMSEL_R &= ~LCD_INST_PIN;
    GPIO_PORTE_PCTL_R  &= ~0x00000FFF;
    GPIO_PORTE_AFSEL_R &= ~LCD_INST_PIN;
    GPIO_PORTE_DIR_R   |= LCD_INST_PIN;
    GPIO_PORTE_DEN_R   |= LCD_INST_PIN;
    GPIO_PORTE_DATA_R  &= ~LCD_INST_PIN;
}

void lcd_init(void){
    lcd_portD_DATA_init();
    lcd_portE_INST_init();
    SET_LCD_DATA |= LCD_DATA_PIN;
    SET_LCD_INST |= LCD_INST_PIN;
    lcd_inst(LCD_DISPLAY_ON);
    lcd_inst(LCD_FSET_8B2L5X10D);
    lcd_inst(LCD_CLR);
}

void lcd_data(char d){
    LCD_INST &= ~(1<<En);
    LCD_INST &= ~(1<<RW);
    LCD_INST |= (1<<RS);
    LCD_DATA = d;
    lcd_en();
}

void lcd_str(const char *d){//ex: lcd_str("Hello world")
    char i=0;
    while(d[i]!='\0'){
        lcd_data(d[i]);
        i++;
    }
}
