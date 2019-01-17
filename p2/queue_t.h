#ifndef QUEUE_T_H_
#define QUEUE_T_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "lan.h"

#define MAXCUA 10
#define MAXPDU 10
typedef struct {
  int front;
  int rear;
  int count;
  lan_pdu_t elements[MAXPDU];
}queue_t;

void queue_empty(queue_t *const q);

bool queue_is_empty(const queue_t *const q);

bool queue_is_full(const queue_t *const q);

void queue_enqueue(queue_t *const q, lan_pdu_t v);

void queue_dequeue(queue_t *const q);

void queue_front(const queue_t *const q, lan_pdu_t *a);

#endif
