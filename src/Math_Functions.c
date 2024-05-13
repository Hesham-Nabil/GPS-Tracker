#include <math.h>
const float PI = 3.14159;
double Torad(double angle)
{
	return (angle * PI / 180);
}
double Todecimal(double angle)
{
	int degree = (int)angle / 100;
	double minutes = angle - (double)degree * 100;
	return (degree + minutes / (double)60);
}

void floatToString(float number, char* str, int precision) {
    int whole = (int)number;
    float fraction = number - whole;
    sprintf(str, "%d", whole);
    while (*str != '\0') {
        str++;
    }
    *str++ = '.';
    while (precision > 0) {
        fraction *= 10;
        int digit = (int)fraction;
        *str++ = '0' + digit;
        fraction -= digit;
        precision--;
    }
    *str = '\0';
}
