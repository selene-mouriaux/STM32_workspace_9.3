/*
 *****************************************************************************

 *****************************************************************************
 */

#include<stdio.h>
#include<stdbool.h>

int vowels_count;
int others_count;
char text1[] = "Bonjour, je suis heureux d'être au campus";

int text_length(char text[]) {
	int i = 0;
	int text_length = 0;
	while (text[i] != '\0') {
		text_length += 1;
		i++;
	}
	return text_length;
}

int main(void){

	vowels_count = 0;
	others_count = 0;
	int txt_length;
	int consonants_count;
	bool is_other = false;
	txt_length = text_length(text1);

	char vowels[] = "AEIOUaàéèeêiouyY";
	char other_chars[] = " 0123456789&%.,_!:/?='*#<>{}()-+\"\\;";

	for (int i = 0; i <= txt_length; i++) {
		for (int j = 0; j < 35; j++) {
			if ( text1[i] == other_chars[j]) {
				is_other = true;
				others_count = others_count + 1;
			}
		}
		if (!is_other) {
			for (int k = 0; k < 16; k++) {
				if ( text1[i] == vowels[k] ) {
					vowels_count = vowels_count + 1;
				}
			}
		}
		is_other = false;
	}
	consonants_count = txt_length - others_count - vowels_count;
	printf("Longueur du texte : %d caracteres.\n", txt_length);
	printf("contient %d voyelles, %d consonnes et %d caracteres autres.\n", vowels_count, consonants_count, others_count);
	return 0;

}
