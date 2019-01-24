#ifndef LAN_H
#define LAN_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct {
	uint8_t origen;
	uint8_t desti;
	uint8_t payload[30];
} lan_pdu_t;

typedef enum{
	high,
	low
}lan_buffer_t;

typedef void (*lan_callback_t)(void);

typedef uint8_t * missatge_lan_t;

void lan_init(uint8_t no);//inicialitza el mòdul i per tant el protocol. Té com paràmetre "no" que és l'adreça origen del propi node.

bool lan_can_put(lan_buffer_t prioritat);//gestiona la  predefinida sobre la transmisió pel canal. Retornara true si la H o la L del buffer estan lliures i retorna false en cas contrari.???????????

void lan_block_put(const missatge_lan_t m, uint8_t nd, lan_buffer_t prioritat);//té tres paràmetres. El primer és el missatge que es vol transmetre en forma de taula missatge_lan_t . El segon és l'adreça del node a qui va dirigit. El tercer es la prioritat.

uint8_t lan_block_get(missatge_lan_t m);//té com a paràmetre la taula missatge_lan_t on es recollirà el missatge. També retorna l'adreça del node que ha enviat el missatge. Aquesta funció està molt relacionada amb lan_can_get() ja que aquesta última indica quan hi ha disponible un missatge per llegir i per tant quan es pot cridar a lan_block_get().

void on_lan_received(lan_callback_t l);//fa un callback de la funció que te al parametre "l".

#endif
