#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "leadingRadio.h"

int main(void){
	leading_t * newLeading[3];
	for (int i = 0; i < 3; i++) {
		newLeading[i] = new_leading();
	}
	leading_downloadXML(newLeading, "leadingRadio.xml");
	for (int i = 0; i < 3; i++) {
		leading_printXML(newLeading[i], i);
	}
	for (int i = 0; i < 3; i++) {
		leading_delete(newLeading[i]);
	}
	return 0;
}
