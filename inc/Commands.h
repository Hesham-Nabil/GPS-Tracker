#ifndef Commands
#define Commands
#define ClearReg(Reg,Value)          Reg &=~Value
#define ClearBit(Reg,Bit)            Reg &=~(1<<Bit)
#define GetBit(Reg,Bit)              ((Reg>>Bit)&1)
#define SetReg(Reg,Value)            Reg |= Value
#define SetBit(Reg,Bit)              Reg |= (1<<Bit)
#define ClearAll(Reg)                Reg=0x00000000
#define InvertBit(Reg,Bit)           ((Reg>>Bit)^0x01)
#define RXFE                         0X10
#define RXFF                         OX40
#define TXFF                         OX20
#define TXFE                         OX80
#endif