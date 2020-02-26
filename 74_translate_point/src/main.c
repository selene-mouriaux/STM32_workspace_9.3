/*
*****************************************************************************

*****************************************************************************
*/

#include<stdio.h>
#include<math.h>
typedef struct {
	int xx;
	int yy;
} point;

float distance_calculation(point x, point y) {

	float distance;
	distance = sqrt(pow(x.xx-y.xx,2) + pow(x.yy-y.yy,2));
	return distance;
}


int main(void){

	point x;
	point y;
	x.xx = 2;
	x.yy = 2;
	y.xx = 19;
	y.yy = 20;

	double eucl_distance;

	eucl_distance = distance_calculation(x, y);
	printf("%lf", eucl_distance);

	return 0;
}
