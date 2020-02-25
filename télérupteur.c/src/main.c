/*
*****************************************************************************

Programme de télérupteur

*****************************************************************************
*/

#include <stdio.h>
#include <stdbool.h>

int main(void){

	bool lights_on;
	int pushed_button = 0;

	while (1) {
		scanf("%d", &pushed_button);
		if (lights_on && (pushed_button == 1 || pushed_button == 2)) {
			printf("L'appui sur l'interrupteur %d éteint les lumières.", pushed_button);
			lights_on = false;
		}
		else if (!lights_on && (pushed_button == 1 || pushed_button == 2)) {
			printf("L'appui sur l'interrupteur %d allume les lumières.", pushed_button);
			lights_on = true;
		}
		else {
			printf("Merci d'utiliser le bouton 1 ou 2");
		}


	}


	return 0;
}
