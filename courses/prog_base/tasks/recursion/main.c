#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int quantityNum (int i, int len, char str[], int n){
    if (i == len){
        return n;
    }
    else if (str[i] >= '0' && str[i] <= '9'){
        return quantityNum (i+1, len, str, n+1);
    }
    else {
        return quantityNum (i+1, len, str, n);
    }

}

int quantityLet (int i, int len, char str[], int l){
    if (i == len){
        return l;
    }
    else if (str[i] >= 'a' && str[i] <= 'z'){
        return quantityLet (i+1, len, str, l+1);
    }
    else if (str[i] >= 'A' && str[i] <= 'Z'){
        return quantityLet (i+1, len, str, l+1);
    }
    else {
        return quantityLet (i+1, len, str, l);
    }

}

int main (void){
    char str[100];
    int resNum;
    int resLet;
    puts("Enter your string:");
    gets(str);
    resNum = quantityNum (0, strlen(str), str, 0);
    resLet = quantityLet (0, strlen(str), str, 0);
    printf("Quantity of numbers in a string:  %d\n", resNum);
    printf("Quantity of letters in a string:  %d  ", resLet);
    return 0;
}


