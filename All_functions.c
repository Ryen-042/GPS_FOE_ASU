#include "All_functions.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include<math.h>

#define Red          0x02
#define Blue         0x04
#define Green        0x08



void Delay(void){
	unsigned long volatile time;
  time = 145448;  // 0.1sec
  while(time){
		time--;
  }
}


void PortF_Init(void){ 
	volatile unsigned long delay;
  SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOF;     // 1) activate clock for Port F
  delay = SYSCTL_RCGC2_R;           // allow time for clock to start
  GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;   // 2) unlock GPIO Port F
  GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
  // only PF0 needs to be unlocked, other bits can't be locked
  GPIO_PORTF_AMSEL_R = 0x00;        // 3) disable analog on PF
  GPIO_PORTF_PCTL_R = 0x00000000;   // 4) PCTL GPIO on PF4-0
  GPIO_PORTF_DIR_R = 0x0E;          // 5) PF4,PF0 in, PF3-1 out
  GPIO_PORTF_AFSEL_R = 0x00;        // 6) disable alt funct on PF7-0
  GPIO_PORTF_PUR_R = 0x11;          // enable pull-up on PF0 and PF4
  GPIO_PORTF_DEN_R = 0x1F;          // 7) enable digital I/O on PF4-0
}


// U0Rx (VCP receive) connected to PC4
// U0Tx (VCP transmit) connected to PC5
void UART_Init(void){            // should be called only once
  SYSCTL_RCGCUART_R |= 0x00000002;  // activate UART1
  SYSCTL_RCGCGPIO_R |= 0x00000004;  // activate port C
  UART1_CTL_R &= ~0x00000001;    // disable UART
  UART1_IBRD_R = 104;     // IBRD = int(16,000,000 / (16 * 9600)) = int(104.16667)
  UART1_FBRD_R = 11;     // FBRD = int(0.16667 * 64 + 0.5) = 11
  UART1_LCRH_R = 0x00000070;  // 8 bit, no parity bits, one stop, FIFOs
  UART1_CTL_R |= 0x00000001;     // enable UART
  GPIO_PORTC_AFSEL_R |= 0x30;    // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0x30;      // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)+0x00220000;
  GPIO_PORTC_AMSEL_R &= ~0x30;   // disable analog on PC5-4
}

// Wait for new input, then return ASCII code
unsigned char UART_InChar(void){
  while((UART1_FR_R&0x0010) != 0);      // wait until RXFE is 0
  return((char)(UART1_DR_R&0xFF));
}
// Wait for buffer to be not full, then output
void UART_OutChar(unsigned char data){
  while((UART1_FR_R&0x0020) != 0);      // wait until TXFF is 0
  UART1_DR_R = data;
}
//turn on Red led if distance exceed 100m
void enable_Red(int distance){
	if( distance >= 100 ){
		GPIO_PORTF_DATA_R |= Red ;   // Turn on red LED, PF1
	}
	else
		GPIO_PORTF_DATA_R &= ~Red ;  // Turn off red LED, PF1
}


//*Function calculate distance and accumulate total distance during moving by passing the previous and current longitude & latitude of each position

uint32_t calc_distance(double lat1, double long1,double lat2, double long2){
	
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
