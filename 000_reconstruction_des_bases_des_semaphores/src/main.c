/*
 *****************************************************************************

 *****************************************************************************
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>


void randomSleep() {
	int nb_seconds = (rand() % 4) + 2; // Tire un nombre aléatoire entre 2 et 5
	sleep(nb_seconds);
}

void * fn_1 (void * cookie) {
	while(1) {
		randomSleep();
		printf("Reveil 1\n");
	}

}
void * fn_2(void* cookie) {
	while(1) {
		sleep(1); // A REMPLACER
		printf("Reveil 2\n");
	}

}
int main(int argc, char * argv[]) {
	pthread_t thread1;
	pthread_t thread2;

	srand(time(NULL)); // Initialisation du générateur aléatoire

	pthread_create(&thread1, NULL, fn_1, NULL);
	pthread_create(&thread2, NULL, fn_2, NULL);
	while(1);
	return 0;
}