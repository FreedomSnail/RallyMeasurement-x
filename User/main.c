/*
*********************************************************************************************************
*
*	模块名称 : 主程序模块。
*	文件名称 : main.c
*	版    本 : V2.0
*	说    明 : 按键检测和LED控制例程。核心文件为 bsp_timer.c bsp_key.c 和 bsp_led.c
*	修改记录 :
*		版本号  日期       作者    说明
*		v1.0    2013-02-01 armfly  首发
*		v1.1    2013-06-20 armfly  更新bsp代码; 更新打印提示信息。
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#include "bsp.h"			/* 底层硬件驱动 */

/* 定义例程名和例程发布日期 */
#define EXAMPLE_NAME	"X3-001_按键检测和LED控制例程"
#define EXAMPLE_DATE	"2013-06-20"
#define DEMO_VER		"1.1"

/* 仅允许本文件内调用的函数声明 */
static void PrintfLogo(void);
/*
*********************************************************************************************************
*	函 数 名: main
*	功能说明: c程序入口
*	形    参：无
*	返 回 值: 错误代码(无需处理)
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
	_Draw_String_HZ_H(0, OLED_ORIGIN_Y-18,"天翔航空", HZ32x36,1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X+8+4, OLED_ORIGIN_Y-48-2-4, "迎", HZ48x48,1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-56-4, OLED_ORIGIN_Y+2-4,   "过", HZ48x48,1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X+8+4, OLED_ORIGIN_Y+2-4,    "磅", HZ48x48,1,0,TEXT_NORMAL);
	
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
** 显示峰值重量
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
	_Draw_String_HZ_H(OLED_ORIGIN_X-32, 18-14,"升力", HZ16x16, 1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-32, 18-14,"升", HZ16x16, 1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-16, 18-14,"力", HZ16x16, 1,0,TEXT_NORMAL);
	_Draw_String_Ascii(OLED_ORIGIN_X, 18-12,":g", ASCII8x12, 1,0,TEXT_NORMAL);
	Disp_Weight_value(Value);
	_Draw_String_HZ_H(OLED_ORIGIN_X-64, OLED_ORIGIN_Y+14,"峰值", HZ16x16, 1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-64, OLED_ORIGIN_Y+14,"峰", HZ16x16, 1,0,TEXT_NORMAL);
	//_Draw_One_HZ(OLED_ORIGIN_X-48, OLED_ORIGIN_Y+14,"值", HZ16x16, 1,0,TEXT_NORMAL);
	_Draw_String_Ascii(OLED_ORIGIN_X-32, OLED_ORIGIN_Y+16,":", ASCII8x12, 1,0,TEXT_NORMAL);
	Disp_Weight_Max_Value(Value);
}
int main(void)
{
	/*
		ST固件库中的启动文件已经执行了 SystemInit() 函数，该函数在 system_stm32f4xx.c 文件，主要功能是
	配置CPU系统的时钟，内部Flash访问时序，配置FSMC用于外部SRAM
	*/
	u16 maxWeightPoint = 500;			//起跳峰值，超过这个数值时开始显示峰值，低于这个数值3s后自动随动当前值变化
	u16 maxWeightDisplayHoldTime=30;	//峰值显示时间
	//u8	isMaxWeightAppear=0;			// 1为出现
	u16 cntcnt;
	bsp_Init();		/* 硬件初始化 */
	//PrintfLogo();	/* 打印例程信息到串口1 */
	bsp_StartAutoTimer(0, 100);	/* 启动1个500ms的自动重装的定时器 */
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
	Weight.WeightFullScale = AlarmValue;	//最大量程值设为3kg
	Weight.LastWeight = Weight.CurWeight;
	Weight.CurWeightMax = Weight.CurWeight;
	Get_Weight();
	Disp_Weight_value_Init(Weight.CurWeight);
	GUI_Exec();
	//Disp_Weight_value_Init(Weight.CurWeight);
	/* 进入主程序循环体 */
	while (1){
		bsp_Idle();		/* 这个函数在bsp.c文件。用户可以修改这个函数实现CPU休眠和喂狗 */

		if (bsp_CheckTimer(0))	{/* 判断定时器超时时间 */
			
			/* 每隔500ms 进来一次 */
			bsp_LedToggle(4);	/* 翻转LED4的状态 */
			//Read_KS10X_Data(SLAVE_ADDRESS1);
			Get_Weight();
			//printf("重量=%dg\r\n",Weight.CurWeight);
			printf("%d",Weight.CurWeight);
			if(Weight.LastWeight != Weight.CurWeight) {
				Weight.LastWeight = Weight.CurWeight;
				Disp_Weight_value(Weight.CurWeight);
				if(Weight.CurWeight>Weight.CurWeightMax) {//更新峰值
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
				if(Weight.CurWeight>Weight.CurWeightMax) {//更新峰值
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
*	函 数 名: PrintfLogo
*	功能说明: 打印例程名称和例程发布日期, 接上串口线后，打开PC机的超级终端软件可以观察结果
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
static void PrintfLogo(void)
{
	/* 检测CPU ID */
	{
		/* 参考手册：
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
	printf("* 例程名称   : %s\r\n", EXAMPLE_NAME);	/* 打印例程名称 */
	printf("* 例程版本   : %s\r\n", DEMO_VER);		/* 打印例程版本 */
	printf("* 发布日期   : %s\r\n", EXAMPLE_DATE);	/* 打印例程日期 */

	/* 打印ST固件库版本，这3个定义宏在stm32f10x.h文件中 */
	printf("* 固件库版本 : V%d.%d.%d (STM32F4xx_StdPeriph_Driver)\r\n", __STM32F4XX_STDPERIPH_VERSION_MAIN,
			__STM32F4XX_STDPERIPH_VERSION_SUB1,__STM32F4XX_STDPERIPH_VERSION_SUB2);
	printf("* \r\n");	/* 打印一行空格 */
	printf("* QQ    : 1295744630 \r\n");
	printf("* 旺旺  : armfly\r\n");
	printf("* Email : armfly@qq.com \r\n");
	printf("* 淘宝店: armfly.taobao.com\r\n");
	printf("* Copyright www.armfly.com 安富莱电子\r\n");
	printf("*************************************************************\n\r");
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
