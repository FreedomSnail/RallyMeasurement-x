/*
*********************************************************************************************************
*
*	ģ������ : I2C��������ģ��
*	�ļ����� : bsp_i2c_gpio.c
*	��    �� : V1.0
*	˵    �� : ��gpioģ��i2c����, ������STM32F4ϵ��CPU����ģ�鲻����Ӧ�ò�����֡��������I2C���߻�������������
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2013-02-01 armfly  ��ʽ����
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

/*
	Ӧ��˵����
	�ڷ���I2C�豸ǰ�����ȵ��� i2c_CheckDevice() ���I2C�豸�Ƿ��������ú���������GPIO
*/

#include "bsp.h"

#define SDA_READ()  GPIO_ReadInputDataBit(GPIO_PORT_I2C, I2C_SDA_PIN)

/*
*********************************************************************************************************
*	�� �� ��: bsp_InitI2C
*	����˵��: ����I2C���ߵ�GPIO������ģ��IO�ķ�ʽʵ��
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void bsp_InitI2C(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_I2C_PORT, ENABLE);	/* ��GPIOʱ�� */

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* ��Ϊ����� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;		/* ��Ϊ��©ģʽ */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ���������費ʹ�� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO������ٶ� */

	GPIO_InitStructure.GPIO_Pin = I2C_SCL_PIN | I2C_SDA_PIN;
	GPIO_Init(GPIO_PORT_I2C, &GPIO_InitStructure);

	/* ��һ��ֹͣ�ź�, ��λI2C�����ϵ������豸������ģʽ */
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
*	�� �� ��: i2c_Delay
*	����˵��: I2C����λ�ӳ٣����400KHz
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void i2c_Delay(void)
{
	uint8_t i;

	/*��
		CPU��Ƶ168MHzʱ�����ڲ�Flash����, MDK���̲��Ż�����̨ʽʾ�����۲Ⲩ�Ρ�
		ѭ������Ϊ5ʱ��SCLƵ�� = 1.78MHz (����ʱ: 92ms, ��д������������ʾ����̽ͷ���ϾͶ�дʧ�ܡ�ʱ��ӽ��ٽ�)
		ѭ������Ϊ10ʱ��SCLƵ�� = 1.1MHz (����ʱ: 138ms, ���ٶ�: 118724B/s)
		ѭ������Ϊ30ʱ��SCLƵ�� = 440KHz�� SCL�ߵ�ƽʱ��1.0us��SCL�͵�ƽʱ��1.2us

		��������ѡ��2.2Kŷʱ��SCL������ʱ��Լ0.5us�����ѡ4.7Kŷ����������Լ1us

		ʵ��Ӧ��ѡ��400KHz���ҵ����ʼ���
	*/
	for (i = 0; i < 100; i++);
}
void i2c_Delay_Test(void)
{
	u8 i;
	SDA_OUT();               //sda�����
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
*	�� �� ��: i2c_Start
*	����˵��: CPU����I2C���������ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Start(void)
{
	SDA_OUT();               //sda�����
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C���������ź� */
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
*	�� �� ��: i2c_Start
*	����˵��: CPU����I2C����ֹͣ�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Stop(void)
{
	SDA_OUT();               //sda�����
	/* ��SCL�ߵ�ƽʱ��SDA����һ�������ر�ʾI2C����ֹͣ�ź� */
	I2C_SCL_0();
	I2C_SDA_0();
	i2c_Delay();
	I2C_SCL_1();
	I2C_SDA_1();
	i2c_Delay();
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_WaitAck
*	����˵��: CPU����һ��ʱ�ӣ�����ȡ������ACKӦ���ź�
*	��    ��:  ��
*	�� �� ֵ: ����0��ʾ��ȷӦ��1��ʾ��������Ӧ
*********************************************************************************************************
*/
uint8_t i2c_WaitAck(void)
{
	uint8_t ucErrTime=0;
	
	SDA_IN();      //SDA����Ϊ����

	I2C_SDA_1();	/* CPU�ͷ�SDA���� */
	
	i2c_Delay();
	I2C_SCL_1();	/* CPU����SCL = 1, ��ʱ�����᷵��ACKӦ�� */
	i2c_Delay();
	while (I2C_SDA_READ())	/* CPU��ȡSDA����״̬ */
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
*	�� �� ��: i2c_Ack
*	����˵��: CPU����һ��ACK�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_Ack(void)
{
	I2C_SCL_0();
	SDA_OUT();
	
	I2C_SDA_0();	/* CPU����SDA = 0 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
	//I2C_SDA_1();	/* CPU�ͷ�SDA���� */
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_NAck
*	����˵��: CPU����1��NACK�ź�
*	��    ��:  ��
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_NAck(void)
{
	I2C_SCL_0();
	SDA_OUT();
	
	I2C_SDA_1();	/* CPU����SDA = 1 */
	i2c_Delay();
	I2C_SCL_1();	/* CPU����1��ʱ�� */
	i2c_Delay();
	I2C_SCL_0();
	i2c_Delay();
}
/*
*********************************************************************************************************
*	�� �� ��: i2c_SendByte
*	����˵��: CPU��I2C�����豸����8bit����
*	��    ��:  _ucByte �� �ȴ����͵��ֽ�
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void i2c_SendByte(uint8_t _ucByte)
{
	uint8_t i;
	
	SDA_OUT();
	I2C_SCL_0();
	/* �ȷ����ֽڵĸ�λbit7 */
	for (i = 0; i < 8; i++) {
		if (_ucByte & 0x80){
			I2C_SDA_1();
		} else {
			I2C_SDA_0();
		}
		_ucByte <<= 1;	/* ����һ��bit */
		i2c_Delay();
		I2C_SCL_1();
		i2c_Delay();
		I2C_SCL_0();
		i2c_Delay();
	}
}

/*
*********************************************************************************************************
*	�� �� ��: i2c_ReadByte
*	����˵��: CPU��I2C�����豸��ȡ8bit����
*	��    ��:  ��
*	�� �� ֵ: ����������
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

