#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "7_segment"
void PORTABD_Init(void){
	SYSCTL_RCGCGPIO_R |= 0x1B; // Port (A, B, D, E)
	while ((SYSCTL_PRGPIO_R & 0x1B) ==0); // Delay
	// Port (A)
	GPIO_PORTA_LOCK_R = 0x4C4F434B ;
	GPIO_PORTA_CR_R |= 0xFF; // Allow Changes to PortA
	GPIO_PORTA_AMSEL_R &= ~0xFF; // Disable Analog Pins 
	GPIO_PORTA_PCTL_R &= ~0xFFFFFFFF; // Disable Serial Pin-Type For Pins
	GPIO_PORTA_AFSEL_R &= ~0xFF; // Disable Serial Pins
	GPIO_PORTA_DIR_R |= 0xFF; // Set Pins as Output
	GPIO_PORTA_DEN_R |= 0xFF; // Set Pins as Digital
	GPIO_PORTA_DATA_R &= 0x00; // Initalize Pins -> All Pins Are Active (For Active Low 7-Segment)
	
	// Port (B)
	GPIO_PORTB_LOCK_R = 0x4C4F434B ;
	GPIO_PORTB_CR_R |= 0xFF; // Allow Changes to PortB
	GPIO_PORTB_AMSEL_R &= ~0xFF; // Disable Analog Pins 
	GPIO_PORTB_PCTL_R &= ~0xFFFFFFFF; // Disable Serial Pin-Type For Pins
	GPIO_PORTB_AFSEL_R &= ~0xFF; // Disable Serial Pins
	GPIO_PORTB_DIR_R |= 0xFF; // Set Pins as Output
	GPIO_PORTB_DEN_R |= 0xFF; // Set Pins as Digital
	GPIO_PORTB_DATA_R &= 0x00; // Initalize Pins -> All Pins Are Active (For Active Low 7-Segment)
	
	// Port (D)
	GPIO_PORTD_LOCK_R = 0x4C4F434B ; // Unlock PortD Commit Register
	GPIO_PORTD_CR_R |= 0xFF; // Allow Changes to PortD
	GPIO_PORTD_AMSEL_R &= ~0xFF; // Disable Analog Pins 
	GPIO_PORTD_PCTL_R &= ~0xFFFFFFFF; // Disable Serial Pin-Type For Pins
	GPIO_PORTD_AFSEL_R &= ~0xFF; // Disable Serial Pins
	GPIO_PORTD_DIR_R |= 0xFF; // Set Pins as Output
	GPIO_PORTD_DEN_R |= 0xFF; // Set Pins as Digital
	GPIO_PORTD_DATA_R &= 0x00; // Initalize Pins -> All Pins Are Active (For Active Low 7-Segment)
	
	// port (E)
	GPIO_PORTE_LOCK_R = 0x4C4F434B;
	GPIO_PORTE_CR_R = 0x36; // Allow Changes to PortE (1, 2, 4, 5)
	GPIO_PORTE_AMSEL_R &= ~0xFF; // Disable Analog Pins 
	GPIO_PORTE_PCTL_R &= ~0xFFFFFFFF; // Disable Serial Pin-Type For Pins
	GPIO_PORTE_AFSEL_R &= ~0xFF; // Disable Serial Pins
	GPIO_PORTE_DIR_R |= 0xFF; // Set Pins as Output
	GPIO_PORTE_DEN_R |= 0xFF; // Set Pins as Digital
}