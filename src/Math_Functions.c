#include <math.h>
const double Earth_Radius = 6371000;
const float PI = 3.14159;

double Todegree(double angle)
{
	int degree = (int)angle / 100;
	double minutes = angle - (double)degree * 100;
	return (degree + (minutes / 60));
}

double Torad(double angle)
{
	return (angle * PI / 180);
}
