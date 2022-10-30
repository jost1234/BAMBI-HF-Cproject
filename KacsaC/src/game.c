/*
 * game.c
 *
 *  Created on: 2022. okt. 30.
 *      Author: DjMastR
 */

#include "game.h"

//PELDANYOK

const uint8_t pozicioMin = 0;	// ezen poziciok kozott lehet
const uint8_t pozicioMax = 6;	// jatekos, kacsa vagy lovedek

const uint8_t kacsaDefaultIdoKvantum = 5;

uint8_t jatekosPozicio; // kozepen kezdjen

// ha ez true akkor a kacsa elkezd villogni majd meghal
bool kacsaHaldoklik;
//segedvaltozo a villogashoz
uint8_t haldokloKacsaCounter;

// ha ez igaz akkor vege lesz a jateknak
bool kacsaUtolso;
uint8_t osszesKacsa;	// eredmenyjelzonek kell
uint8_t lelottKacsa;	//

// kacsa parameterei
uint8_t kacsaPozicio;
uint8_t kacsaElozoPozicio;
uint8_t kacsaMaradekIdo;

// lovedek parameterei
lov_type lovedek;

//FUGGVENYEK

//Jatekos fuggvenyek

// a jatekos eggyel balrabb kerul
// ha a 0. szegmensben van, akkor atkerul a 6. szegmensbe
void jatekosBalraLep(){
	if(jatekosPozicio == pozicioMin)
		jatekosPozicio = pozicioMax;
	else jatekosPozicio--;
}

// a jatekos eggyel jobbrabb kerul
// ha a 6. szegmensben van, akkor atkerul a 0. szegmensbe
void jatekosJobbraLep(){
	if(jatekosPozicio == pozicioMax)
			jatekosPozicio = pozicioMin;
		else jatekosPozicio++;
}

// egyszeru getter a jatekos szegmensindexere
uint8_t getPoz(){
	return jatekosPozicio;
}


//Kacsa fuggvenyek

// letesz valahova egy uj kacsat
// nem kerulhet oda ahol az elobb volt, hogy kihivas legyen
void ujKacsa(){
	do{
		// ne ugyanoda kerüljön: majd nezzuk meg a randot, ha furan mukodik
		kacsaPozicio = pozicioMin + (int)((double)rand()/(double)RAND_MAX*(double)pozicioMax);
	} while (kacsaPozicio == kacsaElozoPozicio);
	osszesKacsa++;
	kacsaElettartam.lastCheck = msTicks;
	kacsaRender(kacsaPozicio, true);
	kacsaHaldoklik = false;
	haldokloKacsaCounter = 0;
}

// eltunik a kacsa, ha 25. volt akkor veget er a jatek
void eltunoKacsa(){
	kacsaHaldoklik = false;
	haldokloKacsaCounter = 0;

	kacsaElozoPozicio = kacsaPozicio;
	kacsaRender(kacsaPozicio, false);
	kacsaPozicio = pozicioMax + 1;
	kacsaWait.lastCheck = msTicks;
	if(osszesKacsa >= 25)
		kacsaUtolso = true;
}

// kacsa kezdeti parametereinek beallitasa
void initKacsa(){
	// kicsit rossz elnevezes, mert minek kisebb a nehezsegszint, annal nehezebb
	// ugyanis van egy elettartamkvantum, ez szorzodik a nehezsegszammal
	// a szorzat adja, hogy meddig el egy kacsa
	// vagyis az 1-es szint a legnehezebb, es az 5-os a legkonnyebb
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
		if((msTicks - kacsaElettartam.lastCheck > kacsaElettartam.interval) && !kacsaHaldoklik){
			kacsaElettartam.lastCheck = msTicks;
			eltunoKacsa();
		}
	}
}

//Lovedek fuggvenyek

// a jatekos kilo egy lovadeket alacsony magassagban a jelenlegi szegmenseben
void lovedekKiloves(uint8_t poz){
	if(lovedek.aktiv)
		return;
	lovedek.aktiv = true;
	lovedek.pozicio = poz;
	lovedek.magassag = lm_alacsony;
	lovedekEmelkedes.lastCheck = msTicks;
}

// a lovedek feljebb szall
// ha magasan volt elobb es felette kacsa van akkor eltalalja
void lovedekFeljebb(){

	if(lovedek.magassag == lm_alacsony){
		lovedek.magassag = lm_magas;
	}
	else if(lovedek.magassag == lm_magas){ // vagyis
		// ha eltalal egy kacsat: a kacsa meghal
		if(kacsaPozicio == lovedek.pozicio){
			kacsaHaldoklik = true;
			//eltunoKacsa();
			lelottKacsa++;
		}

		//lovedek alapállapotba kerül
		lovedek.aktiv = false;
		lovedek.magassag = lm_invalidErtek;
	}
}
