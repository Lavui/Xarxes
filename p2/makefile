CC=avr-gcc
CPPFLAGS=-DF_CPU=16000000UL
CFLAGS=-Wall -std=c99 -Os -mmcu=atmega328p -fshort-enums -Ilibpbn
LDFLAGS=-mmcu=atmega328p -std=c99
PORT=/dev/ttyACM0

vpath lib% libpbn

error_morse.o: error_morse.h

lan.o: lan.h error_morse.h

queue_t.o: queue_t.h lan.h error_morse.h

main.o: queue_t.h lan.h error_morse.h

app: main.o queue_t.o lan.o error_morse.o -lpbn
	$(CC) $(CFLAGS) -o app $^
	avr-objcopy -Oihex app app.hex


.PHONY: clean veryclean

clean:
	\rm -f *~ *.o *.s *.hex

veryclean: clean
	\rm -f app
