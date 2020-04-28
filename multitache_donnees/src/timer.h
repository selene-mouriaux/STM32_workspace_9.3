/*
 * timer.h
 *
 *  Created on: 23 avr. 2020
 *      Author: marc
 */

#ifndef TIMER_H_
#define TIMER_H_

#include<pthread.h>
#include<unistd.h>
#include<stdlib.h>

#define TIMER_NB 5

typedef enum {
	STOP, ACTIVE, TIMEOUT
} timer_status;

typedef enum {
	NO_OWNER, APP, DISPLAY
} timer_owner;

typedef struct {
	int8_t number;
	timer_status status;
} timer_msg;

typedef struct {
	int8_t number;
	timer_status status;
	timer_owner owner;
	int countdown;
} timer_struct;

typedef struct {
	timer_struct timer[TIMER_NB];
	pthread_mutex_t mutex;
} timer;

typedef enum {
	QUEUE_READ, QUEUE_SEND
} QUEUE_ID;

int8_t stop_timer(int8_t timer); // RETOURNE -1 SI TIMER INEXISTANT, 0 SI OK
int8_t start_timer(timer_owner owner, int countdown); // RETOURNE -1 SI ERREUR, NUMÉRO DU TIMER SI OK

#endif /* TIMER_H_ */
