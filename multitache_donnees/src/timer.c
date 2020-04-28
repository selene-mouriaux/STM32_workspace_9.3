/*
 * timer.c
 *
 *  Created on: 23 avr. 2020
 *      Author: marc
 */
#include"timer.h"
#include"game.h"

static timer timer_list;

void init_timer(void) {
	pthread_mutex_lock(&timer_list.mutex);
	for (int8_t i = 0; i < TIMER_NB; i++) {
		timer_list.timer[i].countdown = 0;
		timer_list.timer[i].owner = NO_OWNER;
		timer_list.timer[i].status = STOP;
		timer_list.timer[i].number = -1;
	}
	pthread_mutex_unlock(&timer_list.mutex);
}

int8_t start_timer(timer_owner owner, int countdown) {
	int8_t activated_timer = 0;
	int8_t selected_timer = 0;
	pthread_mutex_lock(&timer_list.mutex);
	while (activated_timer == 0 && selected_timer != -1) {
		if (timer_list.timer[selected_timer].status == STOP) {
			timer_list.timer[selected_timer].countdown = countdown;
			timer_list.timer[selected_timer].owner = owner;
			timer_list.timer[selected_timer].status = ACTIVE;
			timer_list.timer[selected_timer].number = selected_timer;
			activated_timer = 1;
		} else {
			selected_timer++;
			if (selected_timer == TIMER_NB) {
				selected_timer = -1; // POUR RETOUR = -1 SI ERREUR
			}
		}
	}
	pthread_mutex_unlock(&timer_list.mutex);
	return selected_timer;
}

int8_t stop_timer(int8_t timer) {
	if (timer > TIMER_NB || timer < 0) {
		printf("STOP TIMER - VALEUR CHOISIE INEXISTANTE\n");
		return -1; //RETOUR ERREUR VALEUR PARAMETRE
	} else {
		pthread_mutex_lock(&timer_list.mutex);
		timer_list.timer[timer].countdown = 0;
		timer_list.timer[timer].number = -1;
		timer_list.timer[timer].owner = NO_OWNER;
		timer_list.timer[timer].status = STOP;
		pthread_mutex_unlock(&timer_list.mutex);
		return 0; //RETOUR OK
	}

}

/*****************************************************************************
 *
 *
 *                             		  THREAD
 *
 *
 ****************************************************************************/

void *timers(void *arg) {
	init_timer();
	data_msg message;
	pthread_mutex_init(&timer_list.mutex, NULL);
	while (1) {
		usleep(100000); // == 100 millisecondes
		pthread_mutex_lock(&timer_list.mutex);
		for (int8_t i = 0; i < TIMER_NB; i++) {
			if (timer_list.timer[i].status == ACTIVE) { // décrémente tous les timer actifs
				timer_list.timer[i].countdown--;
				if (timer_list.timer[i].countdown == 0) {
					QUEUE_ID queue =
							timer_list.timer[i].owner == APP ? QUEUE_READ :
							timer_list.timer[i].owner == DISPLAY ?
									QUEUE_SEND : 2; // identification du proprio du timer 2 == err
					message.type = TIMER;
					message.timer.status = TIMEOUT;
					message.timer.number = timer_list.timer[i].number;
					printf("TIMER TIMEOUT : %d, %d\n", message.timer.status,
							message.timer.number);
					send_message(queue, &message, sizeof(message)); // envoi message timer timeout + numéro
					// remise à zéro du timer
					timer_list.timer[i].countdown = 0;
					timer_list.timer[i].owner = NO_OWNER;
					timer_list.timer[i].status = STOP;
					timer_list.timer[i].number = -1;
				}
			}
		}
		pthread_mutex_unlock(&timer_list.mutex);
	}
	return NULL;
}
