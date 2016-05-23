#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED

#define MAX_SIZE 100

typedef struct queue_s queue_t;

queue_t * queue_new();
void queue_free(queue_t * newQueue);
void queue_enqueue(queue_t * newQueue, int num);
int queue_dequeue(queue_t * newQueue);
int queue_getSize(queue_t * newQueue);
void queue_show(queue_t * newQueue);

#endif // QUEUE_H_INCLUDED
