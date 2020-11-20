#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include <p2switches.h>

#define LED_GREEN BIT6        // P1.6

short redrawScreen = 1;
u_int row = 0;
u_int col = screenWidth;
u_int car_right = (screenWidth/2 + 8);

void make_car();
void make_road();

void wdt_c_handler()
{
  static int count = 0;

  count++;
  if (count == 20) {
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

  clearScreen(COLOR_FOREST_GREEN);

  make_road();
  make_car(0);

  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      if (row == screenHeight + 3) {
	row = 0;
      }
      make_rock();
    }
    P1OUT &= ~LED_GREEN;      // green off
    or_sr(0x10);              // CPU off
    P1OUT |= LED_GREEN;       // green on
  }
}

void make_road()
{
  int count = 0;
  for (int r = 0; r < screenHeight; r++) {
    for (int c = 0; c < 60; c++) {
      drawPixel(c + 35, r, COLOR_GRAY);
    }
    if (count < 5 == 0) {
      drawPixel(65, r, COLOR_YELLOW);
    }
    if (count == 10) count = 0;
    count++;
  }
}

void make_car()
{
  int position = car_right;
 
  for (int r = 0; r < 30; r++) {
    for (int c = 0; c < 16; c++) {
      drawPixel(c + position, r + (screenHeight - 35), COLOR_BLUE);
    }
  }
  for (int i = 0; i < 16; i++) {
    drawPixel(i + position, (screenHeight - 25), COLOR_BLACK);
    drawPixel(i + position, (screenHeight - 15), COLOR_BLACK);
  }
}

void make_rock()
{
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      drawPixel(c + (screenWidth/2 + 12), r + row, COLOR_CHOCOLATE);
      drawPixel(c + (screenWidth/2 + 12), r + row - 6, COLOR_GRAY);
    }
  }
}
