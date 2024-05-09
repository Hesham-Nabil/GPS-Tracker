  //      UART0_TRANSMIT_CHAR('c');
      //      char output_buffer[10];
      //      UART0_TRANSMIT_CHAR('d');
      //  UART0_TRANSMIT_CHAR('\n');
      //  UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/1000) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/100) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/10) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/1) % 10) + 48);
      //  UART0_TRANSMIT_CHAR('.');
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*10)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*100)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*1000)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*10000)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*100000)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*1000000)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR(' ');
      //  UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/1000) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/100) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/10) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/1) % 10) + 48);
      //  UART0_TRANSMIT_CHAR('.');
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*10)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*100)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*1000)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*10000)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*100000)) % 10) + 48);
      //  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*1000000)) % 10) + 48);

      // UART0_TRANSMIT_CHAR('\n');
      // sprintf(buffer, "latitude=%d.%d°", (int)i, j);
      // LCD_1602_I2C_Write(buffer);
      // delay(100);
      // sprintf(buffer, "longitude=%d.%d°", (int)x, y);
      // LCD_1602_I2C_Write(buffer);
      // delay(100);
      // LCD_1602_I2C_Write("Embedded Project ");
      // delay(100);
      // LCD_1602_I2C_Write("GPS Tracker ");
      // delay(100);
// { UART0_RECIEVE_CHAR(&x);
//     EepromWrite(x,0,0);
//   UART0_TRANSMIT_CHAR(EepromRead(0,0));
//   UART0_TRANSMIT_CHAR(EepromRead(0,1));
//   UART0_TRANSMIT_CHAR(EepromRead(0,2));
//   UART0_TRANSMIT_CHAR('1');
//   delay(1000);
//   UART0_RECIEVE_CHAR(&x);
//     EepromWrite(x,0,1);
//   UART0_TRANSMIT_CHAR(EepromRead(0,0));
//   UART0_TRANSMIT_CHAR(EepromRead(0,1));
//   UART0_TRANSMIT_CHAR(EepromRead(0,2));
//   UART0_TRANSMIT_CHAR('2');
//   delay(1000);
//   UART0_RECIEVE_CHAR(&x);
//     EepromWrite(x,0,2);
//     UART0_TRANSMIT_CHAR(EepromRead(0,0));
//   UART0_TRANSMIT_CHAR(EepromRead(0,1));
//   UART0_TRANSMIT_CHAR(EepromRead(0,2));
//   UART0_TRANSMIT_CHAR('3');
//   delay(1000);

//  const int length = 4;
//  char buffer[length];
//  const int L = 3;
//  const int W = 2;
//  double coordinates[L][W];
//  double distance =0;
//  int i = 0 ;
//  char x ;
//  char y ;
//  char z;
//  char f;

// UART0_TRANSMIT_CHAR('1');
//  GPS_Start(&distance,coordinates,buffer,i);
//      UART0_TRANSMIT_CHAR('c');
//      char output_buffer[10];
//      UART0_TRANSMIT_CHAR('d');
//  UART0_TRANSMIT_CHAR('\n');
//  UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/1000) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/100) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/10) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) coordinates[0][0]/1) % 10) + 48);
//  UART0_TRANSMIT_CHAR('.');
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*10)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*100)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*1000)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*10000)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*100000)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][0]*1000000)) % 10) + 48);
//  UART0_TRANSMIT_CHAR(' ');
//  UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/1000) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/100) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/10) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) coordinates[0][1]/1) % 10) + 48);
//  UART0_TRANSMIT_CHAR('.');
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*10)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*100)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*1000)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*10000)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*100000)) % 10) + 48);
//  UART0_TRANSMIT_CHAR((((int) (coordinates[0][1]*1000000)) % 10) + 48);

// UART0_TRANSMIT_CHAR('\n');


 // UART0_TRANSMIT_CHAR('a');
      // GPS_Start(&distance, coordinates, buffer, i);
      // int_part = ((int)distance);
      // fr_part = (distance - (int)distance) * 1000;
      // sprintf(output_buffer, "%d.%d", int_part, fr_part);
      // LCD_1602_I2C_Write(output_buffer);
      // delay(100);


      //parsing function
// $GPRMC,161229.487,A,3723.2475,N,12158.3416,W,0.13,309.62,120598, ,*10
// double coordinates[300][2];      // this line should be written in main before GPS_Start() should be called
// double Distance=0;               // this line should be written in main before GPS_Start() should be called
// int i = 0    
// char buffer[500];                //initialize a buffer with size very very big to be certain that the data is recieved 
//GPS_Start( &Distance,  coordinates, buffer,  i)    //how to call the functiuon in main

//LCD

// void lcd_en(void){
//     LCD_INST |= (1<<En);
//     delay(1);
//     LCD_INST &= ~(1<<En);
// }

// void lcd_inst(char d){
//     LCD_INST &= ~(1<<En);
//     LCD_INST &= ~(1<<RW);
//     LCD_INST &= ~(1<<RS);
//     LCD_DATA = d;
//     lcd_en();
// }

// void lcd_portD_DATA_init(void){
//     SYSCTL_RCGCGPIO_R |= 0x08;
//     while ((SYSCTL_PRGPIO_R & 0x08)==0);
//     GPIO_PORTD_AMSEL_R &= ~LCD_DATA_PIN;
//     GPIO_PORTD_PCTL_R  &= ~0xFFFFFFFF;
//     GPIO_PORTD_AFSEL_R &= ~LCD_DATA_PIN;
//     GPIO_PORTD_DIR_R   |= LCD_DATA_PIN;
//     GPIO_PORTD_DEN_R   |= LCD_DATA_PIN;
//     GPIO_PORTD_DATA_R  &= ~LCD_DATA_PIN;
// }

// void lcd_portE_INST_init(void){
//     SYSCTL_RCGCGPIO_R |= 0x10;
//     while ((SYSCTL_PRGPIO_R & 0x10)==0);
//     GPIO_PORTE_AMSEL_R &= ~LCD_INST_PIN;
//     GPIO_PORTE_PCTL_R  &= ~0x00000FFF;
//     GPIO_PORTE_AFSEL_R &= ~LCD_INST_PIN;
//     GPIO_PORTE_DIR_R   |= LCD_INST_PIN;
//     GPIO_PORTE_DEN_R   |= LCD_INST_PIN;
//     GPIO_PORTE_DATA_R  &= ~LCD_INST_PIN;
// }

// void lcd_init(void){
//     lcd_portD_DATA_init();
//     lcd_portE_INST_init();
//     SET_LCD_DATA |= LCD_DATA_PIN;
//     SET_LCD_INST |= LCD_INST_PIN;
//     lcd_inst(LCD_DISPLAY_ON);
//     lcd_inst(LCD_FSET_8B2L5X10D);
//     lcd_inst(LCD_CLR);
// }

// void lcd_data(char d){
//     LCD_INST &= ~(1<<En);
//     LCD_INST &= ~(1<<RW);
//     LCD_INST |= (1<<RS);
//     LCD_DATA = d;
//     lcd_en();
// }

// void lcd_str(const char *d){//ex: lcd_str("Hello world")
//     char i=0;
//     while(d[i]!='\0'){
//         lcd_data(d[i]);
//         i++;
//     }
// }