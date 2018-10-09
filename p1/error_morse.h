#ifndef ERROR_MORSE_H
#define ERROR_MORSE_H

#include <stdbool.h>
#include <string.h>
#include <stdint.h>


typedef struct lh{
  uint8_t L,H;
}check;


check add_check(char p[]);//Entrada: un string el qual se l'hi creara un Checksum d'un Byte. Sortida: Retorna el mateix string amb el Checksum (en hexa) al final. També retorna especificament el Checksum.

bool check_is_ok(char p[]);//Entrada: String + el Checksum corresponent. Sortida: Bolea. True -> no error, False -> error. L'string d'entrada es modificara i s'eliminara el check del final.

check get_redun(char p[]);//Entrada: String + checksum. Sortida: String sense Checksum i Checksum sense string.



check add_crc(char p[]);//Entrada: string amb el bloc de dades que es vol protegir amb el CRC. Sortida: Retorna el mateix string amb els dos caracter (al final) que codifiquen en hexa el Byte que s'ha calculat. També retorna especificament el Checksum.

bool crc_is_ok(char p[]);//Entrada: String que conté el bloc de dades + el Byte de CRC al final, codificat en hexadecimal. Sortida: Bolea. True -> no error, False -> error. L'string d'entrada es modificara i s'eliminara el CRC del final.


/*funcions auxiliars*/

static check byte2hex(uint8_t byte);
static uint8_t hex2byte(check hex);



#endif
