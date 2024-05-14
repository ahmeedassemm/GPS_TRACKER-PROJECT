#ifndef UTILITIES_H_INCLUDED
#define UTILITIES_H_INCLUDED

double to_degree(float raw_degree);
double to_radians(double degrees);
double distance(double lat1, double lon1, double lat2, double lon2);
int approximate(double a, float d);
void UART0SendFloat(float num);

#endif
