/*
*****************************************************************************

lights_command varies from 0 to 12V.
total_darness false means dawn, dusk or eclipse.
time is 24h format, midnight is 0.
printf("La commande sort %3.2f %% de puissance avec %2.2f V sur 12 en sortie\n", pourcentage, lights_command);
*****************************************************************************
*/

#include<stdio.h>
#include<stdbool.h>


	bool day = true;
	bool night = false;
	bool partial_darkness = false;
	float full_power = 12;
	float lights_command = 0;
	int time = 12;
	float pourcentage = 100;
	regular_consumption;
	reduced_consumption;

int powersaving(int hour, int minutes, int halflight) {

	if ((day || !night) && partial_darkness) {
		pourcentage = 50;
		lights_command = full_power * pourcentage / 100;
	} else if (night && time >= 0 && time < 5) {
		pourcentage = 70;
		lights_command = full_power * pourcentage / 100;
	} else if (night && time >= 5 ) {
		lights_command = full_power;
	}

	return 0;
}



int main(void){

	int nightfall_hh, nightfall_mn, night_length_hh, night_length_mn, nb_of_calculations = 0, halflight, hour;

	while(1) {
		printf("Heure du coucher de soleil (ex: 08 49), durée de la nuit (ex : 14 02");
		scanf("%d %d %d %d", nightfall_hh, nightfall_mn, night_length_hh, night_length_mn);
		int hour = nightfall_hh - 1, minutes = nightfall_mn;

		if (night_length_hh %2 != 0) {
			nb_of_calculations = night_length_hh / 2 + 1 ;
		} else {
			nb_of_calculations = night_length_hh / 2 ;
		} if (night_length_mn > 0 && night_length_mn <= 30 ) {
			nb_of_calculations = nb_of_calculations + 1 ;
		} else if (night_length_mn < 60) {
			nb_of_calculations = nb_of_calculations + 2 ;
		}
		if (minutes == 0) {
			minutes = 30;
		} else if (minutes < 30) {
			minutes = minutes + 30;
		} else if (minutes > 30 && minutes < 60) {
			minutes = minutes - 30 ;
		}
		for ( int n = 0; n < nb_of_calculations; n++) {
			if ( n ==0 || n == nb_of_calculations - 1) {
				halflight = 1;
			} else {
				halflight = 0;
			}
			if ( n % 2 == 0) {
				hour =+ 1;
				powersaving(hour, nightfall_mn, halflight);
			} else {
				powersaving(hour + 1, minutes, halflight);
			}

		}
	}

	return 0;
}
