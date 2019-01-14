#include <stdio.h>
#include <stdlib.h>
#include <pbn.h>
#include "lan.h"
#include "error_morse.h"

static queue_t H,L;

static uint8_t node_origen;

static missatge_lan_t missatge;

static lan_callback_t lan_cb=NULL;

void lan_init(uint8_t no){
  ether_init();
  timer_init();
  on_message_received(message_for_me);
  node_origen=no;
  queue_empty(&H);
  queue_empty(&L);
  timer_every(TIMER_MS(5000),checking_queue)
}
