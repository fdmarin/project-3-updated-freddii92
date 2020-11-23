#ifndef switches_included
#define switches_included

#define SW1 BIT0                             // switch S1 is P2.0
#define SW2 BIT1                             // switch S2 is P2.1
#define SW3 BIT2                             // switch S3 is P2.2
#define SW4 BIT3                             // switch S4 is P2.3
#define SWITCHES (SW1 | SW2 | SW3 | SW4)     // all switches

void switch_init();
void switch_interrupt_handler();

extern char switch_state_down, switch_state_changed;

#endif // included
