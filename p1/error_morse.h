#ifndef ERROR_MORSE_H
#define ERROR_MORSE_H

#include <stdbool.h>
#include <string.h>
#include <stdint.h>


typedef struct lh{
  uint8_t L,H;
}check;

check add_check(char p[]);//Entrada: un string el qual se l'hi creara un Checksum d'un Byte. Sortida: Retorna el mateix string amb el Checksum (en hexa) al final. També retorna especificament el Checksum.

bool check_is_ok(char p[]);//Entrada: String + el Checksum corresponent. Sortida: Bolea. True -> no error, False -> error.

check get_redun(char p[]);//Entrada: String + checksum. Sortida: String sense Checksum i Checksum sense string.


#endif
