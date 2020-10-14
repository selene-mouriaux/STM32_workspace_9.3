/*
 * game_p4.c
 *
 *  Created on: Mar 30, 2020
 *      Author: mickaell
 */
#include "FIFO.h"
#include "leds_control.h"
#include "thread.h"
#include "game_p4.h"
#include <stdint.h>
#include <stdio.h>
//

int8_t matrix[COL_COUNT][LINE_COUNT ];
int8_t g_token_top_selector = 3;
extern int8_t active_player;

////initialise la matrice
void gp4_init(void) {
	g_token_top_selector=3;
	active_player= PLAYER_1;
	clear_matrix();
}
////
//matrice vide
void clear_matrix(void) {

	for (int8_t row = 0; row < LINE_COUNT; row++) {
		for (int8_t col = 0; col < COL_COUNT; col++) {
			matrix[col][row] = EMPTY_SPACE;
		}
	}
}
//
//affiche la top line
void top_line_display(void) {
	printf("TOP     : ");
	for (int8_t col = 0; col < COL_COUNT; col++) {
		if (col == g_token_top_selector ) {
			printf("%d ", active_player);
		} else {
			printf("%d ", EMPTY_SPACE);
		}
	}
	printf("\n");
}
//
//affiche la matrice
void diplay_matrix(void) {

	for (int8_t row = 0; row < LINE_COUNT; row++) {
		printf("Ligne %d : ", row );
		for (int8_t col = 0; col < COL_COUNT; col++) {
			printf("%d ", matrix[col][row]);
		}
		printf("\n");
	}
}

//affiche le jeu
void gp4_display(void) {
	top_line_display();
	diplay_matrix();

}
//
//deplace le jeton du joueur vers la droite et si il arrive en but��e de droite se retrouve tout a gauche
pos_token_played_t  gp4_move_right(void) {
	pos_token_played_t pos_token;
	pos_token.beg_position.c = g_token_top_selector;
	pos_token.beg_position.l = 0;
	g_token_top_selector++;
	if (g_token_top_selector > (COL_COUNT)) {
		g_token_top_selector = 0;
	}
	pos_token.end_position.c = g_token_top_selector;
	pos_token.end_position.l = 0;
	pos_token.is_ok = 1;
	return pos_token;

}

//deplace le jeton du joueur vers la gauche et si il arrive en but��e se retrouve tout a droite
pos_token_played_t  gp4_move_left(void) {
	pos_token_played_t pos_token;
	pos_token.beg_position.c = g_token_top_selector;
	pos_token.beg_position.l = 0;
	g_token_top_selector--;
	if (g_token_top_selector < 0) {
		g_token_top_selector = COL_COUNT - 1 ;

	}
	pos_token.end_position.c = g_token_top_selector;
	pos_token.end_position.l = 0;
	pos_token.is_ok = 1;
	return pos_token;

}
bool is_col_empty(int col) {
	if (col < 0) {
		return false;
	}
	if (col > COL_COUNT) {
		return false;
	}
	if (matrix[col][0] == 0) {
		return true;
	}
	return false;
}
winner_t gp4_check_vertically(void){
	winner_t game_status;
	game_status.status = 0;
	for (int line = 0; line < 7; line++) {
		for (int col = 0; col < 7; col++) {
			if (matrix[line][col] == matrix[line][col + 1]) {
				if (matrix[line][col] == matrix[line][col + 2]) {
					if (matrix[line][col] == matrix[line][col + 3]) {
						if (matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = vert;
							if (matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}
						}
					}
				}
			}
		}
	}
	return game_status;
}

winner_t gp4_check_horizontally(void){
	winner_t game_status;
	game_status.status = 0;
	for (int col = 0; col < 7; col++) {
		for (int line = 0; line < 7; line++) {
			if (matrix[line][col] == matrix[line + 1][col]) {
				if (matrix[line][col] ==matrix[line + 2][col]) {
					if (matrix[line][col] == matrix[line + 3][col]) {
						if (matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = horiz;
							if (matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}
						}
					}
				}
			}
		}
	}
	return game_status;
}

winner_t gp4_check_diagonals_right_and_left(void){
	winner_t game_status;
	game_status.status = 0;
//	int col, line;

	for (int col = 0; col < 7; col++)  {
		for (int line = 0; line < 7; line++){
			if (matrix[line][col] == matrix[line + 1][col + 1]) {
				if (matrix[line][col] == matrix[line + 2][col + 2]) {
					if (matrix[line][col] == matrix[line + 3][col + 3]) {
						if (matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = right_diag;
							if (matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}
						}
					}
				}
			}
		}
	}
	for (int col = 0; col < 7; col++) {
		for (int line = 0; line < 7; line++) {
			if (matrix[line][col] == matrix[line - 1][col - 1]) {
				if (matrix[line][col] == matrix[line - 2][col - 2]) {
					if (matrix[line][col] == matrix[line - 3][col - 3]) {
						if (matrix[line][col] != 0) {
							game_status.status = stop_winner;
							game_status.win_type = left_diag;
							if (matrix[line][col] == 1) {
								game_status.win_player = PLAYER_1;
								return game_status;
							} else {
								game_status.win_player = PLAYER_2;
								return game_status;
							}
						}
					}
				}
			}
		}
	}
	return game_status;
}

winner_t gp4_check_winner (void) {
	winner_t game_status;

	int compteur = 0;

	game_status = gp4_check_horizontally();
	if(game_status.status == live){
	}
	game_status = gp4_check_vertically();
	if(game_status.status == live){
	}
	game_status = gp4_check_diagonals_right_and_left();
	if (game_status.status == live){

	}

	for (int col = 0; col < 7; col++) {
		if (!is_col_empty(col)) {
			compteur++;
		}
	}
	if (compteur == 6) {
		game_status.status = stop_equal;
	}
	return game_status;
}


pos_token_played_t gp4_play_token(void){
	int8_t play_line = LINE_COUNT -1;
	while (matrix[g_token_top_selector][play_line] != EMPTY_SPACE){
		play_line -= 1;
	}
	matrix[g_token_top_selector][play_line] = active_player;
	pos_token_played_t token_played;
	token_played.is_ok = true;
	token_played.beg_position.c = g_token_top_selector;
	token_played.beg_position.l = 0;
	token_played.end_position.c = g_token_top_selector ;
	token_played.end_position.l = play_line+1;

	return token_played;
}

//
////valide le coup jouer par le joueur et verifie si il y a un jetons pos�� avant de valid��
//pos_token_played_t  gp4_play_token(void) {
//	pos_token_played_t pos_token;
//	pos_token.beg_position.c = g_token_top_selector;
//	pos_token.beg_position.l = 0;
//	pos_token.end_position.c = g_token_top_selector;
//	if (matrix[g_token_top_selector ][LINE_COUNT - 1] == EMPTY_SPACE) {
//		matrix[g_token_top_selector ][LINE_COUNT - 1] = active_player;
//		pos_token.end_position.l = LINE_COUNT - 1 ;
//	}
//	else {
//		for (int8_t row = 0; row < LINE_COUNT; row++) {
//			if (matrix[g_token_top_selector ][row] != EMPTY_SPACE) {
//				matrix[g_token_top_selector ][row - 1 ] = active_player;
//				pos_token.end_position.l = row - 1 ;
//				return pos_token;
//			}
//		}
//
//	}
////
//	while (matrix[g_token_top_selector ][0] != EMPTY_SPACE) {
//		g_token_top_selector += 1;
//
//		if (g_token_top_selector > (COL_COUNT - 1)) {
//			g_token_top_selector = EMPTY_SPACE;
//		}
//		else if (g_token_top_selector < 0){
//			g_token_top_selector = COL_COUNT - 1 ;
//		}
//
//	}
//	pos_token.is_ok = 1;
//	return pos_token;
//}

//change de joueur
pos_token_played_t gp4_next_player(void) {
	pos_token_played_t pos_token;
	pos_token.beg_position.l = 10;
	pos_token.beg_position.c = 10;
	pos_token.end_position.l = 0;
	if (active_player == PLAYER_1) {
		active_player = PLAYER_2;
		g_token_top_selector = 3;
	} else {
		active_player = PLAYER_1;
		g_token_top_selector = 3;

	}
	while (matrix[g_token_top_selector ][0] != EMPTY_SPACE) {
		g_token_top_selector += 1;

		if (g_token_top_selector > (COL_COUNT - 1)) {
			g_token_top_selector = EMPTY_SPACE;
		}
		else if (g_token_top_selector < 0){
			g_token_top_selector = COL_COUNT - 1 ;
		}

		//			if (matrix[g_token_top_selector][0] != EMPTY_SPACE) {
		//				gp4_move_right();
		//			}


	}
	pos_token.end_position.c = g_token_top_selector;
	return pos_token;
}



//void gp4_test_phase(void) {
//	gp4_display();
//	gp4_move_left();
//	printf("\n");
//	gp4_display();
//	gp4_move_left();
//	printf("\n");
//	gp4_display();
//	gp4_move_left();
//	printf("\n");
//	gp4_display();
//	gp4_play_token();
//	printf("\n");
//	gp4_display();
//	gp4_next_player();
//	printf("\n");
//	gp4_display();
//	gp4_move_left();
//	gp4_move_left();
//	printf("\n");
//	gp4_display();
//	gp4_play_token();
//	gp4_display();
//	printf("\n");
//
//}
