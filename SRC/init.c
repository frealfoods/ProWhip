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

// WTDR
#define WTCL  7
#define WDTEN 7

void WDT_enable(void)
{
	WDTCR|=(1<<WDTEN); // wdt enable
}

void WDT_disable(void)
{
	WDTCR&=~(1<<WDTEN); // wdt disable
}

/* =====================	Watch dog define ============	*/
void WDT_clear()
{
	WDTCR |= 0x20;  	// Clear Watch-dog timer
}

void WDT_init()
{
	// initialize Watch-dog timer
	WDTDR = 0x01;   	// period
	WDTCR = 0xC2;   	// setting
	WDT_clear();
}

/* =====================	ADC define ============	*/

#define ADST		0x40		// ADC conversion start
#define AFLAG		0x10		// ADC conversion completed?

unsigned int ADC_read()
{
	unsigned int adcVal,dd=0x40;;
	
	while(!(ADCCRL & AFLAG)&& --dd);	// wait ADC busy
	adcVal = (ADCDRH << 8) | ADCDRL;	// read ADC
	return	adcVal>>2;					// 12bit>>2 = 10bit
}

void ADC_init()
{
	// initialize A/D convertor
	ADCCRL = 0x80;  	// setting
	ADCCRH = 0x07;  	// trigger source, alignment, frequency
	ADWCRL = 0x00;  	// Wake-up enable Low
	ADWCRH = 0x00;  	// Wake-up enable High
	ADWRCR0 = 0x00; 	// Wake-up R selection
	ADWRCR1 = 0x00; 	// Wake-up R selection
	ADWRCR2 = 0x00; 	// Wake-up R selection
	ADWRCR3 = 0x00; 	// Wake-up R selection
}

void ADC_start(unsigned char ch)
{
	// start A/D convertor
	ADCCRL = (ADCCRL & 0xf0) | (ch & 0x0f);	// select channel
	ADCCRL |= ADST;   						// start ADC
}


/* =====================	Timer0 interrupt deine ============	*/
// T0CR
#define T0EN	7
#define T1EN	7
#define T2EN	7
#define T0MS0	4
#define T0CK0	1
#define T0CC	0

void Timer0_init()
{
	// initialize Timer0
	// 8bit timer, period = 2.000000mS
	T0CR = 0x88;    	// timer setting
	T0DR = 0xF9;    	// period count
	IE2 |= 0x02;    	// Enable Timer0 interrupt
	T0CR |= 0x01;   	// clear counter
}

void Timer1_init()
{
	// initialize Timer1
	// 16bit PWM, period = 0.066687mS ( 14995.313964Hz )
	//     PWM duty = 49.953140%
//	T1CRH = 0x20;   	// PWM setting High, 1 shot mode
	T1CRH |= 0x30;		// PWM repeat mode
	T1CRL = 0xC0;   	// PWM setting Low
	T1BDRH = 0x02;  	// duty High
	T1BDRL = 0x16;  	// duty Low
	T1ADRH = 0x04;  	// period count High
	T1ADRL = 0x2A;  	// period count Low
	timer1_stop();
}

void timer1_start(void)
{
	DATA16 = cPWM_INIT;
	PO_MOTORPWM  = CLR;	// LED Pwm OFF 
	T1CRH|=(1<<T1EN); 	// Timer1(16bit)  enable
}

void timer1_stop(void)
{
	DATA16 = cPWM_INIT;
	PO_MOTORPWM  = CLR;   // LED Pwm OFF 
	T1CRH&=~(1<<T1EN);	// Timer1(16bit)  disable
}

void Timer2_init()
{
	// initialize Timer2
	// 16bit timer, period = 0.500000mS
	T2CRH = 0x00;   	// timer setting High
	T2CRL = 0xC0;   	// timer setting Low
	T2ADRH = 0x1F;  	// period count High
	T2ADRL = 0x3F;  	// period count Low
	IE2 |= 0x08;    	// Enable Timer2 interrupt
	T2CRH |= 0x80;  	// enable counter
}

/* =====================	OSC stabilization time ============	*/
void Clock_init()
{
	// internal RC clock (16.000000MHz)
	//Xout_Xin function setting

	/*--- Oscillator Control ---------------------------------------------------------------- 
  	 * OSCCR 	: 0000 0000 = 0x00			: Oscillator Control Register
 	 * OSCCR	= 0x00;			// initial int_1Mhz,int_osc enable,main_osc enable,sub_osc enalbe 	 
  	 *-----------------------------------------------------------------------------------
  	 */
	OSCCR =0	//Oscillator Control Register
		|(5<<3)	//0:int_0_5Mhz, 1:int_1Mhz, 2:int_2Mhz, 3: int_4Mhz	4:int_8Mhz, 5: int_16Mhz 
		|(0<<2)	//0:int_rc_osc enable, 1:int_rc_osc disable	
		|(0<<1)	//0:main_osc disable, 1:main_osc enable
		|(0<<0)	//0:sub_osc disable, 1:sub_osc enable
		//|(1<<0)	//0:sub_osc disable, 1:sub_osc enable
		;
	BITCR=(1<<3)|(1<<0);	// BIT counter clear!!
	while((BITCR&0x80)==0);	// BIT 안정화 16ms wait time @ int_osc 1Mhz
	
	/*--- Set System and Clock Control ------------------------------------------------------ 
  	 * SCCR 	: 0000 0000 = 0x00			: System and Clock Control Register.
  	 * SCCR	= 0x01;					// -,-,-,-,-,-,sclk1,sclk0
  	 *-----------------------------------------------------------------------------------
  	 */
	SCCR =0		//System and Clock Control Register
		|(0<<0)	//0:INT_RC OSC, 1:external OSC, 2:external sub_osc[1]
		;	
}

void Port_init()
{
	// initialize ports
	//   1 : P35      out relay
	//   5 : RXD      in  rxd
	//   6 : TXD      out txd
	//   9 : P24      out led5
	//  10 : P23      out led4
	//  11 : P22      out led3
	//  12 : P21      out led2
	//  13 : P20      out led1
	//  14 : P17      out com2
	//  15 : P16      out com1
	//  16 : P15      in  run switch
	//  17 : P14      in  foot switch
	//  18 : P13      in  limit switch
	//  19 : PWM1o    out motor pwm
	//  24 : AN4      in  adc temp
	//  25 : AN3      in  adc rpm
	//  26 : AN2      in  adc ocr
	//  31 : P37      in  dip1
	//  32 : P36      in  dip2
	
	P0IO = 0xE3;    	// direction
	P0PU = 0x00;    	// pullup
	P0OD = 0x00;    	// open drain
	P03DB = 0x00;   	// bit7~6(debounce clock), bit5~0=P35,P06~02 debounce
	P0   = 0x00;    	// port initial value

	P1IO = 0xC7;    	// direction
	P1PU = 0x38;    	// pullup
	P1OD = 0x38;    	// open drain
	P12DB = 0x08;   	// debounce : P23~20, P13~10
	P1   = 0x00;    	// port initial value

	P2IO = 0xFF;    	// direction
	P2PU = 0x00;    	// pullup
	P2OD = 0x00;    	// open drain
	P2   = 0x00;    	// port initial value

	P3IO = 0x3D;    	// direction
	P3PU = 0xC2;    	// pullup
	P3OD = 0xC2;    	// open drain
	P3   = 0x00;    	// port initial value

	// Set port functions
	P0FSR = 0x38;   	// P0 selection
	P1FSRH = 0x00;  	// P1 selection High
	P1FSRL = 0x08;  	// P1 selection Low
	P2FSR = 0x00;   	// P2 selection
	P3FSR = 0x01;   	// P3 selection

	LVRCR = 0x00;		//LVREN[0]= 0: LVR enable, 1:LVR disable	 //1.6v LVR Voltage Select
}

/**/
/*			 Ram initalize routine		       			*/
/**/
void Ram_init(void)
{
	unsigned int i;
	
	i = 20000;
	
	delay_xms(200);

	do{
		if( !PI_JIG ) ++i;
		else --i;
		WDT_clear();
		if( i>40000 || i<100 ) break;
	}while(1);

	Motor_RPM_old = Motor_RPM = 0;
	Mode_Key_old = Mode_Key = 0;;
	Clean_KeyTimer=0;
	IS_Checker = 0;
	fKEY_Init=OFF;
	fCLEAN_Init=OFF;
	Disp_ModeTimer = cS100MS3S;
	Mode_Key = cNORMAL_MODE;
	Dipkeyin=0;

/*
	-------------------------------------------------------------
					|	Model(0:Sheo/1:Dress)
	----------------+--------------------------------------------
		PI_DIP1		|	PI_DIP2(Model)
	----------------+--------------------------------------------
	[0x00]	0		|		0	--> Normal mode
	----------------+--------------------------------------------
	[0x01]	0		|		1	--> Speed change 80->90%	
	----------------+--------------------------------------------
	[0x02]	1		|		0	--> Test mode(무부하 감지 삭제)
	----------------+--------------------------------------------
	[0x04]	1		|		1	--> x
	-------------------------------------------------------------
*/

	if( PI_DIP1 )	// dip init value = 3;
	{
		if( PI_DIP2 ) Dipkeyin = 0x00;
		else Dipkeyin = 0x01;	
	}else
	{				
		if( PI_DIP2 ) Dipkeyin = 0x02;
		else Dipkeyin = 0x04;	
	}
	
	if( Dipkeyin & 0x02 ) IS_Checker = 1;	// test mode

#if cEEPROM
	Lflash_read(cSector);
	if( Read_Data[0] == 0x55 ) 
	{
		Motor_RPM = Read_Data[1];
		Motor_RPM_old = Motor_RPM;
		Mode_Key = Read_Data[2];
	}
#endif
	
}


/* EOF	*/
