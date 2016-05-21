#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "list.h"

struct post_s{
    char ** userName;
    char ** array;
    int * repost;
    int length;
};

post_t * new_post(int length){
    post_t * newPost = malloc(sizeof(struct post_s));
    newPost->array = calloc(length, sizeof(char*));
    newPost->repost = calloc(length, sizeof(int*));
    newPost->userName = calloc(length, sizeof(char*));
    newPost->length = length;
    return newPost;
}

void post_delete(post_t * list){
    free(list->userName);
    free(list->array);
    free(list->repost);
    free(list);
}

int post_getLength(post_t * list){
    return list->length;
}

void post_add(post_t * list, char * userName,  char * string, int index, int repost ){
    int i;
    list->array = realloc(list->array, (list->length + 1)*(sizeof(char *)));
    list->repost = realloc(list->repost, (list->length + 1)*(sizeof(int *)));
    list->userName = realloc(list->userName, (list->length + 1)*(sizeof(char *)));
    if(index < 0 || index > list->length){
        printf("Invalid index: %i", index);
    }
    else {
        for(i = index ; i < list->length; i++){
            list->array[i + 1] = list->array[i];
            list->repost[i + 1] = list->repost[i];
            list->userName[i + 1] = list->userName[i];
        }
        list->array[index] = string;
        list->repost[index] = repost;
        list->userName[index] = userName;
        list->length++;
    }
}


void post_remove(post_t * list, int index){
    int i;
    if(index < 0 || index >= list->length){
        printf("Invalid index: %i", index);
    }
    else {
        for(i = index; i < list->length - 1; i++){
            list->array[i] = list->array[i + 1];
            list->userName[i] = list->userName[i + 1];
            list->repost[i] = list->repost[i + 1];
        }
        list->array = realloc(list->array, (list->length - 1)*(sizeof(char *)));
        list->userName = realloc(list->userName, (list->length - 1)*(sizeof(char *)));
        list->repost = realloc(list->repost, (list->length - 1)*(sizeof(int *)));
        list->length--;
    }
}

void post_print(post_t * list) {
    int i;
    for (i = 0; i < list->length; i++) {
        printf("%s:\n%s\nrepost >> %i\n\n\n", list->userName[i], list->array[i], list->repost[i]);
    }
}
