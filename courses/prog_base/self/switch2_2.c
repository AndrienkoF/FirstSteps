#include <stdio.h>
#include <stdlib.h>

int main() {
	int den = 0;
    int den1 = 0;
	scanf("%d", &den);
    den1= (den-1) %7;
	switch (den1) {

	case 0:
		printf( "Sereda");
		break;

	case 1:
		printf("Chetver");
		break;

	case 2:
		printf( "Piatnisa");
		break;

	case 3:
		printf("Sybota");
		break;

	case 4:
		printf( "Nedila");
		break;

	case 5:
		printf("Ponedilok");
		break;

    case 6:
        printf( "Vivtorok");
        break;

 	default:
		return 1;
	}

		return 0;


}
