/*
*********************************************************************************************************
*
*	ģ������ : ����������ģ��
*	�ļ����� : bsp_beep.c
*	��    �� : V1.0
*	˵    �� : ����������. STM8S �� PD4 ���ž���BEEP���ܡ� ����BEEP_Start()�������԰�ָ������ʱ����
*		   ���д����������У���ռ��������ִ��ʱ�䣬�޵ȴ�����̨�Զ����Ʒ�������������ֹͣ��
*
*	�޸ļ�¼ :
*		�汾��  ����        ����     ˵��
*		V1.0    2013-08-16 armfly  ��ʽ����
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"

//#define BEEP_HAVE_POWER		/* ������б�ʾ��Դ��������ֱ��ͨ��GPIO����, ����PWM */

#ifdef	BEEP_HAVE_POWER		/* ��Դ������ */

	/* PB9 */
	#define GPIO_RCC_BEEP   RCC_AHB1Periph_GPIOB
	#define GPIO_PORT_BEEP	GPIOB
	#define GPIO_PIN_BEEP	GPIO_Pin_9

	#define BEEP_ENABLE()	GPIO_PORT_BEEP->BSRRL = GPIO_PIN_BEEP			/* ʹ�ܷ��������� */
	#define BEEP_DISABLE()	GPIO_PORT_BEEP->BSRRH = GPIO_PIN_BEEP			/* ��ֹ���������� */
#else		/* ��Դ������ */
	/* PB9 ---> TIM11_CH1 */

	/* 2000��ʾƵ��2KHz��5000��ʾ50.00%��ռ�ձ� */
	#define BEEP_ENABLE()	bsp_SetTIMOutPWM(GPIOB, GPIO_Pin_9, TIM11, 1, 1000, 5000);

	/* ��ֹ���������� */
	#define BEEP_DISABLE()	bsp_SetTIMOutPWM(GPIOB, GPIO_Pin_9, TIM11, 1, 0, 5000);
#endif

static BEEP_T g_tBeep;		/* ���������ȫ�ֽṹ����� */

/*
*********************************************************************************************************
*	�� �� ��: BEEP_InitHard
*	����˵��: ��ʼ��������Ӳ��
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BEEP_InitHard(void)
{
#ifdef	BEEP_HAVE_POWER		/* ��Դ������ */
	GPIO_InitTypeDef GPIO_InitStructure;

	/* ��GPIOF��ʱ�� */
	RCC_AHB1PeriphClockCmd(GPIO_RCC_BEEP, ENABLE);

	BEEP_DISABLE();

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* ��Ϊ����� */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* ��Ϊ����ģʽ */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* ���������費ʹ�� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	/* IO������ٶ� */

	GPIO_InitStructure.GPIO_Pin = GPIO_PIN_BEEP;
	GPIO_Init(GPIO_PORT_BEEP, &GPIO_InitStructure);
#endif
}

/*
*********************************************************************************************************
*	�� �� ��: BEEP_Start
*	����˵��: ������������
*	��    �Σ�_usBeepTime : ����ʱ�䣬��λ10ms; 0 ��ʾ������
*			  _usStopTime : ֹͣʱ�䣬��λ10ms; 0 ��ʾ��������
*			 _usCycle : ���д����� 0 ��ʾ��������
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BEEP_Start(uint16_t _usBeepTime, uint16_t _usStopTime, uint16_t _usCycle)
{
	if (_usBeepTime == 0)
	{
		return;
	}

	g_tBeep.usBeepTime = _usBeepTime;
	g_tBeep.usStopTime = _usStopTime;
	g_tBeep.usCycle = _usCycle;
	g_tBeep.usCount = 0;
	g_tBeep.usCycleCount = 0;
	g_tBeep.ucState = 0;
	g_tBeep.ucEnalbe = 1;	/* ������ȫ�ֲ�������ʹ�ܷ�����־ */

	BEEP_ENABLE();			/* ��ʼ���� */
}

/*
*********************************************************************************************************
*	�� �� ��: BEEP_Stop
*	����˵��: ֹͣ��������
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BEEP_Stop(void)
{
	g_tBeep.ucEnalbe = 0;

	if ((g_tBeep.usStopTime == 0) || (g_tBeep.usCycle == 0))
	{
		BEEP_DISABLE();	/* ����������Ʊ�־����ֹͣ����������ֹͣ�����ж����ֿ��� */
	}
}

/*
*********************************************************************************************************
*	�� �� ��: BEEP_KeyTone
*	����˵��: ���Ͱ�����
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BEEP_KeyTone(void)
{
	BEEP_Start(5, 1, 1);	/* ����50ms��ͣ10ms�� 1�� */
}

/*
*********************************************************************************************************
*	�� �� ��: BEEP_Pro
*	����˵��: ÿ��10ms����1�θú��������ڿ��Ʒ������������ú����� bsp_timer.c �б����á�
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void BEEP_Pro(void)
{
	if ((g_tBeep.ucEnalbe == 0) || (g_tBeep.usStopTime == 0))
	{
		return;
	}

	if (g_tBeep.ucState == 0)
	{
		if (g_tBeep.usStopTime > 0)	/* ��Ϸ��� */
		{
			if (++g_tBeep.usCount >= g_tBeep.usBeepTime)
			{
				BEEP_DISABLE();		/* ֹͣ���� */
				g_tBeep.usCount = 0;
				g_tBeep.ucState = 1;
			}
		}
		else
		{
			;	/* �����κδ������������� */
		}
	}
	else if (g_tBeep.ucState == 1)
	{
		if (++g_tBeep.usCount >= g_tBeep.usStopTime)
		{
			/* ��������ʱ��ֱ������stopֹͣΪֹ */
			if (g_tBeep.usCycle > 0)
			{
				if (++g_tBeep.usCycleCount >= g_tBeep.usCycle)
				{
					/* ѭ����������ֹͣ���� */
					g_tBeep.ucEnalbe = 0;
				}

				if (g_tBeep.ucEnalbe == 0)
				{
					g_tBeep.usStopTime = 0;
					return;
				}
			}

			g_tBeep.usCount = 0;
			g_tBeep.ucState = 0;

			BEEP_ENABLE();			/* ��ʼ���� */
		}
	}
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/