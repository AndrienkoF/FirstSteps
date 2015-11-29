#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void fprocess(const char * pread, const char * pwrite){
    int firsScore;
    int secondScore;
    char myStr[100];
    char firsTeam[20];
    char secondTeam[20];

    FILE * fp;
    FILE * fn;

    fp = fopen(pread, "r");
    if (fp == NULL) {
        puts("Error!");
    }

    puts("i read this!");

    fscanf(fp, "%s %i %s %i", &firsTeam, &firsScore, &secondTeam, &secondScore);
    fgets(myStr, 100, fp);

    fn = fopen(pwrite, "w");
    if (fn == NULL) {
        puts("Error open file!");
    }
    else if (firsScore > secondScore){
        fprintf(fn, "%s", firsTeam);
    }
    else if (firsScore < secondScore){
        fprintf(fn, "%s", secondTeam);
    }
    else {
        fprintf(fn, "NO WINNERS");
    }

    puts("i wrote this!");

    fclose(fp);
    fclose(fn);
}
