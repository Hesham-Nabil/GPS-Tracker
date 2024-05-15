#include <math.h>
const float PI = 3.14159;
double Torad(double angle)
{
    return (angle * PI / 180);                                      // change angle from degree to radian 
}
double Todecimal(double angle)
{
    int degree = (int)angle / 100;                                  //Take first 2 numbers as the degree 
    double minutes = angle - (double)degree * 100;                  //Get minutes 
    return (degree + minutes / (double)60);                         
}

void floatToString(float number, char *str, int precision)
{
    int whole = (int)number;                                        // Get the integer part of the number
    float fraction = number - whole;                                //Get the fraction Part of the number
    sprintf(str, "%d", whole);                                      //fill the string with the integer part of the number
    while (*str != '\0')                                            //Loop until you get the end of the integer part in the string
    {
        str++;                                                      //string pointer increment
    }
    *str++ = '.';                                                   //put decimal point after the whole number
    while (precision > 0)                                           //loop over the precision
    {
        fraction *= 10;                                             //multiply the fraction by 10 to get the number in fraction part
        int digit = (int)fraction;                                  //digit= integer part of fraction
        *str++ = '0' + digit;                                       //if digit =0 it will print "0" depend on ASCII
        fraction -= digit;                                          //fraction -=digit to remove the part you add 
        precision--;                                                //precision decrements
    }
    *str = '\0';                                                    //add null char at the end
}
