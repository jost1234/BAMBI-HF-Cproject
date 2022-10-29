/*
 * timer.h
 *
 *  Created on: 2022. okt. 10.
 *      Author: DjMastR
 */
#pragma once
#include "em_timer.h"

typedef struct {
    uint32_t lastCheck;
    uint32_t timeRemaining;
} RemainingTime;

void InitCounter(void);
void SysTick_Handler(void);
void Delay(uint32_t dlyTicks);
RemainingTime CheckTime(RemainingTime input);
