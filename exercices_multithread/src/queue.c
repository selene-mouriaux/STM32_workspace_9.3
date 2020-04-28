/*
 * queue.c
 *
 *  Created on: Apr 7, 2020
 *      Author: jonathan
 */

#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include<pthread.h>


// Créer un nouvel élément de queue.
struct Queue_element* create_Queue_element(int value) {
	struct Queue_element* tmp = (struct Queue_element*) malloc(sizeof(struct Queue_element));
	tmp->value = value;
	tmp->next = NULL;
	return tmp;
}


// Créer une queue vide.
struct Queue* create_Queue(void) {
	struct Queue* queue = (struct Queue*) malloc(sizeof(struct Queue));
	queue->first = queue->last = NULL;
	queue->queue_mutex = (pthread_mutex_t ) PTHREAD_MUTEX_INITIALIZER;
	sem_init(&queue->semaphore, 0, 0);
	return queue;
}


// Créer un élément de queue et l'ajouter à la queue voulue.
void add_to_Queue(struct Queue* queue, int value) {
	pthread_mutex_lock(&queue->queue_mutex);
	// Nouvel élément
	struct Queue_element* element_to_add = create_Queue_element(value);
	// Si la queue est vide, le nouvel élément devient le premier et le dernier.
	if (queue->last == NULL) {
		queue->first = queue->last = element_to_add;
		pthread_mutex_unlock(&queue->queue_mutex);
		return;
	}
	// Ajouter le nouvel élément à la queue et le définir comme étant le dernier.
	queue->last->next = element_to_add;
	queue->last = element_to_add;
	pthread_mutex_unlock(&queue->queue_mutex);
}


// Supprimer un élément de la queue.
int del_from_Queue(struct Queue* queue, char* message) {
	// Si la queue est vide, aucun retour.
	pthread_mutex_lock(&queue->queue_mutex);
	if (queue->first == NULL)
		return -1;
	// Récupère l'addresse du premier élement, puis le second élément devient le premier.
	struct Queue_element* element_to_delete = queue->first;
	queue->first = queue->first->next;
	// Si le premier devient nul, le dernier aussi.
	if (queue->first == NULL)
		queue->last = NULL;
	pthread_mutex_unlock(&queue->queue_mutex);
	*message = element_to_delete->value;
	free(element_to_delete);
	return 0;
}


void print_Queue(struct Queue* queue) {
	if (queue->first != NULL) {
		printf("My Queue : ");
		struct Queue_element* my_element = queue->first;
		do {
			printf("%d ", my_element->value);
			my_element = my_element->next;
		} while (my_element != NULL);
		printf("//\n");
		free(my_element);
	}
}


