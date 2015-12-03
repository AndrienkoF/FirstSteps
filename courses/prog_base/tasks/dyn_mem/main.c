#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main (void){
    char * string = (char *)malloc(sizeof(char)*100);
    int  * point  = (int  *)malloc(sizeof(int ));
    int  * sum    = (int  *)malloc(sizeof(int ));
    * sum = 0;
    puts("Your string:");
    gets(string);

    for (* point = 0; * point < strlen(string); (* point)++){
        if (isalpha(string[*point] )){
                * sum += 1;
            }
    }
    puts("Char than 5 ? (1 - true, 0 - false)");
    if (* sum > 5){
        puts("1");
    }
    else {
        puts("0");
    }
    free(string);
    free(point);
    free(sum);
    return 0;
}
