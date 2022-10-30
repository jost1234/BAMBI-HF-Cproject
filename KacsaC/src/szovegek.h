/*
 * game_over.h
 *
 *  Created on: 2022. okt. 30.
 *      Author: Jost Bence
 */

#pragma once
#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "segmentlcd.h"
#include "kijelzo.h"

// ciklikusan kiir egy szoveget az also sorba
void endCreditsPrint(char* stringArray[DEFAULT_BOARD_SIZE],uint8_t size, uint8_t idx);

// a jatek vegen meg kell hivni ahhoz, hogy jol fusson le az endcredits
void gameOverInit();


// kulso definiciok szovegek.c-bol
extern const uint8_t end_credits_size;
extern char end_credits[][DEFAULT_BOARD_SIZE];
extern const uint8_t start_string_size;
extern const char restart_string[][DEFAULT_BOARD_SIZE];
extern const char start_string[][DEFAULT_BOARD_SIZE];

extern uint8_t endCreditsIdx;
extern uint8_t restartStringIdx;
extern uint8_t startStringIdx;
extern bool restartStringEnable;
