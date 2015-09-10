/****************************************Copyright(c)********************************************
**
**                            2015-2023, Guangzhou TX-Aviation Technology Co.Ltd.
**
**----------------------------------------File Info----------------------------------------------
** File name : bsp_ks103.c
** Latest modified date :
** Latest version :
** Description :
**-----------------------------------------------------------------------------------------------
** Created by : Luzhi
** Created date :2015��7��12��16:43:54
** Version :V1.0
** Description :
**-----------------------------------------------------------------------------------------------
** Modified by :
** Modified date :
** Version :
** Description :
************************************************************************************************/
#include "bsp.h"
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :

************************************************************************************************/

void delay_us(u16 time)
{
	u16 i,j;
	for(i=0;i<time;i++){
		for(j=0;j<30;j++);
	}
}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :

************************************************************************************************/

void delay_ms(u16 time)
{
	u16 i;
	for(i=0;i<time;i++){
		delay_us(100);
	}
}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :

************************************************************************************************/
void bsp_InitKs10x(void)
{
	
}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :
��I2C�豸��ȡһ���ֽ�����
************************************************************************************************/

u8 Ks10x_ReadByte(u8 SlaveAddress,u8 REG_Address)
{
    u8 REG_data=0;
	i2c_Start();   
	i2c_SendByte(SlaveAddress);
	i2c_WaitAck();
	i2c_SendByte(REG_Address);
	i2c_WaitAck();
	i2c_Start();
	i2c_SendByte(SlaveAddress+1);
	i2c_WaitAck();
	delay_us(50);
	REG_data=i2c_ReadByte(0);
    i2c_Stop(); 
	return REG_data;
}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :

************************************************************************************************/
void Ks10x_WriteByte(u8 SlaveAddress,u8 REG_Address,u8 REG_data)
{      
    i2c_Start();                    //��ʼ�ź�
    i2c_SendByte(SlaveAddress);   //�����豸��ַ+д�ź�
	i2c_WaitAck();
	i2c_SendByte(REG_Address);    //�ڲ��Ĵ�����ַ
	i2c_WaitAck();     
	i2c_SendByte(REG_data);       //�ڲ��Ĵ�������
	i2c_WaitAck();      
	i2c_Stop();                     //����ֹͣ�ź�
}         

/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :

************************************************************************************************/
u16 Read_KS10X(u8 SlaveAddress)
{   
	u16 sum;
	sum=Ks10x_ReadByte(SlaveAddress,0x02);             //��8λ
	sum<<=8;
	sum+=Ks10x_ReadByte(SlaveAddress,0x03);                //��8λ
	return sum;

}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :

************************************************************************************************/
void Change_Addr(u8 OldAdddr,u8 NewAddr)
{
	Ks10x_WriteByte(OldAdddr,0x02,0x9a);             //Ĭ��ԭ��ַ��0x00;
	delay_ms(10);
	Ks10x_WriteByte(OldAdddr,0x02,0x92);
	delay_ms(10);
	Ks10x_WriteByte(OldAdddr,0x02,0x9e);
	delay_ms(10);
	Ks10x_WriteByte(OldAdddr,0x02,NewAddr);
	delay_ms(200);
}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :

************************************************************************************************/
u16 Read_KS10X_Data(u8 SlaveAddress)
{
	u16 Distance;
	
    Ks10x_WriteByte(SlaveAddress,0x02,0xb0);
	delay_ms(50);
    //Distance=Read_KS10X(SlaveAddress);          //������һ��������������
    Distance=Ks10x_ReadByte(SlaveAddress,0x02);             //��8λ
	Distance<<=8;
	Distance+=Ks10x_ReadByte(SlaveAddress,0x03);                //��8λ
    printf("����=%d\r\n",Distance);
    
    return Distance;
}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :

************************************************************************************************/
void KS10X_Change_Addr_Init(u8 OldAddr,u8 NewAddr)  //�˺�������ʵ��ѡ�������ĵ�ַ
{
    Change_Addr(OldAddr,NewAddr);
    delay_ms(80);
}

 

