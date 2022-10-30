/*
 * entity.c
 *
 *  Created on: 2022. okt. 30.
 *      Author: Jost Bence
 */
#include <stdbool.h>
#include <stdint.h>


// inicializacios valtozok
bool start = false;

	// játék nehézsége: azt befolyásolja, hogy meddig él egy kacsa
const uint8_t nehezsegMin = 0;
uint8_t nehezsegMax = 5;
uint8_t nehezseg;
void nehezsegCsokkent(){
	if(nehezseg > nehezsegMin)
		nehezseg--;
}
void nehezsegNovel(){
	if(nehezseg < nehezsegMax)
		nehezseg++;
}


uint8_t osszesKacsa = 0;	// eredményjelzönek kell
uint8_t lelottKacsa = 0;	//

const uint8_t pozicioMin = 0;	// ezen poziciok között lehet
const uint8_t pozicioMax = 6;	// jatekos, kacsa vagy lovedek


// JATEKOS valtozok es fuggvenyek
uint8_t jatekosPozicio = 3; // kozepen kezdjen
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

// KACSA valtozok es fuggvenyek
uint8_t kacsaPozicio = 0;
uint8_t kacsaElozoPozicio;
bool haldokloKacsa = false; // allapotgepnek

void ujKacsa(){
	do{
		// ne ugyanoda kerüljön: majd nezzuk meg a randot, ha furan mukodik
		kacsaPozicio = pozicioMin + rand()*pozicioMax;
	} while (kacsaPozicio == kacsaElozoPozicio);

}



// lovedek magassagara enum (lm = "lovedek magassag")
// az invalid ertek csak biztonsagi okokbol van, nem biztos hogy kell
typedef enum {lm_alacsony, lm_magas, lm_invalidErtek} lovMag;

typedef struct{
	bool aktiv;			// ha true, akkor ki van love lovedek
	uint8_t pozicio; 	// min: 0 - max: 6
	lovMag magassag;
} lov_type;

lov_type lovedek;

void lovedekKiloves(uint8_t poz){
	lovedek.aktiv = true;
	lovedek.pozicio = poz;
	lovedek.magassag = lm_alacsony;
}

void lovedekFeljebb(){
	if(lovedek.magassag == lm_alacsony){
		lovedek.magassag = lm_magas;
	}
	else if(lovedek.magassag == lm_alacsony){ // vagyis
		// ha eltalal egy kacsat: a kacsa meghal
		if(kacsaPozicio == lovedek.pozicio){
			haldokloKacsa = true;
			lelottKacsa++;
		}

		//lovedek alapállapotba kerül
		lovedek.aktiv = false;
		lovedek.magassag = lm_invalidErtek;
	}
}

