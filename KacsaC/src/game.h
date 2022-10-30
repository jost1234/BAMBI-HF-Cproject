/*
 * game.h
 *
 *  Created on: 2022. okt. 30.
 *      Author: DjMastR
 */

#pragma once
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include "timer.h"

#define DEFAULT_BOARD_SIZE 7

//TIPUSOK

// lovedek magassagara enum (lm = "lovedek magassag")
// az invalid ertek csak biztonsagi okokbol van, nem biztos hogy kell
typedef enum {lm_alacsony, lm_magas, lm_invalidErtek} lovMag;

typedef struct{
	bool aktiv;			// ha true, akkor ki van love lovedek
	uint8_t pozicio; 	// min: 0 - max: 6
	lovMag magassag;
} lov_type;

//VALTOZOK

extern uint8_t jatekosPozicio; // kozepen kezdjen

extern uint8_t osszesKacsa;	// eredményjelzönek kell
extern uint8_t lelottKacsa;	//

extern uint8_t kacsaPozicio;
extern uint8_t kacsaElozoPozicio;
extern uint8_t kacsaMaradekIdo;
extern volatile uint32_t msTicks;
extern idozites kepfrissites;
extern lov_type lovedek;



//FUGGVENYEK

void jatekosBalraLep();

void jatekosJobbraLep();

uint8_t getPoz();

void ujKacsa();

void lovedekKiloves(uint8_t poz);

void lovedekFeljebb();
