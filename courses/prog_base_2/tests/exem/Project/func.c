#include <stdlib.h>
#include "func.h"

void numString(char myStr[]){
    int sum = 0;
    if(myStr == NULL){
        return NULL;
    }
    char sep [10] = ",";
    char *istr;
    istr = strtok (myStr,sep);

    while (istr != NULL){
        sum += atoi(istr);
        istr = strtok (NULL,sep);
    }
    printf("Sum: %i", sum);
}

