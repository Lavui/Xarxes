#include "lan.h"
#include "error_morse.h"
#include <pbn.h>
#include <stdlib.h>
#include <avr/io.h>

static void envia_trama(void); //uniques d'aqui
static void rep_trama(void);
//static void reintents(void);

typedef struct {
  uint8_t origen;
  uint8_t desti;
  uint8_t payload[30];
} lanpdu_t;

typedef struct {
  lanpdu_t H,L;
} lanbuffer;

static lanpdu_t tx_pdu,rx_pdu;
static lan_callback_t lan_cb;
//static enum {pendent_enviar,esperant} estat;

void lan_init(uint8_t no){
  timer_init();
  ether_init();
  on_message_received(rep_trama);
  lan_cb=NULL;
  tx_pdu.origen=no; //no es el node origen, per aixo posem en el tx_pdu el no
  // hem falla la interpretacio de la transmissio, ja que en el init hem de posar una funció que cada 0,5s crida a la funcio reintent, que aquesta sera la queens dira si podem transmetre o no, es a dir si hi ha cues pendents utilitzar el timerevery
  timerevery(500,reintents);
  //tinc el dubte de si elsestats de la maquina d'estats els necessiteeem, diria que si ja que de la transmissio nomes hem canviar el numero d'intents, static enum comentat adalt
  //estat=esperant;
}

void on_lan_received(lan_callback_t l){
  //substitut del lan_can_get(), aquesta nomes sera cridada quan hi hagi dades disponibles
  lan_cb=l;
  return;
}
static void rep_trama(void){
  //Funcio interna del programa
  /*Hem de fer primer un ether_block_get que ens llegira el contingut del block_morse rebut (el block_morse es el missatge en la construcció del ether_block_get també hi ha d'haver el receptor*/
  ether_block_get((block_morse)&rx_pdu);/*tan el receptor com transmissor s'ha creat un static que té com a struct el lanpdu_t i hem creat el tx_pdu i rx_pdu*/
  if crc_is_ok((block_morse)&rx_pdu){
      if(rx_pdu.desti==tx_pdu.origen){
	get_redun((block_morse)&rx_pdu);
	lan_cb();
      }
    }
  return;
}


uint8_t lan_block_get(missatge_lan_t m){
  /*retorna l'adreça del node que ha enviat el missatge (node del tx)*/
  for(uint8_t con=0; rx_pdu.payload[con]!='\0'; con++)
    m[con]=rx_pdu.payload[con];
  m[con]='\0';
  return rx_pdu.origen;
}
