#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "list.h"

int main(){
    post_t * newPost = new_post(0);
    post_add(newPost,"James", "It begins! ", 0, 102);
    post_add(newPost,"Mary", "Hello friends! ", 1, 234);
    post_add(newPost,"Lili", "Hello World! ", 2, 453);
    post_add(newPost,"Nick", "Hello! ", 3, 430);
    post_add(newPost,"Ivan", "Zdarova! ", 4, 830);
    post_print(newPost);

    printf("-------------------------------------------------\n");
    post_remove(newPost, 0);
    post_print(newPost);

    printf("-------------------------------------------------\n");
    printf("Size list: %i\n",  post_getLength(newPost));

    printf("-------------------------------------------------\n");
    largestNumRepost(newPost);

    printf("-------------------------------------------------\n");
    reposMoreThanGivenNum(newPost, 100);

    printf("-------------------------------------------------\n");
    reposMoreThanGivenNum(newPost, 1000);
    memory_delete(newPost);

    return 0;
}
