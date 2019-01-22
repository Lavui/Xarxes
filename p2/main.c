#include <stdio.h>
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lan.h"
#include <pbn.h>

#define DEFAULT_PRIORITY low

static uint8_t NO;

static void recepcio(void){
  uint8_t x[31];
  char a=lan_block_get(x);
  char b=NO; /* S'han de convertir tots a char per a coincidir amb el format que te el print */
  serial_put(a);
  serial_put('-');
  serial_put('>');
  serial_put(b);
  serial_put(' ');
  print((char *)x);
}   

void enviament(void){
  int i;
  char enviament[33]="";
  uint8_t missatge[30];
  readline(enviament,34);
  for(i=2; enviament[i]!='\0'; i++){
    missatge[i-2]=enviament[i];}
  missatge[i-2]='\0';
  if (lan_can_put(DEFAULT_PRIORITY)){ /* Donem prioritat baixa per defecte */
    //print((char *)enviament);
    lan_block_put(missatge, enviament[0],DEFAULT_PRIORITY);}
}

int main(void){
  serial_open();
  sei();
  NO=serial_get();
  cli();
  lan_init(NO);
  sei();
  on_lan_received(recepcio);
  while(1){
    enviament();}
  return 0;
}
