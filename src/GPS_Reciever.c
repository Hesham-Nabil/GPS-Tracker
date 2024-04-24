#include "UART.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "Math_Functions.h"
#define COORDINATES_SIZE 100
const double Earth_Radius = 6371000;
const float PI = 3.14159;

char check_logname()
{
    int i = 0;
    char logname[] = "$GPRMC,";
    while (i < 7)
    {
        if (logname[i] != UART0_RECIEVE_CHAR())
        {
            i = 0;
            break;
        }
        i++;
    }
    return i;
}

void getGpsData(char *GPS_DATA)
{
    char data = UART0_RECIEVE_CHAR();
    char i = 0;
    if (check_logname())
    {
        while (data != '*')
        {
            data = UART0_RECIEVE_CHAR();
            GPS_DATA[i] = data;
            if (i >= 80)
                break;
            i++;
        }
    }
}

// parsing function
// 161229.487,A,3723.2475,N,12158.3416,W,0.13,309.62,120598, ,*10

void GPS_Start(){                                         // A function that parces the data after $GPRMC, and retrieve the data in variables
    while (1)
    {
        const char *rmc = "$GPRMC";
        const char *rmc_ptr = NULL;

        float coordinates[COORDINATES_SIZE][2];
        float(*coordinates_ptr)[2] = coordinates;

       // rmc_ptr = strstr( "HERE SHOULD BE AN ARRAY OF STRING THAT HAS ALL THE DATA", rmc);

        if (rmc_ptr != NULL)
        {
            float time, latitude, longitude, knots;
            char status, ns, ew;

            if (sscanf(rmc_ptr, "$GPRMC,%f,%c,%f,%c,%f,%c,%f,", &time, &status, &latitude, &ns, &longitude, &ew, &knots) == 7)
            {
                (*coordinates_ptr)[0] = latitude;
                (*coordinates_ptr)[1] = longitude;
            }
        }

    }
}
float gps_getdistance(float long1, float lat1, float long2, float lat2)
{ // getting the parameters of the 2 points from the gps module
  // Calculating distance between current point and destination point
  // converting longitude and lattitude to rad

    float long1_rad = Torad(Todegree(long1));
    float lat1_rad = Torad(Todegree(lat1));
    float long2_rad = Torad(Todegree(long2));
    float lat2_rad = Torad(Todegree(lat2));

    // calculate distance from haversine law
    float a = pow(sin((lat2_rad - lat1_rad) / 2), 2) + cos(lat1_rad) * cos(lat2_rad) * pow(sin((long2_rad - long1_rad) / 2), 2);
    float c = 2 * atan2(sqrt(a), sqrt(1 - a));
    float d = Earth_Radius * c; // destance calculated
    return d;
}