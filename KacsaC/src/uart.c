#include "uart.h"
/*
 * uart.c
 *
 *  Created on: 2022. okt. 30.
 *      Author: DjMastR
 */

// UART flagek
// volatile hogy a fordito ne egyszerusitse ki
volatile int UARTValue;
volatile bool UARTFlag;


// Az UART0 felkonfiguralasa
void InitUART(){
	CMU->HFPERCLKEN0 |= CMU_HFPERCLKEN0_GPIO;
	GPIO_PinModeSet(gpioPortF, 7, gpioModePushPull, 1);
	CMU_ClockEnable(cmuClock_UART0, true);

	GPIO_PinModeSet(gpioPortC, 0, gpioModeInput, 0);
	GPIO_PinModeSet(gpioPortC, 3, gpioModeInput, 0);
	GPIO_PinModeSet(gpioPortC, 4, gpioModeInput, 0);
	GPIO_PinModeSet(gpioPortC, 5, gpioModeInput, 0);

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

	// flag torlese
	UARTFlag = false;

	// uzenet hogy kesz az uart
	USART_Tx(UART0, 'j');
	USART_Tx(UART0, 'o');
	USART_Tx(UART0, 'h');
	USART_Tx(UART0, 'e');
	USART_Tx(UART0, 't');

}


// IT fuggveny
void UART0_RX_IRQHandler(void){
	USART_IntClear(UART0, USART_IEN_RXDATAV);
	UARTValue = USART_RxDataGet(UART0);
	UARTFlag = true;
}
