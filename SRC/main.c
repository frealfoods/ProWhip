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
	= 수정내용 
	 - 20.10.14 = 이사님 프로그램 2개만 부탁드려요.한개는 과부하 기준 28a. 
	 - 하나는 과부하 기준 28a랑 스피드 1 40% 2 50% 3 56% 4  63% 5 70%
*/

#define	ROOT

#include <intrins.h>
#include "Typech.h"
#include "mc96f8316.h"
#include "define.h"
#include "func.h"
#include "ram.h"
#include "uart.h"

void main(void);

void Main_Proc(void);
void SequenceSort(unsigned int *base, int n);

code unsigned int	d_TARGETPWM1[5] = { cPWM_MAX*0.4,cPWM_MAX*0.45,cPWM_MAX*0.5,cPWM_MAX*0.6,cPWM_MAX*0.65};
code unsigned int	d_TARGETPWM2[5] = { cPWM_MAX*0.5,cPWM_MAX*0.6,cPWM_MAX*0.7,cPWM_MAX*0.8,cPWM_MAX*0.9};

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
 	cli();
 	WDT_init();
	WDT_disable();
	Port_init();
	Clock_init();
	Ram_init();
	
	WDT_enable();
	ADC_init();
	Timer0_init();
	Timer1_init();
	Timer2_init();
#if cRS232C	
	UART_init();
#endif
	timer1_start();
	sei();
		 
    while (1U)
    {
		if (fTime_up)			// 2ms x 2 = 4ms
		{
			fTime_up = OFF;
			switch( Index )
			{
				case 0:
					Main_Proc();
					++Index;
					break;
				case 1:
					WDT_clear();
					Key_Proc1();
					ADC_Proc();
#if cEEPROM	
					EEPROM_Proc();
#endif
					Index = 0;
				default :
					Index = 0;
					break;
			}
		}
	}
}

/**/
/*		Main Procedure routine				       		*/
/**/
//#define PI_DIP1			(P3&0x40)	//(*(MB_BTF*)&P2).b6
//#define PI_DIP2			(P3&0x80)	//(*(MB_BTF*)&P2).b7
/*
	-------------------------------------------------------------
					|	Model(0:Sheo/1:Dress)
	----------------+--------------------------------------------
		PI_DIP1		|	PI_DIP2(Model)
	----------------+--------------------------------------------
	[0]		0		|		0	--> 
	----------------+--------------------------------------------
	[1]		1		|		0	--> 	
	----------------+--------------------------------------------
	[2]		0		|		1	--> 
	----------------+--------------------------------------------
	[3]		1		|		1	--> 
	-------------------------------------------------------------
*/

void Main_Proc(void)
{
	if( fCLEAN_Standby && !Disp_CleanTimer ) fCLEAN_Standby = OFF;
//	AUTO_Off_Timer = 10;		// 연속동작 허락 21.12.6
	if( !fREADY || System_Error || AUTO_Off_Timer > cAUOTOFFTIME )
	{
		timer1_stop();
		PO_RELAY = OFF;
		fCLEAN_Init=OFF;
		fRUN = OFF;
		fFOOT = OFF;
		fSYSTEM_Run = OFF;
		if( AUTO_Off_Timer > cAUOTOFFTIME ) fAUTOOFF_Init = ON;
		fCLEAN_Standby = OFF;
		AUTO_Off_Timer = 0;
		Disp_CleanTimer = 0;
	}else 
	{
		if( fRUN || fFOOT || fCLEAN_Init )
		{	
			fSYSTEM_Run = ON;
			if( Start_DlyTimer == 2 ) 
			{
				timer1_start();
				Start_DlyTimer = 0;
			}
			
			if( !fCLEAN_Init )
			{		
				if( Dipkeyin == 1 ) TargetPWM = d_TARGETPWM2[Motor_RPM];
				else TargetPWM = d_TARGETPWM1[Motor_RPM];
			}else
			{
				switch( Clean_Index )
				{
					case 0:
						Clean_Timer=0;
						TargetPWM = cPWM_MAX*0.5;
						Clean_Index++;
						break;

					case 1:	// Finish Clean mode
						if( Clean_Timer>= cS100MS30S )
						{
							Clean_Timer=0;
							Clean_Index=0;
							fCLEAN_Init=OFF;
							fRUN = OFF;
							fFOOT = OFF;
							Start_DlyTimer = cS100MS03S;
							timer1_stop();
						}	
						break;
					default :
						break;
				}
			}			
			if( DATA16 < TargetPWM ) DATA16+=2;
			else if( DATA16 > TargetPWM ) DATA16-=2;
		
		}else
		{
			if( Start_DlyTimer > 2 ) 
			{
				Start_DlyTimer = 2;
				timer1_stop();
			}else if(!Start_DlyTimer)
			{
				PO_RELAY = OFF;
				Start_DlyTimer = 0;
				fSYSTEM_Run = OFF;
				fCLEAN_Init = OFF;
			}		  	
		}		
	}					

	T1BDR = DATA16;

//	T1BDRH = DATA_H;  	// duty High
//	T1BDRL = DATA_L;  	// duty Low
	
#if cRS232C	

	if( fRX_COMPLETED && !TX_DELAY )
	{
		fRX_COMPLETED = OFF;
		Comm_Proc();
	}
#endif
}

/*	==============================================================================	*/
/*	==============================================================================	*/
/*	==============================================================================	*/
/*	=========	communication data format	=============	*/
/*	1Byte = [0xAE] cHEADER_CODE								*/
/*	2Byte = [0xXX] Command									*/
/*	3Byte = [0xXX] data[0x55 = Rx Comm ok / 0x49 = err		*/
/*	4Byte = [0xXX] checksum(1B+2B+3B)						*/
/*	=====================================================	*/
/*	==============================================================================	*/
/*	==============================================================================	*/
/*	==============================================================================	*/
#if cRS232C
void	Comm_Proc(void)
{
	unsigned char i;
	
	for(i=0;i<BUF_SIZE;i++)
	{
		TXCOMM_BUFF[i] = 0x89;
	}	
/*	=============================== 	Transmit	==============================	*/
	TX_CHECKSUM = 0;
	TXCOMM_BUFF[0] = cHEADER_CODE;
	TX_CHECKSUM += cHEADER_CODE;

	TXCOMM_BUFF[1] = TX_COMMAND;
	TX_CHECKSUM += TX_COMMAND;

	TXCOMM_BUFF[2] = TX_DATA1;
	TX_CHECKSUM += TX_DATA1;

	TX_DATA_counter = 0;
	TXCOMM_BUFF[3] = TX_CHECKSUM;
	UARTCR2|=(TXCIE+UDRIE);	// TX interrtup enable
}
#endif

/*	==============================================================================	*/
/*	======================	AD Conversion routine ================================	*/
/*	==============================================================================	*/

#define cADCOCR		2		// [ ch=2/OCR ]
#define cADCRPM		3		// [ ch=3/RPM sensor]
#define cADCTMP		4		// [ ch=4/Temp sensor]

#define	cADCSOFFSET	 0
/*
	0.45V = 6.38A = 92
	0.46V = 6.52A = 94
	0.60V = 8.50A = 123
	1.45V = 20.00A = 297
*/
//#define cADCOCRL0S	 55+cADCSOFFSET		// [ 3.8A ]
#define cADCOCRL0S4A	 58+cADCSOFFSET		// [ 4A ]
#define cADCOCRL0S5A	 73+cADCSOFFSET		// [ 4A ]
#define cADCOCRL0S6A	 86+cADCSOFFSET		// [ 6A ]
#define cADCOCRL0S7A	100+cADCSOFFSET		// [ 7A ]
#define cADCOCRL0S8A	115+cADCSOFFSET		// [ 8A ]
#define cADCOCRL0S9A	130+cADCSOFFSET		// [ 9A ]
#define cADCOCRL0S10A	144+cADCSOFFSET		// [ 10A ]
#define cADCOCRL0S11A	159+cADCSOFFSET		// [ 11A ]
#define cADCOCRL0S12A	173+cADCSOFFSET		// [ 12A ]
#define cADCOCRL0S13A	188+cADCSOFFSET		// [ 13A ]
#define cADCOCRL0S14A	202+cADCSOFFSET		// [ 14A ]
//#define cADCOCRL0S	 65+cADCSOFFSET		// [ 4.5A ]
//#define cADCOCRL0S	 72+cADCSOFFSET		// [ 5.0A ]
//#define cADCOCRL0S	 79+cADCSOFFSET		// [ 5.5A ]

#define cADCOCRMAX	476					// [ 1.8V ]= 33A = 370

code unsigned int	ADC_MOTCURRENT_DIP_TB[6]  = { cADCOCRL0S6A,cADCOCRL0S7A,cADCOCRL0S8A,cADCOCRL0S10A,cADCOCRL0S11A,cADCOCRL0S8A};
code unsigned int	ADC_MOTCURRENT_DIP_TB1[6] = { cADCOCRL0S7A,cADCOCRL0S8A,cADCOCRL0S9A,cADCOCRL0S11A,cADCOCRL0S12A,cADCOCRL0S9A};

/*
	V = (i(10A) x r(0.015)) * 4.7 = 0.705 = 144
	V = (i(12A) x r(0.015)) * 4.7 = 0.846 = 173
	V = (i(14A) x r(0.015)) * 4.7 = 0.987 = 202
	V = (i(25A) x r(0.015)) * 4.7
	V = (i(28A) x r(0.015)) * 4.7 = 1.974 = 404
	V = (i(30A) x r(0.015)) * 4.7 = 1.974 = 433
	V = (i(33A) x r(0.015)) * 4.7 = 2.326 = 433
*/

/*
//순차 정렬(Sequential Sort)
 
#define SWAP(a,b)  {int t; t = a; a=b; b=t;}//a와 b를 교환
 
 
void SequenceSort(int *base, int n);
int main(void)
{
    int arr[10] = { 9,4,3,10,5,8,7,6,2,1 };
    SequenceSort(arr, 10);
    return 0;
}
 
//정렬 과정을 출력하기 위한 함수입니다.
void SequenceSort(int *base, int n)
{
    int i, j;
    for (i = 0; i<n; i++)
    {
        for (j = i; j<n; j++)
        {
            if (base[i]>base[j])		//앞쪽 원소가 더 크면
            {
                SWAP(base[i], base[j]);	//교환
            }
        }
    }
}
*/

#define SWAP(a,b)  {unsigned int t; t = a; a=b; b=t;}	//a와 b를 교환
 
void SequenceSort(unsigned int *base, int n)
{
    int i, j;
    for (i = 0; i<n; i++)
    {
        for (j = i; j<n; j++)
        {
            if (base[i]>base[j])		//앞쪽 원소가 더 크면
            {
                SWAP(base[i], base[j]);	//교환
            }
        }
    }
}

unsigned int ADC_Cal(unsigned int *adbuff)
{
    unsigned char  k,m=0;
    unsigned int wad_data,j=0;
    
	j = 0xf000;
	for(k=0;k<6;k++)
	{   
		if(adbuff[k] < j)       // Min data drop
		{   
			j = *(adbuff+k);
	    	m = k;
		}
	}
	adbuff[m] = 0;
	
	j = 0;
	for(k=0;k<6;k++)
	{   
		if(adbuff[k] > j)  		// Max data drop
	    {   
			j = *(adbuff+k);
	        m = k;                	
	    }                           
	}                               
	adbuff[m] = 0;                 
	
	j = 0;
	for(k=0;k<6;k++)  j += *(adbuff+k);
	wad_data = j>>2;			// 4개 값 평균 구하기..
	
return(wad_data);
}	

void ADC_Proc(void)			// 1read cycle = 4ms
{
	unsigned int adc;
	if( Start_DlyTimer || System_Error ) 
	{
		ADC_Index=0;
		ADC_OCRSum=0;
		ADC_Min_sampling=0;
		ADC_Max_sampling=0;
		ADC_Min_cnt = 0;
		ADC_CMPOCR = 0;
		ADC_CancelTimer = 0;
		return;
	}	
		
	if( ADC_Index < 6 ) 		// Conversion time cycle = 4ms x7 = 28ms
	{
		ADC_start(cADCOCR);
		adc = ADC_read();  		// ADC 6회 읽기..
//		adc = 0x123;
		ADC_Buf0[ADC_Index] = adc;
		ADC_Index++;

	}else if( ADC_Index == 6 ) 	// Conversion time cycle = 28ms
	{		
		ADC_Index = 0;
		adc = ADC_Cal(ADC_Buf0);
		ADC_Buf[ADC_Counter] = adc;
		ADC_OCRSum += adc;
		
		if(++ADC_Counter > 15)	// Conversion time cycle = 28ms x 32 = 0.896ms
		{
			ADC_Counter=0;

		    SequenceSort(ADC_Buf, 16);
		    ADC_OCRResult = ADC_Buf[8];

			if( fSYSTEM_Run )
			{
				if( Dipkeyin != 4 )
				{	
					ADC_TGOCR = ADC_MOTCURRENT_DIP_TB[Motor_RPM];
					if( fCLEAN_Init ) ADC_TGOCR = ADC_MOTCURRENT_DIP_TB[5];
				}else
				{
					ADC_TGOCR = ADC_MOTCURRENT_DIP_TB1[Motor_RPM];
					if( fCLEAN_Init ) ADC_TGOCR = ADC_MOTCURRENT_DIP_TB1[5];
				}		
				
				if( ADC_CancelTimer > cS100MS1S )
				{	
					if( ADC_OCRResult > ADC_CMPOCR ) ADC_CMPOCR = ADC_OCRResult;
					if( ADC_OCRResult > cADCOCRL0S5A )
					{
						if( ADC_OCRResult < (ADC_CMPOCR- cADCOCRL0S5A) ) System_Error = 1;
					}			
				}
				
				if( ADC_CancelTimer > cS100MS4S )
				{	
					ADC_CancelTimer = cS100MS5S;
					if( ADC_OCRResult < ADC_TGOCR ) ADC_Min_sampling++;
				}else 
				{
					ADC_Min_sampling = 0;
					ADC_CMPOCR = 0;
				}	
			}else
			{
				ADC_Min_sampling=0;
				ADC_CancelTimer = 0;
				ADC_CMPOCR = 0;
			}				

			if( ADC_Min_cnt++ > 7 ) 
			{
				if( ADC_Min_sampling > 3 ) 
				{
					System_Error = 1;
//					System_Error = 2;
//					fCHECK = ON;
				}		
				
				ADC_Min_cnt = 0;
				ADC_Min_sampling = 0;
			}	
		
			if( Dipkeyin != 1 )
			{	
				if( ADC_OCRResult > cADCOCRMAX ) ADC_Max_sampling++;
				else ADC_Max_sampling = 0;
						 
				if( ADC_Max_sampling > 6 ) 
				{
					ADC_Max_sampling = 0;
					System_Error = 1;
				}	
			}
		}
	}
}

void delay_xms(U_CHAR time)
{
	U_CHAR i;
	while(time != 0)
	{
		for(i = 0; i<150; i++)
		{
			NOP();
			NOP();
			NOP();
		}
		time--;
	}

}

