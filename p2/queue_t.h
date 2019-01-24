#ifndef QUEUE_T_H_
#define QUEUE_T_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "lan.h"

#define MAXCUA 2

typedef struct {
	int front;
	int rear;
	int count;
	lan_pdu_t elements[MAXCUA];
}queue_p;

void queue_t_empty(queue_p *const q);

bool queue_t_is_empty(const queue_p *const q);

bool queue_t_is_full(const queue_p *const q);

void queue_t_enqueue(queue_p *const q, lan_pdu_t v);

void queue_t_dequeue(queue_p *const q);

void queue_t_front(const queue_p *const q, lan_pdu_t *a);

#endif
