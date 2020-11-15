/**************************************************************************/
//Name:  RGBLED.c																						 							//
//Purpose:  Allow configuration and use of external RGB LED								//
//Author:  Thomas Smallarz																								//
//Revision:  1.0 06Oct2020 TS Initial Revision														//
//Target:  Freescale K22f																									//
/**************************************************************************/

#include "MK22F51212.h" 													//Device header
#include "RGBLED.h"																// RGBLED header

/******************************************************************/
//						Function for Initialization of RGB LED							//
/******************************************************************/

void RGBLED_Init(void){
		SIM->SCGC5           |= SIM_SCGC5_PORTA_MASK;	//Enables clock to PORTA
    SIM->SCGC5           |= SIM_SCGC5_PORTD_MASK; //Enables clock to PORTD
	
	  PORTA->PCR[1]         = PORT_PCR_MUX(0x1u);   // Set Signal Multiplexing to ALT1 for PTA1
		PORTA->PCR[2]         = PORT_PCR_MUX(0x1u);		// Set Signal Multiplexing to ALT1 for PTA2
    PORTD->PCR[5]         = PORT_PCR_MUX(0x1u);		// Set Signal Multiplexing to ALT1 for PTD5

	  GPIOA->PDDR          |= GPIO_PDDR_PDD(~(0x0u << 1)); //Sets PTA1 to Output GPIO
    GPIOA->PDDR          |= GPIO_PDDR_PDD(~(0x0u << 2)); //Sets PTA2 to Output GPIO
		GPIOD->PDDR          |= GPIO_PDDR_PDD(~(0x0u << 5)); //Sets PTD5 to Output GPIO
	
		GPIOA->PDOR          |= GPIO_PDOR_PDO(0x1u << 1); // R = 0
		GPIOA->PDOR					 |= GPIO_PDOR_PDO(0x1u << 2); // G = 0
	  GPIOD->PDOR					 |= GPIO_PDOR_PDO(0x1u << 5); // B = 0
	
	
}//End RGBLED_Init

/******************************************************************/
//					End Function for Initialization of RGB LED						//
/******************************************************************/
