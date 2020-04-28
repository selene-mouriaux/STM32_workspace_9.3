#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#include "FIFO.h"
#include <pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include "thread.h"
extern struct List liste_app;
extern struct List liste_send;
extern sem_t sem_app;
extern sem_t sem_read;
extern pthread_mutex_t mutex ;


void init_liste(struct List *liste){
	liste->mutex = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
	liste->head = NULL;
	liste->tail = NULL;

}
int pop_element(struct List* liste,struct Element *value_to_return) {

	struct Element* tmp;
	if (liste->head == NULL) {
		return 0; /* Retourne -1 si la pile est vide. */
	}
	pthread_mutex_lock (&mutex);
//	tmp = liste->head->next_p;
	tmp = liste->head;
	memcpy(value_to_return ,tmp, sizeof(struct Element));
	liste->head = tmp->next_p;
	free(tmp);
//	*value = liste->head->value;
//	free(liste->head);
//	liste->head = tmp;/* Le pointeur pointe sur le dernier ��l��ment. */
	pthread_mutex_unlock (&mutex);
	return 1;/* Retourne la valeur soutir��e de la pile. */
}


// envoie un element dans la liste chain��e
void push_element(struct List *liste,struct Element *value_to_push) {

	struct Element*  new_element = malloc(sizeof(struct Element)); //new_element contient l'adresse memoire des 8 octets cr��e

	if (new_element) {
		pthread_mutex_lock (&mutex);// si le malloc contient bien une adresse
		memcpy(new_element,value_to_push,sizeof(struct Element));
//		new_element->value = *value;                      //valeur du struct
		new_element->next_p = NULL;                  // adresse du prochain element
		if (liste->head == NULL) {                          // si la liste est vide
			liste->tail = new_element; //on attache le nouvel element a la queue de liste
			liste->head = new_element;              // on attache la tete aussi
		} else {                        //si la liste contient deja des elements

			liste->tail->next_p = new_element;
			liste->tail = new_element;
		}

		pthread_mutex_unlock (&mutex);
	}
}
void send_message(QUEUE_ID liste, struct Element *value_to_push,
		int message_lenght) {
		if (message_lenght <= SIZEOFMESSAGE) {
	if (liste == QUEUE_READ) {
		push_element(&liste_app, value_to_push);
		sem_post(&sem_read);
	} else if (liste == QUEUE_SEND) {
		push_element(&liste_send, value_to_push);
		sem_post(&sem_app);
	}

		}
		else{
			printf("mauvaise taille de message");
		}
}

int receive_message(QUEUE_ID liste, struct Element* value_to_return,
		int message_lenght) {
	int pop_status = 0;
		if(message_lenght >= SIZEOFMESSAGE){

	if (liste == QUEUE_READ) {
		sem_wait(&sem_read);
		pop_status = pop_element(&liste_app, value_to_return);
	} else if (liste == QUEUE_SEND) {
		sem_wait(&sem_app);
		pop_status = pop_element(&liste_send, value_to_return);

	}
		}
	return pop_status;
}

