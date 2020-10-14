/*
 * thread.h
 *
 *  Created on: Apr 9, 2020
 *      Author: mickaell
 */

#ifndef THREAD_H_
#define THREAD_H_
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define PLAYER_COLOR_1 red
#define PLAYER_COLOR_2 green
#define BACKGROUND black
#define TAB_SIZE 6
#define TIMER_MAX 4
#include"leds_control.h"
#include "FIFO.h"
#include<stdbool.h>

void *thread_display(void *arg);
void *thread_read(void *arg);
void *thread_app(void *arg);
void *thread_timer(void *arg);
void init_matrix(void);
void set_all_black(void);
void compute_message(struct Element* message, pos_token_played_t* data);
void setledmatrix(struct Element *message);


typedef enum{
	START = 3,
	STOP = 4 ,
}Status;

typedef enum{
	thd_app,
	thd_display,
}Owner;

typedef struct {
	int8_t ID;
	Status status;
	int8_t countdown;
	Owner owner;
}Timer;
//
//typedef enum{
//	ON,
//	OFF,
//	BLINK
//}token_mod_t;

void start_timer(int8_t timer_id,int8_t countdown,Owner owner);
void stop_timer(int8_t timer_id);
#endif /* THREAD_H_ */
