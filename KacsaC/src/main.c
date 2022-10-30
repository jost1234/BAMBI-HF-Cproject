#include "em_device.h"
#include "em_chip.h"
#include "timer.h"



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
typedef enum {_sInit, _sStart, _sJatek, _sJatekVege} allapot;


int main(void)
{
  /* Chip errata */
  CHIP_Init();

  //Timer inicializacio
  InitCounter();

  /* Infinite loop */
  while (1) {
  }
}
