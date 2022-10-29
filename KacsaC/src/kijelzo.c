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


// Kezdeti kepernyo beallitas, utana hasznalhato a kepernyo
void LCD_Kijelzo_Init(){
	// Kijelzo beallito fuggveny
    SegmentLCD_Init(false);

   // Letorli a kepernyot
   SegmentLCD_AllOff();
};

// Kiirja az allast osszes:lelott formatumban
void eredmenyJelzo(int pOsszesKacsa, int pLelottKacsa){
	SegmentLCD_Symbol(LCD_SYMBOL_DEGC, 1);	// Kettospont kozepen
	    if(pOsszesKacsa > 25)
	        pOsszesKacsa = 25;
	    if(pLelottKacsa > 25)
	        pLelottKacsa = 25;
	    SegmentLCD_Number(100 * pOsszesKacsa + pLelottKacsa);
}
