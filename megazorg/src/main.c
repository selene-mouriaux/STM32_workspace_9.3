#include<stdio.h>
#include <stdint.h>
#include <pthread.h>
#include<unistd.h>
#include"leds_control.h"
#include"FIFO.h"
#include "thread.h"
#include <semaphore.h>
struct List liste_app;
struct List liste_send;
pthread_mutex_t mutex ;
sem_t sem_read;
sem_t sem_app;
//Color matrix[7][7];
//Color actual_display[7][7];


int main(int argc, char *argv[]) {
	init_matrix();
	init_liste(&liste_app);
	init_liste(&liste_send);
	sem_init(&sem_read, 0, 0);
	sem_init(&sem_app,0,0);
	pthread_t t1, t2, t3,t4;
	openLink();

	pthread_create(&t1, NULL, &thread_read, NULL);
	pthread_create(&t2, NULL, &thread_display, NULL);
	pthread_create(&t3, NULL, &thread_app,  NULL);
	pthread_create(&t4, NULL, &thread_timer, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	closeLink();

	return 0;
}
