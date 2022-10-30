/*
 * start.h
 *
 *  Created on: 2022. okt. 30.
 *      Author: DjMastR
 */

#pragma once
#include "game.h"

//Alaphelyzetetek defincioja
#define DEFAULT_DIFF 3
#define DEFAULT_POZ 3

//VALTOZOK
extern const uint8_t nehezsegMin;
extern const uint8_t nehezsegMax;
extern uint8_t nehezseg;

//FUGGVENYEK
void initGame();

void nehezsegCsokkent();

void nehezsegNovel();
