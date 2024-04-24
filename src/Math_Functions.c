#include <math.h>
const double Earth_Radius = 6371000;
const float PI = 3.14159;

float Todegree(float angle)
{
	int degree = (int)angle / 100;
	float minutes = angle - (float)degree * 100;
	return (degree + (minutes / 60));
}

float Torad(float angle)
{
	return (angle * PI / 180);
}
