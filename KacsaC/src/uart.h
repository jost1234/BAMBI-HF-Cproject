/*
 * uart.h
 *
 *  Created on: 2022. okt. 30.
 *      Author: DjMastR
 */

#pragma once
#include "em_cmu.h"
#include "em_usart.h"
#include "em_gpio.h"

extern volatile int UARTValue;
extern volatile bool UARTFlag;

void InitUART();
