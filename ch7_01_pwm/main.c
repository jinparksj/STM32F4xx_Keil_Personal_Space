#include "main.h"

#define MAX_Intensity 1600

void Timer4_Configuration(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Prescaler = 1 - 1;
	TIM_TimeBaseStructure.TIM_Period = MAX_Intensity - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	TIM_Cmd(TIM4, ENABLE);
}

void PWM_Configuration(void) {
	TIM_OCInitTypeDef TIM_OCStructure;
	
	TIM_OCStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCStructure.TIM_Pulse = 0;
	
	TIM_OC1Init(TIM4, &TIM_OCStructure);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM4, &TIM_OCStructure);
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM4, &TIM_OCStructure);
	TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM4, &TIM_OCStructure);
	TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);
	
}

void GPIO_PWM_Configuration(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);
	
	GPIO_InitStructure.GPIO_Pin = ALL_LEDS;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
}

int main(void) {
	GPIO_PWM_Configuration();
	Timer4_Configuration();
	PWM_Configuration();
	TIM2_Configuration(500);
	
	while(1) {
	}
	return 0;
}

static uint16_t Intensity = 10;


void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		if (Intensity > MAX_Intensity) Intensity = 10;
		
		TIM4->CCR1 = Intensity;
		TIM4->CCR2 = Intensity;
		TIM4->CCR3 = Intensity;
		TIM4->CCR4 = Intensity;
		
		Intensity *= 2;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}