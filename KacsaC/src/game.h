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
#include "timer.h"
#include "start.h"
//#include "kijelzo.h"

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
extern bool kacsaUtolso;

extern lov_type lovedek;

//FUGGVENYEK

void jatekosBalraLep();
void jatekosJobbraLep();
uint8_t getPoz();

extern void kacsaRender(uint8_t kacsaPoz, bool on);
void ujKacsa();
void eltunoKacsa();
void initKacsa();
void Kacsa();

void lovedekKiloves(uint8_t poz);
void lovedekFeljebb();
