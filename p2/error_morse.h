#ifndef ERROR_MORSE_H
#define ERROR_MORSE_H

#include <stdint.h>

typedef struct {
  uint8_t H, L;
}check;

check add_check(uint8_t str[]);

bool check_is_ok(uint8_t str[]);

check add_crc(uint8_t str[]);

bool crc_is_ok(uint8_t str[]);

#endif

