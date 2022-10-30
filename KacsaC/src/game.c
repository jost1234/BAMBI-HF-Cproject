/*
 * game.c
 *
 *  Created on: 2022. okt. 30.
 *      Author: DjMastR
 */

#include "game.h"

//PELDANYOK

const uint8_t pozicioMin = 0;	// ezen poziciok között lehet
const uint8_t pozicioMax = 6;	// jatekos, kacsa vagy lovedek

const uint8_t kacsaDefaultIdoKvantum = 5;

uint8_t jatekosPozicio; // kozepen kezdjen

bool kacsaUtolso;
uint8_t osszesKacsa;	// eredményjelzönek kell
uint8_t lelottKacsa;	//

uint8_t kacsaPozicio;
uint8_t kacsaElozoPozicio;
uint8_t kacsaMaradekIdo;

lov_type lovedek;

//FUGGVENYEK

//Jatekos fuggvenyek

void jatekosBalraLep(){
	if(jatekosPozicio == pozicioMin)
		jatekosPozicio = pozicioMax;
	else jatekosPozicio--;
}

void jatekosJobbraLep(){
	if(jatekosPozicio == pozicioMax)
			jatekosPozicio = pozicioMin;
		else jatekosPozicio++;
}

uint8_t getPoz(){
	return jatekosPozicio;
}


//Kacsa fuggvenyek

void ujKacsa(){
	do{
		// ne ugyanoda kerüljön: majd nezzuk meg a randot, ha furan mukodik
		//kacsaPozicio = pozicioMin + rand()/RAND_MAX*pozicioMax;
		if(kacsaPozicio <= pozicioMax)
			kacsaPozicio = kacsaElozoPozicio +1;
		else
			kacsaPozicio = pozicioMin;
	} while (kacsaPozicio == kacsaElozoPozicio);
	osszesKacsa++;
	kacsaElettartam.lastCheck = msTicks;
	kacsaRender(kacsaPozicio, true);
}

void eltunoKacsa(){
	kacsaElozoPozicio = kacsaPozicio;
	kacsaRender(kacsaPozicio, false);
	kacsaPozicio = pozicioMax + 1;
	kacsaWait.lastCheck = msTicks;
	if(osszesKacsa == 25)
		kacsaUtolso = true;
}

void initKacsa(){
	kacsaElettartam.interval = nehezseg * kacsaElettatramKvantum;
	kacsaElettartam.lastCheck = 0;
	kacsaWait.interval = nehezseg * kacsaWaitKvantum;
	kacsaWait.lastCheck = 0;
}

void Kacsa(){
	if(kacsaPozicio > pozicioMax){
		if(msTicks - kacsaWait.lastCheck > kacsaWait.interval){
			kacsaWait.lastCheck = msTicks;
			ujKacsa();
		}
	}
	else{
		if(msTicks - kacsaElettartam.lastCheck > kacsaElettartam.interval){
			kacsaElettartam.lastCheck = msTicks;
			eltunoKacsa();
		}
	}
}

//Lovedek fuggvenyek

void lovedekKiloves(uint8_t poz){
	if(lovedek.aktiv)
		return;
	lovedek.aktiv = true;
	lovedek.pozicio = poz;
	lovedek.magassag = lm_alacsony;
	lovedekEmelkedes.lastCheck = msTicks;
}

void lovedekFeljebb(){

	if(lovedek.magassag == lm_alacsony){
		lovedek.magassag = lm_magas;
	}
	else if(lovedek.magassag == lm_magas){ // vagyis
		// ha eltalal egy kacsat: a kacsa meghal
		if(kacsaPozicio == lovedek.pozicio){
			eltunoKacsa();
			lelottKacsa++;
		}

		//lovedek alapállapotba kerül
		lovedek.aktiv = false;
		lovedek.magassag = lm_invalidErtek;
	}
}
