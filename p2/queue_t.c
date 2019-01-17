#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <util/atomic.h>
#include "queue_t.h"
#include "lan.h"
#include <pbn.h>

void queue_t_empty(queue_p *const q){
  q->front=0;
  q->rear=0;
  q->count=0;
}

bool queue_t_is_empty(const queue_p *const q){
  return (q->count)==0;
}

bool queue_t_is_full(const queue_p *const q){
  return (q->count)==MAXCUA;
}

void queue_t_enqueue(queue_p *const q, lan_pdu_t v){
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    if (!queue_t_is_full(q)){
      q->elements[q->rear]=v;
      if (q->rear==MAXCUA-1)
	(q->rear)=0;
      else 
	q->rear++;
      q->count++;  
    }
  }
}

void queue_t_dequeue(queue_p *const q){
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    if (!queue_t_is_empty(q)){
      if (q->front==MAXCUA-1)
	(q->front)=0;
      else
	q->front++;
      q->count--; 
    }
  }
}

void queue_t_front(const queue_p *const q, lan_pdu_t *a){
  ATOMIC_BLOCK(ATOMIC_RESTORESTATE){
    if (!queue_t_is_empty(q))
      *a=(q->elements)[q->front];
  }
}
