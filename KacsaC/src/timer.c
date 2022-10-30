//
// Created by DjMastR on 2022. 10. 06..
//

#include "timer.h"

volatile uint32_t msTicks;

// typedef struct {
// uint32_t interval;
// uint32_t lastCheck;
// } idozites;

idozites kepfrissites;
const uint32_t kepFrissiterInt = 50; // 20fps
idozites lovedekEmelkedes;
const lovedekEmelkedesInt = 300;
idozites kacsaElettartam;
const kacsaElettatram0nehezsegen = 5000;

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

    kepfrissites.lastCheck = msTicks;
    kepfrissites.interval = kepFrissiterInt;
    lovedekEmelkedes.interval = lovedekEmelkedesInt;
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

RemainingTime CheckTime(RemainingTime input){
    RemainingTime temp;
    temp.lastCheck = msTicks;
    temp.timeRemaining = input.timeRemaining - (temp.lastCheck - input.lastCheck);
    return temp;
}
