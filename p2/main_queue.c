#include "queue_t.h"
#include "lan.h"
int main(void){
  lan_pdu_t tst;
  lan_pdu_t trama;
  trama.origen=1;
  trama.desti=2;
  trama.payload="HOLA";
  lan_pdu_t trama2;
  trama.origen=3;
  trama.desti=4;
  trama.payload="ADEU";
  queue_t cua;
  if (queue_empty(&cua))
    printf("cua buidada");
  if (queue_is_empty(&cua)){
    printf("cua buida");
    queue_enqueue(&cua,trama);
    queue_enqueue(&cua,trama2);
    queue_enqueue(&cua,trama2);
    queue_enqueue(&cua,trama2);
    queue_enqueue(&cua,trama2);
    if (!queue_is_full(&cua)){
      printf("cua no plena");
      queue_enqueue(&cua,trama2);
      queue_enqueue(&cua,trama2);
      queue_enqueue(&cua,trama2);
      queue_enqueue(&cua,trama);
      queue_enqueue(&cua,trama2);
      if (queue_is_full(&cua)){
	printf("cua plena");
	queue_front(&cua,&tst);
	queue_dequeue(&cua);
	queue_front(&cua,&tst);
	queue_dequeue(&cua);
      }
    }
    else
      printf("cua plena");
  }
  else
    prinf("cua no buida");
}
