/*
 * thread.c
 *
 *  Created on: Apr 9, 2020
 *      Author: mickaell
 */

#include<stdio.h>
#include <stdint.h>
#include <pthread.h>
#include<unistd.h>
#include"leds_control.h"
#include "FIFO.h"
#include <semaphore.h>
#include "thread.h"
#include "game_p4.h"


char recep_tab[5];
Timer timer_table[TIMER_MAX];

//Color matrix[COL_COUNT][LINE_COUNT];
Color matrix_led[COL_COUNT][LINE_COUNT + 1 ];
Color actual_display[COL_COUNT][LINE_COUNT + 1 ];
int8_t active_player;
pthread_mutex_t mutex_timer ;
//le rgb des couleurs
#pragma GCC diagnostic ignored "-Wunused-variable"
const Color red = { 255, 0, 0 };
const Color green = { 0, 255, 0 };
const Color blue = { 0, 0, 255 };
const Color white = { 255, 255, 255 };
const Color purple = { 255, 0, 255 };
const Color yellow = { 255, 255, 0 };
const Color black = { 0, 0, 0 };
#pragma GCC diagnostic warning "-Wunused-variable"

void init_matrix(void) {
	for (int row = 0; row < 7; row++) {
		for (int col = 0; col < 7; col++) {
			matrix_led[row][col].RValue = black.RValue;
			matrix_led[row][col].GValue = black.GValue;
			matrix_led[row][col].BValue = black.BValue;
			actual_display[row][col].RValue = black.RValue;
			actual_display[row][col].GValue = black.GValue;
			actual_display[row][col].BValue = black.BValue;
		}
	}
}
void set_all_black(void) {
	for (int row = 0; row < 7; row++) {
		for (int col = 0; col < 7; col++) {
			setLedColor((row + 1), (col + 1), 0, 0, 0);
		}
	}
}
void *thread_read(void *arg) {

	while (1) {
		struct Element command;
		if (readbutton(recep_tab, 5) == LCRC_OK) {
			printf("%d %d %d %d \n", recep_tab[0], recep_tab[1], recep_tab[2],
					recep_tab[3]);
			command.msg=msg_player;
			if (recep_tab[0] == 'p') {
				if (recep_tab[1] == '1') {
					command.data.player.player = PLAYER_1;
				} else if (recep_tab[1] == '2') {
					command.data.player.player  = PLAYER_2;
				}
				if (recep_tab[3] == 100) {

					if (recep_tab[2] == 'd') {
						command.data.player.direction  = DOWN;
					}
					if (recep_tab[2] == 'u') {
						command.data.player.direction = UP;
					}
					if (recep_tab[2] == 'r') {
						command.data.player.direction = RIGHT;
					}
					if (recep_tab[2] == 'l') {
						command.data.player.direction = LEFT;
					}
					send_message(QUEUE_READ, &command, SIZEOFMESSAGE);
				}

			}
		}
	}

	return NULL;

}

void check_win(const winner_t* winner_status, struct Element* send_value) {
	if (winner_status->win_type == horiz) {
		printf("player win horiz\n");
		active_player = NO_PLAYER;
	} else if (winner_status->win_type == vert) {
		printf("player win vert\n");
		active_player = NO_PLAYER;
	} else if (winner_status->win_type == right_diag) {
		printf("player win right diag\n");
		active_player = NO_PLAYER;
	} else if (winner_status->win_type == left_diag) {
		printf("player win left diag\n");
		active_player = NO_PLAYER;
	}

	if (active_player == PLAYER_1) {
		send_value->data.token.color = PLAYER_COLOR_1;
	} else if (active_player == PLAYER_2) {
		send_value->data.token.color = PLAYER_COLOR_2;
	}
}

void *thread_app(void *arg) {
	//	struct Element nb_value;
	//	nb_value.data.value[1]=0;
	active_player = 0;
	winner_t winner_status;
	struct Element receive_value;
	struct Element send_value;
	pos_token_played_t played_token;
	while (1) {
		//		iddle 5
		//		round 15
		if (receive_message(QUEUE_READ, &receive_value, SIZEOFMESSAGE)) {
			//			printf("app %d %d \n", receive_value.data.value[0],
			//					receive_value.data.value[1]);
			if (receive_value.msg==msg_timer){
				if (receive_value.data.timer_id == ROUND_TIMER || receive_value.data.timer_id == IDLE_TIMER) {
					played_token = gp4_play_token();
					compute_message(&send_value, &played_token);
					send_message(QUEUE_SEND, &send_value, SIZEOFMESSAGE);
					played_token = gp4_next_player();
					winner_status=gp4_check_winner();
					check_win(&winner_status, &send_value);
					//decompte(&receive_value, &nb_value);
				}

			}
			else if(receive_value.msg==msg_player){
				stop_timer(IDLE_TIMER);
				if (receive_value.data.player.player == active_player) {
					if (receive_value.data.player.direction == DOWN) {
						played_token = gp4_play_token();
						compute_message(&send_value, &played_token);
						send_message(QUEUE_SEND, &send_value, SIZEOFMESSAGE);
						played_token=gp4_next_player();
						winner_status=gp4_check_winner();
						check_win(&winner_status, &send_value);
//						if(winner_status.win_type == horiz){
//							printf("player win horiz\n");
//							active_player = NO_PLAYER;
//
//						}
//						else if(winner_status.win_type == vert){
//							printf("player win vert\n");
//							active_player = NO_PLAYER;
//
//						}
//						else if (winner_status.win_type == right_diag){
//							printf("player win right diag\n");
//							active_player =NO_PLAYER;
//						}
//						else if (winner_status.win_type == left_diag){
//							printf("player win left diag\n");
//							active_player = NO_PLAYER;
//						}
//
//						if (active_player == PLAYER_1) {
//							send_value.data.token.color = PLAYER_COLOR_1;
//						}
//						else if (active_player == PLAYER_2) {
//							send_value.data.token.color = PLAYER_COLOR_2;
//						}


					}
					if (receive_value.data.player.direction == RIGHT) {

						played_token = gp4_move_right();

					}
					if (receive_value.data.player.direction == LEFT) {

						played_token = gp4_move_left();

					}
					start_timer(IDLE_TIMER,5,thd_app);
				}
				if (active_player == NO_PLAYER ){
					set_all_black();
					init_matrix();
					gp4_init();
					gp4_display();
					active_player = PLAYER_1;
					played_token.beg_position.c = 0;
					played_token.beg_position.l = 0;
					played_token.end_position.l = 0;
					played_token.end_position.c = 3;
					send_value.data.token.color = PLAYER_COLOR_1;
					start_timer(ROUND_TIMER,15,thd_app);
					start_timer(IDLE_TIMER,5,thd_app);

				}


			}

			gp4_display();
			compute_message(&send_value, &played_token);
			send_message(QUEUE_SEND, &send_value, SIZEOFMESSAGE);
		}

	}

}

void *thread_display(void *arg) {
	struct Element value_compt;
	while (1) {

		if (receive_message(QUEUE_SEND, &value_compt, SIZEOFMESSAGE)) {
			printf(" display b %d%d  e %d%d \n",
					value_compt.data.token.position.beg_position.c,
					value_compt.data.token.position.beg_position.l,
					value_compt.data.token.position.end_position.c,
					value_compt.data.token.position.end_position.l);
			//			set_number(value_compt.data.value[1]);
			setledmatrix(&value_compt);


			for (int row = 0; row < 7; row++){
				for (int col = 0; col < 7; col++){
					if ((matrix_led[row][col].RValue == actual_display[row][col].RValue)
							&& (matrix_led[row][col].GValue == actual_display[row][col].GValue)
							&& (matrix_led[row][col].BValue == actual_display[row][col].BValue)) {
					} else {
						setLedColor((row + 1 ), (col + 1 ),
								matrix_led[row][col].RValue,
								matrix_led[row][col].GValue,
								matrix_led[row][col].BValue);
						actual_display[row ][col] = matrix_led[row ][col];
					}
				}
			}

		}
	}
}
void stop_timer(int8_t timer_id){
	pthread_mutex_lock (&mutex_timer);
	timer_table[timer_id].status = STOP;
	pthread_mutex_unlock (&mutex_timer);

}

void start_timer(int8_t timer_id,int8_t countdown,Owner owner){
	pthread_mutex_lock (&mutex_timer);
	timer_table[timer_id].countdown = countdown;
	timer_table[timer_id].owner = owner;
	timer_table[timer_id].status = START;
	pthread_mutex_unlock (&mutex_timer);
}


void *thread_timer(void *arg){
	struct Element msg_blink;

	while(1){
		pthread_mutex_lock (&mutex_timer);
		for(int8_t i=0;i<TIMER_MAX;i ++){
			if (timer_table[i].status == START){
				if(timer_table[i].countdown == 0 ){
					msg_blink.msg =msg_timer;
					msg_blink.data.timer_id=i;
					if(timer_table[i].owner == thd_app){
						send_message(QUEUE_READ,&msg_blink,SIZEOFMESSAGE);
					}
					else if(timer_table[i].owner == thd_display){
						send_message(QUEUE_SEND,&msg_blink,SIZEOFMESSAGE);
					}
					timer_table[i].status=STOP;
				}
				else{
					timer_table[i].countdown --;
				}
			}
		}
		pthread_mutex_unlock (&mutex_timer);
		usleep(1000000);
	}


}

void compute_message(struct Element* message, pos_token_played_t* data) {
	message->data.token.position.beg_position.l = data->beg_position.l;
	message->data.token.position.beg_position.c = data->beg_position.c;
	message->data.token.position.end_position.l = data->end_position.l;
	message->data.token.position.end_position.c = data->end_position.c;
}
//// pour le puissance 4

void setledmatrix(struct Element *message) {
	int beg_row = message->data.token.position.beg_position.l;
	int beg_col = message->data.token.position.beg_position.c;
	int end_row = message->data.token.position.end_position.l;
	int end_col = message->data.token.position.end_position.c;
	if (beg_row == 10 && beg_col == 10) {
	} else {
		matrix_led[beg_row ][beg_col] = BACKGROUND;
	}
	matrix_led[end_row ][end_col] = message->data.token.color;
}

