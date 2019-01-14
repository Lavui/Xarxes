#ifndef LAN_H
#define LAN_H

#include <inttypes.h>
#include <stdbool.h>

typedef struct {
  uint8_t origen;
  uint8_t desti;
  uint8_t payload[30];
} lanpdu_t;

typedef enum{
  high,
  low
}lan_buffer_t;

typedef void (*lan_callback_t)(void);
typedef uint8_t * missatge_lan_t;

void lan_init(uint8_t no);

bool lan_can_put(lan_buffer_t prioritat);

void lan_block_put(const missatge_lan_t m, uint8_t nd, lan_buffer_t prioritat);

uint8_t lan_block_get(missatge_lan_t m);

void on_lan_received(lan_callback_t l);

#endif
