/*
 * game.c
 *
 *  Created on: 9 avr. 2020
 *      Author: marc
 */

#include "game.h"

static Matrix matrix;
static Matrix actual_display;

queue *queue_init(void) {
	queue *list = malloc(sizeof(*list));
	list->first = NULL;
	list->last = NULL;
	return list;
}

void init_matrix(void) {
	for (int row = 0; row < TAB_SIZE; row++) {
		for (int col = 0; col < TAB_SIZE; col++) {
			matrix.board[row][col].RValue = black.RValue;
			matrix.board[row][col].GValue = black.GValue;
			matrix.board[row][col].BValue = black.BValue;
			actual_display.board[row][col].RValue = black.RValue;
			actual_display.board[row][col].GValue = black.GValue;
			actual_display.board[row][col].BValue = black.BValue;
		}
	}
	matrix.init = INIT_OK;
}

void set_number(int nbr) {
	color nbr_color = COLOR_P1;
	color bckgrnd_color = BACKGROUND;
	for (int row = 0; row < TAB_SIZE; row++) {
		for (int col = 0; col < TAB_SIZE; col++) {
			if (nbr == 1) { /*Ensemble de conditions pour afficher le chiffre 1*/
				if ((col == 4) || (row == 3 && col == 1)
						|| (row == 2 && col == 2) || (row == 1 && col == 3)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 2) { /*Ensemble de conditions pour afficher le chiffre 2*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 1 && col == 5) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 5 && col == 1) || (row == 6 && col == 2)
						|| (row == 5 && col == 5) || (row == 6 && col == 3)
						|| (row == 6 && col == 4)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 3) { /*Ensemble de conditions pour afficher le chiffre 3*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 1 && col == 5) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 5)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 5 && col == 1)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 4) { /*Ensemble de conditions pour afficher le chiffre 4*/
				if ((row == 0 && col == 4) || (row == 1 && col == 3)
						|| (row == 1 && col == 4) || (row == 2 && col == 2)
						|| (row == 2 && col == 4) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 4) || (row == 5 && col == 4)
						|| (row == 6 && col == 4)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 5) { /*Ensemble de conditions pour afficher le chiffre 5*/
				if ((row == 0 && col == 1) || (row == 0 && col == 2)
						|| (row == 0 && col == 3) || (row == 0 && col == 4)
						|| (row == 0 && col == 5) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 5)
						|| (row == 5 && col == 5) || (row == 6 && col == 1)
						|| (row == 6 && col == 2) || (row == 6 && col == 3)
						|| (row == 6 && col == 4)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 6) { /*Ensemble de conditions pour afficher le chiffre 6*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 3 && col == 1)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 7) { /*Ensemble de conditions pour afficher le chiffre 7*/
				if ((row == 0 && col == 1) || (row == 0 && col == 2)
						|| (row == 0 && col == 3) || (row == 0 && col == 4)
						|| (row == 0 && col == 5) || (row == 1 && col == 5)
						|| (row == 2 && col == 5) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 5) || (row == 5 && col == 5)
						|| (row == 6 && col == 5)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 8) { /*Ensemble de conditions pour afficher le chiffre 8*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 9) { /*Ensemble de conditions pour afficher le chiffre 9*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 2) || (row == 3 && col == 3)
						|| (row == 3 && col == 4) || (row == 3 && col == 5)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
			if (nbr == 0) { /*Ensemble de conditions pour afficher le chiffre 0*/
				if ((row == 0 && col == 2) || (row == 0 && col == 3)
						|| (row == 0 && col == 4) || (row == 1 && col == 1)
						|| (row == 2 && col == 1) || (row == 2 && col == 5)
						|| (row == 3 && col == 5) || (row == 4 && col == 1)
						|| (row == 4 && col == 5) || (row == 5 && col == 1)
						|| (row == 5 && col == 5) || (row == 6 && col == 2)
						|| (row == 6 && col == 3) || (row == 6 && col == 4)
						|| (row == 1 && col == 5) || (row == 3 && col == 1)) {
					matrix.board[row][col] = nbr_color;
				} else
					matrix.board[row][col] = bckgrnd_color;
			}
		}
	}
}

void push(queue *queue, void *message, size_t msg_size) {
	user_input *new_input = malloc(sizeof(*new_input));
	new_input->data = malloc(msg_size);
	new_input->size_of_data = msg_size;
	if (new_input == NULL) {
		printf("erreur alloc mémoire push\n");
	}
	memcpy(new_input->data, message, msg_size);
	new_input->next = NULL;
	pthread_mutex_lock(&queue->mutex);
	if (queue->first != NULL) {
		user_input *first_input = queue->last;
		first_input->next = new_input;
		queue->last = new_input;
	} else {
		queue->first = new_input;
		queue->last = new_input;
	}
	pthread_mutex_unlock(&queue->mutex);
}

int pop_element(queue *queue, void *message, size_t msg_size) {
	pthread_mutex_lock(&queue->mutex);
	if (queue->first == NULL) { // retourne -1 si liste vide
		pthread_mutex_unlock(&queue->mutex);
		printf("liste vide (pop)\n");
		return -1;
	}
	user_input *first_input = queue->first;
	memcpy(message, first_input->data, msg_size);
	queue->first = first_input->next;
	pthread_mutex_unlock(&queue->mutex);
	free(first_input->data);
	free(first_input);
	return 0;
}

void send_message(QUEUE_ID queue_id, void* message, int message_length) {
	queue * queue_to_use = queue_id == QUEUE_READ ? queue_push_app :
							queue_id == QUEUE_SEND ? queue_app_display :
							NULL;
	if (queue_to_use != NULL) {
		push(queue_to_use, message, message_length);
		sem_post(&queue_to_use->semaphore);
	}
}

int receive_message(QUEUE_ID queue_id, void* message, int message_length) {
	int return_value = -1;
	if (queue_id == QUEUE_READ) {
		sem_wait(&queue_push_app->semaphore);
		return_value = pop_element(queue_push_app, message, message_length);
	}
	if (queue_id == QUEUE_SEND) {
		sem_wait(&queue_app_display->semaphore);
		return_value = pop_element(queue_app_display, message, message_length);
	}
	return return_value;
}

void compute_movement_message(data_msg* message, pos_token_t* data) {
	message->type = INPUT;
	message->token.locate.beg_position.l = data->beg_position.l;
	message->token.locate.beg_position.c = data->beg_position.c;
	message->token.locate.end_position.l = data->end_position.l;
	message->token.locate.end_position.c = data->end_position.c;
//	printf("COMPUTE MESSAGE : beg: %d%d, end: %d%d\n",
//			message->token.locate.beg_position.l,
//			message->token.locate.beg_position.c,
//			message->token.locate.end_position.l,
//			message->token.locate.end_position.c);
}

void matrix_to_simu(void) {
	for (int row = 0; row < TAB_SIZE; row++) {
		for (int col = 0; col < TAB_SIZE; col++) {
			if ((matrix.board[row][col].RValue
					== actual_display.board[row][col].RValue)
					&& (matrix.board[row][col].GValue
							== actual_display.board[row][col].GValue)
					&& (matrix.board[row][col].BValue
							== actual_display.board[row][col].BValue)
					&& actual_display.init == INIT_OK) {
			} else {
				setLedColor(row + 1, col + 1, matrix.board[row][col].RValue,
						matrix.board[row][col].GValue,
						matrix.board[row][col].BValue);
				actual_display.board[row][col] = matrix.board[row][col];
			}
		}
	}
	actual_display.init = INIT_OK;
}

void set_matrix(data_msg *message) {
	int8_t beg_row = message->token.locate.beg_position.l;
	int8_t beg_col = message->token.locate.beg_position.c;
	int8_t end_row = message->token.locate.end_position.l;
	int8_t end_col = message->token.locate.end_position.c;
//	printf("SET_MATRIX : begL/C: %d%d, endL/C: %d%d\n", beg_row, beg_col,
//			end_row, end_col);
	if (beg_row == 0 && beg_col == 0) {
	} else {
		matrix.board[beg_row - 1][beg_col - 1] = BACKGROUND;
	}
	matrix.board[end_row - 1][end_col - 1] = message->token.color;
	matrix_to_simu();
}

void animated_horiz_movement(data_msg *message) {
	int8_t beg_row = message->token.locate.beg_position.l;
	int8_t end_col = message->token.locate.end_position.c;
	int8_t end_row = message->token.locate.end_position.l;
	for (int8_t line_pos = beg_row; line_pos < end_row; line_pos++) {
		matrix.board[line_pos - 1][end_col - 1] = BACKGROUND;
		matrix.board[line_pos][end_col - 1] = message->token.color;
		matrix_to_simu();
		usleep(200000);
	}
}

void compute_victory_message(data_msg *message, winner_t *data) {
	message->victory.first_token.c = data->win_position[0].c;
	message->victory.first_token.l = data->win_position[0].l;
	message->victory.last_token.c = data->win_position[3].c;
	message->victory.last_token.l = data->win_position[3].l;
	message->victory.type = data->win_type;
	message->type = WIN;
}

color horiz_vict_led_off(data_msg *message) {
	int8_t line = message->victory.first_token.l;
	int8_t beg_col = message->victory.first_token.c;
	int8_t end_col = message->victory.last_token.c;
	color color_off = matrix.board[line - 1][beg_col - 1];
	for (int8_t col_pos = beg_col; col_pos < end_col; col_pos++) {
		matrix.board[line][col_pos - 1] = BACKGROUND;
	}
	matrix_to_simu();
	return color_off;
}

void horiz_vict_led_on(color *color, data_msg *message) {
	int8_t line = message->victory.first_token.l;
	int8_t beg_col = message->victory.first_token.c;
	int8_t end_col = message->victory.last_token.c;
	for (int8_t col_pos = beg_col; col_pos < end_col; col_pos++) {
		matrix.board[line][col_pos - 1] = *color;
	}
	matrix_to_simu();
}

void print_send_msg(data_msg *message) {
	printf(
			"THREAD APP mesage envoyé : pos_beg : %d%d pos_end : %d%d couleur : %d %d %d\n",
			message->token.locate.beg_position.l,
			message->token.locate.beg_position.c,
			message->token.locate.end_position.l,
			message->token.locate.end_position.c,
			message->token.color.RValue, message->token.color.GValue,
			message->token.color.BValue);
}

/*-----------------------------------------------------------------------------------
 *
 *
 *                                     THREAD
 *
 *
 * -----------------------------------------------------------------------------------
 */

/*THREAD POUR AFFICHER LA MATRICE*/
void *show_board(void *arg) {
	data_msg command;
	int8_t blink_timer = STOP_TIMER;
	int8_t blink_vict_timer = STOP_TIMER;
	color blink_color;
	while (1) {
		if (matrix.init != INIT_OK) {
			init_matrix();
		}
		command.type = NO_COMMAND;
		if (receive_message(QUEUE_SEND, &command, sizeof(command)) == 0) {
			printf(
					"THREAD AFFICHAGE réception trame : pos_beg: %d%d, pos_end: %d%d, couleur: %d %d %d\n",
					command.token.locate.beg_position.l,
					command.token.locate.beg_position.c,
					command.token.locate.end_position.l,
					command.token.locate.end_position.c,
					command.token.color.RValue, command.token.color.GValue,
					command.token.color.BValue);
			if (command.type == INPUT) {
				if (command.token.locate.beg_position.c
						!= command.token.locate.end_position.c) {
					set_matrix(&command);
				} else {
					animated_horiz_movement(&command);
				}
			}
			if (command.type == WIN || command.type == TIMER) {
				if (blink_vict_timer == STOP_TIMER) {
					blink_vict_timer = start_timer(DISPLAY,
					BLINK_VICTORY_TIMER);
				}
				if (command.victory.type == horiz) {
					blink_color = horiz_vict_led_off(&command);
					if (blink_timer == STOP_TIMER) {
						blink_timer = start_timer(DISPLAY, BLINK_TIMER);
					}
				}
				if (command.type == TIMER
						&& command.timer.number == blink_timer) {
					horiz_vict_led_on(&blink_color, &command);
					if (command.timer.status == TIMEOUT) {
						blink_timer = STOP_TIMER;
					}
				}
			}
		}
	}
	return NULL;
}

/*THREAD APP*/
void *application(void *arg) {
	int8_t pad_player_1 = 0;
	int8_t pad_player_2 = 0;
	int8_t player_round = NO_PLAYER;
	winner_t victory_infos;
	int8_t idle_timer = STOP_TIMER;
	int8_t round_timer = STOP_TIMER;
	while (1) {
		data_msg received_message;
		pos_token_t played_token;
		data_msg to_display;
		if (victory_infos.status == live) {
			if (round_timer == STOP_TIMER) {
				round_timer = start_timer(APP, ROUND_TIMER);
			}
			if (idle_timer == STOP_TIMER) {
				idle_timer = start_timer(APP, IDLE_TIMER);
			}
		}
		if (receive_message(QUEUE_READ, &received_message,
				sizeof(received_message)) == 0) {
			printf("application - réception valeur : pad : %d command : %d\n",
					received_message.pad, received_message.command);

			if (received_message.timer.status == TIMEOUT
					&& received_message.type == TIMER) {
				if (received_message.timer.number == idle_timer) {
					idle_timer = STOP_TIMER;
				}
				if (received_message.timer.number == round_timer) {
					round_timer = STOP_TIMER;
				}
				received_message.pad = player_round;
				received_message.command = DOWN;
			}
			if ((received_message.pad == player_round)
					&& (victory_infos.status == live)
					&& (received_message.type == INPUT
							|| received_message.type == TIMER)) {
				stop_timer(idle_timer);
				idle_timer = STOP_TIMER;
				if (received_message.command == RIGHT) {
					played_token = gp4_move_right();
					compute_movement_message(&to_display, &played_token);
				}
				if (received_message.command == LEFT) {
					played_token = gp4_move_left();
					compute_movement_message(&to_display, &played_token);
				}
				if (received_message.command == DOWN) {
					stop_timer(round_timer);
					round_timer = STOP_TIMER;
					played_token = gp4_play_token();
					compute_movement_message(&to_display, &played_token);
					print_send_msg(&to_display);
					send_message(QUEUE_SEND, &to_display, sizeof(to_display));
					victory_infos = gp4_check_winner();
					if (victory_infos.status == live) {
						played_token = gp4_set_player();
						if (player_round == pad_player_1) {
							player_round = pad_player_2;
							to_display.token.color = COLOR_P2;
						} else {
							player_round = pad_player_1;
							to_display.token.color = COLOR_P1;
						}
						compute_movement_message(&to_display, &played_token);
					} else if (victory_infos.status == stop_winner) {
						printf("APP victory_status = stop_winner\n");
						compute_victory_message(&to_display, &victory_infos);
						print_send_msg(&to_display);
						send_message(QUEUE_SEND, &to_display,
								sizeof(to_display));
						gp4_show_board();
					}
				}
				if (victory_infos.status == live) {
					print_send_msg(&to_display);
					send_message(QUEUE_SEND, &to_display, sizeof(to_display));
					gp4_show_board();
				}
			}
			if (player_round == NO_PLAYER) { //INITIALISATION D'UNE PARTIE : JETON JOUEUR 1 AU CENTRE
				printf("init game\n");
				if (received_message.pad == PAD_1) {
					pad_player_1 = PAD_1;
					pad_player_2 = PAD_2;
				} else {
					pad_player_1 = PAD_2;
					pad_player_2 = PAD_1;
				}
				player_round = pad_player_1;
				victory_infos.status = live;
				played_token.beg_position.c = 0;
				played_token.beg_position.l = 0;
				played_token.end_position.l = 1;
				played_token.end_position.c = START_POSITION;
				to_display.token.color = COLOR_P1;
				gp4_init();
				compute_movement_message(&to_display, &played_token);
				print_send_msg(&to_display);
				send_message(QUEUE_SEND, &to_display, sizeof(to_display));
				gp4_show_board();
			}
			//TODO passer active_player à NO_PLAYER en fin de partie
		}
	}
	return NULL;
}

/*THREAD POUR GÉRER LES COMMANDES ENTRANTES*/
void *user_button(void *arg) {
	char input[READ_BUTTON_BUFER_SIZE] = { 0 };
	data_msg to_app;
	while (1) {
		if (readbutton(input, READ_BUTTON_BUFER_SIZE) == LCRC_OK) {
			if (input[1] == PAD_1) {
				to_app.pad = PAD_1;
			} else if (input[1] == PAD_2) {
				to_app.pad = PAD_2;
			}
			if (input[3] == PRESSED) {
				printf("\nnouvelle entrée\n");
				for (int i = 0; i < 4; i++) {
					printf("%d ", input[i]);
				}
				printf("\n");
				if (input[2] == UP) {
					to_app.command = UP;
				}
				if (input[2] == DOWN) {
					to_app.command = DOWN;
				}
				if (input[2] == RIGHT) {
					to_app.command = RIGHT;
				}
				if (input[2] == LEFT) {
					to_app.command = LEFT;
				}
				to_app.type = INPUT;
				send_message(QUEUE_READ, &to_app, sizeof(to_app));
			}
		}
	}
	return NULL;
}
