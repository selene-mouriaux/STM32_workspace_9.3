/*
 *****************************************************************************



 *****************************************************************************
 */

#include<stdio.h>
#include<string.h>
#include<stdbool.h>

char text1[] = "Bonjour, je suis heureux d'être au campus";
char text2[] = "Qu'est-ce qu'un processeur ARM ? C'est un type de processeur particulier dont l'agencement des composants électroniques permet une taille réduite. ARM est l'acronyme de Advanced Risk Machine. A l'origine, le A de ARM signifiait Acorn, le nom de la société qui a équipé pour la première fois un ordinateur avec un processeur ARM, en 1987. Depuis, l'architecture ARM a rencontré un succès qui ne se dément pas, notamment ces dernières années. Des processeurs ARM, on en trouve dans tous les smartphones récents : iPhone 4, Samsung Galaxy S, tout comme dans l'iPad, le Nokia N97 ou le Nexus One de Google. Mais la société ARM ltd ne fabrique pas, à proprement parler, les processeurs. Elle conçoit les architectures des processeurs, leurs plans en quelque sorte. Ce sont les clients qui, après achat des licences, produisent les processeurs. Par exemple, Samsung fabrique un processeur ARM pour ses téléphones haut de gamme (Samsung Galaxy S et Wave), reposant sur l'architecture ARM Cortex-A8, cadencée à 1 GHz. Le processeur Apple A4, qui équipe les iPhone 4 et les iPad, utilise exactement la même architecture Cortex-A8. Ces \" petits \" processeurs connaissent un tel succès qu'ils évoluent très rapidement : Samsung a déjà annoncé le remplaçant de Cortex-A8 ; celui-ci répond au nom de Cortex-A9 et intègre deux coeurs, comme dans les PC. Quant au Cortex-A15, qui devrait être disponible dans une vingtaine de mois, on sait déjà qu'il s'agira d'un processeur quatre coeurs cadencé à 2,5 GHz et basse consommation ! Un tel processeur devrait avoir des performances similaires à celles d'un ordinateur portable très haut de gamme, alors qu'il est prévu pour être embarqué dans un téléphone de seulement quelques millimètres d'épaisseur.";

int vowels_count;
int others_count;


int text_length(char text[]) {
	int i = 0;
	int text_length = 0;
	while (text[i] != '\0') {
		text_length += 1;
		i++;
	}
	return text_length;
}


int details_in(char text[], int block_length) {

	char vowels[] = "AEIOUaàéèeêiouyY";
	char other_chars[] = " 0123456789&%.,_!:/?='*#<>{}()-+\"\\;";
	bool is_other = false;
	for (int i = 0; i <= block_length; i++) {
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


int words_in(const char *block, int block_length)
{
	int count=0;
	char lastC;
	if(block_length > 0)
	{
		lastC = block[0];
	}
	for(int i = 0; i <= block_length; i++)
	{
		if((block[i]==' ' || block[i]=='\0') && lastC != ' ')
		{
			count++;
		}
		lastC = block[i];
	}
	return count;
}


int main(void){

	int txt_length = 0;
	int block_length = 0;
	int consonants_count;
	int total_words = 0;
	vowels_count = 0;
	others_count = 0;

	FILE *fp;
	char buffer[255];
	fp = fopen("/home/vincent/Documents/texte2.txt", "r");

	while (fgets(buffer, 255, fp) != NULL) {
//		printf("%s", buffer);
		block_length = text_length(buffer) - 1;
		total_words = total_words + words_in(buffer, block_length + 1);
		txt_length = txt_length + block_length;
		details_in(buffer, block_length);
	}

	fclose(fp);
	consonants_count = txt_length - others_count - vowels_count;
	printf("Longueur du texte : %d caracteres.\n", txt_length);
	printf("Le texte contient %d mots détaillés en ", total_words);
	printf("%d voyelles, %d consonnes et %d caracteres autres.\n", vowels_count, consonants_count, others_count);
	percentage(vowels_count, consonants_count, txt_length);

	return 0;
}
