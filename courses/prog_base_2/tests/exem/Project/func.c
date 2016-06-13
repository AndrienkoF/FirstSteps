#include <stdlib.h>
#include "func.h"

int numString(char myStr[]){
    int sum = 0;
    char sep [10] = ",";
    char *istr;
    istr = strtok (myStr,sep);

    while (istr != NULL){
        sum += atoi(istr);
        istr = strtok (NULL,sep);
    }
    //printf("Sum: %i", sum);
    return sum;
}

int checkStr(char myStr[]){
    if(myStr == NULL){
        return -1;
    }
    numString(myStr);

    return 1;
}
