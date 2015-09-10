#ifndef _BSP_OLED12864_H
#define _BSP_OLED12864_H	



#define XLevelL		0x00
#define XLevelH		0x10
#define XLevel	    ((XLevelH&0x0F)*16+XLevelL)
#define Max_Column	128
#define Max_Row		64
#define	Brightness	0xCF 
#define X_WIDTH 	128
#define Y_WIDTH 	64

#define		OLED_ORIGIN_X		64			//��Ļԭ��x���꣬128*64
#define		OLED_ORIGIN_Y		32			//��Ļԭ��x���꣬128*64

//-----------------OLED�˿ڶ���----------------    
/*
   ��OLEDģ�����롿 ��������TFT�ӿڣ�STM32���ߣ���
        VCC ----------- 3.3V
        GND ----------- GND
        SCK ----------- PA3
        SDA ----------- PA2
        RST ----------- PA1
        D/C ----------- PA0
         CS ----------- PC9
*/
#define RCC_OLED_PORT (RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOC)		/* GPIO�˿�ʱ�� */


#define OLED_SCK_PORT	GPIOA
#define OLED_SCK_PIN	GPIO_Pin_3

#define OLED_SDA_PORT	GPIOA
#define OLED_SDA_PIN	GPIO_Pin_2

#define OLED_RST_PORT	GPIOA
#define OLED_RST_PIN	GPIO_Pin_1

#define OLED_DC_PORT	GPIOA
#define OLED_DC_PIN		GPIO_Pin_0

#define OLED_CS_PORT	GPIOC
#define OLED_CS_PIN		GPIO_Pin_9


#define OLED_SCK_1()	OLED_SCK_PORT->BSRRL = OLED_SCK_PIN
#define OLED_SCK_0()	OLED_SCK_PORT->BSRRH = OLED_SCK_PIN

#define OLED_SDA_1()	OLED_SDA_PORT->BSRRL = OLED_SDA_PIN
#define OLED_SDA_0()	OLED_SDA_PORT->BSRRH = OLED_SDA_PIN

#define OLED_RST_1()	OLED_RST_PORT->BSRRL = OLED_RST_PIN
#define OLED_RST_0()	OLED_RST_PORT->BSRRH = OLED_RST_PIN

#define OLED_DC_1()		OLED_DC_PORT->BSRRL = OLED_DC_PIN
#define OLED_DC_0()		OLED_DC_PORT->BSRRH = OLED_DC_PIN

#define OLED_CS_1()		OLED_CS_PORT->BSRRL = OLED_CS_PIN
#define OLED_CS_0()		OLED_CS_PORT->BSRRH = OLED_CS_PIN

#define OLED_MODE 0
		    						  
 

//OLED�����ú���
void OLED_GPIO_Config(void);
void OLED_Init(void);
void OLED_WrDat(unsigned char dat);//д����
void OLED_WrCmd(unsigned char cmd);//д����
void OLED_SetPos(unsigned char x, unsigned char y);//������ʼ������
void OLED_Fill(unsigned char bmp_dat);//ȫ�����
void OLED_CLS(void);//����
void OLED_6x8Str(unsigned char x, unsigned char y, unsigned char ch[]);
void OLED_8x16Str(unsigned char x, unsigned char y, unsigned char ch[]);
void OLED_16x16CN(unsigned char x, unsigned char y, unsigned char N);
void OLED_BMP(unsigned char x0, unsigned char y0, unsigned char x1, unsigned char y1, unsigned char BMP[]);

void GUI_Exec(void);

void GUI_Clear(void);

void GUI_Logo(void);


void GUI_Point(u8 x, u8 y, u8 color);

void _Draw_One_HZ(u8 x, u8 y, u8 * text, FONT_SIZE FontSize, u16 color, u16 BackgroundColor, TEXT_OPTION Option);
void _Draw_String_HZ_H(u8 x, u8 y, u8 * text, FONT_SIZE FontSize, u16 color, u16 BackgroundColor, TEXT_OPTION Option);
void _Draw_One_Ascii(u8 x, u8 y, u8 * text, FONT_SIZE FontSize, u16 color, u16 BackgroundColor, TEXT_OPTION Option);
void _Draw_String_Ascii(u8 x, u8 y, u8 * text, FONT_SIZE FontSize, u16 color, u16 BackgroundColor, TEXT_OPTION Option);

#endif  
	 



