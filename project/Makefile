all: lcd.elf

CPU	= msp430g2553
CFLAGS	= -mmcu=${CPU} -Os -I../h
LDFLAGS = -L../lib -L/opt/ti/msp430_gcc/include/

CC	= msp430-elf-gcc
AS	= msp430-elf-gcc -mmcu=${CPU} -c

lcd.elf: ${COMMON_OJBECTS} lcd.o wdt_handler.o switches.o led.o stateMachine.o buzzer.o dimmer_advance.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lLcd -lp2sw -lTimer

clean:
	rm -f *.a *.o *.elf

load: lcd.elf
	msp430loader.sh $^
