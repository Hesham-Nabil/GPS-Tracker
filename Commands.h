#ifndef Commands
#define Commands

#define ClearReg(Reg,Value)        Reg &=~Value
#define ClearBit(Reg,Bit)    Reg &=~(1<<Bit)
#define GetBit(Reg,Bit)   ((Reg>>Bit)&1)
#define SetReg(Reg,Value)        Reg |= Value
#define SetBit(Reg,Bit)    Reg |= (1<<Bit)
#define ClearAll(Reg)      Reg=0x00000000


#endif