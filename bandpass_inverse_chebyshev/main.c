
#include "MK22F51212.h"                 				//Device header
#include "MCG.h"																//Clock header
#include "TimerInt.h"														//Timer Interrupt Header
#include "DAC.h"																//DAC Header
#include "BUTTONS.h"														//BUTTONS Header
#include "RGBLED.h"															//RGB LED Header

uint8_t i = 0;
uint8_t K = 5;
uint8_t pos = 0;
uint8_t Kinc = 0;
uint8_t Kdec = 0;

uint16_t K1[] = {2369,2264,2144,2013,1873,1729,1584,1441,1304,1176,1061,961,879,816,775,756,760,787,835,905,993,1098,1218,1349,1489,1633,1778,1921,2058,2186,2301,2401,2483,2546,2587,2606,2602,2575,2527,2457};
uint16_t K2[] = {1854,1635,1462,1345,1286,1279,1315,1379,1456,1527,1576,1590,1560,1483,1363,1207,1029,848,683,554,478,470,537,682,901,1182,1509,1859,2210,2536,2816,3030,3165,3213,3174,3056,2871,2637,2375,2107};
uint16_t K3[] = {1586,1209,972,897,977,1177,1442,1708,1914,2015,1988,1835,1585,1283,981,726,555,484,508,606,746,895,1027,1131,1210,1284,1381,1530,1751,2048,2404,2785,3139,3413,3557,3537,3346,3002,2551,2055};
uint16_t K4[] = {1291,754,530,638,999,1472,1898,2150,2174,1993,1692,1380,1144,1024,1003,1021,1010,925,767,584,451,440,586,872,1232,1579,1837,1972,2010,2026,2109,2329,2698,3154,3579,3832,3801,3444,2810,2033};
uint16_t K5[] = {1149,441,230,526,1141,1784,2197,2262,2032,1681,1393,1268,1285,1336,1303,1133,869,613,467,472,593,752,886,983,1090,1267,1537,1860,2152,2338,2409,2441,2556,2841,3279,3720,3943,3756,3110,2145};
uint16_t K6[] = {1030,201,67,574,1361,1995,2225,2083,1795,1581,1512,1508,1449,1288,1082,923,841,792,704,572,473,512,722,1032,1311,1477,1564,1682,1915,2238,2528,2682,2719,2793,3059,3510,3915,3934,3347,2245};
uint16_t K7[] = {974,72,6,647,1488,2037,2136,1960,1772,1683,1627,1511,1336,1182,1100,1044,934,755,578,494,529,640,783,959,1183,1435,1653,1805,1938,2135,2412,2679,2832,2899,3041,3388,3822,3971,3473,2323};
uint16_t K8[] = {897,17,50,729,1495,1960,2081,2004,1854,1690,1550,1456,1379,1264,1106,966,879,799,660,501,451,585,827,1041,1190,1357,1598,1849,2020,2142,2334,2624,2876,2981,3048,3310,3767,4015,3556,2330};
uint16_t K9[] = {815,31,135,743,1414,1921,2150,2065,1804,1614,1576,1540,1379,1180,1080,1042,929,738,591,540,532,572,742,1027,1271,1396,1529,1788,2070,2218,2308,2539,2876,3065,3075,3234,3717,4075,3625,2291};
uint16_t K10[] = {692,86,259,687,1291,1977,2274,2009,1681,1669,1699,1484,1256,1236,1204,986,806,794,715,484,409,628,865,972,1148,1452,1652,1733,1947,2274,2432,2484,2753,3121,3198,3179,3594,4095,3748,2236}; // 4095 value in this line was actually 4131...

uint16_t OUT[] = {1149,441,230,526,1141,1784,2197,2262,2032,1681,1393,1268,1285,1336,1303,1133,869,613,467,472,593,752,886,983,1090,1267,1537,1860,2152,2338,2409,2441,2556,2841,3279,3720,3943,3756,3110,2145};

void PIT0_IRQHandler(void){	//This function is called when the timer interrupt expires
	//Place Interrupt Service Routine Here
	GPIOA->PSOR          |= GPIO_PSOR_PTSO(0x1u << 1); // R = 1

	DAC0->DAT[0].DATL = DAC_DATL_DATA0(OUT[pos] & 0xFF);		//Set Lower 8 bits of Output
	DAC0->DAT[0].DATH = DAC_DATH_DATA1(OUT[pos] >> 0x8);		//Set Higher 8 bits of Output
	
	if(pos == 39) pos = 0;
	else pos++;
	
	NVIC_ClearPendingIRQ(PIT0_IRQn);							//Clears interrupt flag in NVIC Register
	PIT->CHANNEL[0].TFLG	= PIT_TFLG_TIF_MASK;		//Clears interrupt flag in PIT Register	
		
	GPIOA->PCOR          |= GPIO_PCOR_PTCO(0x1u << 1); // R = 0
}

// K++ BUTTON
void PORTB_IRQHandler(void){ //This function might be called when the SW3 is pushed
	if(K!=10) K++;
	
	Kinc++;
	switch (K){
		case 1:
			for(i = 0; i<40;i++)  OUT[i] = K1[i];
			break;
		case 2:
			for(i = 0; i<40;i++)  OUT[i] = K2[i];
			break;
		case 3:
			for(i = 0; i<40;i++)  OUT[i] = K3[i];
			break;
		case 4:
			for(i = 0; i<40;i++)  OUT[i] = K4[i];
			break;
		case 5:
			for(i = 0; i<40;i++)  OUT[i] = K5[i];
			break;
		case 6:
			for(i = 0; i<40;i++)  OUT[i] = K6[i];
			break;
		case 7:
			for(i = 0; i<40;i++)  OUT[i] = K7[i];
			break;
		case 8:
			for(i = 0; i<40;i++)  OUT[i] = K8[i];
			break;
		case 9:
			for(i = 0; i<40;i++)  OUT[i] = K9[i];
			break;
		case 10:
			for(i = 0; i<40;i++)  OUT[i] = K10[i];
			break;
		}
	
	NVIC_ClearPendingIRQ(PORTB_IRQn);              				//CMSIS Function to clear pending interrupts on PORTB	
	PORTB->ISFR 							= (0x1u << 17);
		
}

// K-- BUTTON
void PORTC_IRQHandler(void){ //This function might be called when the SW2 is pushed
	
	if(K!=1) K--;
	Kdec++;
	switch (K){
		case 1:
			for(i = 0; i<40;i++)  OUT[i] = K1[i];
			break;
		case 2:
			for(i = 0; i<40;i++)  OUT[i] = K2[i];
			break;
		case 3:
			for(i = 0; i<40;i++)  OUT[i] = K3[i];
			break;
		case 4:
			for(i = 0; i<40;i++)  OUT[i] = K4[i];
			break;
		case 5:
			for(i = 0; i<40;i++)  OUT[i] = K5[i];
			break;
		case 6:
			for(i = 0; i<40;i++)  OUT[i] = K6[i];
			break;
		case 7:
			for(i = 0; i<40;i++)  OUT[i] = K7[i];
			break;
		case 8:
			for(i = 0; i<40;i++)  OUT[i] = K8[i];
			break;
		case 9:
			for(i = 0; i<40;i++)  OUT[i] = K9[i];
			break;
		case 10:
			for(i = 0; i<40;i++)  OUT[i] = K10[i];
			break;
		}
	
	NVIC_ClearPendingIRQ(PORTC_IRQn);              				//CMSIS Function to clear pending interrupts on PORTC
	PORTC->ISFR 							= (0x1u << 1);
}

int main(void){
		
	RGBLED_Init();
	BUTTONS_Init();
	MCG_Clock120_Init();
	DAC_Init();
	TimerInt_Init();
	while(1){
		
	}
}
