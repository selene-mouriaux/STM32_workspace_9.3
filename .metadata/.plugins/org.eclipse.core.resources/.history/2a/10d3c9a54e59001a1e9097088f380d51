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



void SetLedColor(RGB tabline[], int tabsize) {
	int j;
	for (j = 0; j < tabsize; j++) {
		if (tabline[j].R != 0 && tabline[j].G == 0 && tabline[j].B == 0) {
			printf("couleur %d = RED %d\n",j +1, tabline[j].R);
		} else if (tabline[j].R == 0 && tabline[j].G != 0 && tabline[j].B == 0) {
			printf("couleur %d = Green %d, ",j +1, tabline[j].G);
		} else if (tabline[j].R == 0 && tabline[j].G == 0 && tabline[j].B != 0) {
			printf("couleur %d = Blue %d, ",j +1, tabline[j].B);
		} else if (tabline[j].R == tabline[j].G && tabline[j].G == tabline[j].B && tabline[j].R != 0) {
			printf("couleur %d = White %d, ",j +1, tabline[j].R);
		} else if (tabline[j].R !=0 && tabline[j].G == 0 && tabline[j].B !=0 ) {
			printf("couleur %d = Purple %d %d, ",j +1, tabline[j].R, tabline[j].B);
		} else if (tabline[j].R == tabline[j].G && tabline[j].B ==0 ) {
			printf("couleur %d = Yellow %d ",j +1, tabline[j].R);
		}
	}
}


int main(void){

	RGB green = {0,255,0};
	RGB white = {255,255,255};
	RGB blue = {0,0,255};
	RGB red = {255,0,0};
	RGB purple = {255,0,255};
	RGB yellow = {255,255,0};
	RGB none = {0,0,0};

	RGB tabline[7] = {green, white, blue, red, purple, yellow, none};

	SetLedColor(tabline, 7);

	return 0;
}
