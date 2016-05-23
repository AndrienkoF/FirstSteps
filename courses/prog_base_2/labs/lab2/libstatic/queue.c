#include <stdlib.h>
#include <stdio.h>

#include "queue.h"

struct queue_s{
    int head;
    int data[MAX_SIZE];
    int tail;
    int size;
};

queue_t * queue_new(){
    queue_t * newQueue = malloc(sizeof(struct queue_s));
    newQueue->size = 0;
    newQueue->head = newQueue->tail = 0;
    return newQueue;
}

void queue_free(queue_t * newQueue){
    free(newQueue);
}

void queue_enqueue(queue_t * newQueue, int num){
    if (newQueue->size == MAX_SIZE){
        return 0;
    }
    if (newQueue->tail == MAX_SIZE){
        newQueue->tail = 0;
    }
    newQueue->size++;
    newQueue->data[newQueue->tail] = num;
    newQueue->tail++;
}

int queue_dequeue(queue_t * newQueue){
    if (newQueue->head == MAX_SIZE){
        newQueue->head = 0;
    }
    if (newQueue->size == 0){
        return 0;
    }
    int num = newQueue->data[newQueue->head];
    newQueue->head++;
    newQueue->size--;
    return num;
}


int queue_getSize(queue_t * newQueue){
    return newQueue->size;
}

void queue_show(queue_t * newQueue){
    int i = 0;
    int j = newQueue->head;
    printf("Queue: ");
    while(i < newQueue->size){
        if (j == MAX_SIZE){
            j = j - MAX_SIZE;
        }
        printf("%i ", newQueue->data[j]);
        j++;
        i++;
    }
    puts("\n");
}
