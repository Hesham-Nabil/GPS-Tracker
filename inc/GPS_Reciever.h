#ifndef GPS
#define GPS
char check_logname();
void getGpsData(char *GPS_DATA);
void GPS_Start();
float gps_getdistance(float long1, float lat1, float long2, float lat2);
#endif