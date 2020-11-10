#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>

#define LED_GREEN BIT6        // P1.6

short redrawScreen = 1;
u_int row = 10;
u_int col = 10;

void wdt_c_handler()
{
  static int count = 0;

  count++;
  if (count == 150) {
    count = 0;
    row++;
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
      clearScreen(COLOR_WHITE);
      if (row == screenHeight) {
	row = 0;
      }
      drawString5x7(col, row, "TEST", COLOR_BLACK, COLOR_WHITE);
    }
    P1OUT &= ~LED_GREEN;      // green off
    or_sr(0x10);              // CPU off
    P1OUT |= LED_GREEN;       // green on
  }
}
