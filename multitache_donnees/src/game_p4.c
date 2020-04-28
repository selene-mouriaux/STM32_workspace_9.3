/*
 * game_p4.c
 *
 *  Created on: 30 mars 2020
 *      Author: marc
 */
#include "game_p4.h"

static int8_t gp4_matrix[NB_OF_COLUMN][NB_OF_LINE];
/* token_top_selector = position du jeton dans ligne de sélection (de 1 à NB_OF_COLUMN)*/
static int8_t token_top_selector;
static int8_t active_player;

/* INITIALISE LA PARTIE
 * vide la matrice
 * fixe le active_player
 * initialise les couleurs associées à chaque joueur
 * */
void gp4_init(void) {
	for (int8_t line = 0; line < NB_OF_LINE; line++) {
		for (int8_t col = 0; col < NB_OF_COLUMN; col++) {
			gp4_matrix[col][line] = EMPTY_SPACE;
		}
	}
	active_player = PLAYER_1;
	token_top_selector = START_POSITION;
}

/*AFFFICHE LA MATRICE DE JEU AVEC LA LIGNE DE SELECTION*/
void gp4_show_board(void) {
	printf("\ntop line\t");
	for (int8_t col = 0; col < NB_OF_COLUMN; col++) {
		if (col == token_top_selector - 1) {
			printf("%d ", active_player);
		} else {
			printf("%d ", EMPTY_SPACE);
		}
	}

	for (int8_t line = 0; line < NB_OF_LINE; line++) {
		printf("\nline %d  \t", line);
		for (int8_t col = 0; col < NB_OF_COLUMN; col++) {
			printf("%d ", gp4_matrix[col][line]);
		}
	}
	printf("\n\n");
}

/*MOUVEMENT À GAUCHE*/
pos_token_t gp4_move_left(void) {
	pos_token_t pos_token;
	pos_token.beg_position.c = token_top_selector;
	pos_token.beg_position.l = 1;
	token_top_selector--;
	if (token_top_selector < 1) { //SI JETON À L'EXTREMITÉ DE LA LIGNE IL BASCULE AU COTÉ OPPOSÉ
		token_top_selector = NB_OF_COLUMN;
	}
	while (gp4_matrix[token_top_selector - 1][0] != EMPTY_SPACE) { //SI COLONNE PLEINE LE JETON PASSE À LA COLONNE SUIVANTE
		token_top_selector--;
		if (token_top_selector < 1) {
			token_top_selector = NB_OF_COLUMN;
		}
	}
	pos_token.end_position.c = token_top_selector;
	pos_token.end_position.l = 1;
	pos_token.is_ok = 1;
	return pos_token;
}

/*MOUVEMENT À DROITE*/
pos_token_t gp4_move_right(void) {
	pos_token_t pos_token;
	pos_token.beg_position.c = token_top_selector;
	pos_token.beg_position.l = 1;
	token_top_selector++;
	if (token_top_selector > NB_OF_COLUMN) { //SI JETON À L'EXTREMITÉ DE LA LIGNE IL BASCULE AU COTÉ OPPOSÉ
		token_top_selector = 1;
	}
	while (gp4_matrix[token_top_selector - 1][0] != EMPTY_SPACE) { //SI COLONNE PLEINE LE JETON PASSE À LA COLONNE SUIVANTE
		token_top_selector++;
		if (token_top_selector > NB_OF_COLUMN) {
			token_top_selector = 1;
		}
	}
	pos_token.end_position.c = token_top_selector;
	pos_token.end_position.l = 1;
	pos_token.is_ok = 1;
	return pos_token;
}

/*VALIDATION DU COUP À JOUER*/
pos_token_t gp4_play_token(void) {
	pos_token_t pos_token;
	pos_token.beg_position.c = token_top_selector;
	pos_token.beg_position.l = 1;
	pos_token.end_position.c = token_top_selector;
	for (int8_t line = 1; line < NB_OF_LINE; line++) {
		if (gp4_matrix[token_top_selector - 1][line] != EMPTY_SPACE) { //CONTROLE SI PRÉSENCE JETON DANS LA LIGNE
			gp4_matrix[token_top_selector - 1][line - 1] = active_player;
			pos_token.end_position.l = line + 1;
			pos_token.is_ok = 1;
//			printf("retour gp4_play_token ligne : %d\n",
//					pos_token.end_position.l);
			return pos_token;
		}
	}
	if (gp4_matrix[token_top_selector - 1][NB_OF_LINE - 1] == EMPTY_SPACE) { //SI COLONNE VIDE LE JETON EST TOUT EN BAS
		gp4_matrix[token_top_selector - 1][NB_OF_LINE - 1] = active_player;
		pos_token.end_position.l = NB_OF_LINE + 1;
		pos_token.is_ok = 1;
	}
	return pos_token;
}

/*CHANGEMENT DE JOUEUR*/
pos_token_t gp4_set_player(void) {
	pos_token_t pos_token;
	pos_token.beg_position.l = 0;
	pos_token.beg_position.c = 0;
	pos_token.end_position.l = 1;
	if (active_player == PLAYER_1) {
		active_player = PLAYER_2;
		token_top_selector = START_POSITION;
		if (gp4_matrix[START_POSITION - 1][0] != EMPTY_SPACE) { //SI LA 1ÈRE COLONNE EST PLEINE LE JETON EST DÉPLACÉ SUR LA COLONNE LIBRE LA PLUS PROCHE
			gp4_move_right();
		}
	} else {
		active_player = PLAYER_1;
		token_top_selector = START_POSITION;
		if (gp4_matrix[START_POSITION - 1][0] != EMPTY_SPACE) {
			gp4_move_right();
		}
	}
	pos_token.end_position.c = token_top_selector;
	return pos_token;
}

winner_t gp4_check_winner(void) {
	winner_t victory_infos;
	int8_t aligned_tokens = 0;
//VÉRIFICATION DE VICTOIRE HORIZONTALE
	for (int8_t line = 0; line < NB_OF_LINE; line++) {
		aligned_tokens = 0;
		for (int8_t col = 0; col < NB_OF_COLUMN; col++) {
			if (gp4_matrix[col][line] == active_player) {
				victory_infos.win_position[aligned_tokens].c = col + 1;
				victory_infos.win_position[aligned_tokens].l = line + 1;
				aligned_tokens++;
			} else {
				aligned_tokens = 0;
			}
			if (aligned_tokens == 4) {
				victory_infos.win_type = horiz;
				victory_infos.status = stop_winner;
				victory_infos.win_player = active_player;

				return victory_infos;
			}
		}
	}
//VÉRIFICATION DE VICTOIRE VERTICALE
	for (int8_t col = 0; col < NB_OF_COLUMN; col++) {
		aligned_tokens = 0;
		for (int8_t line = 0; line < NB_OF_LINE; line++) {
			if (gp4_matrix[col][line] == active_player) {
				victory_infos.win_position[aligned_tokens].c = col + 1;
				victory_infos.win_position[aligned_tokens].l = line + 1 ;
				aligned_tokens++;
			} else {
				aligned_tokens = 0;
			}
			if (aligned_tokens == 4) {
				victory_infos.win_type = horiz;
				victory_infos.status = stop_winner;
				victory_infos.win_player = active_player;
				return victory_infos;
			}
		}
	}
//VÉRIFICATION DE VICTOIRE EN DIAGONALE DROITE
	for (int8_t line = 0; line < 3; line++) {
		for (int8_t col = 0; col < 4; col++) {
			if (gp4_matrix[col][line] == active_player) {
				if (gp4_matrix[col + 1][line + 1] == active_player
						&& gp4_matrix[col + 2][line + 2] == active_player
						&& gp4_matrix[col + 3][line + 3] == active_player) {
					victory_infos.status = stop_winner;
					victory_infos.win_player = active_player;
					victory_infos.win_position[0].c = col;
					victory_infos.win_position[1].c = col + 2;
					victory_infos.win_position[2].c = col + 3;
					victory_infos.win_position[3].c = col + 4;
					victory_infos.win_position[0].l = line;
					victory_infos.win_position[1].l = line + 2;
					victory_infos.win_position[2].l = line + 3;
					victory_infos.win_position[3].l = line + 4;
					victory_infos.win_type = right_diag;
					return victory_infos;
				}
			}
		}
	}

//VÉRIFICATION DE VICTOIRE EN DIAGONALE DROITE GAUCHE
	for (int8_t line = 0; line < 3; line++) {
		for (int8_t col = 3; col < NB_OF_COLUMN; col++) {
			if (gp4_matrix[col][line] == active_player) {
				if (gp4_matrix[col - 1][line + 1] == active_player
						&& gp4_matrix[col - 2][line + 2] == active_player
						&& gp4_matrix[col - 3][line + 3] == active_player) {
					victory_infos.status = stop_winner;
					victory_infos.win_player = active_player;
					victory_infos.win_position[0].c = col;
					victory_infos.win_position[1].c = col - 2;
					victory_infos.win_position[2].c = col - 3;
					victory_infos.win_position[3].c = col - 4;
					victory_infos.win_position[0].l = line;
					victory_infos.win_position[1].l = line + 2;
					victory_infos.win_position[2].l = line + 3;
					victory_infos.win_position[3].l = line + 4;
					victory_infos.win_type = left_diag;
					return victory_infos;
				}
			}
		}
	}

	victory_infos.status = live;
	return victory_infos;
}
