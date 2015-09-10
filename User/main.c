/*
*********************************************************************************************************
*
*	ģ������ : ������ģ�顣
*	�ļ����� : main.c
*	��    �� : V2.0
*	˵    �� : ��������LED�������̡������ļ�Ϊ bsp_timer.c bsp_key.c �� bsp_led.c
*	�޸ļ�¼ :
*		�汾��  ����       ����    ˵��
*		v1.0    2013-02-01 armfly  �׷�
*		v1.1    2013-06-20 armfly  ����bsp����; ���´�ӡ��ʾ��Ϣ��
*
*	Copyright (C), 2013-2014, ���������� www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"			/* �ײ�Ӳ������ */

/* ���������������̷������� */
#define EXAMPLE_NAME	"X3-001_��������LED��������"
#define EXAMPLE_DATE	"2013-06-20"
#define DEMO_VER		"1.1"

/* �������ļ��ڵ��õĺ������� */
static void PrintfLogo(void);
/*
*********************************************************************************************************
*	�� �� ��: main
*	����˵��: c�������
*	��    �Σ���
*	�� �� ֵ: �������(���账��)
*********************************************************************************************************
*/
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :
** 
************************************************************************************************/
void Disp_Power_On_Logo(void)
{
	
	GUI_Clear();
	//GUI_Logo();
	_Draw_String_HZ_H(0, OLED_ORIGIN_Y-18,"���躽��", HZ32x36,1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X+8+4, OLED_ORIGIN_Y-48-2-4, "ӭ", HZ48x48,1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-56-4, OLED_ORIGIN_Y+2-4,   "��", HZ48x48,1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X+8+4, OLED_ORIGIN_Y+2-4,    "��", HZ48x48,1,0,TEXT_NORMAL);
	
}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :
** 
************************************************************************************************/
void Disp_Weight_value(u16 Value)
{
	u8 String[6];
	u8 i;
	
	if(Value<10) {
		String[0] = ' ';
		String[1] = ' ';
		String[2] = Value+'0';
		String[3] = ' ';
		String[4] = ' ';
		String[5] = 0;
		_Draw_String_Ascii(OLED_ORIGIN_X-12*5, OLED_ORIGIN_Y-12,String, ASCII24x24, 1,0,TEXT_NORMAL);
		
	} else if(Value<100) {
		String[0] = ' ';
		String[1] = Value/10%10+'0';
		String[2] = Value%10+'0';
		String[3] = ' ';
		for(i=0;i<4;i++) {
			_Draw_One_Ascii(OLED_ORIGIN_X-24*2+i*24, OLED_ORIGIN_Y-12,String+i, ASCII24x24, 1,0,TEXT_NORMAL);
		}
	} else if(Value<1000) {
		String[0] = ' ';
		String[1] = Value/100%10+'0';
		String[2] = Value/10%10+'0';
		String[3] = Value%10+'0';
		String[4] = ' ';
		String[5] = 0;
		_Draw_String_Ascii(OLED_ORIGIN_X-12*5, OLED_ORIGIN_Y-12,String, ASCII24x24, 1,0,TEXT_NORMAL);
	
	} else  if(Value<10000){
		String[0] = Value/1000+'0';
		String[1] = Value/100%10+'0';
		String[2] = Value/10%10+'0';
		String[3] = Value%10+'0';
		_Draw_One_Ascii(OLED_ORIGIN_X-12*5+0*24, OLED_ORIGIN_Y-12," ", ASCII24x24, 1,0,TEXT_NORMAL);
		for(i=0;i<4;i++) {
			_Draw_One_Ascii(OLED_ORIGIN_X-24*2+i*24, OLED_ORIGIN_Y-12,String+i, ASCII24x24, 1,0,TEXT_NORMAL);
		}
		_Draw_One_Ascii(OLED_ORIGIN_X-12*5+4*24+12, OLED_ORIGIN_Y-12," ", ASCII24x24, 1,0,TEXT_NORMAL);
	} else {
		String[0] = Value/10000+'0';
		String[1] = Value/1000%10+'0';
		String[2] = Value/100%10+'0';
		String[3] = Value/10%10+'0';
		String[4] = Value%10+'0';
		for(i=0;i<5;i++) {
			_Draw_One_Ascii(OLED_ORIGIN_X-12*5+i*24, OLED_ORIGIN_Y-12,String+i, ASCII24x24, 1,0,TEXT_NORMAL);
		}
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
** ��ʾ��ֵ����
************************************************************************************************/
void Disp_Weight_Max_Value(u16 Value)
{
	u8 String[6];
	u8 i;
	
	if(Value<10) {
		String[0] = ' ';
		String[1] = ' ';
		String[2] = Value+'0';
		String[3] = ' ';
		String[4] = ' ';
		String[5] = 0;
		_Draw_String_Ascii(OLED_ORIGIN_X-4*5, OLED_ORIGIN_Y+16,String, ASCII8x12, 1,0,TEXT_NORMAL);
		
	} else if(Value<100) {
		String[0] = ' ';
		String[1] = Value/10%10+'0';
		String[2] = Value%10+'0';
		String[3] = ' ';
		for(i=0;i<4;i++) {
			_Draw_One_Ascii(OLED_ORIGIN_X-8*2+i*8, OLED_ORIGIN_Y+16,String+i, ASCII8x12, 1,0,TEXT_NORMAL);
		}
	} else if(Value<1000) {
		String[0] = ' ';
		String[1] = Value/100%10+'0';
		String[2] = Value/10%10+'0';
		String[3] = Value%10+'0';
		String[4] = ' ';
		String[5] = 0;
		_Draw_String_Ascii(OLED_ORIGIN_X-4*5, OLED_ORIGIN_Y+16,String, ASCII8x12, 1,0,TEXT_NORMAL);
	
	} else if(Value<10000){
		String[0] = Value/1000+'0';
		String[1] = Value/100%10+'0';
		String[2] = Value/10%10+'0';
		String[3] = Value%10+'0';
		
		for(i=0;i<4;i++) {
			_Draw_One_Ascii(OLED_ORIGIN_X-8*2+i*8, OLED_ORIGIN_Y+16,String+i, ASCII8x12, 1,0,TEXT_NORMAL);
		}
	} else {
		String[0] = Value/10000+'0';
		String[1] = Value/1000%10+'0';
		String[2] = Value/100%10+'0';
		String[3] = Value/10%10+'0';
		String[4] = Value%10+'0';
		for(i=0;i<5;i++) {
			_Draw_One_Ascii(OLED_ORIGIN_X-4*5+i*8, OLED_ORIGIN_Y+16,String+i, ASCII8x12, 1,0,TEXT_NORMAL);
		}
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
** 
************************************************************************************************/
void Disp_Weight_value_Init(u16 Value)
{
	//OLED_CLS();
	GUI_Clear();
	_Draw_String_HZ_H(OLED_ORIGIN_X-32, 18-14,"����", HZ16x16, 1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-32, 18-14,"��", HZ16x16, 1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-16, 18-14,"��", HZ16x16, 1,0,TEXT_NORMAL);
	_Draw_String_Ascii(OLED_ORIGIN_X, 18-12,":g", ASCII8x12, 1,0,TEXT_NORMAL);
	Disp_Weight_value(Value);
	_Draw_String_HZ_H(OLED_ORIGIN_X-64, OLED_ORIGIN_Y+14,"��ֵ", HZ16x16, 1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-64, OLED_ORIGIN_Y+14,"��", HZ16x16, 1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-48, OLED_ORIGIN_Y+14,"ֵ", HZ16x16, 1,0,TEXT_NORMAL);
	_Draw_String_Ascii(OLED_ORIGIN_X-32, OLED_ORIGIN_Y+16,":", ASCII8x12, 1,0,TEXT_NORMAL);
	Disp_Weight_Max_Value(Value);
}
int main(void)
{
	/*
		ST�̼����е������ļ��Ѿ�ִ���� SystemInit() �������ú����� system_stm32f4xx.c �ļ�����Ҫ������
	����CPUϵͳ��ʱ�ӣ��ڲ�Flash����ʱ������FSMC�����ⲿSRAM
	*/
	u16 maxWeightPoint = 500;			//������ֵ�����������ֵʱ��ʼ��ʾ��ֵ�����������ֵ3s���Զ��涯��ǰֵ�仯
	u16 maxWeightDisplayHoldTime=30;	//��ֵ��ʾʱ��
	//u8	isMaxWeightAppear=0;			// 1Ϊ����
	u16 cntcnt;
	bsp_Init();		/* Ӳ����ʼ�� */
	//PrintfLogo();	/* ��ӡ������Ϣ������1 */
	bsp_StartAutoTimer(0, 100);	/* ����1��500ms���Զ���װ�Ķ�ʱ�� */
	OLED_Init();
	Hx711_GPIO_Config();
	Disp_Power_On_Logo();
	GUI_Exec();
	Weight.DataRef = HX711_Read();
	Weight.DataRef = HX711_Read();
	Weight.DataRef2 = HX711_2_Read();
	Weight.DataRef2 = HX711_2_Read();
	Weight.LastWeight = Weight.CurWeight;
	Weight.GapValue = GAP_VALUE;
	
	bsp_DelayMS(1500);
	Weight.DataRef = HX711_Read();
	Weight.DataRef = HX711_Read();
	Weight.DataRef2 = HX711_2_Read();
	Weight.DataRef2 = HX711_2_Read();
	Weight.Status = WEIGHT_STATUS_NORMAL;
	Weight.WeightFullScale = AlarmValue;	//�������ֵ��Ϊ3kg
	Weight.LastWeight = Weight.CurWeight;
	Weight.CurWeightMax = Weight.CurWeight;
	Get_Weight();
	Disp_Weight_value_Init(Weight.CurWeight);
	GUI_Exec();
	//Disp_Weight_value_Init(Weight.CurWeight);
	/* ����������ѭ���� */
	while (1){
		bsp_Idle();		/* ���������bsp.c�ļ����û������޸��������ʵ��CPU���ߺ�ι�� */

		if (bsp_CheckTimer(0))	{/* �ж϶�ʱ����ʱʱ�� */
			
			/* ÿ��500ms ����һ�� */
			bsp_LedToggle(4);	/* ��תLED4��״̬ */
			//Read_KS10X_Data(SLAVE_ADDRESS1);
			Get_Weight();
			//printf("����=%dg\r\n",Weight.CurWeight);
			printf("%d",Weight.CurWeight);
			if(Weight.LastWeight != Weight.CurWeight) {
				Weight.LastWeight = Weight.CurWeight;
				Disp_Weight_value(Weight.CurWeight);
				if(Weight.CurWeight>Weight.CurWeightMax) {//���·�ֵ
					Weight.CurWeightMax = Weight.CurWeight;
					Disp_Weight_Max_Value(Weight.CurWeightMax);
					//GUI_Exec();
				}
				GUI_Exec();
			}
			#if 0
			if(Weight.CurWeight<maxWeightPoint) {
				cntcnt++;
			} else {
				cntcnt = 0;
			}
			if(cntcnt>maxWeightDisplayHoldTime) {
				Weight.CurWeightMax = 0;
				Disp_Weight_Max_Value(Weight.CurWeightMax);
				GUI_Exec();
			} else {
				if(Weight.CurWeight>Weight.CurWeightMax) {//���·�ֵ
					Weight.CurWeightMax = Weight.CurWeight;
					Disp_Weight_Max_Value(Weight.CurWeightMax);
					GUI_Exec();
				}
			}
			#endif
		}
		
	}
}

/*
*********************************************************************************************************
*	�� �� ��: PrintfLogo
*	����˵��: ��ӡ�������ƺ����̷�������, ���ϴ����ߺ󣬴�PC���ĳ����ն�������Թ۲���
*	��    �Σ���
*	�� �� ֵ: ��
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
	/* ���CPU ID */
	{
		/* �ο��ֲ᣺
			32.6.1 MCU device ID code
			33.1 Unique device ID register (96 bits)
		*/
		uint32_t CPU_Sn0, CPU_Sn1, CPU_Sn2;

		CPU_Sn0 = *(__IO uint32_t*)(0x1FFF7A10);
		CPU_Sn1 = *(__IO uint32_t*)(0x1FFF7A10 + 4);
		CPU_Sn2 = *(__IO uint32_t*)(0x1FFF7A10 + 8);

		printf("\r\nCPU : STM32F407IGT6, LQFP176, UID = %08X %08X %08X\n\r"
			, CPU_Sn2, CPU_Sn1, CPU_Sn0);
	}

	printf("\n\r");
	printf("*************************************************************\n\r");
	printf("* ��������   : %s\r\n", EXAMPLE_NAME);	/* ��ӡ�������� */
	printf("* ���̰汾   : %s\r\n", DEMO_VER);		/* ��ӡ���̰汾 */
	printf("* ��������   : %s\r\n", EXAMPLE_DATE);	/* ��ӡ�������� */

	/* ��ӡST�̼���汾����3���������stm32f10x.h�ļ��� */
	printf("* �̼���汾 : V%d.%d.%d (STM32F4xx_StdPeriph_Driver)\r\n", __STM32F4XX_STDPERIPH_VERSION_MAIN,
			__STM32F4XX_STDPERIPH_VERSION_SUB1,__STM32F4XX_STDPERIPH_VERSION_SUB2);
	printf("* \r\n");	/* ��ӡһ�пո� */
	printf("* QQ    : 1295744630 \r\n");
	printf("* ����  : armfly\r\n");
	printf("* Email : armfly@qq.com \r\n");
	printf("* �Ա���: armfly.taobao.com\r\n");
	printf("* Copyright www.armfly.com ����������\r\n");
	printf("*************************************************************\n\r");
}

/***************************** ���������� www.armfly.com (END OF FILE) *********************************/
