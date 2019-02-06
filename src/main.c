//
// AIIT Template for using GPIOs with direct register access

// Includes ------------------------------------------------------------------
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "stm32f4xx.h"
#include "stm32f429i_discovery.h"
#include "stm32f429i_discovery_lcd.h"
#include "stm32f429i_discovery_ioe.h"

// Variables ------------------------------------------------------------------
volatile int32_t SysTickCnt;

// Functions ------------------------------------------------------------------
void SysTick_Handler(void) {	// will be called by SysTick Timer, every 10ms
															// see function: SysTick_Config()
  SysTickCnt++;

}

// GetUserButtonPressed 
// return: 
// 0: User Button not pressed
// 1: User Button pressed
static int GetUserButtonPressed () {

	return (GPIOA->IDR & 0x0001);

}	

int main(void) {
  
  RCC_ClocksTypeDef Clocks;
  static int32_t SysTickCnt_Hold;
	
  SysTickCnt = 0;
  SysTickCnt_Hold = 0;
  
  RCC_GetClocksFreq(&Clocks);
  SysTick_Config( Clocks.HCLK_Frequency/100 - 1 );	// 100 Hz ( T=10ms)
							
  LCD_Init();					// LCD initialization
  LCD_LayerInit(); 		// LCD Layer initialization
  LTDC_Cmd(ENABLE);  	// Enable the LTDC 
  LCD_SetLayer(LCD_FOREGROUND_LAYER);	// Set LCD foreground layer
  LCD_Clear(LCD_COLOR_BLUE);
  LCD_SetColors(LCD_COLOR_YELLOW, LCD_COLOR_BLUE); // TextColor,BackColor
 
  LCD_SetFont(&Font16x24);				//  line: 0...12	, column: 0...14		(default)
  LCD_SetPrintPosition(1,0);  		// line 1, column 0
  printf("   HTL-WELS    ");

  LCD_SetFont(&Font8x8);					// line: 0...39	, column: 0...29
  LCD_SetPrintPosition(39,0);			// line 39, column 0
  LCD_SetColors(LCD_COLOR_MAGENTA, LCD_COLOR_BLUE); // TextColor,BackColor
  printf("  (c) Bernhard Breinbauer  ");

  LCD_SetFont(&Font16x24);
  LCD_SetColors(LCD_COLOR_WHITE, LCD_COLOR_BLUE);
	

	// ToDo: Declare pointers for GPIO registers
	uint32_t *moder = (uint32_t *)0x40021800;



	// ToDo: Configure GPIO PG13 and PG14 as output
	
	
  while (1) {
    // main loop with 100ms cycle time
		// Delay Execution of Code below
    if( SysTickCnt - SysTickCnt_Hold < 10 ) {
			continue;  // 10 * 10ms = 100ms
		}
    SysTickCnt_Hold += 10;

    LCD_SetPrintPosition(6,0);	// line 6, column 0
    printf("Time:%5.1f sec",(float)SysTickCnt/(float)100.0);
		
		// ToDo: Blink LED by using pointers declared above

		
    
  }
}
