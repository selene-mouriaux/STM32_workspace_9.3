/*
*****************************************************************************



*****************************************************************************
*/

#include<stdio.h>
#include<stdlib.h>
#include "queue.h"

int main(int argc, char *argv[]) {


	Queue* queue_principale = create_empty_queue();
	display_queue(queue_principale);
	printf("liste vide ? %d.\n", is_list_empty(queue_principale));
	printf("index de %d = %d.\n", 1, return_element_index(queue_principale, 1));
	add_to_queue_top(queue_principale, 1);
	add_to_queue_top(queue_principale, 2);
	add_to_queue_top(queue_principale, 3);
	add_to_queue_top(queue_principale, 4);
	add_to_queue_bottom(queue_principale, 5);
	add_to_queue_bottom(queue_principale, 6);
	add_to_queue_bottom(queue_principale, 7);
	display_queue(queue_principale);
	printf("Nombre d'éléments dans la queue : %d.\n", nombre_d_elements(queue_principale));
	printf("insertion de 8 avant 3\n");
	insert_in_queue_before(queue_principale, 8, 3);
	display_queue(queue_principale);
	printf("Nombre d'éléments dans la queue : %d.\n", nombre_d_elements(queue_principale));
	printf("insertion de 9 après 6\n");
	insert_in_queue_after(queue_principale, 9, 6);
	display_queue(queue_principale);
	printf("Nombre d'éléments dans la queue : %d.\n", nombre_d_elements(queue_principale));
	printf("index de %d = %d.\n", 1, return_element_index(queue_principale, 1));
	printf("liste vide ? %d.\n", is_list_empty(queue_principale));
	printf("popped top element : %d.\n", pop_top_in_queue(queue_principale));
	display_queue(queue_principale);
	printf("popped top element : %d.\n", pop_top_in_queue(queue_principale));
	display_queue(queue_principale);
	printf("popped bottom element : %d.\n", pop_bottom_in_queue(queue_principale));
	display_queue(queue_principale);
	printf("popped bottom element : %d.\n", pop_bottom_in_queue(queue_principale));
	display_queue(queue_principale);
	printf("Nombre d'éléments dans la queue : %d.\n", nombre_d_elements(queue_principale));
	printf("insertion de 10 à l'index N = 2 pour N de 0 à N-1\n");
	insert_at_N(queue_principale, 10, 2);
	display_queue(queue_principale);
	printf("dépop de l'élément à l'index N = 2 pour N de 0 à N-1\n");
	pop_at_N(queue_principale, 2);
	display_queue(queue_principale);
//	sort_queue(queue_principale);
//	display_queue(queue_principale);


	return 0;
}