#ifndef SEGMENTLCD_H
#define SEGMENTLCD_H

#include "segmentlcdconfig.h"

/***************************************************************************//**
 * @addtogroup kitdrv
 * @{
 ******************************************************************************/

/***************************************************************************//**
 * @addtogroup SegmentLcd
 * @{
 ******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define SEGMENT_LCD_BLOCK_MODE_BLANK          0
#define SEGMENT_LCD_BLOCK_MODE_FILL           1
#define SEGMENT_LCD_BLOCK_MODE_OUTLINE        2
#define SEGMENT_LCD_BLOCK_MODE_OUTLINE_FILL   3

#define SEGMENT_LCD_NUM_BLOCK_COLUMNS         7

/*******************************************************************************
 ********************************   ENUMS   ************************************
 ******************************************************************************/

typedef enum {
  segmentLCDBlockModeBlank = SEGMENT_LCD_BLOCK_MODE_BLANK,              /**< Blank */
  segmentLCDBlockModeFill = SEGMENT_LCD_BLOCK_MODE_FILL,                /**< Fill */
  segmentLCDBlockModeOutline = SEGMENT_LCD_BLOCK_MODE_OUTLINE,          /**< Outline */
  segmentLCDBlockModeOutlineFill = SEGMENT_LCD_BLOCK_MODE_OUTLINE_FILL, /**< Outline and fill */
} SegmentLCD_BlockMode_TypeDef;

/*******************************************************************************
 *******************************  FUNCTIONS  ***********************************
 ******************************************************************************/

/* Bence belenyult a rendszerfajlokba mert zavarta a 250 soros syntax error*/
uint8_t getComFrom_EFM_Display_Text(uint8_t index, uint8_t i);
uint8_t getBitFrom_EFM_Display_Text(uint8_t index, uint8_t i);

/* Regular functions */
void SegmentLCD_AllOff(void);
void SegmentLCD_AllOn(void);
void SegmentLCD_AlphaNumberOff(void);
void SegmentLCD_Disable(void);
void SegmentLCD_Init(bool useBoost);
void SegmentLCD_LowerHex(uint32_t num);
void SegmentLCD_LowerNumber(int num);
void SegmentLCD_Number(int value);
void SegmentLCD_NumberOff(void);
void SegmentLCD_Symbol(lcdSymbol s, int on);
void SegmentLCD_UnsignedHex(uint32_t value);
void SegmentLCD_Write(const char *string);
void SegmentLCD_Block(
  SegmentLCD_BlockMode_TypeDef topMode[SEGMENT_LCD_NUM_BLOCK_COLUMNS],
  SegmentLCD_BlockMode_TypeDef botMode[SEGMENT_LCD_NUM_BLOCK_COLUMNS]);

#if defined(_SILICON_LABS_32B_SERIES_1)
// Dynamic charge redistribution
unsigned int SegmentLCD_segCnt(unsigned int segdl, unsigned int segdh);
void SegmentLCD_chargeRedistributionEnable(bool enable);
void SegmentLCD_updateCHGRDST(void);
#endif

#if defined(LCD_MODULE_CE322_1001)
void SegmentLCD_Array(int element, bool on);
#else
void SegmentLCD_ARing(int anum, int on);
void SegmentLCD_Battery(int batteryLevel);
void SegmentLCD_EnergyMode(int em, int on);
#endif

#ifdef __cplusplus
}
#endif

/** @} (end group SegmentLcd) */
/** @} (end group kitdrv) */

#endif
