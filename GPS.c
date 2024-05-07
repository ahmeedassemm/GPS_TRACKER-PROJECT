#include <string.h>


#include "GPIO.h"
#include "GPS.h"
#include "UART.h"

const char* GPS_logname = "$GPRMC";
char GPS[80];
char GPS_formated[12][20];
char* token;
float currentLat;
float currentLong;

// extract $GPRMC message content
void GPS_read(void) {
    char i = 0;
    char counter = 0;

    // wait till $GPRMC message
    do {
        while (UART2_read_byte() != GPS_logname[i]) {
            i = 0;
        }
        i++;
    } while (i != 6);

    // extract GPRMC message content
    do {
        GPS[counter] = UART2_read_byte();
        counter++;
    } while (GPS[counter - 1] != '*');
}

// extract Latitude  and Longitude of the $GPRMC message
void GPS_format(void) {
    char i = 0;
    token = strtok(GPS, ",");

    do {
        strcpy(GPS_formated[i], token);
        token = strtok(NULL, ",");
        i++;
    } while (token != NULL);

    if (strcmp(GPS_formated[1], "A") == 0) {

        currentLat = atof(GPS_formated[2]);
        if (strcmp(GPS_formated[3], "N"))
            currentLat = -currentLat;

        currentLong = atof(GPS_formated[4]);
        if (strcmp(GPS_formated[5], "E"))
            currentLong = -currentLong;

    }
}