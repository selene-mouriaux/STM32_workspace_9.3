/*
 * queue.h
 *
 *  Created on: Apr 7, 2020
 *      Author: jonathan
 */

#ifndef QUEUE_H_
#define QUEUE_H_
#include<semaphore.h>

typedef enum Queue_id {
	QUEUE_READ, QUEUE_WRITE}Queue_id;

struct Queue_list{
	struct Queue *read_queue, *write_queue;
};

// Élément de liste.
struct Queue_element{
    int value;
    struct Queue_element* next;
};

// Structure de file, contient le pointeur vers le premier
//élément (pour delete) et vers le dernier (pour add).
struct Queue{
	struct Queue_element *first, *last;
	pthread_mutex_t queue_mutex;
	sem_t semaphore;
};


struct Queue* create_Queue(void);

struct Queue_element* create_Queue_element(int value);

void add_to_Queue(struct Queue* queue, int value);

int del_from_Queue(struct Queue* queue, char *message);

void print_Queue(struct Queue* queue);

#endif /* QUEUE_H_ */
