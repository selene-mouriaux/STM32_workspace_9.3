/*
 * game_p4.h
 *
 *  Created on: Mar 31, 2020
 *      Author: mickaell
 */

#ifndef GAME_P4_H_// ifnotdefine , le preprocesseur verifie si il n'y pas de doublons par rapport au define qui sont ici
#define GAME_P4_H_
#include<stdbool.h>
#define COL_COUNT 7//definit le nombre de colones
#define LINE_COUNT 6 // definit le nombre de lignes
//#define PLAYER_1 1 // joueur 1
//#define PLAYER_2 2// joueur 2
#define EMPTY_SPACE 0 // cases vide de la matrice
#include<stdint.h>


//matrice vide
void clear_matrix(void);
//initialise la matrice
void gp4_init(void);
//initialise la top line
void top_line_display(void);
//affiche la matrice
void diplay_matrix(void) ;
//affiche le jeu
void gp4_display(void);
//change de joueur

//deplace le token versla droite

//phase de test pour les mouvement et la validation et le changement de joueur
void gp4_test_phase(void);

typedef struct{
	int RValue;
	int GValue;
	int BValue;
}Color;

typedef enum{
	ON,
	OFF,
	BLINK
}token_mod_t;

typedef enum {
	live, //!< Need to continue game
	stop_winner, //!< game is finish and winner
	stop_equal //<! game is finish and equal
} status_t;

typedef enum {
	vert,
	horiz,
	right_diag,
	left_diag,
} victory_t;

typedef enum {
	NO_PLAYER,
	PLAYER_1,
	PLAYER_2,
} player_t;

typedef enum {
	UP,
	DOWN,
	RIGHT,
	LEFT,
}direction_t;

typedef struct{
	player_t player;
	direction_t direction;
}player_data_msg;

typedef struct {
	int8_t l;
	int8_t c;
} point_t;

typedef struct {
	status_t status; //!< status of winner
	victory_t win_type; //<!
	player_t win_player; //<! the winner player
	point_t win_position[4]; //!< position of 4 winner tiken
} winner_t;

typedef struct{
	point_t beg_position;
	point_t end_position;
	bool is_ok;
}pos_token_played_t;

typedef struct{
	pos_token_played_t position;
	Color color;
	token_mod_t mode;
}token_t;

pos_token_played_t  gp4_move_right(void);
//deplace le token vers la gauche
pos_token_played_t  gp4_move_left(void) ;
//joue le token
pos_token_played_t  gp4_play_token(void);
pos_token_played_t  gp4_next_player(void);
winner_t check_winner_vertically(void);
winner_t gp4_check_winner(void);
winner_t gp4_check_diagonals_right_and_left(void);
winner_t gp4_check_horizontally(void);
#endif /* GAME_P4_H_ */
