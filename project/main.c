#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>

#define LED_GREEN BIT6        // P1.6

short redrawScreen = 1;
u_int row = screenHeight/2;
u_int col = screenWidth;

void wdt_c_handler()
{
  static int count = 0;

  count++;
  if (count == 20) {
    count = 0;
    col--;
    redrawScreen = 1;
  }
}

void main()
{
  P1DIR |= LED_GREEN;         // green led on when cpu on
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();

  enableWDTInterrupts();      // enable periodic interrupts      
  or_sr(0x8);                 // GIE (enable interrupts)
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_WHITE);

  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      if (col == 0) {
	col = screenWidth;
	clearScreen(COLOR_WHITE);
      }
      for (int r = 0; r < 10; r++) {
	for (int c = 0; c < r; c++) {
	  drawPixel(col + c + 7, r + row - 10, COLOR_BLACK);
	  drawPixel(col - c + 7, r + row - 10, COLOR_BLACK);
	  drawPixel(col + c + 8, r + row - 10, COLOR_WHITE);
	}
      }
      for (int i = 0; i < 15; i++) {
	for (int j = 0; j < 15; j++) {
	  drawPixel(i + col, j + row, COLOR_BLACK);
	  drawPixel(i + col + 15, j + row, COLOR_WHITE);
	}
      }
    }
    P1OUT &= ~LED_GREEN;      // green off
    or_sr(0x10);              // CPU off
    P1OUT |= LED_GREEN;       // green on
  }
}
