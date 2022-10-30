/*
 * start.c
 *
 *  Created on: 2022. okt. 30.
 *      Author: DjMastR
 */

#include "start.h"
#include "game.h"
#include "uart.h"
#include "segmentlcd.h"
#include "kijelzo.h"

//PELDANYOK

const uint8_t nehezsegMin = 1;
const uint8_t nehezsegMax = 5;
uint8_t nehezseg;

//FUGGVENYEK

// a jatek kezdeti parametereinek beallitasa
void initGame(){
	// az alap nehezseg 3-as (skala 1-5-ig)
	nehezseg = DEFAULT_DIFF;
	// a jatekos kozepen kezd
	jatekosPozicio = DEFAULT_POZ;

	osszesKacsa = 0;
	lelottKacsa = 0;
	kacsaUtolso = false;
	kacsaPozicio = 8;
	kacsaElozoPozicio = 8;

	// kezdetben nincs kilott lovedek
	lovedek.aktiv = false;
	lovedek.pozicio = 8;
	// biztonsagi kepernyo torles
	SegmentLCD_AllOff();
}

// nehezseg soros portra irasahoz hasznalt segedfuggveny
// egy egy digites szamnak adja vissza az ascii kodjat
uint8_t charConverter(uint8_t num){
	return num + '0';
}

// csokkenti a nehezsegi szintet, ha meg nem minimalis
// ha valtozott a szint, azt jelzi a soros porton
void nehezsegCsokkent(){
	if(nehezseg > nehezsegMin){
		nehezseg--;

		USART_Tx(UART0,charConverter(nehezseg));
	}
}

// noveli a nehezsegi szintet, ha meg nem maximalis
// ha valtozott a szint, azt jelzi a soros porton
void nehezsegNovel(){
	if(nehezseg < nehezsegMax){
		nehezseg++;

		USART_Tx(UART0,charConverter(nehezseg));
	}

}
