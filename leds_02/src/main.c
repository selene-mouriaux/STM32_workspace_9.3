/*
 *****************************************************************************

 *****************************************************************************
 */

#include<stdio.h>
#include"leds_control.h"
typedef struct {
	int R;
	int G;
	int B;
} RGB;
typedef struct {
	RGB grid[7][7];
} GRID;


/*
void SetLedColor(int Numlignes, RGB tabline[], int tabsize) {
	int j;
	printf("\n");
	for (j = 0; j < tabsize; j++) {
		if (tabline[j].R != 0 && tabline[j].G == 0 && tabline[j].B == 0) {
			printf("%d, %d = RED %d",j +1, Numlignes, tabline[j].R);
		} else if (tabline[j].R == 0 && tabline[j].G != 0 && tabline[j].B == 0) {
			printf("%d, %d = Green %d",j +1, Numlignes, tabline[j].G);
		} else if (tabline[j].R == 0 && tabline[j].G == 0 && tabline[j].B != 0) {
			printf("%d, %d = Blue %d",j +1, Numlignes, tabline[j].B);
		} else if (tabline[j].R == tabline[j].G && tabline[j].G == tabline[j].B && tabline[j].R != 0) {
			printf("%d, %d = White %d",j +1, Numlignes, tabline[j].R);
		} else if (tabline[j].R !=0 && tabline[j].G == 0 && tabline[j].B != 0 ) {
			printf("%d, %d = Purple %d %d",j +1, Numlignes, tabline[j].R, tabline[j].B);
		} else if (tabline[j].R == 0 && tabline[j].G == 0 && tabline[j].B == 0 ) {
			printf("%d, %d = Black %d",j +1, Numlignes, tabline[j].R);
		} else if (tabline[j].R == tabline[j].G && tabline[j].B == 0 ) {
			printf("%d, %d = Yellow %d",j +1, Numlignes, tabline[j].R);
		}
		printf(", ");
	}
}
*/

GRID iteration4(RGB color1, RGB color2, RGB color3, RGB color4) {
	int y;
	int x;
	GRID iteration4;
	for ( y = 0; y < 7; y++) {
		for ( x = 0; x < 7; x++) {
			if (x + 3 == 3 || x - 3 == 3 || y + 3 == 3 || y - 3 == 3) {
				iteration4.grid[x][y] = color1;
			} else if (x + 2 == 3 || x - 2 == 3 || y + 2 == 3 || y - 2 == 3) {
				iteration4.grid[x][y] = color2;
			} else if (x + 1 == 3 || x - 1 == 3 || y + 1 == 3 || y - 1 == 3) {
				iteration4.grid[x][y] = color3;
			} else if (x == 3 || y - 3) {
				iteration4.grid[x][y] = color4;
			}
		}
	}
	return iteration4;
}



int main(void){

	RGB green = {0,255,0};
//	RGB white = {255,255,255};
//	RGB blue = {0,0,255};
	RGB red = {255,0,0};
//	RGB purple = {255,0,255};
	RGB yellow = {255,255,0};
	RGB black = {0,0,0};

	RGB tabline[7] = {black, black, black, black, black, black, black};
	GRID it4_grid;
	it4_grid = iteration4(red, black, green, yellow);

	for (int h = 0; h < 7; h++) {
		for (int i = 0; i < 7; i++) {
			setLedColor(h+1, i+1, it4_grid.grid[h][i].R, it4_grid.grid[h][i].G, it4_grid.grid[h][i].B);
			sleep(1);
		}
//		setLedColor(h, tabline, 7);
	}

	return 0;
}
