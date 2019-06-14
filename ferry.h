#ifndef FERRY_H
#define FERRY_H
#include "status.h"

typedef void* QUEUE;

QUEUE queue_init_default(void);
//enqueue
Status queue_enqueue(QUEUE hQ, int item);
//service
Status queue_service(QUEUE hQ);
//empty
Boolean queue_empty(QUEUE hQ);
//front
int queue_front(QUEUE hQ, Status* pStatus);

void queue_destroy(QUEUE* phQueue);

#endif
