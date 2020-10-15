/*
 * debug.c
 *
 *  Created on: Oct 14, 2020
 *      Author: silvanas
 */

#include "debug.h"
#include <stdarg.h>
#include <stdio.h>

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
