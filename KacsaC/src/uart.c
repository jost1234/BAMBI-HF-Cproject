#include "uart.h"

/*
 * uart.c
 *
 *  Created on: 2022. okt. 30.
 *      Author: DjMastR
 */

volatile int UARTValue;

void InitUART(){
	CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
	GPIO_PinModeSet(gpioPortF, 7, gpioModePushPull, 1);
	CMU_ClockEnable(cmuClock_UART0, true);

	USART_InitAsync_TypeDef UART0_init = USART_INITASYNC_DEFAULT;
	USART_InitAsync(UART0, &UART0_init);
	GPIO_PinModeSet(gpioPortE, 0, gpioModePushPull, 1);
	GPIO_PinModeSet(gpioPortE, 1, gpioModeInput, 0);
	UART0->ROUTE |= UART_ROUTE_LOCATION_LOC1;
	UART0->ROUTE |= UART_ROUTE_TXPEN | UART_ROUTE_RXPEN;

	USART_IntClear(UART0, USART_IEN_RXDATAV);
	USART_IntEnable(UART0, USART_IEN_RXDATAV);
	NVIC_ClearPendingIRQ(UART0_RX_IRQn);
	NVIC_EnableIRQ(UART0_RX_IRQn);
}



void UART0_RX_IRQHandler(void){
	USART_IntClear(UART0, USART_IEN_RXDATAV);
	UARTValue = USART_RxDataGet(UART0);

}
