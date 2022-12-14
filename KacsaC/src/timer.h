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
	uint32_t interval;
	uint32_t lastCheck;
} idozites;

extern volatile uint32_t msTicks;


extern idozites SzovegCsere;
extern const int SzovegCsereInt;

extern idozites kepfrissites;

extern idozites lovedekEmelkedes;

extern idozites kacsaElettartam;
extern const int kacsaElettatramKvantum;
extern idozites kacsaWait;
extern const int kacsaWaitKvantum;
extern idozites kacsaVillogas;
extern const int kacsaVillogasInt;


void InitCounter(void);
void SysTick_Handler(void);
void Delay(uint32_t dlyTicks);
