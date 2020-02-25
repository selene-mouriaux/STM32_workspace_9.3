/*
*****************************************************************************

Max and Min values are are calculated on basis +- 2%

*****************************************************************************
*/

#include<stdio.h>
#include<stdbool.h>

char cinderblock_category = 'O';
int max_weight = 19380;
int min_weight = 18620;
int max_length = 510;
int min_length = 490;
int max_width = 204;
int min_width = 196;
int max_height = 204;
int min_height = 196;


bool iscorrect(int measure, int measure_max, int measure_min) {

	bool result;

	if (measure <= measure_max && measure >= measure_min)
		result = true;
	else
		result = false;

	return result;
}


char sort_block(int weight, int length, int width, int height) {

	bool correct_weight = iscorrect(weight, max_weight, min_weight);
	bool correct_length = iscorrect(length, max_length, min_length);
	bool correct_width = iscorrect(width, max_width, min_width);
	bool correct_height = iscorrect(height, max_height, min_height);

	if(correct_weight) {
		if((correct_length && correct_width) || (correct_width && correct_height) || (correct_length && correct_height)) {
			return 'A';
		} else if((!correct_length && !correct_width) || (!correct_width && !correct_height) ||(!correct_length && !correct_height)) {
			return 'B';
		}
	} else {
		if(!correct_length || !correct_width || !correct_height) {
			return 'C';
		} else {
			return 'B';
		}
	}
	return 0;
}


int main(void){

	int weight = 0;
	int length = 0;
	int width = 0;
	int height = 0;

	while(1) {
		scanf("%d %d %d %d", &weight, &length, &width, &height);
		printf("%c", sort_block(weight, length, width, height));
	}
	return 0;
}
