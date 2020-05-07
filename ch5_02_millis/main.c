#include "main.h"


int main(void) {
	LED_Init();
	TIM2_Configuration();
	
	while(1) {
	
	}
	return 0;
}


void TIM2_IRQHandler(void) {
		if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
			GPIO_ToggleBits(GPIOD, ALL_LEDS);
			TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		}
}

