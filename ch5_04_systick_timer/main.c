#include "main.h"

void Delays(__IO uint32_t dlyTicks);
volatile unsigned int msTicks = 0;

int main(void) {
	LED_Init();
	
	SysTick_Config(SystemCoreClock / 1000);
	
	while(1) {
		Delays(1000);
		GPIO_ToggleBits(GPIOD, ALL_LEDS);
	}
	return 0;
}



void Delays(__IO uint32_t dlyTicks) {
	uint32_t curTicks;
	curTicks = msTicks;
	while((msTicks - curTicks) < dlyTicks);
	msTicks = 0;
}



void SysTick_Handler(void) {
	msTicks++;
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

