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

#define	cKEYCHT		15	// Key Chatt counter value[6mm*20=120ms]-Speed key
#define	cKEYCHT1	15	// Key Chatt counter value[6mm*20=120ms]- Foot & Run
#define	cKEYCHT2	15	// Key Chatt counter value[6mm*20=120ms]- Limit

/* Key part Start	*/
void KeyAnaly(void);
char KeyChattering(void);

void KeyAnaly1(void);
char KeyChattering1(void);

void KeyAnaly2(void);
char KeyChattering2(void);

/*	==============================================================================	*/
/*	==============================================================================	*/
/*	==============================================================================	*/
void	Key_Proc(void)
{
	if(!KeyChattering())	KeyAnaly();
}

char	KeyChattering(void)
{
	unsigned char x;
	
	if(Wchact == 0)	Wchact = cKEYCHT;
	
	P2IO = 0xEF;    // P24(in) direction
	P2PU = 0x00;    	// pullup
	P2OD = 0x10;    	// open drain
	
	for(x=0;x<50;x++) 	NOP();
	
	x = 0;	
	if( !PI_TACTKEY ) x = 1;
					
	P2IO = 0xFF;    // P24(out) direction
	P2PU = 0x00;    	// pullup
	P2OD = 0x00;    	// open drain
	if(x != Wkeyin)
	{
		Wkeyin = x;
		Wchact = cKEYCHT;
	}
return(--Wchact);
}

void 	KeyAnaly(void)
{
	keyin = Wkeyin;
	fKEY_Init = ON;
		
	switch( keyin )
	{
		case 0:		// Not key
			fKEYFREE = OFF;
			Clean_KeyTimer=0;
			break;

		case 1:		// Power key
			if( fKEYFREE || fCLEAN_Init ) break;
			fKEYFREE = ON;

			ADC_Index=0;
			ADC_OCRSum=0;
			ADC_Min_sampling=0;
			ADC_Max_sampling=0;
			ADC_Min_cnt = 0;
			ADC_CMPOCR = 0;
			ADC_CancelTimer = 0;

			if( Motor_RPM < 4 ) Motor_RPM++;
			else 
			{
				Motor_RPM = 0;
			}	
			break;

		default :	// no defined key
			break;
	}
}


void	Key_Proc1(void)		// 4ms x 15 = 60ms
{
	if(!KeyChattering1())	KeyAnaly1();
	if(!KeyChattering2())	KeyAnaly2();
}

/**/
/*		key data Routine								*/
/*-----------------------------------------------------*/
/*		4:run											*/
/*		2:foot											*/
/*		1:Limit											*/
/**/
char	KeyChattering1(void)
{
	unsigned char x;
	
	if(Wchact1 == 0)	Wchact1 = cKEYCHT1;
	
	x = PI_KEY;
	x >>= 4;
	x &= 0x03;
	x ^= 0x03;
					
	if(x != Wkeyin1)
	{
		Wkeyin1 = x;
		Wchact1 = cKEYCHT1;
	}
return(--Wchact1);
}

void 	KeyAnaly1(void)
{
	keyin1 = Wkeyin1;
		
	switch( keyin1 )
	{
		case 0:		// Not key
//			if( System_Error == 2 )	
//			{
//				System_Error = 0;
//				fRUN = OFF;
//			}	

			Mode_KeyTimer = 0;
			fFOOT = OFF;	
			fAUTOOFF_Init = OFF;
				
			if( Mode_Key == cNORMAL_MODE )	// 누를때만 동작하는모드...
			{	  
				fRUN = OFF;
				if( fKEYFREE1)
				{	
					fAUTOOFF_Init = OFF;
					Start_DlyTimer = cS100MS05S;
					timer1_stop();
				}
			}
			fKEYFREE1 = OFF;
			break;

		case 1:		// Foot(pedal) key
			if( !fREADY || System_Error ){ break; }
			
			if( fCLEAN_Init )
			{
				if( fKEYFREE1) break;
				fKEYFREE1 = ON;
				fCLEAN_Init=OFF;
				fRUN = OFF;
				fFOOT = OFF;
				timer1_stop();
				Start_DlyTimer = cS100MS03S;
				break;
			}
				
			if( fCLEAN_Standby && Disp_CleanTimer )
			{
				fKEYFREE1 = ON;
				fCLEAN_Init = ON;
				fCLEAN_Standby = OFF;
				Disp_CleanTimer=0;
				Clean_Index=0;
				Clean_Timer=0;
				Start_DlyTimer = cS100MS05S;
				PO_RELAY = ON;
				break;
			}	

			if( fAUTOOFF_Init ) break;

			fFOOT = ON;	
			
			if( fKEYFREE1) break;
			fKEYFREE1 = ON;

			if( fRUN )
			{	
				fRUN = OFF;
			}else
			{
				Start_DlyTimer = cS100MS05S;
				timer1_stop();
				PO_RELAY = ON;
				fFLASH_SET = ON;
			}		
			fCHECK = OFF;

			break;
		case 2:		// Run key = 60ms interval
			if( !fREADY || System_Error || fFOOT )
			{ 
				if( !fREADY )
				{
					if( fKEYFREE1) break;
					if( Mode_KeyTimer++ > 50 ) 
					{
						fKEYFREE1 = ON;
						Mode_Key ^= ON;
						Disp_ModeTimer = cS100MS3S;
					}
				}			
				
				break; 
			}
			
			if( fCLEAN_Init )
			{
				if( fKEYFREE1) break;
				fKEYFREE1 = ON;
				fCLEAN_Init=OFF;
				fRUN = OFF;
				fFOOT = OFF;
				timer1_stop();
				Start_DlyTimer = cS100MS03S;
				break;
			}	
			
			if( fCLEAN_Standby && Disp_CleanTimer )
			{
				fKEYFREE1 = ON;
				fCLEAN_Init = ON;
				fCLEAN_Standby = OFF;
				Disp_CleanTimer=0;
				Clean_Index=0;
				Clean_Timer=0;
				Start_DlyTimer = cS100MS05S;
				PO_RELAY = ON;
				break;
			}	

			if( fAUTOOFF_Init ) break;

			if( Mode_Key == cTOGGLE_MODE )
			{	  
				if( fKEYFREE1) break;
				fKEYFREE1 = ON;
				fRUN ^= ON;	
	
				fFLASH_SET = ON;
				Start_DlyTimer = cS100MS05S;
				timer1_stop();
				PO_RELAY = ON;
			}else
			{
				fRUN = ON;	
				
				if( fKEYFREE1) break;
				fKEYFREE1 = ON;
	
				if( fFOOT )
				{	
					fFOOT = OFF;
				}else
				{
					Start_DlyTimer = cS100MS05S;
					timer1_stop();
					PO_RELAY = ON;
					fFLASH_SET = ON;
				}		
			}		
			fCHECK = OFF;
			break;

		default :	// no defined key
			break;
	}
}

/**/
/*		key data Routine								*/
/*-----------------------------------------------------*/
/*		4:run											*/
/*		2:foot											*/
/*		1:Limit											*/
/**/
char	KeyChattering2(void)
{
	unsigned char x;
	
	if(Wchact2 == 0)	Wchact2 = cKEYCHT2;
	
	x = 0;
	if( !PI_LIMIT ) x = 1;
					
	if(x != Wkeyin2)
	{
		Wkeyin2 = x;
		Wchact2 = cKEYCHT2;
	}
return(--Wchact2);
}

void 	KeyAnaly2(void)
{
	keyin2 = Wkeyin2;

	if( keyin2 ) fREADY = ON;
	else 
	{
		fREADY = OFF;
		System_Error = 0;
		fCHECK = OFF;
		fCLEAN_Init=OFF;
	}
}


/*	EOF	*/				
