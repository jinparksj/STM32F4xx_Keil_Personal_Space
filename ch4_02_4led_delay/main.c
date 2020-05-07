#include "main.h"

void Delay(__IO uint32_t nCount);
void LED_Init(void);

int main(void) {
	LED_Init();
	GPIO_ResetBits(GPIOD, ALL_LEDS);
	
	while(1) {
		GPIO_ToggleBits(GPIOD, ALL_LEDS);
		Delay(0x3FFFFF);
	}
	return 0;
}                                                    