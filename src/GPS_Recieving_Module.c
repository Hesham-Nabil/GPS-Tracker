#include "UART.h"
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "Math_Functions.h"
#include "GPIO.h"


const double Earth_Radius = 6371000;

        //parsing function
        // $GPRMC,161229.487,A,3723.2475,N,12158.3416,W,0.13,309.62,120598, ,*10
        // double coordinates[300][2];      // this line should be written in main before GPS_Start() should be called
        // double Distance=0;               // this line should be written in main before GPS_Start() should be called
        // int i = 0
        // char buffer[500];                //initialize a buffer with size very very big to be certain that the data is recieved
        //GPS_Start( &Distance,  coordinates, buffer,  i)    //how to call the functiuon in main

// function to work as a flag if we received the right data
char check_logname(void){
    char i=0;
    char logname[] = "$GPRMC,";       //if the beginning of array is "$GPRMC," so we will return 1 as an indicator of valid data
    while (i<7){
        if (logname[i] != UART1_RECEIVE_CHAR()){
            i=0;
            break;
        }
        i++;
    }
    return (i/6);               //or return 1 (as if we received the right data the value of i will be 6)
}

void Get_array(char *Str_Of_Chars){
    char data = UART1_RECEIVE_CHAR();
    int i = 6;                          //not taking "$GPRMC," with us
    while (data!='*'){
        Str_Of_Chars[i] = data;
        data = UART1_RECEIVE_CHAR();

        i++;
    }                               //so we are now having the string of the characters 
    Str_Of_Chars[strlen(input)] = '*';   //after that adding "*" again to the array and we will know why
}                                   

void Get_GPS_Data(const char *input, char elements[MAX_ROWS][MAX_COLS]) {
    // Define indices for row and column in the 2-D array
    int row = 0;
    int col = 0;

    // Iterate through the characters of the input string
    for (int i = 0; input[i] != '\0'; i++) {
        // If comma is encountered, move to the next row and reset column index
        if (input[i] == ',') {
            elements[row][col] = '\0';            // Null-terminate the current element
            row++;                             // Move to the next row
            col = 0;                        // Reset column index
        } 
        else {
            // Store the character in the 2-D array
            elements[row][col] = input[i];
            col++;                           // Move to the next column
            if(elements[row][col] == "*"){
                elements[row][col] = '\0';            // Null-terminate the last element
                break;                           //that's why we need "*" again to terminate from the loop and getting the end of the string
              }

            }
    }

}











void GPS_Start(double *Distance, double coordinates[300][2], char* buffer, int i){                      // A function that parces the data after $GPRMC, and retrieve the data in variables
    while (1)
    {
//        const char *RMC = "$GPRMC";                                                                     // match string
//        const char *RMC_PTR = NULL;                                                                     // "TO BE" address of the $ sign of the GPRMC
//        UART1_RECIEVE_DATA(buffer);                                                                     // this function fills the buffer filled with the data and the garbage

        while (check_logname()); //wait for desired log name
        Get_array(buffer);
        char elements[MAX_ROWS][MAX_COLS] = {0};          // Define a 2-D array to store extracted elements
        Get_GPS_Data(Str_Of_Chars);
        // now defining our parameters
        time  = float (elements[0]);
        status = char(elements[1]);
        latitude = float(elements[2]);
        ns = char(elements[3]);
         //need to redefine
        int j = 0 ; 
        for (int i = 0; elements[4][k] != '\0'; i++) {
        if (elements[4][i] != 'E') {
            param1[j++] = elements[4][i];         //taking param1 without the character at the enf of the number
            }
        }
        
        param2 = elements[5];
        param3 = elements[6];
        param4 = elements[7];
        param5 = elements[8];










//        RMC_PTR = strstr( buffer , RMC);                                                                // search for a needle ("$GPRMC") in a hay stack (buffer)
//        if (RMC_PTR == NULL)
//        continue;
        double time, latitude, longitude, knots;                                                        // the variables that we want from the gps
        char status, ns, ew;

        for(int b ;b<3000;b++);
                                                                                                        //sscanf takes string input ($ bta3 al GPRMC) and format string ("$GPRMC,%f,%c,%f,%c,%f,%c,%f,") and refrenced var
        if (status != 'A')
        continue;
        // coordinates[i][0]=longitude;                    //longitude should be stored in the 1st column
        coordinates[i][1]=latitude;                                                                 //lattitude should be stored in the 2nd column
        i++;

        LED_ON();
        if (i == 300)                                                                                   //if i becomes too large exit the inf loop
        break;

        if (i==1)
            continue;
            double long1_rad = Torad(Todegree(coordinates[i-1][0]));
            double lat1_rad  = Torad(Todegree(coordinates[i-1][1]));
            double long2_rad = Torad(Todegree(coordinates[i-2][0]));
            double lat2_rad  = Torad(Todegree(coordinates[i-2][1]));

            // calculate the distance from haversine law
            double a = pow(sin((lat2_rad - lat1_rad) / 2), 2) + cos(lat1_rad) * cos(lat2_rad) * pow(sin((long2_rad - long1_rad) / 2), 2);
            double c = 2 * asin(sqrt(a));
            *Distance += Earth_Radius * c;                                                              // destance calculated
    }
}
