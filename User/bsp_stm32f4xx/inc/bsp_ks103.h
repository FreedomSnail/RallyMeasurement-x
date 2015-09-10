
#ifndef _BSP_KS103_H
#define _BSP_KS103_H

//****************************************
// 定义KS10X内部地址
//****************************************

#define SLAVE_ADDRESS1   0xE8    //IIC写入时的地址字节数据，+1为读取
#define SLAVE_ADDRESS2   0xd0
#define SLAVE_ADDRESS3   0xd2
#define SLAVE_ADDRESS4   0xd4
#define SLAVE_ADDRESS5   0xd6
#define SLAVE_ADDRESS6   0xd8
#define SLAVE_ADDRESS7   0xda
#define SLAVE_ADDRESS8   0xdc
#define SLAVE_ADDRESS9   0xde
#define SLAVE_ADDRESS10  0xe0
#define SLAVE_ADDRESS11  0xe2
#define SLAVE_ADDRESS12  0xe4
#define SLAVE_ADDRESS13  0xe6
#define SLAVE_ADDRESS14  0xea
#define SLAVE_ADDRESS15  0xec
#define SLAVE_ADDRESS16  0xee
#define SLAVE_ADDRESS17  0xf8
#define SLAVE_ADDRESS18  0xfa
#define SLAVE_ADDRESS19  0xfc
#define SLAVE_ADDRESS20  0xfe

void bsp_InitKs10x(void);
void Ks10x_WriteByte(u8 SlaveAddress,u8 REG_Address,u8 REG_data);
u8 Ks10x_ReadByte(u8 SlaveAddress,u8 REG_Address);
u16 Read_KS10X(u8 SlaveAddress);
void Change_Addr(u8 OldAdddr,u8 NewAddr);
u16 Read_KS10X_Data(u8 SlaveAddress);
void KS10X_Change_Addr_Init(u8 OldAddr,u8 NewAddr);
#endif
