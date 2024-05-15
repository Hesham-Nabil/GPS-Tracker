#ifndef Commands
#define Commands
#define ClearReg(Reg,Value)          Reg &=~Value                   //clear hexadecimal value in reg
#define ClearBit(Reg,Bit)            Reg &=~(1<<Bit)                //clear specific bit
#define GetBit(Reg,Bit)              ((Reg>>Bit)&1)                 //get specific bit value
#define SetReg(Reg,Value)            Reg |= Value                   //setting reg with hex value
#define SetBit(Reg,Bit)              Reg |= (1<<Bit)                //setting specific bit
#define ClearAll(Reg)                Reg=0x00000000                 //clearing the register
#define InvertBit(Reg,Bit)           ((Reg>>Bit)^0x01)              //invert specific bit
#define RXFE                         0X10
#define RXFF                         OX40
#define TXFF                         OX20
#define TXFE                         OX80
#endif