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



#endif // All_FUNCTIONS
