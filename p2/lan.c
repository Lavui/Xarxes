#include <stdio.h>
#include <stdlib.h>
#include <pbn.h>
#include "queue_t.h"
#include "lan.h"
#include "error_morse.h"
#include <avr/interrupt.h>

static queue_p H,L;

static uint8_t node_origen;

static missatge_lan_t missatge; //es un apuntador(mirar.h)

static lan_callback_t lan_cb=NULL;

static void message_for_me(void){
  uint8_t trama[32];
  ether_block_get(trama); //agafar trama de la CF
  if (node_origen==trama[1] && crc_is_ok(trama)){
    if(lan_cb!=NULL){
      missatge=trama;
      lan_cb();
    }
  }
}

static void clear_queue(void){
	//Es una funció de callback que cada x temps (el marcat en el timer very) mirara si hi ha elements a la cua si nhi ha ho processa i els desencua, sino no fa res
	lan_pdu_t trama;
	if (!queue_t_is_empty(&H)){
	if (ether_can_put()){
		queue_t_front(&H,&trama);
		add_crc((missatge_lan_t)&trama);
		ether_block_put((missatge_lan_t)&trama);
		queue_t_dequeue(&H);
	}
	}
	else
	if (!queue_t_is_empty(&L)){
		if (ether_can_put()){
			queue_t_front(&L,&trama);
			add_crc((missatge_lan_t)&trama);
			ether_block_put((missatge_lan_t)&trama);
			queue_t_dequeue(&L);
		}
	}
}

void lan_init(uint8_t no){
	ether_init();
	timer_init();
	on_message_received(message_for_me); //crida la funció de callback quan rep un missatge
	node_origen=no;
	queue_t_empty(&H);
	queue_t_empty(&L);
	timer_every(TIMER_MS(1000),clear_queue);
}


	
bool lan_can_put(lan_buffer_t prioritat){
	//donar prioritat a una cua o a la altra, si la High no esto plena enquem alla, si està plena passm a la Low, si Low esta plena esperarem a que la de major prioritat es buidi, en el main definirem la prioritat
	if (prioritat==high){
	if (!queue_t_is_full(&H))
		return true;
	}
	else
	if(!queue_t_is_full(&L))
		return true;
	return false;
}

void lan_block_put(const missatge_lan_t m, uint8_t nd, lan_buffer_t prioritat){
	//encua les trames a la de major prioritat
	lan_pdu_t trama;
	trama.origen=node_origen;
	trama.desti=nd;
	int i;
	for (i=0; m[i]!='\0'; i++){ //preparem la trama a encuar
		trama.payload[i]=m[i];
	}
	trama.payload[i]='\0'; //trama completa (faltarien el no i nd que s'afegeix en el enqueue)
	if (prioritat==high){
		queue_t_enqueue(&H,trama); //enquem trama al 100%
	}
	else{
		queue_t_enqueue(&L,trama);
	}
}

void on_lan_received(lan_callback_t l){
	//serà cridada quan hi hagi dades disponibles
	lan_cb=l;
}

uint8_t lan_block_get(missatge_lan_t m){
	//retorna l'adreça origen
	int i;
	for (i=0; missatge[i]!='\0'; i++){
		m[i]=missatge[i+2];
	}
	m[i]='\0';
	return missatge[0];
}
 
