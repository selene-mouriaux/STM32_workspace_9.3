/*
 *****************************************************************************

 File        : main.c

 Gerald Hermant - 1 / 4 / 2020 - I'm not a fish
 *****************************************************************************
 */

#include<stdio.h>
#include <stdint.h>
// enum TheEnumeration : int8_t {
enum TheEnumeration {
	ZERO_ELMT = 0, FIRST_ELEMENT = 2, SECOND_ELEMENT = 4,
};

void question(void) {
	printf(
			"Pour ce tableau, Comment sont les adresses de chaque zone du tableau dans la mémoire ?\n");
	printf(
			"Quel est le rapport entre les indices du tableau et l'adresse de chaque ligne ?\n");
	printf(
			"Comment sont organisées les  du tableau dans la mémoire ?\n");
}

#define SIZE 4
int T[SIZE] = { 10, 20, 30, 40 };

void array1(void) {
	printf("\nTableau T[%d] : \n", SIZE);
	for (int i = 0; i < SIZE; i++) {
		int * theAdd = &(T[i]);
		printf(
				"indice=%d, Access(T[i])=%d, Addresse (&xx)= %p, Dereferencement(*addresse)=%02d\n",
				i, T[i], theAdd, *theAdd);
	}
	question();
}
#define SIZE_DIM1 4
#define SIZE_DIM2 2
int T2[SIZE_DIM1][SIZE_DIM2];

void array2d(void) {
	for (int x = 0; x < SIZE_DIM1; x++) {
		for (int y = 0; y < SIZE_DIM2; y++) {
			T2[x][y] = x * 100 + 10 * y;
		}
	}
	printf("\nTableau T2[%d][%d] : \n", SIZE_DIM1, SIZE_DIM2);
	for (int x = 0; x < SIZE_DIM1; x++) {
		for (int y = 0; y < SIZE_DIM2; y++) {
			int * theAdd = &(T2[x][y]);
			printf(
					"indice(x,y)=[%d][%d], Access(T2[x][y])=%03d, Addresse (&xx)= %p, Dereferencement(*addresse)=%03d\n",
					x, y, T2[x][y], theAdd, *theAdd);
		}
		printf("\n");
	}
	question();
}

#define SIZE_DIM3 3
int T3[SIZE_DIM1][SIZE_DIM2][SIZE_DIM3];

void array3d(void) {
	for (int x = 0; x < SIZE_DIM1; x++) {
		for (int y = 0; y < SIZE_DIM2; y++) {
			for (int z = 0; z < SIZE_DIM3; z++) {
				T2[x][y] = x * 100 + 10 * y + z;
			}
		}
	}
	printf("\nTableau T3[%d][%d][%d] : \n", SIZE_DIM1, SIZE_DIM2, SIZE_DIM3);
	for (int x = 0; x < SIZE_DIM1; x++) {
		for (int y = 0; y < SIZE_DIM2; y++) {
			for (int z = 0; z < SIZE_DIM3; z++) {
				int * theAdd = &(T3[x][y][z]);
				printf(
						"indice(x,y,z)=[%d][%d][%d], Access(T3[x][y][z])=%02d, Addresse (&xx)= %p, Dereferencement(*addresse)=%03d\n",
						x, y, z, T3[x][y][z], theAdd, *theAdd);
			}
			printf("\n");
		}
		printf("\n");
	}
	question();
}

int size(int inParamTableau[]) {

	printf("Taille d'un char   %ld\n", sizeof(char));
	printf("Taille d'un int8_t %ld\n", sizeof(int8_t));
	printf("Taille d'un enum   %ld\n", sizeof(enum TheEnumeration));

	printf("Taille d'un short  %ld\n", sizeof(short));

	printf("Taille d'un int    %ld\n", sizeof(int));
	printf("Taille d'un sizeof(long)   %ld\n", sizeof(long));

	printf("Taille de T[%d] : sizeof(T): %ld\n", SIZE, sizeof(T));
	printf("Pourquoi cette taille (%ld) ? alors qu'on a demandé %d elements ?\n", sizeof(T), SIZE);
	int * p = T;
	printf("int *p=T;\n");
	printf("Taille de p : sizeof(p): %ld\n", sizeof(p));
	printf(
			"Pourquoi la taille d'un pointeur de T est différente de la taille de T ?\n");

	// Supprime le warning
	//ref : https://gcc.gnu.org/onlinedocs/gcc/Diagnostic-Pragmas.html#Diagnostic-Pragmas
	// _Pragma("GCC diagnostic ignored \"-Wsizeof-array-argument\"");

	printf("Mon argument est inParamTableau[]. sizeof(inParamTableau)=%ld\n",
			sizeof(inParamTableau));
	printf(
			"Pourquoi la taille sizeof() du paramétre est différente de la taille du tableau ?\n");
	printf("Avez-vous regardé les warnings de la compilations ?\n");
	fflush(stdout);

	return 0;
}
int main(void) {
	size(T);
	array1();
//	array2d();
//	array3d();

}
