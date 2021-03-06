/*
*********************************************************************************************************
*
*	模块名称 : I2C总线驱动模块
*	文件名称 : bsp_i2c_gpio.c
*	版    本 : V1.0
*	说    明 : 用gpio模拟i2c总线, 适用于STM32F4系列CPU。该模块不包括应用层命令帧，仅包括I2C总线基本操作函数。
*
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2013-02-01 armfly  正式发布
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

/*
	应用说明：
	在访问I2C设备前，请先调用 i2c_CheckDevice() 检测I2C设备是否正常，该函数会配置GPIO
*/

#include "bsp.h"

#define SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)

/*
*********************************************************************************************************
*	函 数 名: bsp_InitI2C
*	功能说明: 配置I2C总线的GPIO，采用模拟IO的方式实现
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitI2C(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_I2C_PORT, ENABLE);	/* 打开GPIO时钟 */

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* 设为输出口 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;		/* 设为开漏模式 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* 上下拉电阻不使能 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO口最大速度 */

	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);

	/* 给一个停止信号, 复位I2C总线上的所有设备到待机模式 */
	i2c_Stop();
}
/** 
  * @brief  Set SDA Pin as Output Mode 
  * @retval None 
  */  
void SDA_OUT(void)    
{    
	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_StructInit(&GPIO_InitStructure);    
  	GPIO_InitStructure.GPIO_Pin   = I2C_SDA_PIN;    
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_OUT;    
  	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;    
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;     
  	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);    
}    
/** 
  * @brief  Set SDA Pin as Input Mode 
  * @retval None 
  */  
void SDA_IN(void)    
{    
	GPIO_InitTypeDef GPIO_InitStructure;
  	GPIO_StructInit(&GPIO_InitStructure);    
  	GPIO_InitStructure.GPIO_Pin   = I2C_SDA_PIN;    
  	GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_IN;  
  	GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;     
  	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);    
}   



/*********************************************************************************************************
*	函 数 名: i2c_Delay
*	功能说明: I2C总线位延迟，最快400KHz
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
static void i2c_Delay(void)
{
	uint8_t i;

	/*　
		CPU主频168MHz时，在内部Flash运行, MDK工程不优化。用台式示波器观测波形。
		循环次数为5时，SCL频率 = 1.78MHz (读耗时: 92ms, 读写正常，但是用示波器探头碰上就读写失败。时序接近临界)
		循环次数为10时，SCL频率 = 1.1MHz (读耗时: 138ms, 读速度: 118724B/s)
		循环次数为30时，SCL频率 = 440KHz， SCL高电平时间1.0us，SCL低电平时间1.2us

		上拉电阻选择2.2K欧时，SCL上升沿时间约0.5us，如果选4.7K欧，则上升沿约1us

		实际应用选择400KHz左右的速率即可
	*/
	for (i = 0; i < 100; i++);
}
void i2c_Delay_Test(void)
{
	u8 i;
	SDA_OUT();               //sda线输出
	for(i=0;i<10;i++) {
		//I2C_SDA_0();
		I2C_SCL_1();
		i2c_Delay();
		//I2C_SDA_1();
		I2C_SCL_0();
		i2c_Delay();
	}
}
/*
*********************************************************************************************************
*	函 数 名: i2c_Start
*	功能说明: CPU发起I2C总线启动信号
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Start(void)
{
	SDA_OUT();               //sda线输出
	/* 当SCL高电平时，SDA出现一个下跳沿表示I2C总线启动信号 */
	I2C_SDA_1();
	I2C_SCL_1();
	i2c_Delay();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	函 数 名: i2c_Start
*	功能说明: CPU发起I2C总线停止信号
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Stop(void)
{
	SDA_OUT();               //sda线输出
	/* 当SCL高电平时，SDA出现一个上跳沿表示I2C总线停止信号 */
	I2C_SCL_0();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_1();
	I2C_SDA_1();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	函 数 名: i2c_WaitAck
*	功能说明: CPU产生一个时钟，并读取器件的ACK应答信号
*	形    参:  无
*	返 回 值: 返回0表示正确应答，1表示无器件响应
*********************************************************************************************************
*/
uint8_t i2c_WaitAck(void)
{
	uint8_t ucErrTime=0;
	
	SDA_IN();      //SDA设置为输入

	I2C_SDA_1();	/* CPU释放SDA总线 */
	
	i2c_Delay();
	I2C_SCL_1();	/* CPU驱动SCL = 1, 此时器件会返回ACK应答 */
	i2c_Delay();
	while (I2C_SDA_READ())	/* CPU读取SDA口线状态 */
	//while (SDA_READ())
	{
		ucErrTime++;
		if(ucErrTime>250) {
			i2c_Stop();
			return 1;
		}
	}
	I2C_SCL_0();
	i2c_Delay();
	return 0;
}
/*
*********************************************************************************************************
*	函 数 名: i2c_Ack
*	功能说明: CPU产生一个ACK信号
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_Ack(void)
{
	I2C_SCL_0();
	SDA_OUT();
	
	I2C_SDA_0();	/* CPU驱动SDA = 0 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	//I2C_SDA_1();	/* CPU释放SDA总线 */
}

/*
*********************************************************************************************************
*	函 数 名: i2c_NAck
*	功能说明: CPU产生1个NACK信号
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_NAck(void)
{
	I2C_SCL_0();
	SDA_OUT();
	
	I2C_SDA_1();	/* CPU驱动SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU产生1个时钟 */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}
/*
*********************************************************************************************************
*	函 数 名: i2c_SendByte
*	功能说明: CPU向I2C总线设备发送8bit数据
*	形    参:  _ucByte ： 等待发送的字节
*	返 回 值: 无
*********************************************************************************************************
*/
void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;
	
	SDA_OUT();
	I2C_SCL_0();
	/* 先发送字节的高位bit7 */
	for (i = 0; i < 8; i++) {
		if (_ucByte & 0x80){
			I2C_SDA_1();
		} else {
			I2C_SDA_0();
		}
		_ucByte <<= 1;	/* 左移一个bit */
		i2c_Delay();
		I2C_SCL_1();
		i2c_Delay();
		I2C_SCL_0();
		i2c_Delay();
	}
}

/*
*********************************************************************************************************
*	函 数 名: i2c_ReadByte
*	功能说明: CPU从I2C总线设备读取8bit数据
*	形    参:  无
*	返 回 值: 读到的数据
*********************************************************************************************************
*/
uint8_t i2c_ReadByte(uint8_t ack)
{
	uint8_t i;
	uint8_t receive=0;
	SDA_IN();
	
	for (i = 0; i < 8; i++) {
		I2C_SCL_0();
		i2c_Delay();
		I2C_SCL_1();
		receive <<= 1;
		if (I2C_SDA_READ()){
			receive++;
		}
		i2c_Delay();
	}
	if(ack) {
		i2c_Ack();
	} else {
		i2c_NAck();
	}
	return receive;
}

