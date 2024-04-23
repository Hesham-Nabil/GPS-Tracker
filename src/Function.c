#include <math.h>
const double Earth_Radius = 6371000;
const float PI = 3.14159;

float Todegree (float angle){
	int degree = (int)angle/100;
	float minutes = angle - (float)degree*100;
	return (degree+(minutes/60));}

float Torad (float angle){
	return (angle * PI/180);}

//getting the parameters of the 2 points from the gps module

float gps_getdistance(float long1,float lat1,float long2,float lat2){	//Calculating distance between current point and destination point

//converting longitude and lattitude to rad
	
float long1_rad = Torad(Todegree(long1));
float lat1_rad = Torad(Todegree(lat1));
float long2_rad = Torad(Todegree(long2));
float lat2_rad = Torad(Todegree(lat2));

//calculate distance from haversine law
float a = pow(sin((lat2_rad-lat1_rad)/2),2) + cos(lat1_rad)*cos(lat2_rad)*pow(sin((long2_rad-long1_rad)/2),2);
float c = 2* atan2(sqrt(a),sqrt(1-a));
float d = Earth_Radius * c; //destance calculated 
return d;}
	

	
	

	

	
