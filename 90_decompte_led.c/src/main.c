#include "leds_control.h"
#include<stdio.h>


//type Color RGB
typedef struct{
	int RValue;
	int GValue;
	int BValue;
}Color;


//le rgb des couleurs

const Color red ={255,0,0};
const Color green={0,255,0};
const Color blue={0,0,255};
const Color white={255,255,255};
const Color purple={255,0,255};
const Color yellow={255,255,0};
const Color black={0,0,0};


//fonction qui incremente chaque colone de led
void setledline(Color **matrice,int tabsize){
	for(int row=0; row< tabsize;row++){
		for(int col=0;col<tabsize;col++){
			setLedColor((row + 1),(col + 1),matrice[row][col].RValue,matrice[row][col].GValue,matrice[row][col].BValue);
		}
	}

}
void setsmiley(int tabsize){
	Color number=black;
	Color background=white;
	Color tabline_1[7]={background,background,yellow,yellow,yellow,background,background};
	Color tabline_2[7]={background,yellow,yellow,yellow,yellow,yellow,background};
	Color tabline_3[7]={yellow,yellow,number,yellow,number,yellow,yellow};
	Color tabline_4[7]={yellow,yellow,yellow,yellow,yellow,yellow,yellow};
	Color tabline_5[7]={yellow,number,yellow,yellow,yellow,number,yellow};
	Color tabline_6[7]={background,yellow,number,number,number,yellow,background};
	Color tabline_7[7]={background,background,yellow,yellow,yellow,background,background};

	Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
	setledline(matrice,tabsize);

}
//fonction qui affiche des nombre en decomptant
void setcountdown(int tabsize){
	Color background =black;
	Color number;
	for (int decompte = 9;decompte >=0;decompte --){
		if(decompte == 9){
			number=green;
			Color tabline_1[7]={background,background,number,number,number,background,background};
			Color tabline_2[7]={background,number,background,background,background,number,background};
			Color tabline_3[7]={background,number,background,background,background,number,background};
			Color tabline_4[7]={background,background,number,number,number,number,background};
			Color tabline_5[7]={background,background,background,background,background,number,background};
			Color tabline_6[7]={background,background,background,background,background,number,background};
			Color tabline_7[7]={background,background,number,number,number,number,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}
		if(decompte == 8){
			number=white;
			Color tabline_1[7]={background,background,number,number,number,background,background};
			Color tabline_2[7]={background,number,background,background,background,number,background};
			Color tabline_3[7]={background,number,background,background,background,number,background};
			Color tabline_4[7]={background,background,number,number,number,background,background};
			Color tabline_5[7]={background,number,background,background,background,number,background};
			Color tabline_6[7]={background,number,background,background,background,number,background};
			Color tabline_7[7]={background,background,number,number,number,background,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}
		if(decompte == 7){
			number=blue;
			Color tabline_1[7]={background,number,number,number,number,number,background};
			Color tabline_2[7]={background,background,background,background,background,number,background};
			Color tabline_3[7]={background,background,background,background,background,number,background};
			Color tabline_4[7]={background,background,background,background,number,background,background};
			Color tabline_5[7]={background,background,background,number,background,background,background};
			Color tabline_6[7]={background,background,number,background,background,background,background};
			Color tabline_7[7]={background,number,background,background,background,background,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}
		if(decompte == 6){
			number=red;
			Color tabline_1[7]={background,background,number,number,number,background,background};
			Color tabline_2[7]={background,number,background,background,background,number,background};
			Color tabline_3[7]={background,number,background,background,background,background,background};
			Color tabline_4[7]={background,number,number,number,number,background,background};
			Color tabline_5[7]={background,number,background,background,background,number,background};
			Color tabline_6[7]={background,number,background,background,background,number,background};
			Color tabline_7[7]={background,background,number,number,number,background,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}
		if(decompte == 5){
			number=purple;
			Color tabline_1[7]={background,number,number,number,number,number,background};
			Color tabline_2[7]={background,number,background,background,background,background,background};
			Color tabline_3[7]={background,number,background,background,background,background,background};
			Color tabline_4[7]={background,number,number,number,number,background,background};
			Color tabline_5[7]={background,background,background,background,background,number,background};
			Color tabline_6[7]={background,number,background,background,background,number,background};
			Color tabline_7[7]={background,background,number,number,number,background,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}
		if(decompte == 4){
			number=yellow;
			Color tabline_1[7]={background,background,background,background,number,background,background};
			Color tabline_2[7]={background,background,background,number,number,background,background};
			Color tabline_3[7]={background,background,number,background,number,background,background};
			Color tabline_4[7]={background,number,number,number,number,number,background};
			Color tabline_5[7]={background,background,background,background,number,background,background};
			Color tabline_6[7]={background,background,background,background,number,background,background};
			Color tabline_7[7]={background,background,background,background,number,background,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}
		if(decompte == 3){
			number=black;
			background=white;
			Color tabline_1[7]={background,background,number,number,number,background,background};
			Color tabline_2[7]={background,number,background,background,background,number,background};
			Color tabline_3[7]={background,background,background,background,background,number,background};
			Color tabline_4[7]={background,background,background,number,number,number,background};
			Color tabline_5[7]={background,background,background,background,background,number,background};
			Color tabline_6[7]={background,number,background,background,background,number,background};
			Color tabline_7[7]={background,background,number,number,number,background,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}
		if(decompte == 2){
			number=blue;
			background=black;
			Color tabline_1[7]={background,background,number,number,number,background,background};
			Color tabline_2[7]={background,number,background,background,background,number,background};
			Color tabline_3[7]={background,background,background,background,background,number,background};
			Color tabline_4[7]={background,background,background,background,number,background,background};
			Color tabline_5[7]={background,background,background,number,background,background,background};
			Color tabline_6[7]={background,background,number,background,background,background,background};
			Color tabline_7[7]={background,number,number,number,number,number,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}
		if(decompte == 1){
			number=green;
			Color tabline_1[7]={background,background,background,background,number,background,background};
			Color tabline_2[7]={background,background,background,number,number,background,background};
			Color tabline_3[7]={background,background,number,background,number,background,background};
			Color tabline_4[7]={background,number,background,background,number,background,background};
			Color tabline_5[7]={background,background,background,background,number,background,background};
			Color tabline_6[7]={background,background,background,background,number,background,background};
			Color tabline_7[7]={background,background,background,background,number,background,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}
		if(decompte == 0){
			number=black;
			background=white;
			Color tabline_1[7]={background,background,yellow,yellow,yellow,background,background};
			Color tabline_2[7]={background,yellow,yellow,yellow,yellow,yellow,background};
			Color tabline_3[7]={yellow,yellow,number,yellow,number,yellow,yellow};
			Color tabline_4[7]={yellow,yellow,yellow,yellow,yellow,yellow,yellow};
			Color tabline_5[7]={yellow,number,yellow,yellow,yellow,number,yellow};
			Color tabline_6[7]={background,yellow,number,number,number,yellow,background};
			Color tabline_7[7]={background,background,yellow,yellow,yellow,background,background};

			Color * matrice[7]={tabline_1,tabline_2,tabline_3,tabline_4,tabline_5,tabline_6,tabline_7};
			setledline(matrice,tabsize);
		}

		sleep(4);
		setsmiley(tabsize);
	}


}
int main(void){
	int tabsize=7;


	setcountdown(tabsize);











	return 0;
}
