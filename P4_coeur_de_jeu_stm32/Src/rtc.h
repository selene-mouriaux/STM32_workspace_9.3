/*
 * rtc.h
 *
 *  Created on: Nov 12, 2020
 *      Author: silvanas
 */

#ifndef RTC_H_
#define RTC_H_

#include<stdint.h>


#define SIZE_OF_MESSAGE (29)

typedef struct {
	uint8_t Day[2];
	uint8_t Month[2];
	uint8_t Year[4];
	uint8_t DOW[3];
	uint8_t Hour[2];
	uint8_t Minute[2];
	uint8_t Second[2];
}Timestamp;

char* set_day_from(uint8_t* rtcmessage);
char* set_month_from(uint8_t* rtcmessage);
char* set_year_from(uint8_t* rtcmessage);
char* set_DOW_from(uint8_t* rtcmessage);
char* set_hours_from(uint8_t* rtcmessage);
void set_minutes_from(uint8_t* rtcmessage);
void set_seconds_from(uint8_t* rtcmessage);
struct Timestamp build_timestamp(uint8_t* rctmessage);
unsigned char* create_timestamp_string(Timestamp horodatage);
char* composeRtcMessage(char* rctmessage);


#endif /* RTC_H_ */
