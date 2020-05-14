#include "main.h"
#include <stdio.h>

struct __FILE {
	int dummy;
	
};

FILE __stdout;

void Send_Character(uint16_t ch);

int fputc(int ch, FILE *f) {
	volatile char c = ch;
	Send_Character(c);
	
	return ch;
}

void USART1_Configuration(void);
void USART2_Configuration(void);


int main(void) {
	char str[150];
	float Value01 = 1234.4567;
	USART1_Configuration();
	USART2_Configuration();
	
	sprintf(str, "The value is %4.4f\n", Value01);
	
	printf("\nBluetooth Test\n");
	printf("\n%s\n", str);
	
	while(1) {
	}
	return 0;
}


void USART2_Configuration(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5 | GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	USART_Init(USART2, &USART_InitStructure);
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);
	USART_Cmd(USART2, ENABLE);
	
	//NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	
	NVIC_Init(&NVIC_InitStructure);
}

void Send_Character(uint16_t ch) {
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET);
	USART_SendData(USART2, ch);
	
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART_SendData(USART1, ch);
}

void USART2_IRQHandler(void) {
	uint16_t data;
	
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		data = USART_ReceiveData(USART2);
		Send_Character(data);
	}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	
}

void USART1_Configuration(void) {
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	
	GPIO_InitTypeDef GPIO_In;
	
	GPIO_In.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7;
	GPIO_In.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_In.GPIO_OType = GPIO_OType_PP;
	GPIO_In.GPIO_Mode = GPIO_Mode_AF;
	GPIO_In.GPIO_Speed = GPIO_Speed_100MHz;
	
	GPIO_Init(GPIOB, &GPIO_In);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	USART_InitTypeDef USART_InitStructure;
	
	USART_InitStructure.USART_BaudRate = 9600;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	
	USART_Init(USART1, &USART_InitStructure);
	USART_Cmd(USART1, ENABLE);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
}

void USART_Send(volatile char *c) {
	while(*c) {
		while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET) {
		}
		USART_SendData(USART1, *c);
		*c++;
	}
}

void Send_Charc(volatile char c) {
	while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	
	USART_SendData(USART1, c);
	
}


void USART2_IRQHandler(void) {
	uint16_t data;
	
	if (USART_GetITStatus(USART2, USART_IT_RXNE) == SET) {
		data = USART_ReceiveData(USART2);
		Send_Character(data);
	}
	USART_ClearITPendingBit(USART2, USART_IT_RXNE);
	
}