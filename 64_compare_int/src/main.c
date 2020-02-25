/*
 *****************************************************************************

 *****************************************************************************
 */

#include<stdio.h>

int main(void){

	int nombre1;
	int nombre2;

	printf("Saisissez deux entiers :");
	scanf("%d %d", &nombre1, &nombre2);

	if (nombre1 == nombre2) {
		printf("\n 0");
	} else {
		printf("autre chose");
	}

	return 0;
}
