#include <math.h>
#include <stdio.h>

#include "tm4c123gh6pm.h"

#define M_PI 3.14159265358979323846
#define RADIUS 6371000 // radius of earth in meters

//gps output to degrees
double to_degree(float raw_degree) {
    int dd = (int)(raw_degree / 100);
    double mm = raw_degree - (dd * 100);
    double degree = dd + (mm / 60);
    return degree;
}

// degree to rad
double to_radians(double degrees) {
    return degrees * M_PI / 180.0;
}

//calc distance between 2 coordinates in M
double distance(double lat1, double lon1, double lat2, double lon2) {
    double dlat = to_radians(lat2 - lat1);
    double dlon = to_radians(lon2 - lon1);
    double a = pow(sin(dlat / 2), 2) + cos(to_radians(lat1)) * cos(to_radians(lat2)) * pow(sin(dlon / 2), 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    return RADIUS * c;
}

int approximate(double a, float d) {
    return (int)(a / d + 0.5) * d;
}

void UART0SendFloat(float num) {
    int i;
    char buffer[50];
    snprintf(buffer, sizeof(buffer), "%f", num);

    for (i = 0; buffer[i] != '\0'; i++) {
        while ((UART0_FR_R & UART_FR_TXFF) == UART_FR_TXFF); // Wait until the transmitter is not full
        UART0_DR_R = buffer[i]; // Transmit the character
    }
}
