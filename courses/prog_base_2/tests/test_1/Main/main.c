#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "blog.h"

int main(){
    post_t * newPost = new_post(0);
    post_add(newPost,"James", "It begins! ", 0, 102);
    post_print(newPost);

    post_delete(newPost);

    return 0;
}
