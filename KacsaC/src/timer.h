/*
 * timer.h
 *
 *  Created on: 2022. okt. 10.
 *      Author: DjMastR
 */
#pragma once
#include "em_timer.h"
#include "em_cmu.h"
#include "bsp.h"


typedef struct {
    uint32_t lastCheck;
    uint32_t timeRemaining;
} RemainingTime;

typedef struct {
	uint32_t interval;
	uint32_t lastCheck;
} idozites;


extern idozites SzovegCsere;
extern const int SzovegCsereInt;


void InitCounter(void);
void SysTick_Handler(void);
void Delay(uint32_t dlyTicks);
RemainingTime CheckTime(RemainingTime input);


