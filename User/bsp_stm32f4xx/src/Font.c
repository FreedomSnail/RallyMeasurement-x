/****************************************Copyright(c)********************************************
**
**                             
**
**----------------------------------------File Info----------------------------------------------
** File name : font.c
** Latest modified date :
** Latest version :
** Description :
**-----------------------------------------------------------------------------------------------
** Created by : ף��һ
** Created date :2012��8��26��9:47:32
** Version :V1.1.0
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
** 
************************************************************************************************/
const GUI_FONT_PROP* GUIPROP_FindChar(const GUI_FONT* SourceLib, unsigned short int c)
{
	const GUI_FONT_PROP* TargetChar;
	//TargetChar = (*SourceLib).pProp;
  	for (TargetChar = SourceLib->pProp; TargetChar; TargetChar=(const GUI_FONT_PROP*) TargetChar->pNext) {
    	if ((c>=TargetChar->First) && (c<=TargetChar->Last))
     		break;
  	}
  	return TargetChar;
}

