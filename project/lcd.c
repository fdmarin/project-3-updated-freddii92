#include <msp430.h>
#include <libTimer.h>
#include <lcdutils.h>
#include <lcddraw.h>
#include "lcd.h"
#include "led.h"
#include "buzzer.h"
#include "switches.h"

#define LED_GREEN BIT6        // P1.6

short redrawScreen = 1;
u_int rock_one_row = 60;
u_int rock_two_row = 0;
u_int rock_three_row = 120;
u_int tree_one = 50;
u_int tree_two = 100;
u_int tree_three = 150;
u_int col = screenWidth;
int car_position = (screenWidth/2 - 20);
int right = (screenWidth/2 + 8);
int left = (screenWidth/2 - 20);
int car_color;
int left_siren = COLOR_BLACK;
int right_siren = COLOR_BLACK;
  
void wdt_c_handler()
{
  static int count = 0;
  static char blink_count = 0;

  count++;
  if (count == 20) {
    count = 0;
    rock_one_row++;
    rock_two_row++;
    rock_three_row++;
    tree_one++;
    tree_two++;
    tree_three++;
    redrawScreen = 1;
  }
  if (++blink_count == speed) {
    switch_interrupt_handler();
    blink_count = 0;
  }
}

void main()
{
  P1DIR |= LED_GREEN;         // green led on when cpu on
  P1OUT |= LED_GREEN;
  configureClocks();
  lcd_init();
  led_init();
  buzzer_init();

  enableWDTInterrupts();      // enable periodic interrupts      
  or_sr(0x8);                 // GIE (enable interrupts)
  u_char width = screenWidth, height = screenHeight;

  clearScreen(COLOR_FOREST_GREEN);

  make_road();
  make_car();

  while (1) {
    if (redrawScreen) {
      redrawScreen = 0;
      if (rock_one_row   == screenHeight +  3) rock_one_row   = 0;
      if (rock_two_row   == screenHeight +  3) rock_two_row   = 0;
      if (rock_three_row == screenHeight +  3) rock_three_row = 0;
      if (tree_one       == screenHeight + 10) tree_one       = 0;
      if (tree_two       == screenHeight + 10) tree_two       = 0;
      if (tree_three     == screenHeight + 10) tree_three     = 0;
      make_siren();
      make_rock();
      make_tree();
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
  for (int r = 0; r < 30; r++) {
    for (int c = 0; c < 16; c++) {
      drawPixel(c + car_position, r + (screenHeight - 35), COLOR_BLACK);
    }
  }
  for (int i = 0; i < 16; i++) {
    drawPixel(i + car_position, (screenHeight - 25), COLOR_WHITE);
    drawPixel(i + car_position, (screenHeight - 15), COLOR_WHITE);
  }
}

void make_siren()
{
  for (int j = 0; j < 3; j++) {
    for (int k = 0; k < 3; k++) {
      drawPixel(k + car_position + 4, j + (screenHeight - 21), left_siren);
      drawPixel(k + car_position + 9, j + (screenHeight - 21), right_siren);
    }
  }
}

void make_rock()
{
  for (int r = 0; r < 5; r++) {
    for (int c = 0; c < 5; c++) {
      drawPixel(c + (screenWidth/2 + 40), r + rock_one_row      , COLOR_CHOCOLATE);
      drawPixel(c + (screenWidth/2 + 40), r + rock_one_row - 6  , COLOR_FOREST_GREEN);
      drawPixel(c + 20                  , r + rock_two_row      , COLOR_CHOCOLATE);
      drawPixel(c + 20                  , r + rock_two_row - 6  , COLOR_FOREST_GREEN);
      drawPixel(c + 20                  , r + rock_three_row    , COLOR_CHOCOLATE);
      drawPixel(c + 20                  , r + rock_three_row - 6, COLOR_FOREST_GREEN);
    }
  }
}

void make_tree()
{
  for (int r = 0; r < 10; r++) {
    for (int c = 0; c < 10; c++) {
      drawPixel(c + 15                , r + tree_one       , COLOR_GREEN);
      drawPixel(c + 15                , r + tree_one - 11  , COLOR_FOREST_GREEN);
      drawPixel(c + screenWidth/2 + 40, r + tree_two       , COLOR_GREEN);
      drawPixel(c + screenWidth/2 + 40, r + tree_two - 11  , COLOR_FOREST_GREEN);
      drawPixel(c + screenWidth/2 + 40, r + tree_three     , COLOR_GREEN);
      drawPixel(c + screenWidth/2 + 40, r + tree_three - 11, COLOR_FOREST_GREEN);
    }
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 3; j++) {
      drawPixel(j + 18                , i + tree_one + 10  , COLOR_BROWN);
      drawPixel(j + screenWidth/2 + 43, i + tree_two + 10  , COLOR_BROWN);
      drawPixel(j + screenWidth/2 + 43, i + tree_three + 10, COLOR_BROWN);
    }
  }
}
