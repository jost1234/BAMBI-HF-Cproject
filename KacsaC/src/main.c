#include "em_device.h"
#include "em_chip.h"
#include "timer.h"

#include "start.h"
#include "uart.h"
#include "kijelzo.h"
#include "segmentlcd.h"
#include <ctype.h>

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
 * 	- Iranyitas:
 * 		a : balra megy
 * 		d : jobbra megy
 * 		w : loves
 *
 */

/* ÁLLAPOTGÉP
 *
 *	_sInit: kezdöállapot, feladata a különbözö perifériák, változok beallitasa
 *	_sStart: ekkor lehet nehezseget allitani, 's' karakter érkezése esetén lépünk tovább
 *	_sJatek: a játékosidõ; addig megy, mig nem volt osszesen 25 kacsa
 *	-sJatekVege: a játékosidönek vége
 *
*/
typedef enum {_sInit,_sStart, _sJatek, _sJatekVege} allapot;

void Error(uint8_t button){
	//USART_Tx(UART0, button);

}




int main(void)
{
	// Chip errata
  CHIP_Init();
  InitCounter();
  InitUART();
  LCD_Kijelzo_Init();
  allapot state = _sInit;
  uint8_t button = 0;
  // Infinite loop
  while (1) {
	  switch (state){


	  case _sInit:
		  initGame();
		  SegmentLCD_Write("Start");
		  state = _sStart;
		  break;


	  case _sStart:
		  if(UARTFlag){
			  button = tolower(UARTValue);
			  switch (button){
			  case '+':
				  nehezsegNovel();
				  break;
			  case '-':
				  nehezsegCsokkent();
				  break;
			  case 's':
				  state = _sJatek;
				  break;
			  default:
				  Error(button);
				  break;
			  }
			  UARTFlag = false;
		  }


		  break;


	  case _sJatek:
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
			  default:
				  Error(button);
				  break;
			  }
			  UARTFlag = false;
		  }
		  // feljebb emelkedik egy lovedek
		  if(msTicks - lovedekEmelkedes.lastCheck > lovedekEmelkedes.interval){
			  lovedekEmelkedes.lastCheck = msTicks;
			  lovedekFeljebb();
		  }

		  // új kepernyokep
		  if(msTicks - kepfrissites.lastCheck > kepfrissites.interval){
			  kepfrissites.lastCheck = msTicks;
			  render(getPoz(),kacsaPozicio,0,0,lovedek,osszesKacsa,lelottKacsa);
		  }
		  if(osszesKacsa > 25)
			  state = _sJatekVege;
		  break;


	  case _sJatekVege:
		  break;


	  default:
		  break;
	  }
  }
}

