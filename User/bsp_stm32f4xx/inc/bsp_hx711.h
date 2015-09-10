#ifndef _BSP_HX711_H
#define _BSP_HX711_H




#define RCC_HX711_PORT RCC_AHB1Periph_GPIOA 		/* GPIO�˿�ʱ�� */

#define HX711_SCK_PORT	GPIOA
#define HX711_SCK_PIN	GPIO_Pin_4

#define HX711_SCK_1()	HX711_SCK_PORT->BSRRL = HX711_SCK_PIN
#define HX711_SCK_0()	HX711_SCK_PORT->BSRRH = HX711_SCK_PIN

#define HX711_DOUT_PORT	GPIOA
#define HX711_DOUT_PIN	GPIO_Pin_7
#define HX711_DOUT_READ()  ((HX711_DOUT_PORT->IDR & HX711_DOUT_PIN) != 0)	/* ��HX711_DOUT_PIN����״̬ */


#define HX711_SCK2_PORT	GPIOA
#define HX711_SCK2_PIN	GPIO_Pin_5

#define HX711_SCK2_1()	HX711_SCK2_PORT->BSRRL = HX711_SCK2_PIN
#define HX711_SCK2_0()	HX711_SCK2_PORT->BSRRH = HX711_SCK2_PIN

#define HX711_DOUT2_PORT	GPIOA		
#define HX711_DOUT2_PIN		GPIO_Pin_6	
#define HX711_DOUT2_READ()  ((HX711_DOUT2_PORT->IDR & HX711_DOUT2_PIN) != 0)	/* ��HX711_DOUT_PIN����״̬ */



//У׼����
//��Ϊ��ͬ�Ĵ������������߲��Ǻ�һ�£���ˣ�ÿһ����������Ҫ�������������������ʹ����ֵ��׼ȷ��
//�����ֲ��Գ���������ƫ��ʱ�����Ӹ���ֵ��
//������Գ���������ƫСʱ����С����ֵ��
//��ֵ����ΪС��


//������������ֵ����λ��g
#define AlarmValue 3000			

#define GAP_VALUE 360


typedef enum
{
	WEIGHT_STATUS_NORMAL,
	WEIGHT_STATUS_OVER_WEIGHT
}WeightStatus_Enum;	

typedef struct {
  WeightStatus_Enum	Status;
  u16 	WeightFullScale;	//�趨���������ֵ
  u16	LastWeight;
  u16	CurWeight;
  u16	CurWeightMax;
  u32   GapValue;
  u32 	DataRef;		//��׼������Ƥ��
  u32 	DataSample;		//��ǰ��������
  u32 	DataRef2;		//��׼������Ƥ��
  u32 	DataSample2;		//��ǰ��������
}Weight_TypeDef;

extern Weight_TypeDef	Weight;
void Hx711_GPIO_Config(void);
u32 HX711_Read(void);
u32 HX711_2_Read(void);
void Get_Weight(void);

#endif
