/*
 * rtc.c
 *
 *  Created on: Nov 12, 2020
 *      Author: silvanas
 */
#include "rtc.h"


char date_from_RTC[SIZE_OF_MESSAGE] = "dLUN 08/06/1981 07h00m59s PM";



char* get_day_from(uint8_t* rtcmessage) {
	return "01";
}

char* get_month_from(uint8_t* rtcmessage) {
	return "02";
}

char* get_year_from(uint8_t* rtcmessage) {
	return "03";
}

char* get_DOW_from(uint8_t* rtcmessage) {
	return "04";
}

char* get_hours_from(uint8_t* rtcmessage) {
	uint8_t hours = rtcmessage[2];
	uint8_t hours_units = hours && 0x0F;
	uint8_t hours_tens = hours && 0x10;
	hours_tens = hours >> 4;
	return "05";
}

void get_minutes_from(uint8_t* rtcmessage) {
	uint8_t minutes = rtcmessage[1];
	uint8_t minutes_units = minutes && 0x0F;
	uint8_t minutes_tens = minutes && 0x70;
	minutes_tens = minutes_tens >> 4;
	date_from_RTC[19] = minutes_units;
	if (minutes<10) {date_from_RTC[18] = '0';}
	else {date_from_RTC[18] = minutes_tens;}
}

void get_seconds_from(uint8_t* rtcmessage) {
	uint8_t seconds = rtcmessage[0];
	uint8_t seconds_units = seconds && 0x0F;
	uint8_t seconds_tens = seconds && 0x70;
	seconds_tens = seconds_tens >> 4;
	date_from_RTC[24] = seconds_units;
	if (seconds<10) {date_from_RTC[23] = '0';}
	else {date_from_RTC[23] = seconds_tens;}
}
/*
Timestamp build_timestamp(uint8_t* rtcmessage) {
	Timestamp horodatage = {.Day = get_day_from(&rtcmessage), .Month = get_month_from(&rtcmessage),
			.Year = get_year_from(&rtcmessage), .DOW = get_DOW_from(&rtcmessage), .Hour = get_hours_from(&rtcmessage),
			.Minute = get_minutes_from(&rtcmessage), .Second = get_seconds_from(&rtcmessage)
	};
	return horodatage;
}

unsigned char* create_timestamp_string(Timestamp horodatage) {
	//concat and return string based on struct including 'd'..
	return ;
}
*/
char* composeRtcMessage(char* rtcmessage) {
	//make the calls:
	date_from_RTC[4] = 32;
	date_from_RTC[15] = 32;
	date_from_RTC[25] = 32;
	date_from_RTC[26] = 32;
	date_from_RTC[27] = 32;
	date_from_RTC[28] = '\n';

	get_minutes_from(rtcmessage);
	get_seconds_from(rtcmessage);
	//extract and build struct
	//horodatage = build_timestamp(rtcmessage);
	//create string
	//return string  to send
	return date_from_RTC;
}
