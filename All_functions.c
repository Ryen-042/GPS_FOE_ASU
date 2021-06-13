#include "All_functions.h"
#include "tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include<math.h>

#define Red          0x02
#define Blue         0x04
#define Green        0x08



void Delay(int i){
	unsigned long volatile time;
  time = 1454480*i;  // 1 sec
  while(time){
		time--;
  }
}


void PortF_Init(void){ 
  SYSCTL_RCGCGPIO_R |= 0x20;     // 1) activate clock for Port F
  while((SYSCTL_PRGPIO_R & 0x20 ) ==0);           // allow time for clock to start
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
  UART1_CTL_R |= 0x00000301;     // enable UART	
  GPIO_PORTC_AFSEL_R |= 0x30;    // enable alt funct on PC5-4
  GPIO_PORTC_DEN_R |= 0x30;      // configure PC5-4 as UART1
  GPIO_PORTC_PCTL_R = (GPIO_PORTC_PCTL_R&0xFF00FFFF)|0x00220000;
  GPIO_PORTC_AMSEL_R &= ~0x30;   // disable analog on PC5-4
}

// Wait for new input, then return ASCII code
unsigned char UART1_Inchar(void){
  while((UART1_FR_R&0x0010) != 0);      // wait until RXFE is 0
  return((char)(UART1_DR_R&0xFF));
}
// Wait for buffer to be not full, then output
void UART1_OutChar(unsigned char data){
  while((UART1_FR_R&0x0020) != 0);      // wait until TXFF is 0
  UART1_DR_R = data;
}

//turn on Red led if distance exceed 100m
void enable_Red(int distance){
	if( distance >= 100 ){
		GPIO_PORTF_DATA_R = Red ;   // Turn on red LED, PF1
	}
	else
		GPIO_PORTF_DATA_R = Green ;  // Turn on Green LED, PF1
}
//*Function calculate distance and accumulate total distance during moving by passing the previous and current longitude & latitude of each position

unsigned int calc_distance(double lat1, double long1,double lat2, double long2){

	static double totaldis = 0.0;    //total distance variable 
	double x1, x2, y1, y2, z1, z2, dis;
	
	const double PI =3.14;
  const double r =(6371*1000);   //radius of the earth 
	if((lat1 == 0) || (lat2 == 0) || (long1 == 0) || (long2 == 0))
	{
		return 0;
	}
	
	//Convert Positions Spherical Coordinates to Cartesian Coordinates
	
	x1 = r*cos(lat1*(PI/180))*cos(long1*(PI/180));  
	y1 = r*cos(lat1*(PI/180))*sin(long1*(PI/180));
	z1 = r*sin(lat1*(PI/180));
	
	x2 =r*cos(lat2*(PI/180))*cos(long2*(PI/180));
	y2 =r*cos(lat2*(PI/180))*sin(long2*(PI/180));
	z2 =r*sin(lat2*(PI/180));
	
	//Calculating the distace between  two Close Coordinates assuming approximately linear Path
	
	dis= sqrt(pow((x1-x2),2)+pow(y1-y2,2)+pow(z1-z2,2));
	
	//accumulate to the total distance
	
	totaldis+=dis;
	
	//return the total integer distance in meter with selling approxmation
	return((uint32_t)(totaldis+0.5));
}


	

// Get the Latitude and Longitude from the data.
void getCoor(char data[], double *lat2, double *lon2)
{
    char messageId[20] = {0};
    double lat, lon, x;
    char y;

    // if the message  id isn't accepted.
    if(data[6]==',' && data[7]==',')
    {
	       return;
    }
    sscanf(data, "%[^,],%lf,%lf,%c,%lf", messageId, &x, &lat, &y, &lon );

    *lat2 = ddegree(lat);
    *lon2 = ddegree(lon);
}
// Return the angle in decimal degree.
double ddegree(double angle)
{
	double degree = (int)angle /100;
	return (degree +  (angle - degree * 100)/60.0);
}

// gps
int j;
int gps_correct_data(char data[]){
	while(1){
	    data[0] = UART1_Inchar();	
		if(data[0] == '$'){
			data[1] = UART1_Inchar();
			if(data[1] == 'G'){
				data[2] = UART1_Inchar();
				if(data[2] == 'P'){
					data[3] = UART1_Inchar();
					if(data[3] == 'G'){
						data[4] = UART1_Inchar();
						if(data[4] == 'G'){
							data[5] = UART1_Inchar();
							if(data[5] == 'A'){
								data[6] = UART1_Inchar();
								for ( j = 7; j < 75; j++){
									data[j]= UART1_Inchar();
									if( data[j]=='*'){
										return 1;																	
									}
								}
							} 
						}
					}
				}
			}
		}

	}

}


