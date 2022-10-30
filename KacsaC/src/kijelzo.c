/*
 * kijelzo.c
 *
 *  Created on: 2022. okt. 25.
 *      Author: Jost Bence
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"
#include "bsp.h"
#include "segmentlcd.h"
#include "bsp_trace.h"

#include "game.h"


// Kezdeti kepernyo beallitas, utana hasznalhato a kepernyo
void LCD_Kijelzo_Init(){
	// Kijelzo beallito fuggveny
    SegmentLCD_Init(false);

   // Letorli a kepernyot
   SegmentLCD_AllOff();
};

// Kiirja az allast osszes:lelott formatumban
void eredmenyJelzo(uint8_t pOsszesKacsa, uint8_t pLelottKacsa){
	SegmentLCD_Symbol(LCD_SYMBOL_COL10, 1);	// Kettospont kozepen
	    if(pOsszesKacsa > 99)
	        pOsszesKacsa = 99;
	    if(pLelottKacsa > 99)
	        pLelottKacsa = 99;
	    SegmentLCD_Number(100 * pOsszesKacsa + pLelottKacsa);
}

// Megjeleniti a jatekost a legalso vonalon
void jatekosRender(uint8_t jatekosPoz){
	uint8_t com, bit;

	//uint16_t bitfield = 0B1000;     // 3. elem

	    com = getComFrom_EFM_Display_Text(jatekosPoz, 3);
	    bit = getBitFrom_EFM_Display_Text(jatekosPoz,3);
	    LCD_SegmentSet(com, bit, true);
}

// Megjeleniti a kacsát az also sor legfelsö vonalán
void kacsaRender(uint8_t kacsaPoz, bool on){
	uint8_t com, bit;
	//uint16_t bitfield = 0B1;     // 0. elem

	com = getComFrom_EFM_Display_Text(kacsaPoz, 0);
	bit = getBitFrom_EFM_Display_Text(kacsaPoz, 0);
	LCD_SegmentSet(com, bit, on);
}

// Megjelenit egy lovedeket
void lovedekRender(lov_type lovedek){
	if(lovedek.aktiv == false)
		return;
	uint8_t com, bit;
	// Alacsony: 12. elem ; Magas: 8. elem
	uint8_t bitidx;

	if(lovedek.magassag == lm_alacsony) // alacsony lovedek
	        bitidx = 12;
	else bitidx =8;

	com = getComFrom_EFM_Display_Text(lovedek.pozicio, bitidx);
	bit = getBitFrom_EFM_Display_Text(lovedek.pozicio,bitidx);
	LCD_SegmentSet(com, bit, true);
}

void render(uint8_t jatekosPoz,uint8_t kacsaPoz, bool eltalaltKacsa,
		uint8_t haldoklasi_fazis, lov_type plovedek,
		uint8_t posszkacsa, uint8_t plelottkacsa)
{
	// Letorli a kepernyot
	SegmentLCD_AllOff();
	/* Freeze LCD to avoid partial updates */
	LCD_FreezeEnable(true);

	eredmenyJelzo(posszkacsa, plelottkacsa);

	jatekosRender(jatekosPoz);

	if(kacsaPozicio < 8)
		kacsaRender(kacsaPoz, true);

	if(eltalaltKacsa && haldoklasi_fazis%2)
		kacsaRender(kacsaPoz, false);

	lovedekRender(plovedek);

	/* Enable update */
	    LCD_FreezeEnable(false);


}
