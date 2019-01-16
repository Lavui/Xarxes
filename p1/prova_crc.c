#include <stdbool.h>
#include <pbn.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "error_morse.h"

#define LEN_W 5

int main(void){
	serial_open();
	sei();
	print("Serial open.");
	char s[LEN_W+3];
	while(1){
		readline(s, LEN_W);
		uint8_t *str2;
		str2 = (uint8_t *)&s;
		print(s);
		add_crc(str2);
		if(crc_is_ok(str2))
			print("RIGHT crc1 ");
		else
			print("ERROR crc1 ");
		add_crc(str2);
		str2[0]='A';
		if(crc_is_ok(str2))
			print("RIGHT crc2 ");
		else
			print("ERROR crc2 ");
		}
	serial_close();
	return 1;
}


/*
avr-gcc -Wall -std=c99 -Os -mmcu=atmega328p -fshort-enums -Ilibpbn -DF_CPU=16000000UL  -c -o error_morse.o error_morse.c

avr-gcc -Wall -std=c99 -Os -mmcu=atmega328p -fshort-enums -Ilibpbn -DF_CPU=16000000UL  -c -o prova_crc.o prova_crc.c
avr-gcc -mmcu=atmega328p -std=c99  prova_crc.o error_morse.o libpbn.a   -o prova_crc
avr-objcopy -Oihex prova_crc prova_crc.hex
sudo avrdude -c arduino -p m328p -P /dev/ttyACM0 -U prova_crc.hex
picocom /dev/ttyACM0
*/
