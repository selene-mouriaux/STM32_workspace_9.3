/*
 * game_p4.h
 *
 *  Created on: 31 mars 2020
 *      Author: marc
 */

#ifndef GAME_P4_H_
#define GAME_P4_H_

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

/*paramètres de jeu puissance 4 */
#define NB_OF_COLUMN 7
#define NB_OF_LINE 6
#define EMPTY_SPACE 0
#define START_POSITION 4

typedef struct {
	int RValue;
	int GValue;
	int BValue;
} color;

#pragma GCC diagnostic ignored "-Wunused-variable"
static color white = { 255, 255, 255 };
static color green = { 0, 255, 0 };
static color blue = { 0, 0, 255 };
static color red = { 255, 0, 0 };
static color purple = { 255, 0, 255 };
static color yellow = { 255, 255, 0 };
static color black = { 0, 0, 0 };
#pragma GCC diagnostic warning "-Wunused-variable"

typedef enum {
	live, //!< Need to continue game
	stop_winner, //!< game is finish and winner
	stop_equal //<! game is finish and equal
} status_t;

typedef enum {
	horiz, vert, right_diag, left_diag
} victory_t;

typedef enum {
	NO_PLAYER, PLAYER_1, PLAYER_2
} player_t;

typedef struct {
	int8_t l;
	int8_t c;
} point_t;

typedef struct {
	status_t status; //!< status of winner
	victory_t win_type; //<!
	player_t win_player; //<! the winner player
	point_t win_position[4]; //!< position of 4 winner token
} winner_t;

typedef struct {
	bool is_ok;
	point_t beg_position;
	point_t end_position;
} pos_token_t;

typedef struct {
	pos_token_t locate;
	color color;
} move_token;

/*COMMENTER UTILISATION DES FONCTIONS + VALEURS RETOUR*/
void gp4_init(void);
void gp4_show_board(void);
pos_token_t gp4_set_player(void);
pos_token_t gp4_move_left(void);
pos_token_t gp4_move_right(void);

void gp4_test_move_all(void);
void gp4_test_play_token(void);
void gp4_test_check_winner(void);

/*Valide le coup choisi par joueur
 * retourne struct de l'axe X et Y de la position finale du jeton joué*/
pos_token_t gp4_play_token(void);
winner_t gp4_check_winner(void);

#endif /* GAME_P4_H_ */
