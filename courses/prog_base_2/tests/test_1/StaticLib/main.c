#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "blog.h"

int main(){
    blog_t * newBlog = blog_new(0, 1);
    user_t * newUser = blog_userLogin(newBlog, 200, 0);
    user_add(newUser, "Fedia",  "UK", 18, 1/*, int id*/);
    user_print(newUser);

    printf("-------------------------------------------------\n");

    blog_delete(newBlog);

    return 0;
}
