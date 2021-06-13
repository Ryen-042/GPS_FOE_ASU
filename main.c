#include "All_functions.h"
#include "7_segment.h"
#include "TM4C123/TM4C123GH6PM.h"


void SystemInit(){}
char data[80];
int totalDistance=0;
double lat1 =0;
double long1 =0;
double lat2 =0;
double long2 =0;
int main(void)
{
	SCB -> CPACR|=((3UL<<10*2)|(3UL<<11*2));
	
	PortF_Init();
	UART_Init();
	PORTABD_Init();
	Set_Pins(0);
// get our start location
	while(1){
		if(gps_correct_data(data)){
			getCoor(data,&lat1,&long1);
		break;
		}	
	}
	
	while(1){
		
	if(gps_correct_data(data)){
		getCoor(data,&lat2,&long2);
	  totalDistance=calc_distance(lat1,long1,lat2,long2);
		lat1=lat2;
		long1=long2;
		Set_Pins(totalDistance);
		enable_Red(totalDistance);
		Delay(2);
	}

}
	return 0;
}
