#include "lan.h"
#include "error_morse.h"
#include <pbn.h>
#include <stdlib.h>
#include <avr/io.h>

static void envia_trama(void); //uniques d'aqui
static void rep_trama(void);

typedef struct {
  uint8_t origen;
  uint8_t desti;
  uint8_t payload;
}
