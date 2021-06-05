#ifndef 7_SEGMANT_H
#define 7_SEGMANT_H



void PORTABD_Init(void);
unsigned int Pins_Of_7Segment(unsigned int c);
unsigned int PORTA_in_E(unsigned int c);
unsigned int PORTD_in_E(unsigned int c);
void Set_Pins(unsigned int num);


#endif // 7_SEGMANT_H