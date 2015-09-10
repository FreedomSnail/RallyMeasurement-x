/****************************************Copyright(c)********************************************
**
**                            2015-2023, Guangzhou TX-Aviation Technology Co.Ltd.
**
**----------------------------------------File Info----------------------------------------------
** File name : bsp_oled12864.c
** Latest modified date :
** Latest version :
** Description :
**-----------------------------------------------------------------------------------------------
** Created by : Luzhi
** Created date :2015年7月13日17:14:25
** Version :V1.0
** Description :
**-----------------------------------------------------------------------------------------------
** Modified by :
** Modified date :
** Version :
** Description :
************************************************************************************************/
#include "bsp.h"

/*    格式
				  128列
				 __/\__
				/      \
			 /	0 0 ...0   \
			/	x x ...x    \一个字符占8行
			|	A 5 ...0    /
			|	A 5 ...0   /
			/	  .
		64行		  .
			\	  .
			|	0 0 ...0   \
			|	x x ...x    \一个字符占8行
			\	A 5 ...0    /
			 \	A 5 ...0   /  
	
*/
u8 oledBuf[8][128];//oled的缓冲区
/************************************************************************************************
** Function name :			
** Description :配置OLED控制口线，模拟SPI模式
** 
** Input :
** Output :
** Return :
** Others :

************************************************************************************************/
void OLED_GPIO_Config(void)
{
	/* 1.配置GPIO,模拟SPI */
	GPIO_InitTypeDef GPIO_InitStructure;

	RCC_AHB1PeriphClockCmd(RCC_OLED_PORT, ENABLE);	/* 打开GPIO时钟 */

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		/* 设为输出口 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		/* 设为推挽输出模式 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	/* 上下拉电阻不使能 */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	/* IO口最大速度 */

	

	GPIO_InitStructure.GPIO_Pin = OLED_SCK_PIN;
	GPIO_Init(OLED_SCK_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = OLED_SDA_PIN;
	GPIO_Init(OLED_SDA_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = OLED_RST_PIN;
	GPIO_Init(OLED_RST_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = OLED_DC_PIN;
	GPIO_Init(OLED_DC_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = OLED_CS_PIN;
	GPIO_Init(OLED_CS_PORT, &GPIO_InitStructure);
}
				    
/************************************************************************************************
** Function name :			
** Description :初始化SSD1306
** 
** Input :
** Output :
** Return :
** Others :
	
************************************************************************************************/
void OLED_Init(void)
{ 	
	OLED_GPIO_Config();
	OLED_RST_1();
	bsp_DelayMS(50);
  	OLED_CS_0();
	bsp_DelayMS(100);
					  
	OLED_WrCmd(0xae);
	OLED_WrCmd(0xae);//--turn off oled panel
	OLED_WrCmd(0x00);//---set low column address
	OLED_WrCmd(0x10);//---set high column address
	OLED_WrCmd(0x40);//--set start line address  Set Mapping RAM Display Start Line (0x00~0x3F)
	OLED_WrCmd(0x81);//--set contrast control register
	OLED_WrCmd(0xcf); // Set SEG Output Current Brightness
	OLED_WrCmd(0xa0);//--Set SEG/Column Mapping     0xa0,0xa1
	OLED_WrCmd(0xc0);//Set COM/Row Scan Direction   0xc0,0xc8
	OLED_WrCmd(0xa6);//--set normal display
	OLED_WrCmd(0xa8);//--set multiplex ratio(1 to 64)
	OLED_WrCmd(0x3f);//--1/64 duty
	OLED_WrCmd(0xd3);//-set display offset	Shift Mapping RAM Counter (0x00~0x3F)
	OLED_WrCmd(0x00);//-not offset
	OLED_WrCmd(0xd5);//--set display clock divide ratio/oscillator frequency
	OLED_WrCmd(0x80);//--set divide ratio, Set Clock as 100 Frames/Sec
	OLED_WrCmd(0xd9);//--set pre-charge period
	OLED_WrCmd(0xf1);//Set Pre-Charge as 15 Clocks & Discharge as 1 Clock
	OLED_WrCmd(0xda);//--set com pins hardware configuration
	OLED_WrCmd(0x12);
	OLED_WrCmd(0xdb);//--set vcomh
	OLED_WrCmd(0x40);//Set VCOM Deselect Level
	OLED_WrCmd(0x20);//-Set Page Addressing Mode (0x00/0x01/0x02)
	OLED_WrCmd(0x02);//
	OLED_WrCmd(0x8d);//--set Charge Pump enable/disable
	OLED_WrCmd(0x14);//--set(0x10) disable
	OLED_WrCmd(0xa4);// Disable Entire Display On (0xa4/0xa5)
	OLED_WrCmd(0xa6);// Disable Inverse Display On (0xa6/a7) 
	OLED_WrCmd(0xaf);//--turn on oled panel
	OLED_Fill(0x00);
	OLED_SetPos(0,0);
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
void OLED_WrDat(unsigned char dat)//写数据
{
	unsigned char i;
	OLED_DC_1();
	for(i=0;i<8;i++) {
		if((dat << i) & 0x80)
		{
			OLED_SDA_1();
		}
		else
			OLED_SDA_0();
		OLED_SCK_0();
		OLED_SCK_1();
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
void OLED_WrCmd(unsigned char cmd)//写命令
{
	unsigned char i;
	OLED_DC_0();
	for(i=0;i<8;i++) {//发送一个八位数据
		if((cmd << i) & 0x80){
			OLED_SDA_1();
		} else {
			OLED_SDA_0();
		}
		OLED_SCK_0();
		OLED_SCK_1();
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
void OLED_SetPos(unsigned char x, unsigned char y)//设置起始点坐标
{
	OLED_WrCmd(0xb0 + y);
	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	OLED_WrCmd((x&0x0f)|0x01);
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
void OLED_Fill(unsigned char bmp_dat)//全屏填充
{
	unsigned char y,x;
	for(y=0;y<8;y++){
		OLED_WrCmd(0xb0+y);
		OLED_WrCmd(0x01);
		OLED_WrCmd(0x10);
		for(x=0;x<X_WIDTH;x++){
			OLED_WrDat(bmp_dat);
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
	
************************************************************************************************/
void OLED_CLS(void)//清屏
{
	OLED_Fill(0x00);
}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :
	gui刷新函数
************************************************************************************************/
void GUI_Exec(void)
{
	#if 1
   static u8 buf[8][128];
   u8 x,y;
   for(y=0; y<8; y++) {
      for(x=0;x<128;x++) {
	     if(buf[y][x] != oledBuf[y][x]) {
 	  	    buf[y][x] = oledBuf[y][x];
			OLED_WrCmd(0xb0+y);
	  	 	OLED_WrCmd(((x&0xf0)>>4)|0x10);
	 	 	OLED_WrCmd(x&0x0f);
			OLED_WrDat(buf[y][x]);
 	  	 }
	  }
   }
   #endif
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
void GUI_Clear(void)
{
   u8 x,y;
   for(y=0; y<8; y++) {
      for(x=0;x<128;x++) {
	     oledBuf[y][x] = 0;
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
	
************************************************************************************************/
void GUI_Logo(void)
{
   u8 x,y;
   for(y=0; y<8; y++) {
      for(x=0;x<128;x++) {
	     oledBuf[y][x] = LogoBmp[y][x];
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
	x:0~127,y:0~63,color=1点亮，0熄灭
************************************************************************************************/
void GUI_Point(u8 x, u8 y, u8 color)
{
   if(color == 0){
      oledBuf[y/8][x] &= (~(1 << (y % 8)));
   } else {
      oledBuf[y/8][x] |= (1 << (y % 8));
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
** 颜色只有两种 0无显示 1显示
************************************************************************************************/
void _Draw_Font_Prop(u8 x, u8 y, const GUI_FONT_PROP* pInfo, u16 color,u16 BackgroundColor,TEXT_OPTION Option)
{
	u8 i,j;
	color = color;
	BackgroundColor = BackgroundColor;
	switch(Option) {
		case TEXT_REVERSE:	//交换颜色
			for(i=0;i<pInfo->paCharInfo->XDist;i++) {
				for(j=0;j<pInfo->paCharInfo->XSize;j++) {
					if( ((pInfo->paCharInfo->pData[i*(pInfo->paCharInfo->BytesPerLine)+j/8])&( 0x80>>(j%8) )) == 0 ) {
						oledBuf[(y+i)/8][j] |= (1 << ((y+i) % 8));
					} else {
						oledBuf[(y+i)/8][j] &= ~(1 << ((y+i) % 8));
					}
				}
			}
			break;
		default:
			for(i=0;i<pInfo->paCharInfo->XDist;i++) {
				for(j=0;j<pInfo->paCharInfo->XSize;j++) {
					if( ((pInfo->paCharInfo->pData[i*(pInfo->paCharInfo->BytesPerLine)+j/8])&( 0x80>>(j%8) )) == 0 ) {
						oledBuf[(y+i)/8][x+j] &= ~(1 << ((y+i) % 8));
					} else {
						oledBuf[(y+i)/8][x+j] |= (1 << ((y+i) % 8));
						
					}
				}
			}
			break;
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
** 一个汉字的空格必须要用两个ascii的空格表示
************************************************************************************************/
void _Draw_One_HZ(u8 x, u8 y, u8 *text, FONT_SIZE FontSize, u16 color,u16 BackgroundColor,TEXT_OPTION Option)
{
	u32 index;
	GUI_CHARINFO hz;
	const GUI_FONT_PROP* pInfo;
	GUI_FONT_PROP Info;	
//	u8 ReadBuf[32];
	if( (*text == ' ')&&( *(text+1) == ' ') ) {//是空格,在 座字后面三个都是空格，座的编码是D7 F9
		index = 3755;
	} else {
		index = ((*text)-0xB0)*94 + (*(text+1)-0xA1);			//计算要找到的汉字的编码
	}
	switch(FontSize) {
		case HZ16x16:
			index = (*text)*256 + *(text+1);
			pInfo = GUIPROP_FindChar(&GUI_FontHZ16x16, index);
			hz.BytesPerLine = pInfo->paCharInfo->BytesPerLine;
			hz.XSize = pInfo->paCharInfo->XSize;
			hz.XDist = pInfo->paCharInfo->XDist;
			hz.pData = pInfo->paCharInfo->pData;
			Info.paCharInfo =&hz;
			pInfo = &Info;
			break;
		case HZ32x36:
			index = (*text)*256 + *(text+1);
			pInfo = GUIPROP_FindChar(&GUI_FontHZ32x36, index);
			hz.BytesPerLine = pInfo->paCharInfo->BytesPerLine;
			hz.XSize = pInfo->paCharInfo->XSize;
			hz.XDist = pInfo->paCharInfo->XDist;
			hz.pData = pInfo->paCharInfo->pData;
			Info.paCharInfo =&hz;
			pInfo = &Info;
			break;
		
		default:break;
	}
	_Draw_Font_Prop(x, y,pInfo, color,BackgroundColor,Option);
}
/************************************************************************************************
** Function name :			
** Description :
** 
** Input :
** Output :
** Return :
** Others :
** 水平方向显示字符串
************************************************************************************************/
void _Draw_String_HZ_H(u8 x, u8 y, u8 *text, FONT_SIZE FontSize,  u16 color,u16 BackgroundColor,TEXT_OPTION Option)
{
	u8 i=0;
	u8 x_size=0;
	switch(FontSize) {
		case HZ12x12:
			x_size = 12;
			break;
		case HZ16x16:
			x_size = 16;
			break;
		case HZ32x36:
			x_size = 32;
			break;
		case HZ48x48:
			x_size = 48;
			break;
		default:break;
	}
	while(*(text+i*2)) {
		_Draw_One_HZ((x+x_size*i),y,(text+i*2),FontSize, color, BackgroundColor,Option);
		i++;
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
void _Draw_One_Ascii(u8 x, u8 y, u8 *text, FONT_SIZE FontSize,  u16 color,u16 BackgroundColor,TEXT_OPTION Option)
{
//	GUI_CHARINFO ascii;
	//GUI_FONT_PROP* pInfo;
	GUI_FONT_PROP Info;	
//	u8 ReadBuf[12];
	switch(FontSize) {
		case ASCII8x12:
			if(*text == ' ') { 
				Info.paCharInfo = &GUI_FontAscii_8x12_CharInfo[12];
			} else if(*text == ':') {
				Info.paCharInfo = &GUI_FontAscii_8x12_CharInfo[10];
			} else if(*text == 'g') {
				Info.paCharInfo = &GUI_FontAscii_8x12_CharInfo[11];
			} else {
				Info.paCharInfo = &GUI_FontAscii_8x12_CharInfo[*text-'0'];
			}
			break;
		case ASCII24x24:
			if((*text >= '0')&&(*text <= '9')) {
				Info.paCharInfo = &GUI_FontAscii_24x24_CharInfo[*text-'0'];
			} else if(*text == ' '){
				Info.paCharInfo = &GUI_FontAscii_24x24_CharInfo[10];
			}
			break;
		default:
			break;
	}
	_Draw_Font_Prop(x, y,&Info, color, BackgroundColor,Option);
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
void _Draw_String_Ascii(u8 x, u8 y, u8 *text, FONT_SIZE FontSize,  u16 color,u16 BackgroundColor,TEXT_OPTION Option)
{
	u8 i=0;
	u8 next_x=0;
	
	while(*(text+i)) {
		_Draw_One_Ascii(x+next_x, y, (text+i), FontSize, color, BackgroundColor,Option);
		switch(FontSize) {
			case ASCII6x12:
				next_x += 6;
				break;
			case ASCII8x12:
				next_x += 8;
				break;
			case ASCII24x24:
				next_x += 24;
				break;
			case ASCII32x38:
				if((*(text+i) == ' ')||(*(text+i) == ':')) {
					next_x += 24;
				} else {
					next_x += 32;
				}
				break;
			default:
				break;
		}
		i++;
	}
}













