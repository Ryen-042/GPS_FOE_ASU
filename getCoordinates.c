#include <stdio.h>
#include <string.h>
#include <stdint.h>

// Get the Latitude and Longitude from the data.
void getCoor(char data[], double *lat2, double *lon2)
{
    char acceptedId[] = "$GPGGA";
    char messageId[20] = {0};
    double lat, lon, x;
    char y;

    sscanf(data, "%[^,],%lf,%lf,%c,%lf", messageId, &x, &lat, &y, &lon);

    // if the message  id isn't accepted.
    if (strcmp(messageId, acceptedId))
    {
        return;
    }

    *lat2 = ddegree(lat);
    *lon2 = ddegree(lon);
}
// Return the angle in decimal degree.
double ddegree(double angle)
{
	int degree = (int)angle /100;
	return (degree +  (angle - degree * 100)/60.0);
}

