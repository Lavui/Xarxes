#include "error_morse.h"


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

