all: main.elf

CPU	= msp430g2553
CFLAGS	= -mmcu=${CPU} -Os -I../h
LDFLAGS = -L../lib -L/opt/ti/msp430_gcc/include/

CC	= msp430-elf-gcc
AS	= msp430-elf-gcc -mmcu=${CPU} -c

main.elf: ${COMMON_OJBECTS} main.o wdt_handler.o
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ -lLcd -lp2sw -lTimer

clean:
	rm -f *.a *.o *.elf

load: main.elf
	msp430loader.sh $^
