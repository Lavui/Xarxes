#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lan.h"
#include <pbn.h>

#define PRIORITAT low

static uint8_t NO;

int main(void){
  serial_open();
  sei();
  NO=serial_get();
  cli();
  lan_init(NO);
  
}
