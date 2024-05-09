#include "UART.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "Math_Functions.h"
#include "GPIO.h"
#include "Systick.h"
const double Earth_Radius = 6371000;
void GPS_Start(double *Distance, double coordinates[2][2], char *buffer, int loop_counter)
{ // A function that parces the data after $GPRMC, and retrieve the data in variables
    while (1)
    {
        int fr_part = 0;
        int int_part = 0;
        char output_buffer[17] = {};
        const int length = 300;
        const char *RMC = "$GPRMC"; // match string
        const char *RMC_PTR = NULL;
        UART0_TRANSMIT_CHAR('b'); // "TO BE" address of the $ sign of the GPRMC
        UART1_RECIEVE_DATA(buffer, length);
        UART0_TRANSMIT_CHAR('c'); // this function fills the buffer filled with the data and the garbage
        RMC_PTR = strstr(buffer, RMC);
        UART0_TRANSMIT_CHAR('d'); // search for a needle ("$GPRMC") in a hay stack (buffer)
        if (RMC_PTR == NULL)
            continue;
        double time, latitude, longitude, knots; // the variables that we want from the gps
        char status, ns, ew;                     // sscanf takes string input ($ bta3 al GPRMC) and format string ("$GPRMC,%f,%c,%f,%c,%f,%c,%f,") and refrenced var
        if (sscanf(RMC_PTR, "$GPRMC,%lf,%c,%lf,%c,%lf,%c", &time, &status, &latitude, &ns, &longitude, &ew) == 6)
        {
            if (status != 'A')
                continue;
            coordinates[i][0] = longitude; // longitude should be stored in the 1st column
            coordinates[i][1] = latitude;  // lattitude should be stored in the 2nd column
            loop_counter++;
        }
        else
        {
            continue;
        }
        if (loop_counter == 1)
            continue;
        double long1_rad = Torad(Todegree(coordinates[i - 1][0]));
        double lat1_rad = Torad(Todegree(coordinates[i - 1][1]));
        double long2_rad = Torad(Todegree(coordinates[i - 2][0]));
        double lat2_rad = Torad(Todegree(coordinates[i - 2][1]));
        // calculate the distance from haversine law
        double a = pow(sin((lat2_rad - lat1_rad) / 2), 2) + cos(lat1_rad) * cos(lat2_rad) * pow(sin((long2_rad - long1_rad) / 2), 2);
        double c = 2 * asin(sqrt(a));
        if (Earth_Radius * c > 1)          // calculate if distance larger than 1
            *Distance += Earth_Radius * c; // destance calculated
        if (loop_counter == 2)
        {
            break;
        } // if i becomes too large exit the inf loop
    }
}