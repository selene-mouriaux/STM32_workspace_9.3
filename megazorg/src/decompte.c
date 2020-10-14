///*
// * decompte.c
// *
// *  Created on: Apr 17, 2020
// *      Author: mickaell
// */
//
//
////pour le decompte !
//
//#include "decompte.h"
//#include "game_p4.h"
//extern Color matrix[6][6];
//extern Color actual_display[6][6];
//
////le rgb des couleurs
//#pragma GCC diagnostic ignored "-Wunused-variable"
//const Color red = { 255, 0, 0 };
//const Color green = { 0, 255, 0 };
//const Color blue = { 0, 0, 255 };
//const Color white = { 255, 255, 255 };
//const Color purple = { 255, 0, 255 };
//const Color yellow = { 255, 255, 0 };
//const Color black = { 0, 0, 0 };
//#pragma GCC diagnostic warning "-Wunused-variable"
//


////void decompte(struct Element* receive_value, struct Element* nb_value) {
////	if (receive_message(QUEUE_READ, receive_value, SIZEOFMESSAGE)) {
////		if (receive_value->data.value[1] == UP) {
////			nb_value->data.value[1]++;
////			if (nb_value->data.value[1] > 9) {
////				nb_value->data.value[1] = 0;
////			}
////		} else if (receive_value->data.value[1] == DOWN) {
////			nb_value->data.value[1]--;
////			if (nb_value->data.value[1] < 0) {
////				nb_value->data.value[1] = 9;
////			}
////		}
////
////		send_message(QUEUE_SEND, nb_value, SIZEOFMESSAGE);
////	}
////}
//
//
//void set_number(int compteur) {
//
//	Color nbr_color = PLAYER_COLOR_1;
//	Color bckgrnd_color = BACKGROUND;
//	for (int row = 0; row < TAB_SIZE; row++) {
//		for (int col = 0; col < TAB_SIZE; col++) {
//			if (compteur == 1) { /*Ensemble de conditions pour afficher le chiffre 1*/
//				if ((col == 4) || (row == 3 && col == 1)
//						|| (row == 2 && col == 2)
//						|| (row == 1 && col == 3)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//			if (compteur == 2) { /*Ensemble de conditions pour afficher le chiffre 2*/
//				if ((row == 0 && col == 2) || (row == 0 && col == 3)
//						|| (row == 0 && col == 4) || (row == 1 && col == 1)
//						|| (row == 1 && col == 5) || (row == 2 && col == 5)
//						|| (row == 3 && col == 2) || (row == 3 && col == 3)
//						|| (row == 3 && col == 4) || (row == 4 && col == 1)
//						|| (row == 5 && col == 1) || (row == 6 && col == 2)
//						|| (row == 5 && col == 5) || (row == 6 && col == 3)
//						|| (row == 6 && col == 4)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//			if (compteur == 3) { /*Ensemble de conditions pour afficher le chiffre 3*/
//				if ((row == 0 && col == 2) || (row == 0 && col == 3)
//						|| (row == 0 && col == 4) || (row == 1 && col == 1)
//						|| (row == 1 && col == 5) || (row == 2 && col == 5)
//						|| (row == 3 && col == 2) || (row == 3 && col == 3)
//						|| (row == 3 && col == 4) || (row == 4 && col == 5)
//						|| (row == 5 && col == 5) || (row == 6 && col == 2)
//						|| (row == 6 && col == 3) || (row == 6 && col == 4)
//						|| (row == 5 && col == 1)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//			if (compteur == 4) { /*Ensemble de conditions pour afficher le chiffre 4*/
//				if ((row == 0 && col == 4) || (row == 1 && col == 3)
//						|| (row == 1 && col == 4) || (row == 2 && col == 2)
//						|| (row == 2 && col == 4) || (row == 3 && col == 1)
//						|| (row == 3 && col == 2) || (row == 3 && col == 3)
//						|| (row == 3 && col == 4) || (row == 3 && col == 5)
//						|| (row == 4 && col == 4) || (row == 5 && col == 4)
//						|| (row == 6 && col == 4)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//			if (compteur == 5) { /*Ensemble de conditions pour afficher le chiffre 5*/
//				if ((row == 0 && col == 1) || (row == 0 && col == 2)
//						|| (row == 0 && col == 3) || (row == 0 && col == 4)
//						|| (row == 0 && col == 5) || (row == 1 && col == 1)
//						|| (row == 2 && col == 1) || (row == 3 && col == 1)
//						|| (row == 3 && col == 2) || (row == 3 && col == 3)
//						|| (row == 3 && col == 4) || (row == 4 && col == 5)
//						|| (row == 5 && col == 5) || (row == 6 && col == 1)
//						|| (row == 6 && col == 2) || (row == 6 && col == 3)
//						|| (row == 6 && col == 4)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//			if (compteur == 6) { /*Ensemble de conditions pour afficher le chiffre 6*/
//				if ((row == 0 && col == 2) || (row == 0 && col == 3)
//						|| (row == 0 && col == 4) || (row == 1 && col == 1)
//						|| (row == 2 && col == 1) || (row == 3 && col == 1)
//						|| (row == 3 && col == 2) || (row == 3 && col == 3)
//						|| (row == 3 && col == 4) || (row == 4 && col == 1)
//						|| (row == 4 && col == 5) || (row == 5 && col == 1)
//						|| (row == 5 && col == 5) || (row == 6 && col == 2)
//						|| (row == 6 && col == 3) || (row == 6 && col == 4)
//						|| (row == 1 && col == 5)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//			if (compteur == 7) { /*Ensemble de conditions pour afficher le chiffre 7*/
//				if ((row == 0 && col == 1) || (row == 0 && col == 2)
//						|| (row == 0 && col == 3) || (row == 0 && col == 4)
//						|| (row == 0 && col == 5) || (row == 1 && col == 5)
//						|| (row == 2 && col == 5) || (row == 3 && col == 3)
//						|| (row == 3 && col == 4) || (row == 3 && col == 5)
//						|| (row == 4 && col == 5) || (row == 5 && col == 5)
//						|| (row == 6 && col == 5)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//			if (compteur == 8) { /*Ensemble de conditions pour afficher le chiffre 8*/
//				if ((row == 0 && col == 2) || (row == 0 && col == 3)
//						|| (row == 0 && col == 4) || (row == 1 && col == 1)
//						|| (row == 2 && col == 1) || (row == 2 && col == 5)
//						|| (row == 3 && col == 2) || (row == 3 && col == 3)
//						|| (row == 3 && col == 4) || (row == 4 && col == 1)
//						|| (row == 4 && col == 5) || (row == 5 && col == 1)
//						|| (row == 5 && col == 5) || (row == 6 && col == 2)
//						|| (row == 6 && col == 3) || (row == 6 && col == 4)
//						|| (row == 1 && col == 5)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//			if (compteur == 9) { /*Ensemble de conditions pour afficher le chiffre 9*/
//				if ((row == 0 && col == 2) || (row == 0 && col == 3)
//						|| (row == 0 && col == 4) || (row == 1 && col == 1)
//						|| (row == 2 && col == 1) || (row == 2 && col == 5)
//						|| (row == 3 && col == 2) || (row == 3 && col == 3)
//						|| (row == 3 && col == 4) || (row == 3 && col == 5)
//						|| (row == 4 && col == 5) || (row == 5 && col == 1)
//						|| (row == 5 && col == 5) || (row == 6 && col == 2)
//						|| (row == 6 && col == 3) || (row == 6 && col == 4)
//						|| (row == 1 && col == 5)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//			if (compteur == 0) { /*Ensemble de conditions pour afficher le chiffre 0*/
//				if ((row == 0 && col == 2) || (row == 0 && col == 3)
//						|| (row == 0 && col == 4) || (row == 1 && col == 1)
//						|| (row == 2 && col == 1) || (row == 2 && col == 5)
//						|| (row == 3 && col == 5) || (row == 4 && col == 1)
//						|| (row == 4 && col == 5) || (row == 5 && col == 1)
//						|| (row == 5 && col == 5) || (row == 6 && col == 2)
//						|| (row == 6 && col == 3) || (row == 6 && col == 4)
//						|| (row == 1 && col == 5)
//						|| (row == 3 && col == 1)) {
//					matrix[row][col] = nbr_color;
//				} else
//					matrix[row][col] = bckgrnd_color;
//			}
//		}
//
//	}
//}
