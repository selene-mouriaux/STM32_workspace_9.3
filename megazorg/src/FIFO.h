#ifndef FIFO_H_
#define FIFO_H_

#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include <pthread.h>
#include<unistd.h>
#include "game_p4.h"

#define SIZEOFMESSAGE 10

struct List liste;

typedef enum {
	msg_player,
	msg_move_token,
	msg_timer,
}msg_type;

typedef enum{
	IDLE_TIMER,
	ROUND_TIMER,

}timer;

struct Element {
	msg_type msg;
	union {
		timer timer_id;
		player_data_msg player;
		token_t token;
		char value[SIZEOFMESSAGE];
	} data;

	struct Element *next_p;
};

struct List {
	pthread_mutex_t mutex;
	struct Element *head;
	struct Element *tail;
};
typedef enum QUEUE_ID{
	QUEUE_READ ,
	QUEUE_SEND,
}QUEUE_ID;

void *thread_send(void *arg);
void *thread_pop(void *arg);
void push_element(struct List* liste, struct Element *value_to_push);
int pop_element(struct List* liste, struct Element *value_to_return);
void init_liste(struct List *liste);
void send_message(QUEUE_ID liste, struct Element *value_to_push,int message_lenght);
int receive_message(QUEUE_ID liste,struct Element *value_to_return , int message_lenght);
#endif /* FIFO_H_ */
