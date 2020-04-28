/*COMMANDES POUR LE MUTEX

 pthread_mutex_init(&mutex, NULL);
 pthread_mutex_lock(&mutex);
 pthread_mutex_unlock(&mutex);
 */

#include"game.h"

int main(void) {
	printf("PRINTF DU MAIN\n");

	queue_push_app = queue_init();
	queue_app_display = queue_init();

	printf("intialisation mutex\n");
	pthread_mutex_init(&queue_push_app->mutex, NULL);
	pthread_mutex_init(&queue_app_display->mutex, NULL);

	printf("initialisation semaphores\n");
	sem_init(&sem_button, 0, 0);
	sem_init(&sem_display, 0, 0);

	printf("ouverture liaison port série\n");
	openLink();
	pthread_t read;
	pthread_t display;
	pthread_t app;
	pthread_t timer;
	if (pthread_create(&read, NULL, user_button, NULL) != 0) {
		printf("ECHEC CREATION THREAD Push\n");
	} else {
		printf("création thread reception boutons\n"); // READ
	}
	if (pthread_create(&display, NULL, show_board, NULL) != 0) {
		printf("ECHEC CREATION THREAD show_board\n");
	} else {
		printf("création thread affichage matrice\n"); // WRITE

	}
	if (pthread_create(&app, NULL, application, NULL) != 0) {
		printf("ECHEC CREATION THREAD application\n");
	} else {
		printf("création thread application\n"); // POP
	}
	if (pthread_create(&timer, NULL, timers, NULL) != 0) {
		printf("ECHEC CREATION THREAD timer\n");
	} else {
		printf("création thread timer\n");
	}
	printf("\nFIN PRINTF DU MAIN\n\n");

	pthread_join(timer, NULL);
	pthread_join(read, NULL);
	pthread_join(display, NULL);
	pthread_join(app, NULL);
	closeLink();
}
