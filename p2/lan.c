#include <stdio.h>
#include <stdlib.h>
#include <pbn.h>
#include "lan.h"
#include "error_morse.h"

static queue_t H,L;

static uint8_t node_origen;

static missatge_lan_t missatge; //es un apuntador(mirar.h)

static lan_callback_t lan_cb=NULL;

void lan_init(uint8_t no){
  ether_init();
  timer_init();
  on_message_received(message_for_me); //crida la funció de callback quan rep un missatge
  node_origen=no;
  queue_empty(&H);
  queue_empty(&L);
  timer_every(TIMER_MS(5000),checking_queue)
}

static void message_for_me(void){
  lan_pdu_t trama;
  ether_block_get(trama); //agafar trama de la CF
  if ((node_origen==trama[0]) && (crc_is_ok(trama) && lan_cb!=NULL){
      missatge=trama;
      lan_cb();
    }
}

static void checking_queue(void){
  lan_pdu_t trama;
  if (!queue_is_empty(&H)){
    if (ether_can_put()){
      queue_front
    }
  }
}
    
bool lan_can_put(lan_buffer_t priority){
  if (priority==high){
    if (!queue_is_full(&H))
      return true
  }
}
