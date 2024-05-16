#include "i2c.h"
#include "UART.h"
#include "tm4c123gh6pm.h"

void I2C_Init()
{
    SYSCTL_RCGCI2C_R = SYSCTL_RCGCI2C_R0;
    SYSCTL_RCGCGPIO_R |= 0x2;     // Enable clock to GPIOB
    GPIO_PORTB_ODR_R |= (1 << 3); // Ensure I2C SDA pin is configured open drain
    GPIO_PORTB_AFSEL_R |= (1 << 3) | 1 << 2;
    GPIO_PORTB_PUR_R |= (1 << 3) | 1 << 2;
    GPIO_PORTB_DEN_R |= (1 << 3) | 1 << 2;
    I2C0_MCR_R = 0x10; // Enable Master function mode
    I2C0_MTPR_R = 0x7; // Clock divider, SCL_PERIOD = 2 × (1 + TPR) × (SCL_LP + SCL_HP) × CLK_PRD
                       // 2 × (1 + I2CMTPR) × (6 + 4) × 1/(SYSCLK)
}

void I2C0_Write_Single(int slave_address, char data)
{
    I2C0_MSA_R = slave_address << 1;
    I2C0_MDR_R = data;
    I2C0_MCS_R = 7; // RUN, START, STOP if bytes_count
    while (I2C0_MCS_R & 1)
        ;
}