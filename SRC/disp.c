/*	
	=================================================================
	= Copyright(C) 2009 KEIL CORPORATION All rights reserved		=
	=================================================================
	= Header file for SFR of ABOV(C51-Core)							=
	= Micom       	: ABOV[MC96F8316L]/32QFN						=
	= Main X-tal	: 16.0MHz(Internal OSC)							=
	= Machine Cycle : 0.2us											=
	= Subject       : define file (define.h)						=
	= Project      	: Food Processor MACHINE						=
	= Bender        : XXX CO.,LTD					     			=
	= Programmer	: Gstrading / KJLEE								=
	= Rev			: 19.01.16										=
	= Date			: Start[19.01.16] ~ End[19.01.xx]				=
	=================================================================
*/

#include <intrins.h>
#include "Typech.h"
#include "mc96f8316.h"
#include "define.h"
#include "func.h"
#include "ram.h"

void Display_off(void);

code unsigned char	d_LEDSPEED[5] = { 0x10,0x08,0x04,0x02,0x01};

void Disp_Proc(void)
{
	switch( DigitRotate )
	{
		case 0:	// LED 5 = Motor speed
			PO_LED = d_LEDSPEED[Motor_RPM]; 
			PO_COM1 = ON;
			break;
		case 2:	// LED 4 = Status Mode 
			PO_LED = 0x10;		// Power on
			if( Disp_ModeTimer )
			{
				if( Mode_Key == cNORMAL_MODE )					// Normal mode
				{
					if( fBLINK ) PO_LED = 0x18;		// Power on & Ready
				}else								// Push toggle mode
				{
					if( fBLINK ) PO_LED = 0x1E;		// Blink Ready & Run & Check
				}
			}else
			{
				if( fREADY )
				{
					PO_LED = 0x18;					// Power on & Ready
				}	
				if( System_Error == 1)
//				if( System_Error )
				{
					PO_LED |= 0x02;							// Check led	
				}else
				{	
					if( fCLEAN_Init ) PO_LED |= 0x06;		// Run & Check led
					else
					{		
						if( fCHECK || fCLEAN_Standby )
						{
							if( fBLINK ) PO_LED |= 0x02;	// Check led		
						}
						if( (fRUN || fFOOT || fCLEAN_Standby ) && fBLINK ) PO_LED |= 0x04;	// Run Led blink
					}	
				}
			}
			
			PO_COM2 = ON;
			break;
		default:
			Display_off();	
			Key_Proc();
			break;
	}	

	++DigitRotate;
	if( DigitRotate > 3 ) DigitRotate = 0;		// if use battery is DigitRotate > 19
}


	
void Display_off(void)
{
	PO_COM1 = OFF;
	PO_COM2 = OFF;
	PO_LED &= 0x00;;
}	


/* EOF	*/
	