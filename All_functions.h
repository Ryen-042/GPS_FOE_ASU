
#ifndef All_FUNCTIONS_H
#define All_FUNCTIONS_H

	//make delay by 0.1sec
void Delay(int i);
	//initialize port A
void PortF_Init(void);
	
// U0Rx (VCP receive) connected to PC4
// U0Tx (VCP transmit) connected to PC5
void UART_Init(void);
	// Wait for new input, then return ASCII code
unsigned char UART1_Inchar(void);
	// Wait for buffer to be not full, then output
void UART1_OutChar(unsigned char data);
	//turn on Red led if distance exceed 100m
void enable_Red(int distance);
//*Function calculate distance and accumulate total distance during moving by passing the previous and current longitude & latitude of each position
unsigned int calc_distance(double lat1, double long1,double lat2, double long2);
// Get the Latitude and Longitude from the data.
void getCoor(char data[], double *lat2, double *lon2);
// Return the angle in decimal degree.
double ddegree(double angle);
//extract gpgga data from gps
int gps_correct_data(char data[]);

#endif // All_FUNCTIONS_H
