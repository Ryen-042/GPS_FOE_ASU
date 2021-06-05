#include "All_functions.h"
#include "7_segment"


void SystemInit(void){}
	
	
int main(void)
{
	PortF_Init();
	UART_Init();
	PORTABD_Init();
	//main loop
	while(1)
	{
		Set_Pins(534); // examples: [131, 734]
		//test UART1
		UART1_OutChar('a');
		//test to see red light when distance exceeds 100 m. 
		enable_Red(534);
	}
}

