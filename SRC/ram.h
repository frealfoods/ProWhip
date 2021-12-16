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

EXT idata U_CHAR volatile flag00;
#define	fTime_up		(*(MB_BTF*)&flag00).p0	
#define	fTime10m		(*(MB_BTF*)&flag00).p1	
#define	fTime100m		(*(MB_BTF*)&flag00).p2	
#define	fTime250m		(*(MB_BTF*)&flag00).p3	
#define	fTime500m		(*(MB_BTF*)&flag00).p4	
#define	fBLINK			(*(MB_BTF*)&flag00).p5	
#define	fTOG			(*(MB_BTF*)&flag00).p6	

EXT idata U_CHAR volatile flag01;
#define	fKEYFREE		(*(MB_BTF*)&flag01).p0	
#define	fKEYFREE1		(*(MB_BTF*)&flag01).p1	
#define	fAKEYFREE		(*(MB_BTF*)&flag01).p2	
#define	fKEYTOG			(*(MB_BTF*)&flag01).p3	
#define	fFLASH_SET		(*(MB_BTF*)&flag01).p4	

EXT idata U_CHAR volatile flag02;
#define	fTEMP_Init		(*(MB_BTF*)&flag02).p0	// 
#define	fADC_Init		(*(MB_BTF*)&flag02).p1	
#define	fSYSTEM_Init	(*(MB_BTF*)&flag02).p2	
#define	fBEEP_Init		(*(MB_BTF*)&flag02).p3	
#define	fMODE_Init		(*(MB_BTF*)&flag02).p4	
#define	fKEY_Init		(*(MB_BTF*)&flag02).p5	

EXT idata U_CHAR volatile flag03;
#define	fPOWER_ON		(*(MB_BTF*)&flag03).p0	
#define	fREADY			(*(MB_BTF*)&flag03).p1
#define	fFOOT			(*(MB_BTF*)&flag03).p2
#define	fRUN			(*(MB_BTF*)&flag03).p3
#define	fCHECK			(*(MB_BTF*)&flag03).p4

EXT idata U_CHAR volatile flag04;
#define	fCLEAN_Init		(*(MB_BTF*)&flag04).p0	// 
#define	fCLEAN_Standby	(*(MB_BTF*)&flag04).p1	// Clean mode wait
#define	fSYSTEM_Run		(*(MB_BTF*)&flag04).p2	
#define	fAUTOOFF_Init	(*(MB_BTF*)&flag04).p3	
#define	fMODEKEY_Tog	(*(MB_BTF*)&flag04).p4	// Normal mode : push key누르고 있는동안 모터동작..	

EXT BYTE  	UART_flag;
#define	fTX_BUSY		(*(MB_BTF*)&UART_flag).p0	
#define	fRX_COMPLETED	(*(MB_BTF*)&UART_flag).p1	
#define	fTX_COMPLETED	(*(MB_BTF*)&UART_flag).p2	
#define	fTX_INIT		(*(MB_BTF*)&UART_flag).p3	
#define	fRX_INIT		(*(MB_BTF*)&UART_flag).p4	


/**************************************************************************
User definitions
***************************************************************************/
EXT idata U_CHAR Index;
EXT idata U_CHAR Clean_Index;
EXT idata U_CHAR System_Error;

EXT idata U_CHAR Start_DlyTimer;
EXT idata U_CHAR Mode_Key;			// 0: Normal mode : push key누르고 있는동안 모터동작..	
EXT idata U_CHAR Mode_Key_old;		// 0: Normal mode : push key누르고 있는동안 모터동작..	
EXT idata U_CHAR Mode_KeyTimer;
EXT idata U_CHAR Disp_ModeTimer;

EXT idata U_CHAR Clean_KeyTimer;
EXT idata U_CHAR IS_Checker;

EXT idata U_INT AUTO_Off_Timer;

EXT idata U_INT Clean_Timer;
EXT idata U_CHAR Disp_CleanTimer;

EXT idata U_CHAR DigitRotate;
EXT idata U_CHAR Motor_RPM;
EXT idata U_CHAR Motor_RPM_old;


/* ADC Define	*/
EXT idata unsigned char ADC_Index;
EXT idata unsigned char ADC_Counter;
EXT idata unsigned char ADC_Counters;
EXT idata unsigned char ADC_CancelTimer;

EXT idata U_CHAR ADC_Max_sampling;
EXT idata U_CHAR ADC_Min_sampling;
EXT idata U_CHAR ADC_Min_cnt;

EXT idata unsigned int ADC_OCRResult;		// ADC ocr
EXT idata unsigned int ADC_OCRSum;			// ADC ocr
EXT idata unsigned int ADC_TGOCR;			// ADC ocr
EXT idata unsigned int ADC_CMPOCR;			// ADC ocr

//EXT idata WORD_BTF	_ADC;
//#define	ADC		_ADC.word
//#define	ADCH	_ADC.byte[0]
//#define	ADCL	_ADC.byte[1]

EXT unsigned int ADC_Buf[33];				// ADC data buffer1=Cool Temp 
EXT unsigned int ADC_Buf0[10];				// ADC data buffer1=Cool Temp 
EXT unsigned int ADC_Buf1[10];				// ADC data buffer1=Hot Temp 

/*	===========  Key Define ================= 	*/
EXT idata U_CHAR Wchact,keyin,Wkeyin;
EXT idata U_CHAR Wchact1,keyin1,Wkeyin1;
EXT idata U_CHAR Wchact2,keyin2,Wkeyin2;
EXT idata U_CHAR Dipkeyin;

/* PWM Define	*/
EXT idata unsigned int TargetPWM;					// 

EXT idata U_INT DATA16;
EXT idata U_CHAR DATA_H;
EXT idata U_CHAR DATA_L;
/*
EXT WORD_BTF	_PWM;
#define	PWM		_PWM.word
#define	PWML	_PWM.byte[1]
#define	PWMH	_PWM.byte[0]
*/
/* ADC Define	*/
EXT WORD_BTF	_ADC;
#define	ADC		_ADC.word
#define	fADC	_ADC.bit.b2
#define	ADCL	_ADC.byte[1]
#define	ADCH	_ADC.byte[0]

/*	===========  ADC Define ================= 	*/
/* UART Define	*/
//#define INT_MODE	0	// polling mode
#define INT_MODE	1	// intterupt mode
#define BUF_SIZE	10

#define RXBUF_SIZE	BUF_SIZE
#define TXBUF_SIZE	BUF_SIZE

EXT U_CHAR RX_CHECKSUM;
EXT U_CHAR RX_COMMAND;
EXT U_CHAR RX_DATA;
EXT U_CHAR RX_DATA1;

EXT U_CHAR RX_TEMP;
EXT U_CHAR RX_DATA_counter;
EXT U_CHAR RX_Watchdog;				// 2초동안 Rx신호를 기다린다...
EXT U_CHAR RXCOMM_BUFF[RXBUF_SIZE];

EXT U_CHAR TX_CHECKSUM;
EXT U_CHAR TX_COMMAND;				// Main status(error number)
EXT U_CHAR TX_DATA1;
EXT U_CHAR TX_DELAY;
EXT U_CHAR TX_DATA_counter;
EXT U_CHAR TXCOMM_BUFF[RXBUF_SIZE];

/* Watch time Define	*/
EXT U_CHAR msec;				// ms 
EXT U_CHAR msec5;			// ms 
EXT U_CHAR msec10;			// 10ms
EXT U_CHAR msec100;			// 100ms
EXT U_CHAR sec05;			// 0.5Sec
EXT U_CHAR sec;				// Sec
EXT U_CHAR min;				// min
EXT U_CHAR hour;			// hour
//EXT xdata U_INT AD_buffer[22];			/* Flash remocon ID */
//EXT U_CHAR aadd;			// hour

//====================================================================================
EXT idata U_CHAR flash_status;			// flash status
EXT U_CHAR Read_Data[32];			/* Flash remocon ID */
EXT U_CHAR Write_Data[32];			/* Flash remocon ID */
//EXT U_CHAR dt[32];				/* Flash buffer 	*/

/* EOF */
