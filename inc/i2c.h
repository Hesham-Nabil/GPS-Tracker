#ifndef i2c
#define i2c
void I2C_Init();
void I2C0_Write_Single(int slave_address, char data);
#endif 