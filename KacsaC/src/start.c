/*
 * start.c
 *
 *  Created on: 2022. okt. 30.
 *      Author: DjMastR
 */

#include "start.h"
#include "game.h"

//PELDANYOK

const uint8_t nehezsegMin = 1;
const uint8_t nehezsegMax = 5;
uint8_t nehezseg;

//FUGGVENYEK

void initGame(){
	nehezseg = DEFAULT_DIFF;
	jatekosPozicio = DEFAULT_POZ;

	osszesKacsa = 0;
	lelottKacsa = 0;
	for(int i = 0; i < DEFAULT_BOARD_SIZE; i++){
		kacsaPozicio[i] = 0;
		kacsaMaradekIdo[i] = 0;
	}
	kacsaElozoPozicio = -1;

	lovedek.aktiv = false;
}

void nehezsegCsokkent(){
	if(nehezseg > nehezsegMin)
		nehezseg--;
}
void nehezsegNovel(){
	if(nehezseg < nehezsegMax)
		nehezseg++;
}
