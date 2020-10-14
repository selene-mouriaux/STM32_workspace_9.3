/*
 * queue.h
 *
 *  Created on: Apr 21, 2020
 *      Author: s_il_vanas
 */

#ifndef QUEUE_H_
#define QUEUE_H_


typedef struct Element {
	int contenu;
	struct Element *suivant/*, *precedent*/;
} Element;

typedef struct Queue {
	Element *premier/*, *dernier*/;
} Queue;

Element* create_queue_element(int);
Queue* create_empty_queue(void);
void add_to_queue_top(Queue*, int);
void add_to_queue_bottom(Queue*, int);
void display_queue(Queue*);
void insert_in_queue_before(Queue*, int, int);
void insert_in_queue_after(Queue*, int, int);
int nombre_d_elements(Queue*);
int is_list_empty(Queue*);
int return_element_index(Queue*, int);
int pop_top_in_queue(Queue*);
int pop_bottom_in_queue(Queue*);
void insert_at_N(Queue*, int, int);
int pop_at_N(Queue*, int);
void sort_queue(Queue* queue);

#endif /* QUEUE_H_ */