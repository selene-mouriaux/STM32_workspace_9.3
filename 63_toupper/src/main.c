/*
*****************************************************************************



*****************************************************************************
*/

#include<stdio.h>
#include<string.h>
#include<stdbool.h>
#include<ctype.h>

char text1[] = "Bonjour, je suis heureux d'�tre au campus";
char text2[] = "Qu'est-ce qu'un processeur ARM ? C'est un type de processeur particulier dont l'agencement des composants �lectroniques permet une taille r�duite. ARM est l'acronyme de Advanced Risk Machine. A l'origine, le A de ARM signifiait Acorn, le nom de la soci�t� qui a �quip� pour la premi�re fois un ordinateur avec un processeur ARM, en 1987. Depuis, l'architecture ARM a rencontr� un succ�s qui ne se d�ment pas, notamment ces derni�res ann�es. Des processeurs ARM, on en trouve dans tous les smartphones r�cents : iPhone 4, Samsung Galaxy S, tout comme dans l'iPad, le Nokia N97 ou le Nexus One de Google. Mais la soci�t� ARM ltd ne fabrique pas, � proprement parler, les processeurs. Elle con�oit les architectures des processeurs, leurs plans en quelque sorte. Ce sont les clients qui, apr�s achat des licences, produisent les processeurs. Par exemple, Samsung fabrique un processeur ARM pour ses t�l�phones haut de gamme (Samsung Galaxy S et Wave), reposant sur l'architecture ARM Cortex-A8, cadenc�e � 1 GHz. Le processeur Apple A4, qui �quipe les iPhone 4 et les iPad, utilise exactement la m�me architecture Cortex-A8. Ces \" petits \" processeurs connaissent un tel succ�s qu'ils �voluent tr�s rapidement : Samsung a d�j� annonc� le rempla�ant de Cortex-A8 ; celui-ci r�pond au nom de Cortex-A9 et int�gre deux coeurs, comme dans les PC. Quant au Cortex-A15, qui devrait �tre disponible dans une vingtaine de mois, on sait d�j� qu'il s'agira d'un processeur quatre coeurs cadenc� � 2,5 GHz et basse consommation ! Un tel processeur devrait avoir des performances similaires � celles d'un ordinateur portable tr�s haut de gamme, alors qu'il est pr�vu pour �tre embarqu� dans un t�l�phone de seulement quelques millim�tres d'�paisseur.";

int vowels_count;
int others_count;


int text_length(char text[]) {
	return strlen(text);
}

int details_in(char text[]) {

	char vowels[] = "AEIOUa���e�iouyY";
	char other_chars[] = " 0123456789&%.,_!:/?='*#<>{}()-+\"\\;";
	int to_upper = 'A' - 'a';
	bool is_other = false;
	for (int i = 0; text[i]!= '\0' ; i++) {
		int castvar_i = text[i];
		if (isalpha(text[i]) && islower(text[i])) {
			text[i] = castvar_i + to_upper ;
		}
		for (int j = 0; j < 35; j++) {
			if ( text[i] == other_chars[j]) {
				is_other = true;
				others_count = others_count + 1;
			}
		}
		if (!is_other) {
			for (int k = 0; k < 16; k++) {
				if ( text[i] == vowels[k] ) {
					vowels_count = vowels_count + 1;
				}
			}
		}
		is_other = false;
	}
	return 0;
}

int percentage(int vowels, int consonants, int total) {

	printf("Pourcentage de voyelles : %d %%, de consonnes : %d %%.\n\n", (vowels * 100 / total), (consonants * 100 / total));
	return 0;
}


int main(void){

	int txt_length = 0;
	int block_length = 0;
	int consonants_count;
	vowels_count = 0;
	others_count = 0;

	FILE *fp;
	char buffer[255];
	fp = fopen("/home/vincent/Documents/texte2.txt", "r");

	while (fgets(buffer, 255, fp) != NULL) {
		block_length = text_length(buffer)-1;
		printf("En minuscules : %s", buffer);
		txt_length = txt_length + block_length;
		details_in(buffer);
		printf("En majuscules : %s\n", buffer);
	}

	fclose(fp);
	consonants_count = txt_length - others_count - vowels_count;
	printf("Longueur du texte : %d caracteres.\n", txt_length);
	printf("contient %d voyelles, %d consonnes et %d caracteres autres.\n", vowels_count, consonants_count, others_count);
	percentage(vowels_count, consonants_count, txt_length);

	return 0;
}
