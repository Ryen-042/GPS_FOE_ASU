#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "7_segment"

unsigned int Pins_Of_7Segment(unsigned int c){
	unsigned int b;
/*Pin Segment
	7    g
	6    b
	5    d
	4    f
	3    DP
	2    e
	1    a
	0    c  */

	switch (c) {
		case 0:      // 1000 1000 
		b = 0x88; 
		break;

		case 1:
		b = 0xBE;    // 1011 1110
		break;

		case 2:
		b = 0x19;    // 0001 1001
		break;

		case 3:
		b = 0x1C;    // 0001 1100
		break;

		case 4:
		b = 0x2E;    // 0010 1110
		break;
	
		case 5:
		b = 0x4C;    // 0100 1100
		break;
	
		case 6:
		b = 0x48;    // 01001000
		break;
	
		case 7:
		b = 0xBC;    // 1011 1100
		break;
	
		case 8:
		b = 0x08;    // 0000 1000
		break;
	
		case 9:
		b = 0x0C;    // 0000 1100
		break;
	}
	return b;
}

unsigned int PORTA_in_E(unsigned int c){
	unsigned int a;
	
	// Missing Pins in PortA -> (0, 1)
	switch (c) {
		// Pins (0, 1) are shifted left by (1 Bit) when we Put in PortE beacause PortE Starts from Pin (1)
		case 0:
		a = 0x00;    // 1000 1000 (Before Shifting) 
		break;

		case 1:
		a = 0x04;    // 1011 1110 (Before Shifting)
		break;

		case 2:
		a = 0x02;    // 0001 1001 (Before Shifting)
		break;

		case 3:
		a = 0x00;    // 0001 1100 (Before Shifting)
		break;

		case 4:
		a = 0x04;    // 0010 1110 (Before Shifting)
		break;
	
		case 5:
		a = 0x00;    // 0100 1100 (Before Shifting) -> 1001 1000 (After Shifting)
		break;
	
		case 6:
		a = 0x00;    // 0100 1000  (Before Shifting)
		break;
	
		case 7:
		a = 0x00;    // 1011 1100  (Before Shifting)
		break;
	
		case 8:
		a = 0x00;    // 0000 1000  (Before Shifting)
		break;
	
		case 9:
		a = 0x00;    // 0000 1100  (Before Shifting)
		break;
	}
	return a;
}

unsigned int PORTD_in_E(unsigned int c){
	unsigned int d;
	
	// Missing Pins in PortD -> (4, 5)
	switch (c) {
		// We will not shift Pins (4, 5) when we Put them in PortE and will Put Them in the same Pins (i.e. Pins (4, 5) of PortE)
		case 0:
		d = 0x00;    // 1000 1000 (Before Shifting) 
		break;

		case 1:
		d = 0x30;    // 1011 1110 (Before Shifting)
		break;

		case 2:
		d = 0x10;    // 0001 1001 (Before Shifting)
		break;

		case 3:
		d = 0x10;    // 0001 1100 (Before Shifting)
		break;

		case 4:
		d = 0x20;    // 0010 1110 (Before Shifting)
		break;
	
		case 5:
		d = 0x00;    // 0100 1100 (Before Shifting) -> 1001 1000 (After Shifting)
		break;
	
		case 6:
		d = 0x00;    // 0100 1000  (Before Shifting)
		break;
	
		case 7:
		d = 0x30;    // 1011 1100  (Before Shifting)
		break;
	
		case 8:
		d = 0x00;    // 0000 1000  (Before Shifting)
		break;
	
		case 9:
		d = 0x00;    // 0000 1100  (Before Shifting)
		break;
	}
	return d;
}

void Set_Pins(unsigned int num){
	unsigned int Digit_A;
	unsigned int Digit_B;
	unsigned int Digit_D;
	
	// Splitting Digits
	Digit_A = num % 10; // Smallest Digit (Rightmost Digit)
  num = num / 10;
	Digit_B = num % 10;	// Second Digit
	num = num / 10;
	Digit_D = num % 10; // Last Digit (Leftmost Digit)
	
	// Getting the Values of the 7-Segment Pins
	GPIO_PORTA_DATA_R = Pins_Of_7Segment(Digit_A);
	GPIO_PORTB_DATA_R = Pins_Of_7Segment(Digit_B);
	GPIO_PORTD_DATA_R = Pins_Of_7Segment(Digit_D);
	
	// Extra Step to Get the Full Values of the 7-Segment Pins (Due to the Missing Pins from PortA, PortD)
	// Missing Pins in PortA == (0, 1)   ->    Moved to PortE, Pins (1, 2)  
	// Missing Pins in PortD == (4, 5)   ->    Moved to PortE, Pins (4, 5)
	
	GPIO_PORTE_DATA_R = PORTA_in_E(Digit_A);
	GPIO_PORTE_DATA_R |= PORTD_in_E(Digit_D);
}
