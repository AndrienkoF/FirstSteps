#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include "leadingRadio.h"

struct work_s{
    char station[50];
    int experienceOnRadioStation;
    double rating;
};

struct leading_s{
    char name[20];
    char surname[20];
    char birthdate[20];
    char hometown[20];
    char education[100];
    work_t work;
    char favoriteGenreOfMusic[20];
    char favoriteSingerOrGroup[20];
    char favoriteSong[20];
};

leading_t * new_leading(){
    leading_t * newLeading = malloc(sizeof(struct leading_s));
    return newLeading;
}

void leading_delete(leading_t * list){
    free(list);
}

void work_download(work_t * work, xmlNode * curNode){
	char * buff;
	for (curNode = curNode->children; curNode != NULL; curNode = curNode->next){

		if (xmlStrEqual(curNode->name, "experienceOnRadioStation")){
                buff = xmlNodeGetContent(curNode);
                work->experienceOnRadioStation = atoi(buff);

                buff = xmlGetProp(curNode, "station");
                strcpy(work->station, buff);
            }

		else if (xmlStrEqual(curNode->name, "rating")){
			buff = xmlNodeGetContent(curNode);
			work->rating = atof(buff);
		}
	}
}

leading_t * leading_download(leading_t * leading, xmlNode * curNode){
	char * buff;
	for (curNode = curNode->children; curNode != NULL; curNode = curNode->next){

		if (xmlStrEqual(curNode->name, "name")){
			buff = xmlNodeGetContent(curNode);
			strcpy(leading->name, buff);
		}

		else if (xmlStrEqual(curNode->name, "surname")){
			buff = xmlNodeGetContent(curNode);
			strcpy(leading->surname, buff);
		}

		else if (xmlStrEqual(curNode->name, "birthdate")){
			buff = xmlNodeGetContent(curNode);
			strcpy(leading->birthdate, buff);
		}

		else if (xmlStrEqual(curNode->name, "hometown")){
			buff = xmlNodeGetContent(curNode);
			strcpy(leading->hometown, buff);
		}

		else if (xmlStrEqual(curNode->name, "education")){
			buff = xmlNodeGetContent(curNode);
			strcpy(leading->education, buff);
		}

        // Work
		else if (xmlStrEqual(curNode->name, "work")){
            work_download(&(leading->work), curNode);
        }

        else if (xmlStrEqual(curNode->name, "favoriteGenreOfMusic")){
			buff = xmlNodeGetContent(curNode);
			strcpy(leading->favoriteGenreOfMusic, buff);
		}

		else if (xmlStrEqual(curNode->name, "favoriteSingerOrGroup")){
			buff = xmlNodeGetContent(curNode);
			strcpy(leading->favoriteSingerOrGroup, buff);
		}

		else if (xmlStrEqual(curNode->name, "favoriteSong")){
			buff = xmlNodeGetContent(curNode);
			strcpy(leading->favoriteSong, buff);
		}
	}
	return leading;
}

void leading_downloadXML(leading_t ** list, const char * readXML){
	xmlDoc * xDoc = xmlReadFile(readXML, "UTF-8", 0);
	if (xDoc == NULL) {
		puts("\nError parsing xml from memory.");
		xmlFreeDoc(xDoc);
	}
	else {
		xmlNode * xRootEl = xmlDocGetRootElement(xDoc);
		xmlNode * curNode;
		int i = 0;
		for (curNode = xRootEl->children; curNode != NULL; curNode = curNode->next) {
			if (xmlStrEqual(curNode->name, "leading")) {
				leading_download(list[i], curNode);
				i++;
			}
		}
		xmlFreeDoc(xDoc);
	}
}

void leading_printXML(leading_t * leading, int i){
    int count = i + 1;
	printf("           Leading %i           \n", count);
	printf("Name: %s\n", leading->name);
	printf("Surname: %s\n", leading->surname);
	printf("Birthdate: %s\n", leading->birthdate);
	printf("Hometown: %s\n", leading->hometown);
	printf("Education: %s\n", leading->education);
	printf("Work:\n   Station: %s\n   Experience on radio station: %i\n   Rating: %.1f\n", leading->work.station, leading->work.experienceOnRadioStation, leading->work.rating);
	printf("Favorite genre of music: %s\n", leading->favoriteGenreOfMusic);
	printf("Favorite singer or group: %s\n", leading->favoriteSingerOrGroup);
	printf("Favorite song: %s\n", leading->favoriteSong);
	puts("\n\n");
}




