/*
 *****************************************************************************

 *****************************************************************************
 */

#include<stdio.h>

int main(void){

	float nombre1;
	float nombre2;

	printf("Saisissez deux flottants :");
	scanf("%f %f", &nombre1, &nombre2);

	if (nombre1 == nombre2) {
		printf("\n 0");
	} else {
		printf("%f", nombre1 - nombre2);
	}
	return 0;
}
