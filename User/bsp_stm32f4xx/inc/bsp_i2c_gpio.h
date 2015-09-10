/*
*********************************************************************************************************
*
*	模块名称 : I2C总线驱动模块
*	文件名称 : bsp_i2c_gpio.h
*	版    本 : V1.0
*	说    明 : 头文件。
*
*	
*
*********************************************************************************************************
*/

#ifndef _BSP_I2C_GPIO_H
#define _BSP_I2C_GPIO_H

#define I2C_WR	0		/* 写控制bit */
#define I2C_RD	1		/* 读控制bit */

			
/* 
	    i2c总线GPIO:
		PB6/I2C1_SCL
		PB7/I2C1_SDA
*/

/* 定义I2C总线连接的GPIO端口, 用户只需要修改下面4行代码即可任意改变SCL和SDA的引脚 */
#define GPIO_PORT_I2C	GPIOB					/* GPIO端口 */
#define RCC_I2C_PORT 	RCC_AHB1Periph_GPIOB	/* GPIO端口时钟 */
#define I2C_SCL_PIN		GPIO_Pin_6			/* 连接到SCL时钟线的GPIO */
#define I2C_SDA_PIN		GPIO_Pin_7			/* 连接到SDA数据线的GPIO */


/* 定义读写SCL和SDA的宏 */
#define I2C_SCL_1()  GPIO_PORT_I2C->BSRRL = I2C_SCL_PIN				/* SCL = 1 */
#define I2C_SCL_0()  GPIO_PORT_I2C->BSRRH = I2C_SCL_PIN				/* SCL = 0 */

#define I2C_SDA_1()  GPIO_PORT_I2C->BSRRL = I2C_SDA_PIN				/* SDA = 1 */
#define I2C_SDA_0()  GPIO_PORT_I2C->BSRRH = I2C_SDA_PIN				/* SDA = 0 */

#define I2C_SDA_READ()  ((GPIO_PORT_I2C->IDR & I2C_SDA_PIN) != 0)	/* 读SDA口线状态 */
#define I2C_SCL_READ()  ((GPIO_PORT_I2C->IDR & I2C_SCL_PIN) != 0)	/* 读SCL口线状态 */


void bsp_InitI2C(void);
void i2c_Delay_Test(void);
void i2c_Start(void);
void i2c_Stop(void);
void i2c_SendByte(uint8_t _ucByte);
uint8_t i2c_ReadByte(uint8_t ack);
uint8_t i2c_WaitAck(void);
void i2c_Ack(void);
void i2c_NAck(void);

#endif
