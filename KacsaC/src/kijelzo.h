/*
 * Kijelzo.h
 *
 *  Created on: 2022. okt. 25.
 *      Author: Jost Bence
 */
#pragma once

#include <stdint.h>
#include <stdbool.h>
#include "game.h"

// Kezdeti kepernyo beallitas, utana hasznalhato a kepernyo
    void LCD_Kijelzo_Init();

// Kiirja az allast osszes:lelott formatumban
    void eredmenyJelzo(uint8_t pOsszesKacsa, uint8_t pLelottKacsa);

// Megjeleniti a jatekost a legalso vonalon
    void jatekosRender(uint8_t jatekosPoz);

// Megjeleniti a kacsat a legfelso vonalon
    void kacsaRender(uint8_t kacsaPoz);

// Megjelenit egy lovedeket
    void lovedekRender(uint8_t lokedekPoz, bool lovedekMagassag);


// Egy kepkocka megjelenitese jatek kozben, egyeb funkcionalitasra nem alkalmas (minel gyorsabban lefusson, majd masik fv intezi pl villogast)
    // Kell hozza: jatekos pozicioja, kacsa pozicioja, lovedek(ek) pozicioja, lovedek magassaga: false alacsony, true magas
	// Ha eltalaltak kacsat:
	// 2-szer villog, ez ugy tortenjen hogy egy szamlalo 0 ha elozo kepen magasan volt alatta egy lovedek
void render(uint8_t jatekosPoz, uint8_t kacsaPoz, bool eltalaltKacsa,
		    uint8_t haldoklasi_fazis, uint8_t lovedekszam, uint8_t lokedekIdx[7],
			bool lovedekMagassag[7], uint8_t osszkacsa, uint8_t lelottkacsa);

