#include <stdio.h>
#include <math.h>

/* Calculate the total distance during moving by passing
	 the previous and current Longitude & Latitude */
int totalDistance(double oldLon, double oldLat, double newLon, double newLat){

	static double distance = 0;
	double R = 6371.0, pi = 3.141592654; //radius of the earth in km
	double dLat = newLat-oldLat;
	double dLat_rad = dLat * pi / 180.0;
	double dLon = newLon - oldLon;
	double dLon_rad = dLon * pi / 180.0;
	double lat1_rad = oldLat * pi / 180.0;
	double lat2_rad = newLat * pi / 180.0;

	double a = sin(dLat_rad/2.0) * sin(dLat_rad/2.0) + sin(dLon_rad/2.0) * sin(dLon_rad/2.0) * cos(lat1_rad) * cos(lat2_rad);
	double c = 2.0 * atan2(sqrt(a), sqrt(1.0-a));
	double d = R * c * 1000;
	distance += d;
	return (int)(distance +.5);
}
