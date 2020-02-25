/*
 *****************************************************************************

 *****************************************************************************
 */

#include<stdio.h>

int comparer(const char s1[], const char s2[]) {

	int i;
	for ( i = 0; s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]; i++) {
	}
	return (s1[i] - s2[i]);
}



int main(void){

	char chaine1[] = "c'est moi prosper, youpla boum ! Le meilleur copain d'épice !";
	char chaine2[] = "c'est moi prosper, youpla boum ! Le meilleur copain d'épice !";

	printf("%d", comparer(chaine1, chaine2));

	return 0;
}
