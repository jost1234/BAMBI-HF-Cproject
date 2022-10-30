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

// a jatek kezdeti parametereinek beallitasa
void initGame();

// nehezseg soros portra irasahoz hasznalt segedfuggveny
// egy egy digites szamnak adja vissza az ascii kodjat
uint8_t charConverter(uint8_t num);

// csokkenti a nehezsegi szintet, ha meg nem minimalis
// ha valtozott a szint, azt jelzi a soros porton
void nehezsegCsokkent();

// noveli a nehezsegi szintet, ha meg nem maximalis
// ha valtozott a szint, azt jelzi a soros porton
void nehezsegNovel();
