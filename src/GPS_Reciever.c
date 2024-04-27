#include "UART.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "Math_Functions.h"
const double Earth_Radius = 6371000;
const float PI = 3.14159;

// parsing function
// $GPRMC,161229.487,A,3723.2475,N,12158.3416,W,0.13,309.62,120598, ,*10


void GPS_Start(float &Distance, float coordinates[300][2]){                              // A function that parces the data after $GPRMC, and retrieve the data in variables
    while (1)
    {   char buffer[500];                                     //initialize a buffer with size very very big to be certain that the data is recieved        
        const char *RMC = "$GPRMC";                           // match string
        const char *RMC_PTR = NULL;                           // "TO BE" address of the $ sign of the GPRMC
        int i = 0;                                            // counter

        //float coordinates[300][2];       this line should be written in main before GPS_Start() should be called
        //float Distance=0;                this line should be written in main before GPS_Start() should be called                  

        UART0_RECIEVE_DATA(buffer);                           // this function fills the buffer filled with the data and the garbage
        RMC_PTR = strstr( buffer , RMC);                      // search for a needle ("$GPRMC") in a hay stack (buffer)

        if (RMC_PTR != NULL)                                  // RMC_PTR could fail to find the needle
        {
            float time, latitude, longitude, knots;           // the variables that we want from the gps
            char status, ns, ew;
            //sscand takes string input ($ bta3 al GPRMC) and format string ("$GPRMC,%f,%c,%f,%c,%f,%c,%f,") and refrenced var
            if (sscanf(RMC_PTR, "$GPRMC,%f,%c,%f,%c,%f,%c,%f,", &time, &status, &latitude, &ns, &longitude, &ew, &knots) == 7)
            {
                coordinates[i][0]=longitude;                    //longitude should be stored in the 1st column
                coordinates[i][1]=latitude;                     //lattitude should be stored in the 2nd column
            }
            i++;
        }
        if (i >= 290)                                           //if i becomes too large exit the inf loop
        break;
        if (i==0)   
            continue;
            float long1_rad = Torad(Todegree(coordinates[i][0]));
            float lat1_rad = Torad(Todegree(coordinates[i][1]));
            float long2_rad = Torad(Todegree(coordinates[i-1][0]));
            float lat2_rad = Torad(Todegree(coordinates[i-1][1]));

            // calculate distance from haversine law
            float a = pow(sin((lat2_rad - lat1_rad) / 2), 2) + cos(lat1_rad) * cos(lat2_rad) * pow(sin((long2_rad - long1_rad) / 2), 2);
            float c = 2 * atan2(sqrt(a), sqrt(1 - a));
            Distance += Earth_Radius * c; // destance calculated
    }
}

                        //              [ long1      lat1    ]
                        //              [ long2      lat2    ]
                        //              [ long3      lat3    ]
                        //              [ long4      lat4    ]