/*
 * game_over.c
 *
 *  Created on: 2022. okt. 30.
 *      Author: Jost Bence
 */
#include "game.h"
#include "szovegek.h"


// index valtozok
uint8_t endCreditsIdx = 0;
uint8_t restartStringIdx = 0;
uint8_t startStringIdx = 0;

// eloszor 1x az endcredit fut le, majd ciklikusan a restartString
bool restartStringEnable = false;
void gameOverInit(){
	endCreditsIdx = 0;
	restartStringIdx = 0;
	startStringIdx = 0;
	restartStringEnable = false;

	// Letorli a kepernyot
	   SegmentLCD_AllOff();

	// pont beirasa:
	end_credits[3][0] = lelottKacsa/10 + '0';
	end_credits[3][1] = lelottKacsa%10 + '0';
}

const uint8_t end_credits_size = 14;
char end_credits[][DEFAULT_BOARD_SIZE] =
{"Game","Over","Points:","  ","Made","by","Jost","Mark","Benedek","JXOV52","and","Tabajdi","Mate","JZX5Y4"};

const uint8_t start_string_size = 4;
const char restart_string[][DEFAULT_BOARD_SIZE] =
{"Press","R","to","Restart"};

const char start_string[][DEFAULT_BOARD_SIZE] =
{"Press","S","to","Start"};

void endCreditsPrint(char* stringArray[DEFAULT_BOARD_SIZE],uint8_t size, uint8_t idx){
	if(idx<size)
		SegmentLCD_Write(stringArray[idx]);
}
