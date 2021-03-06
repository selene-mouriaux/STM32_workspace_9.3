/*
 *****************************************************************************

 *****************************************************************************
 */

#include<stdio.h>
typedef struct {
	int R;
	int G;
	int B;
} RGB;



void SetLedColor( int LEDNum, RGB color) {
	if (color.R != 0 && color.G == 0 && color.B == 0) {
		printf("couleur %d = RED %d\n",LEDNum, color.R);
	} else if (color.R == 0 && color.G != 0 && color.B == 0) {
		printf("couleur %d = Green %d, ",LEDNum, color.G);
	} else if (color.R == 0 && color.G == 0 && color.B != 0) {
		printf("couleur %d = Blue %d, ",LEDNum, color.B);
	} else if (color.R == color.G && color.G == color.B && color.R != 0) {
		printf("couleur %d = White %d, ",LEDNum, color.R);
	} else if (color.R !=0 && color.G == 0 && color.B !=0 ) {
		printf("couleur %d = Purple %d %d, ",LEDNum, color.R, color.B);
	} else if (color.R == color.G && color.B ==0 ) {
		printf("couleur %d = Yellow %d ",LEDNum, color.R);
	}
}


int main(void){

	RGB tabline[7] = {{0,255,0},{255,255,255},{0,0,255},{255,0,0},{255,0,255},{255,255,0},{0,0,0}};

	for (int i = 0; i < 6; i++) {
		SetLedColor( i + 1, tabline[i]);
	}

	return 0;
}
