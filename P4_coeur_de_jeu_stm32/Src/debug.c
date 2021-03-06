/*
 * debug.c
 *
 *  Created on: Oct 14, 2020
 *      Author: silvanas
 */

#include "debug.h"
#include <stdarg.h>
#include <stdio.h>
#include <string.h>

static int debugLevel = 0;

void debug_setlevel(int inNewLevel) {
	debugLevel = inNewLevel;
}

int debug_pr_fn(int inLevel, const char *format, ...) {
	if (inLevel <= debugLevel) {
		va_list (ap);
		va_start(ap, format);
		int out = vfprintf(stdout, format, ap);
		fflush(stdout);
		va_end(ap);
		return out;
	}
	return 0;
}

void sendDebugMessage(int message_type, char* message_to_send, char* debug_message) {
	int size = strlen(debug_message);
	int i = 0;
	int to_upper = 'A' - 'a';
	char tmp_message[size];
	message_to_send[0] = 'd';
	if (message_type ==  1) {
		for(i=0 ; i<size ; i++) {
			int castvar_i = debug_message[i];
			if (castvar_i != 32)
				castvar_i+= to_upper;
			message_to_send[i+1] = castvar_i;
		}
	} else if (message_type == 2) {
		for(i=0 ; i<size ; i++) {
			tmp_message[i] = (int)debug_message[size-i];
			message_to_send[i+1] = tmp_message[i];
		}
	} else {
		for(i=0 ; i<size ; i++) {
			message_to_send[i+1] = debug_message[i];
		}
	}
	message_to_send[size+1] = '\n';
	message_to_send[size+2] = '\0';
}
