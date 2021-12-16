/*	
	=================================================================
	= Copyright(C) 2009 KEIL CORPORATION All rights reserved		=
	=================================================================
	= Header file for SFR of ABOV(C51-Core)							=
	= Micom       	: ABOV[MC96F8316L]/32QFN						=
	= Main X-tal	: 16.0MHz(Internal OSC)							=
	= Machine Cycle : 0.2us											=
	= Subject       : define file (define.h)						=
	= Project      	: HSENC LOUVER System							=
	= Bender        : XXX CO.,LTD					     			=
	= Programmer	: GPR / ROBOTKING								=
	= Rev			: 20.07.20										=
	= Date			: Start[20.07.20] ~ End[20.07.xx]				=
	=================================================================
*/

#include <intrins.h>
#include "Typech.h"
#include "mc96f8316.h"
#include "define.h"
#include "func.h"
#include "ram.h"

void EXT10_Int(void) interrupt 0
{}
void RESV0_Int(void) interrupt 3 
{}
void RESV1_Int(void) interrupt 4 
{}
void EXT0_4_Int(void) interrupt 5	// External interrupt 0 ~ 4 
{
	EIFLAG0 = _0000_0000;           // External Interrupt Flag Register
}	
void EXT5_Int(void) interrupt 6
{}
void EXT6_Int(void) interrupt 7
{}
void I2C_Int(void) interrupt 8
{}

/*
void RX_Int(void) interrupt 9
{}
void TX_Int(void) interrupt 10
{}
*/

void ADC_WAKE_UP(void) interrupt 11
{}
void TIMER0_OVER_FLOW_Int(void) interrupt 12
{}
void TIMER0_Int(void) interrupt 13
{
	// Timer2 interrupt = 2ms
	// TODO: add your code here
	fTime_up = ON;

	if(++msec10 >= 5)					// 2ms x 5 = 10.24ms
	{
		msec10 = 0;
		if( TX_DELAY ) --TX_DELAY;

		if (++msec100 >= 10) 			// 10.24ms x 10 = 102.4msec
		{   	
			msec100 = 0;
			fTime100m = ON;
			if( Start_DlyTimer ) --Start_DlyTimer;
			if( Disp_CleanTimer ) --Disp_CleanTimer;	
			if( Disp_ModeTimer ) --Disp_ModeTimer;
			Clean_Timer++;	
			ADC_CancelTimer++;
				
			if( keyin && !fCLEAN_Standby && !fSYSTEM_Run )
			{	
				if( Clean_KeyTimer++>30 ) 
				{
					fCLEAN_Standby = ON;
					Disp_CleanTimer = cS100MS5S;
				}	
			}else Clean_KeyTimer =0;
				
			if(++sec05 >= 5)				// 102.4 x 5 = 512msec
			{
				sec05 = 0;
				fBLINK ^= ON;
				fTime500m = ON;
				
				if( ++sec >= 2 )
				{
					sec = 0;
					if( fSYSTEM_Run ) 
					{
						AUTO_Off_Timer++;
					}else AUTO_Off_Timer = 0;

					if(++min >= 60)
					{
						min = 0;
					}		
				}	
			}
		
		}
	}	
}

 void INT_Timer2() interrupt 15
{
	if( (DigitRotate & 0x01) ) 
	{ 
		T2ADRH = 0x0F;  	// period count High
		T2ADRL = 0x3F;  	// period count Low
	}else
	{
		T2ADRH = 0x1F;  	// period count High
		T2ADRL = 0x3F;  	// period count Low
	}

	T2CRH |= 0x01;   		// clear counter

	Disp_Proc();		
}
void RESV2_Int(void) interrupt 16
{}
void EXT7_A_Int(void) interrupt 17
{}
void ADC_Int(void) interrupt 18
{}
void SPI_Int(void) interrupt 19
{}

void WDT_Int(void) interrupt 21
{}

void INT_BIT() interrupt 22
{}



/* EOF	*/