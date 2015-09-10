/*
*********************************************************************************************************
*
*	模块名称 : 利用STM32F4内部TIM输出PWM信号
*	文件名称 : bsp_tim_pwm.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*	Copyright (C), 2012-2013, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef __BSP_TIM_PWM_H
#define __BSP_TIM_PWM_H

void bsp_SetTIMOutPWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, TIM_TypeDef* TIMx, uint8_t _ucChannel,
	 uint32_t _ulFreq, uint32_t _ulDutyCycle);

#endif


