#include "error_morse.h"
#include <stdio.h>//Pel joc de proves (borrar al acabar)


check add_check(char p[]){
  uint16_t suma,carry,rest;
  uint8_t che_bin;
  check che_hex;
  
  for (uint8_t i=0; p[i]; i++){ // funcio sumadora checksum
    if ((p[i]>='A' && p[i]<='Z') || (p[i]>='0' && p[i]<='9') || (p[i]==' ')){
      suma+=p[i];
    }
  }
  rest = suma & 0x00FF;
  carry = suma & 0xFF00;
  carry = carry >> 8;
  che_bin = ~(carry + rest); // checksum en binari

  che_hex=byte2hex(che_bin);
  return che_hex;
}


static check byte2hex(uint8_t byte){
  check hex;
  uint8_t H=byte>>4;
  uint8_t L=byte & 0b00001111;
  if(H>=0x0A && H<=0x0F)
    H+=55;
  else
    H+=48;

  if(L>=0x0A && L<=0x0F)
    L+=55;
  else
    L+=48;
  //printf("%c %c\n",H,L);
  hex.H=H;
  hex.L=L;
  return hex;
}


static uint8_t hex2byte(check hex){
  uint8_t maj, men;
  if (hex.H>=0x41 && hex.H<=0x5A)
    hex.H-=55;
  else
    hex.H-=48;

  if (hex.L>=0x41 && hex.L<=0x5A)
    hex.L-=55;
  else
    hex.L-=48;
  //printf("%i L \n",hex.L);

  maj=hex.H<<4;
  men=hex.L & 0b00001111;
  //printf("%i maj | %i men = %i\n",maj,men,maj|men);

  return maj|men;
}


/*
void main(){
  check hexad;
  //hexad.L=0x0F;
  //hexad.H=0x00;
  //printf("%i\n",hex2byte(hexad)); // prova hex2byte

  uint8_t byt= 0b01010101;
  
  printf("%i\n",hex2byte(byte2hex(byt))); // prova byte2hex
  }*/
