#include "em_device.h"
#include "em_chip.h"


#include "start.h"
#include "uart.h"
#include "kijelzo.h"
#include "segmentlcd.h"
#include "timer.h"
#include <ctype.h>
#include "szovegek.h"

/*
 * Kacsa vadaszat (Soros port)
 * Keszitette:
 * 	Jost Mark Benedek (JXOV52)
 * 	Tabajdi Mate (JZX5Y4)
 *
 * Jatek celja: A kepernyon veletlenszeruen megjelennek kacsak, amiket le kell tudni vadaszni.
 * A kacsak az also (alfanumerikus) kijelzo valamelyik negy mezejenek legfelso vizszintes szegmenseben
 * jelenhetnek meg veletlenszeruen (lasd zold jelolest), majd a nehezsegi szinttol fuggo ideig maradnak.
 * A vadasznak (also vizszintes szegmens) alajuk kell allnia es leloni oket.
 *
 * Kezeles:
 * 	- Nehezsegi szint allitas:
 * 		+ : noveles
 * 		- : csokkentes
 *
 * 	- Jatek inditas: s
 *
 *  - Jatek ujrainditas: r
 *
 * 	- Iranyitas:
 * 		a : balra megy
 * 		d : jobbra megy
 * 		w : loves
 *
 */

/* ALLLAPOTGEP
 *
 *	_sInit: kezdoallapot, feladata a kulonbozo periferiak es valtozok beallitasa
 *	_sStart: ekkor lehet nehezseget allitani, 's' karakter erkezese eseten lepunk tovabb
 *	_sJatek: a jatekido; addig megy, mig nem volt osszesen 25 kacsa
 *	-sJatekVege: a jatekosidonek vege
 *
*/
typedef enum {_sInit,_sStart, _sJatek, _sJatekVege} allapot;

void Error(uint8_t button){
	USART_Tx(UART0, 0);
}


int main(void)
{
	// Chip errata
  CHIP_Init();
  // Periferiak (szamlalo, uart, lcd) beallitasa
  InitCounter();
  InitUART();
  LCD_Kijelzo_Init();

  // a kacsak random helyen szuletnek ujra, ehhez szukseg van random seedre
  // ehhez a lebego gpioport c-t hasznaljuk
  srand(GPIO_PortInGet(gpioPortC) * (msTicks+123));

  // kezdoallapot _sInit
  allapot state = _sInit;

  // ebben taroljuk az uarton erkezett karaktereket
  uint8_t button = 0;

  // segedvaltozo szovegkiirashoz
  startStringIdx = 0;


  // Infinite loop
  while (1) {
	  switch (state){


	  case _sInit:
		  // jatekparameterek beallitasa
		  initGame();

		  state = _sStart;
		  break;


	  case _sStart:
		  // nezzuk, hogy jott e karakter
		  if(UARTFlag){
			  button = tolower(UARTValue);
			  switch (button){
			  // '+' eseten nehezsegszint novelese
			  case '+':
				  nehezsegNovel();
				  break;
			  // '-' eseten nehezsegszint csokkentese
			  case '-':
				  nehezsegCsokkent();
				  break;
				  // s karakter eseten allapotvaltas: kezdjuk a jatekot
			  case 's':
				  // kacsa beallitasa
				  initKacsa();

				  state = _sJatek;
				  break;
			  default:
				  Error(button);
				  break;
			  }
			  // it flag torlese
			  UARTFlag = false;
		  }
		  if(msTicks - SzovegCsere.lastCheck > SzovegCsere.interval){
		  			  SzovegCsere.lastCheck = msTicks;
		  			SegmentLCD_Write(start_string[startStringIdx%start_string_size]);
		  			startStringIdx++;
		  }

		  break;


	  case _sJatek:
		  // nezzuk, hogy jott e karakter
		  if(UARTFlag){
			  button = tolower(UARTValue);
			  switch (button){
			  case 'a':
				  jatekosBalraLep();
				  break;
			  case 'd':
				  jatekosJobbraLep();
				  break;
			  case 'w':
				  lovedekKiloves(getPoz());
				  break;
				  // csalokarakter: azonnal megnyeri a jatekot 42 ponttal
			  case 'm':
				  osszesKacsa = 26;
				  lelottKacsa = 42;
			  default:
				  // varatlan karakter eseten hibakezelo fuggveny hivasa
				  Error(button);
				  break;
			  }
			  // it flag torlese
			  UARTFlag = false;
		  }
		  // feljebb emelkedik egy lovedek, es esetleg eltalal egy kacsat
		  if(msTicks - lovedekEmelkedes.lastCheck > lovedekEmelkedes.interval){
			  lovedekEmelkedes.lastCheck = msTicks;
			  lovedekFeljebb();
		  }
		  // ha villogtatni kell a kacsat, akkor az alabbi sorok felelnek erte
		  if(kacsaHaldoklik && ((msTicks - kacsaVillogas.lastCheck) > kacsaVillogas.interval)){
			  kacsaVillogas.lastCheck = msTicks;
			  haldokloKacsaCounter++;
			  if(haldokloKacsaCounter == 5)
				  eltunoKacsa();
		  }
		  // Uj kepernyokep
		  if(msTicks - kepfrissites.lastCheck > kepfrissites.interval){
			  kepfrissites.lastCheck = msTicks;
			  render(getPoz(),kacsaPozicio,kacsaHaldoklik,haldokloKacsaCounter,lovedek,osszesKacsa,lelottKacsa);
		  }


		  //kacsa controll
		  Kacsa();

		  if(kacsaUtolso){

			  state = _sJatekVege;
			  gameOverInit();
		  }

		  break;


	  case _sJatekVege:
		  // nezzuk, hogy jott e karakter
		  if(UARTFlag){
			  button = tolower(UARTValue);
			  if(button == 'r'){
				  state = _sInit;
				  // it flag torlese
				  UARTFlag = false;

				  break;
			  }
			  // it flag torlese
			  UARTFlag = false;
		  }

		  // end credit lefut 1x
		  // majd restart szoveg vegtelen loopban
		  if(msTicks - SzovegCsere.lastCheck > SzovegCsere.interval){
			  eredmenyJelzo(0,lelottKacsa);
			  SzovegCsere.lastCheck = msTicks;
			  if(!restartStringEnable){
				  SegmentLCD_Write(end_credits[endCreditsIdx++]);
				  if(endCreditsIdx == end_credits_size)
					  restartStringEnable = true;
			  }
			  else{
				  SegmentLCD_Write(restart_string[(restartStringIdx++)%start_string_size]);

			  }

		  }
		  break;


	  default:
		  break;
	  }
  }
}

