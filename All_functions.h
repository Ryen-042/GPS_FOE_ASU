#ifndef All_FUNCTIONS
#define All_FUNCTIONS


	//make delay by 0.1sec
void Delay(void);
	//initialize port A
void PortF_Init(void);
	
// U0Rx (VCP receive) connected to PC4
// U0Tx (VCP transmit) connected to PC5
void UART_Init(void);
	// Wait for new input, then return ASCII code
unsigned char UART_InChar(void);
	// Wait for buffer to be not full, then output
void UART_OutChar(unsigned char data);
	//turn on Red led if distance exceed 100m
void enable_Red(int distance);

//*Function calculate distance and accumulate total distance during moving by passing the previous and current longitude & latitude of each position
uint32_t calc_distance(double lat1, double long1,double lat2, double long2);
// Get the Latitude and Longitude from the data.
void getCoor(char data[], double *lat2, double *lon2);

#endif // All_FUNCTIONS
