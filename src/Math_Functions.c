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
	return (degree + minutes / 60);
}
