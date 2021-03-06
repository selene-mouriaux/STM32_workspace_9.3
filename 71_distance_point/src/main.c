/*
*****************************************************************************

*****************************************************************************
*/

#include<stdio.h>
#include<math.h>

float distance_calculation(float x1, float y1, float x2,  float y2) {

	float distance;
	distance = sqrt(pow(x2-x1,2) + pow(y2-y1,2));
	return distance;
}


int main(void){

	float x1 = 2.8;
	float y1 = 1.9;
	float x2 = 19.75;
	float y2 = 20.16;
	double eucl_distance;

	eucl_distance = distance_calculation(x1, y1, x2, y2);
	printf("%lf", eucl_distance);

	return 0;
}
