/*
 * threads.c
 *
 *  Created on: Apr 24, 2020
 *      Author: s_il_vanas
 */

#include "cmsis_os2.h"
#include "local_leds.h"
#include "local_button.h"

extern osSemaphoreId_t sem_thread_led;

void thread_red_led(void * arg) {
	while(1) {
		LedRedOn();
		osDelay(400);
		LedRedOff();
		osDelay(400);
	}
}

void thread_blue_led(void * arg) {
	while(1) {
		WaitForLocalButtonReleased();
		LedBlueOn();
		osDelay(400);
		LedBlueOff();
		osDelay(400);
		osSemaphoreRelease(sem_thread_led);
	}
}


void thread_green_led(void * arg) {
	while(1) {
		osSemaphoreAcquire(sem_thread_led,osWaitForever);
		LedGreenOn();
		osDelay(400);
		LedGreenOff();
	}
}
