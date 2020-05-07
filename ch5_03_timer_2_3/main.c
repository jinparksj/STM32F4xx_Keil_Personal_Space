#include "main.h"

void TIM3_Configuration(void) {
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	
	TIM_TimeBaseStructure.TIM_Prescaler = 800-1;
	TIM_TimeBaseStructure.TIM_Period = 10000 - 1;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
	TIM_Cmd(TIM3, ENABLE);
	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
	
}

int main(void) {
	LED_Init();
	TIM2_Configuration(1000);
	TIM3_Configuration();
	
	while(1) {
	
	}
	return 0;
}


void TIM2_IRQHandler(void) {
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
			GPIO_ToggleBits(GPIOD, GPIO_Pin_12 | GPIO_Pin_13);
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		}
}

void TIM3_IRQHandler(void) {
		if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET) {
			GPIO_ToggleBits(GPIOD, GPIO_Pin_14 | GPIO_Pin_15);
			TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
		}
}

