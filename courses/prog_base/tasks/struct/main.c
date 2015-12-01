#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct albums {
    char albumName [30];
    int albumNum;
};

int count(int size, struct albums arr[size]){
    int i;
    int index = 0;
    for (i = 0; i <= size; i++){
        if (arr[i].albumNum > 10){
            index ++;
        }
    }
    return index;
}

void change(struct albums * pVar, const char * newValue){
    strcpy(pVar->albumName, newValue);
}

void print(struct albums * pVar){
    printf("%s (Album title)\n%6.i (Number of photos)\n\n ",pVar->albumName, pVar->albumNum);
}


int main (){
    int i = 0;
    int size = 5;
    int index;
    int check;
    char nums[1];
    struct albums  arr[5] = {
        {" 0. \"My family and I\"" , 36},
        {"1. \"My friends and I\"", 45},
        {"2. \"My travel\""       , 3},
        {"3. \"It's my life\""    , 9},
        {"4. \"Joy in life\""     , 15}
    };

    printf("Number of albums, with more than 10 photos: %i\n\n", count(size, arr));

    while ( i < 5 ){
        print(&arr[i]);
        i++;
    }

    printf("Rename the album (please, enter album index 0 to 4):  ");
    scanf("%i", &index);
    puts("\n");
    change(&arr[index],"NEW album");
    print(&arr[index]);

    return 0;
}
