#include "C:/Keil/ARM/INC/TI/TM4C123/tm4c123gh6pm.h"
#include "C:/Keil/ARM/INC/TI/TM4C123GH6PM.h"
#include<math.h>
#include<stdint.h>

//*Function caculate distance and accumulate total distance during moving by passing the previous and current longitude & latitude of each position

uint32_t calc_distance(double lat1, double long1,float lat2, double long2){
	
	static double totaldis=0.0;    //total distance variable 
	const double PI =3.14;
  const double r =(6371*1000);   //radius of the earth 
	
	//Convert Positions Spherical Coordinates to Cartesian Coordinates
	
	double x1 = r*cos(lat1*(PI/180))*cos(long1*(PI/180));  
	double y1 = r*cos(lat1*(PI/180))*sin(long1*(PI/180));
	double z1 = r*sin(lat1*(PI/180));
	
	double x2 =r*cos(lat2*(PI/180))*cos(long2*(PI/180));
	double y2 =r*cos(lat2*(PI/180))*sin(long2*(PI/180));
	double z2 =r*sin(lat2*(PI/180));
	
	//Calculating the distace between  two Close Coordinates assuming approximately linear Path
	
	double dis= sqrt(pow((x1-x2),2)+pow(y1-y2,2)+pow(z1-z2,2));
	
	//accumulate to the total distance
	
	totaldis+=dis;
	
	//return the total integer distance in meter with selling approxmation
	return((uint32_t)(totaldis+0.5));
}
