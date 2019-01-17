#include "queue_t.h"
#include "lan.h"
#include <string.h>

//static missatge_lan_t missatge[10];
//static missatge_lan_t missatge2[10];

void trans(const missatge_lan_t missatge){
  int i;
  lan_pdu_t trama;
  trama.origen=1;
  trama.desti=2;
  for (i=0;missatge[i]!='\0';i++){
    trama.payload[i]=missatge[i];
  }
  trama.payload[i]='\0';
}

int main(void){
  lan_pdu_t tst;
  lan_pdu_t trama;
  uint8_t missatge[10];
  uint8_t missatge2[10];
  
  int i;
  for (i=0;missatge[i]!='\0';i++){
    trama.payload[i]=missatge[i];
  }
  trama.payload[i]='\0';
  /*uint8_t m1[10], m2[10];
  m1="HOLA";
  m2="ADEU";*/
  trama.origen=1;
  trama.desti=2;
  lan_pdu_t trama2;
  for (i=0;missatge2[i]!='\0';i++){
    trama2.payload[i]=missatge2[i];
  }
  trama2.payload[i]='\0';
  trama2.origen=3;
  trama2.desti=4;
  queue_p cua;
  if (queue_t_empty(&cua))
    printf("cua buidada");
  if (queue_t_is_empty(&cua)){
    printf("cua buida");
    queue_t_enqueue(&cua,trama);
    queue_t_enqueue(&cua,trama2);
    queue_t_enqueue(&cua,trama2);
    queue_t_enqueue(&cua,trama2);
    queue_t_enqueue(&cua,trama2);
    if (!queue_t_is_full(&cua)){
      printf("cua no plena");
      queue_t_enqueue(&cua,trama2);
      queue_t_enqueue(&cua,trama2);
      queue_t_enqueue(&cua,trama2);
      queue_t_enqueue(&cua,trama);
      queue_t_enqueue(&cua,trama2);
      if (queue_t_is_full(&cua)){
	printf("cua plena");
	queue_t_front(&cua,&tst);
	queue_t_dequeue(&cua);
	queue_t_front(&cua,&tst);
	queue_t_dequeue(&cua);
      }
    }
    else
      printf("cua plena");
  }
  else
    prinf("cua no buida");
}
