//
// Created by DjMastR on 2022. 10. 06..
//

#include "timer.h"

volatile uint32_t msTicks;

// typedef struct {
// uint32_t interval;
// uint32_t lastCheck;
// } idozites;

// IDOZITESI VALTOZOK

// ennyi idonkent jelenit meg egy uj kepet
idozites kepfrissites;
const uint32_t kepFrissiterInt = 50; // 20fps

// egy lovedek ennyi idonkent kerul magasabb pozicioba
idozites lovedekEmelkedes;
const int lovedekEmelkedesInt = 300;

// ennyi ideig marad ott egy kacsa
idozites kacsaElettartam;

const int kacsaElettatram0nehezsegen = 5000;

// cserelodo szovegek eseten ennyi idonkent
// tortenik a csere
idozites SzovegCsere;
const int SzovegCsereInt = 1000;

// kacsa elettartamanak alapkvantuma
const int kacsaElettatramKvantum = 1500;
idozites kacsaWait;
const int kacsaWaitKvantum = 500;


// egy villogo kacsa ennyi idonkent villog
idozites kacsaVillogas;
const int kacsaVillogasInt = 200;




/* Local prototypes */
/***************************************************************************//**
 * @brief SysTick_Handler
 *   Interrupt Service Routine for system tick counter
 *   No wrap around protection
 ******************************************************************************/
void SysTick_Handler(void)
{
  msTicks++;       /* increment counter necessary in Delay()*/
}

void InitCounter(void){
    msTicks = 0;

    // idointervallumok beallitasa
    kepfrissites.lastCheck = 0;
    kepfrissites.interval = kepFrissiterInt;
    lovedekEmelkedes.interval = lovedekEmelkedesInt;
    SzovegCsere.interval = SzovegCsereInt;
    SzovegCsere.lastCheck = 0;

    kacsaVillogas.interval = kacsaVillogasInt;
    kacsaVillogas.lastCheck = 0;
    /* Setup SysTick Timer for 1 msec interrupts  */
      if (SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000)) {
        while (1) ;
      }
}

/***************************************************************************//**
 * @brief Delays number of msTick Systicks (typically 1 ms)
 * @param dlyTicks Number of ticks to delay
 ******************************************************************************/
void Delay(uint32_t dlyTicks)
{
  uint32_t curTicks;

  curTicks = msTicks;
  while ((msTicks - curTicks) < dlyTicks) ;
}

