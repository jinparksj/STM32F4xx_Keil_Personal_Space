#include "main.h"

void EXTI0_Configuration(void);

uint16_t LED_CNT = 0;

int main(void) {
	LED_Init();
	SW_Init();
	
	TIM2_Configuration(1000);
	EXTI0_Configuration();
	
	GPIO_ResetBits(GPIOD, ALL_LEDS);
	
	while(1) {
	}
	return 0;
}




void TIM2_IRQHandler(void) {
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
		if (LED_CNT == 0) {
			GPIO_ResetBits(GPIOD, ALL_LEDS);
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			LED_CNT++;
		}
		else if (LED_CNT == 1) {
			GPIO_ResetBits(GPIOD, ALL_LEDS);
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			LED_CNT++;
		}
		else if (LED_CNT == 2) {
			GPIO_ResetBits(GPIOD, ALL_LEDS);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			LED_CNT++;
		}
		else if (LED_CNT == 3) {
			GPIO_ResetBits(GPIOD, ALL_LEDS);
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
			LED_CNT = 0;
		}
		else {
			GPIO_ResetBits(GPIOD, ALL_LEDS);
			LED_CNT = 0;
		}
	}
	TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
}

void EXTI0_IRQHandler(void) {
	if (EXTI_GetITStatus(EXTI_Line0) != RESET) {
		GPIO_SetBits(GPIOD, ALL_LEDS);
		Delay(0x3FFFFF);
		GPIO_ResetBits(GPIOD, ALL_LEDS);
		Delay(0x3FFFFF);
		GPIO_SetBits(GPIOD, ALL_LEDS);
		Delay(0x3FFFFF);
		GPIO_ResetBits(GPIOD, ALL_LEDS);
		Delay(0x3FFFFF);
	}
	EXTI_ClearITPendingBit(EXTI_Line0);
}

