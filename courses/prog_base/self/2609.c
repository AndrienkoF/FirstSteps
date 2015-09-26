#include <stdio.h>
#include <stdlib.h>

int main() {
	int m = 0;
	int h = 0;
	int code = 0;
	int tarif = 0;
	scanf("%d %d %d", &h, &m, &code);
	switch (code) {
	case 44:
		tarif = m*0.44 + h * 60 * 0.44;
		break;

	case 37:
		tarif = m*1.05 + h * 60 * 1.05;
		break;

	case 666:
		tarif = m * 666 + h * 60 * 666;
		break;

	case 111:
		tarif = m * 111 + h * 60 * 111;
		break;

	case 1:
		tarif = m * 1 + h * 60 * 1;
		break;
	default:
		return 1;
	}
		printf(" %d ", tarif);
		return 0;
	

}