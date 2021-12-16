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


#define	ON		1
#define	OFF		0

#define	TON		0
#define	TOFF	1

#define	SET		1
#define	CLR		0

#define	OK		0
#define	ERROR	1

#define	HIGH	1
#define	LOW		0

#define	START	1
#define	STOP	0

#define	ENABLE	1
#define	DISABLE	0

#define  TRUE  	1
#define	 FALSE 	0

#define	STBY	0
#define	NONSTBY	1

/* ===================== MACRO	===========================	*/
#define cEEPROM		1
#define	cSector		510

/* ========================================================	*/

#define	cRS232C	0		

#define	BITF	0x80

#define cli()	do{IE &= ~0x80;}while(0)
#define sei()	do{IE |=  0x80;}while(0)

#define NOP()	_nop_()

/***********************************************************************************************************************
User definitions
***********************************************************************************************************************/
enum SYS_SEQUENCE{
	cNORMAL_MODE = 0, 
	cTOGGLE_MODE, 
	cETC, 
};

#define	c1MIN			60
#define	cAUOTOFFTIME	c1MIN * 2

#define	cPWM_INIT	200
#define	cPWM_MAX	1060

#define cCLOSE	1
#define cOPEN	0

#define cERR_NO1	1	// Sensor open err
#define cERR_NO2	2	// Sensor short err
#define cERR_NO3	3	// Sensor or Heater err
#define cERR_NO4	4

/*	============= I/O PORT DEFINE ======================	*/
// IO Prot define
#define PI_JIG			(P2&0x01)	//(*(MB_BTF*)&P2).b6

#define PI_DIP1	(P3&0x80)	//P37 - dip input1
#define PI_DIP2	(P3&0x40)	//P36 - dip input2

#define PI_TACTKEY	(P2&0x10)	//P24 - Key input
#define PI_KEY		P1			//P13,4,5 - Key input
#define PI_RUN		(P1&0x20)	//P15 - Run switch
#define PI_FOOT		(P1&0x10)	//P14 - Foot switch
#define PI_LIMIT	(P1&0x08)	//P13 - Limit switch(connection check)

#define	PO_RELAY	P35			//Relay
#define PO_MOTORPWM	P12			//LED PWM

#define	PO_LED		P2			//LED SEG
#define	PO_LED1		P20			//LED SEG1
#define	PO_LED2		P21			//LED SEG1
#define	PO_LED3		P22			//LED SEG1
#define	PO_LED4		P23			//LED SEG1
#define	PO_LED5		P24			//LED SEG1

#define	PO_COM1		P16			//LED COM1
#define	PO_COM2		P17			//LED COM2



/*	====================================================	*/
#define	cS10MS020mS		 2			//  2 x 10ms =  20mssec
#define	cS10MS050mS		 5			//  5 x 10ms =  50mssec
#define	cS10MS100mS		10			// 10 x 10ms = 100mssec
#define	cS10MS150mS		15			// 15 x 10ms = 150mssec
#define	cS10MS200mS		20			// 20 x 10ms = 200mssec
#define	cS10MS300mS		30			// 30 x 10ms = 300mssec
#define	cS10MS400mS		40			// 40 x 10ms = 400mssec
#define	cS10MS500mS		50			// 50 x 10ms = 500mssec
#define	cS10MS700mS		70			// 70 x 10ms = 700mssec
#define	cS10MS1S		100			// 100 x 10ms = 1sec
#define	cS10MS2S		200			// 200 x 10ms = 2sec

#define	cS100MS03S		3			//   3 x 100ms = 0.3sec
#define	cS100MS05S		5			//   5 x 100ms = 0.5sec
#define	cS100MS1S		10			//  10 x 100ms = 1sec
#define	cS100MS2S		20			//  20 x 100ms = 2sec
#define	cS100MS3S		30			//  30 x 100ms = 3sec
#define	cS100MS4S		40			//  40 x 100ms = 4sec
#define	cS100MS5S		50			//  50 x 100ms = 5sec
#define	cS100MS6S		60			//  60 x 100ms = 6sec
#define	cS100MS7S		70			//  70 x 100ms = 7sec
#define	cS100MS10S		100			// 100 x 100ms = 10sec
#define	cS100MS15S		150			// 150 x 100ms = 15sec
#define	cS100MS20S		200			// 200 x 100ms = 20sec
#define	cS100MS30S		300			// 300 x 100ms = 30sec

#define	cS05S1SEC 	      2			//     2 x 0.5sec =  1sec
#define	cS05S2SEC 	      4			//     4 x 0.5sec =  2sec
#define	cS05S5SEC 	     10			//    10 x 0.5sec =  5sec
#define	cS05S7SEC 	     14			//    14 x 0.5sec =  7sec
#define	cS05S10SEC 	     20			//    20 x 0.5sec = 10sec
#define	cS05S12SEC 	     24			//    24 x 0.5sec = 12sec
#define	cS05S15SEC 	     30			//    30 x 0.5sec = 15sec
#define	cS05S20SEC 	     40			//    40 x 0.5sec = 20sec
#define	cS05S30SEC 	     60			//    60 x 0.5sec = 30sec
#define	cS05S1MIN 	    120			//   120 x 0.5sec = 1MIN
#define	cS05S2MIN 	    240			//   240 x 0.5sec = 2MIN
#define	cS05S3MIN 	    360			//   360 x 0.5sec = 3MIN
#define	cS05S15MIN 	   1919			//  1800 x 0.5sec = 15MIN
#define	cS05S30MIN 	   3600			//  3600 x 0.5sec = 30MIN
#define	cS05S1HOUR 	   7200			//  7200 x 0.5sec = 1hour
#define	cS05S2HOUR 	  14400			// 14400 x 0.5sec = 2hour
#define	cS05S2H30M 	  18000			// 18000 x 0.5sec = 2h30M
#define	cS05S3HOUR 	  21600			// 21600 x 0.5sec = 3hour

#define	cS1S2SEC 	    2			//    2 x 1sec = 2sec
#define	cS1S5SEC 	    5			//    5 x 1sec = 5sec
#define	cS1S10SEC 	    10			//   10 x 1sec = 10sec
#define	cS1S15SEC 	    15			//   15 x 1sec = 15sec
#define	cS1S30SEC 	    30			//   60 x 1sec = 1MIN
#define	cS1S1MIN 	    60			//   60 x 1sec = 1MIN
#define	cS1S2MIN 	    60*2		//   60 x 1sec = 1MIN
#define	cS1S3MIN 	    60*3		//   60 x 1sec = 1MIN
#define	cS1S5MIN 	    60*5		//   60 x  5 = 5MIN
#define	cS1S15MIN 	    60*15		//   60 x 15 = 15MIN
#define	cS1S20MIN 	    60*20		//   60 x 20 = 20MIN
#define	cS1S30MIN 	    60*30		//   60 x 30 = 30MIN
#define	cS1S60MIN 	    60*60		//   60 x 60 = 60MIN
#define	cS1S120MIN 	    60*120		//   60 x 120 = 120MIN
#define	cS1S1H30MIN 	(60*60)+cS1S30MIN	// 1시간30분..
#define	cS1S3H00MIN 	(60*180)			// 3시간00분..
#define	cS1S4H30MIN 	(60*240)+cS1S30MIN	// 4시간30분..

/* Base Time rate : min	*/
#define	cS1M2M		 	2			// 3 x 1min = 3min
#define	cS1M3M		 	3			// 3 x 1min = 3min
#define	cS1M5M		 	5			// 5 x 1min = 5min
#define	cS1M7M		 	7			// 7 x 1min = 7min
#define	cS1M10M		 	10			// 10 x 1min = 10min
#define	cS1M20M		 	20			// 20 x 1min = 20min
#define	cS1M30M		 	30			// 30 x 1min = 30min
#define	cS1M40M		 	40			// 30 x 1min = 30min
#define	cS1M1H		 	60			// 60 x 1min = 1hour
#define	cS1M1H30M		90			// 60 x 1min = 1hour30min
#define	cS1M2H			(cS1M1H*2)	// 180 x 1min = 2hour30min
#define	cS1M2H30M		150			// 180 x 1min = 2hour30min
#define	cS1M3H			(cS1M1H*3)	// 180 x 1min = 2hour30min
#define	cS1M4H			(cS1M1H*4)	// 180 x 1min = 2hour30min
#define	cS1M6H			(cS1M1H*6)	// 180 x 1min = 2hour30min

#define cTIMEMIN	cS1S60S
#define cTIMEMAX	10*cS1S60S

#define cRUNTIME				cS1M2H
#define cSYNCMOTOR_ONTIME		cS1M40M
#define cSYNCMOTOR_OFFTIME		cS1M30M
#define cSYNCMOTOR_OFFTIMEEN	cS1M20M

//----------------------------------------------------------------------------------
// 		Number characters
//----------------------------------------------------------------------------------
#define 	_0000_0000	0x00
#define 	_0000_0001	0x01
#define 	_0000_0010	0x02
#define 	_0000_0011	0x03
#define 	_0000_0100	0x04
#define 	_0000_0101	0x05
#define 	_0000_0110	0x06
#define 	_0000_0111	0x07
#define 	_0000_1000	0x08
#define 	_0000_1001	0x09
#define 	_0000_1010	0x0A
#define 	_0000_1011	0x0B
#define 	_0000_1100	0x0C
#define 	_0000_1101	0x0D
#define 	_0000_1110	0x0E
#define 	_0000_1111	0x0F
#define 	_0001_0000	0x10
#define 	_0001_0001	0x11
#define 	_0001_0010	0x12
#define 	_0001_0011	0x13
#define 	_0001_0100	0x14
#define 	_0001_0101	0x15
#define 	_0001_0110	0x16
#define 	_0001_0111	0x17
#define 	_0001_1000	0x18
#define 	_0001_1001	0x19
#define 	_0001_1010	0x1A
#define 	_0001_1011	0x1B
#define 	_0001_1100	0x1C
#define 	_0001_1101	0x1D
#define 	_0001_1110	0x1E
#define 	_0001_1111	0x1F
#define 	_0010_0000	0x20
#define 	_0010_0001	0x21
#define 	_0010_0010	0x22
#define 	_0010_0011	0x23
#define 	_0010_0100	0x24
#define 	_0010_0101	0x25
#define 	_0010_0110	0x26
#define 	_0010_0111	0x27
#define 	_0010_1000	0x28
#define 	_0010_1001	0x29
#define 	_0010_1010	0x2A
#define 	_0010_1011	0x2B
#define 	_0010_1100	0x2C
#define 	_0010_1101	0x2D
#define 	_0010_1110	0x2E
#define 	_0010_1111	0x2F
#define 	_0011_0000	0x30
#define 	_0011_0001	0x31
#define 	_0011_0010	0x32
#define 	_0011_0011	0x33
#define 	_0011_0100	0x34
#define 	_0011_0101	0x35
#define 	_0011_0110	0x36
#define 	_0011_0111	0x37
#define 	_0011_1000	0x38
#define 	_0011_1001	0x39
#define 	_0011_1010	0x3A
#define 	_0011_1011	0x3B
#define 	_0011_1100	0x3C
#define 	_0011_1101	0x3D
#define 	_0011_1110	0x3E
#define 	_0011_1111	0x3F
#define 	_0100_0000	0x40
#define 	_0100_0001	0x41
#define 	_0100_0010	0x42
#define 	_0100_0011	0x43
#define 	_0100_0100	0x44
#define 	_0100_0101	0x45
#define 	_0100_0110	0x46
#define 	_0100_0111	0x47
#define 	_0100_1000	0x48
#define 	_0100_1001	0x49
#define 	_0100_1010	0x4A
#define 	_0100_1011	0x4B
#define 	_0100_1100	0x4C
#define 	_0100_1101	0x4D
#define 	_0100_1110	0x4E
#define 	_0100_1111	0x4F
#define 	_0101_0000	0x50
#define 	_0101_0001	0x51
#define 	_0101_0010	0x52
#define 	_0101_0011	0x53
#define 	_0101_0100	0x54
#define 	_0101_0101	0x55
#define 	_0101_0110	0x56
#define 	_0101_0111	0x57
#define 	_0101_1000	0x58
#define 	_0101_1001	0x59
#define 	_0101_1010	0x5A
#define 	_0101_1011	0x5B
#define 	_0101_1100	0x5C
#define 	_0101_1101	0x5D
#define 	_0101_1110	0x5E
#define 	_0101_1111	0x5F
#define 	_0110_0000	0x60
#define 	_0110_0001	0x61
#define 	_0110_0010	0x62
#define 	_0110_0011	0x63
#define 	_0110_0100	0x64
#define 	_0110_0101	0x65
#define 	_0110_0110	0x66
#define 	_0110_0111	0x67
#define 	_0110_1000	0x68
#define 	_0110_1001	0x69
#define 	_0110_1010	0x6A
#define 	_0110_1011	0x6B
#define 	_0110_1100	0x6C
#define 	_0110_1101	0x6D
#define 	_0110_1110	0x6E
#define 	_0110_1111	0x6F
#define 	_0111_0000	0x70
#define 	_0111_0001	0x71
#define 	_0111_0010	0x72
#define 	_0111_0011	0x73
#define 	_0111_0100	0x74
#define 	_0111_0101	0x75
#define 	_0111_0110	0x76
#define 	_0111_0111	0x77
#define 	_0111_1000	0x78
#define 	_0111_1001	0x79
#define 	_0111_1010	0x7A
#define 	_0111_1011	0x7B
#define 	_0111_1100	0x7C
#define 	_0111_1101	0x7D
#define 	_0111_1110	0x7E
#define 	_0111_1111	0x7F
#define 	_1000_0000	0x80
#define 	_1000_0001	0x81
#define 	_1000_0010	0x82
#define 	_1000_0011	0x83
#define 	_1000_0100	0x84
#define 	_1000_0101	0x85
#define 	_1000_0110	0x86
#define 	_1000_0111	0x87
#define 	_1000_1000	0x88
#define 	_1000_1001	0x89
#define 	_1000_1010	0x8A
#define 	_1000_1011	0x8B
#define 	_1000_1100	0x8C
#define 	_1000_1101	0x8D
#define 	_1000_1110	0x8E
#define 	_1000_1111	0x8F
#define 	_1001_0000	0x90
#define 	_1001_0001	0x91
#define 	_1001_0010	0x92
#define 	_1001_0011	0x93
#define 	_1001_0100	0x94
#define 	_1001_0101	0x95
#define 	_1001_0110	0x96
#define 	_1001_0111	0x97
#define 	_1001_1000	0x98
#define 	_1001_1001	0x99
#define 	_1001_1010	0x9A
#define 	_1001_1011	0x9B
#define 	_1001_1100	0x9C
#define 	_1001_1101	0x9D
#define 	_1001_1110	0x9E
#define 	_1001_1111	0x9F
#define 	_1010_0000	0xA0
#define 	_1010_0001	0xA1
#define 	_1010_0010	0xA2
#define 	_1010_0011	0xA3
#define 	_1010_0100	0xA4
#define 	_1010_0101	0xA5
#define 	_1010_0110	0xA6
#define 	_1010_0111	0xA7
#define 	_1010_1000	0xA8
#define 	_1010_1001	0xA9
#define 	_1010_1010	0xAA
#define 	_1010_1011	0xAB
#define 	_1010_1100	0xAC
#define 	_1010_1101	0xAD
#define 	_1010_1110	0xAE
#define 	_1010_1111	0xAF
#define 	_1011_0000	0xB0
#define 	_1011_0001	0xB1
#define 	_1011_0010	0xB2
#define 	_1011_0011	0xB3
#define 	_1011_0100	0xB4
#define 	_1011_0101	0xB5
#define 	_1011_0110	0xB6
#define 	_1011_0111	0xB7
#define 	_1011_1000	0xB8
#define 	_1011_1001	0xB9
#define 	_1011_1010	0xBA
#define 	_1011_1011	0xBB
#define 	_1011_1100	0xBC
#define 	_1011_1101	0xBD
#define 	_1011_1110	0xBE
#define 	_1011_1111	0xBF
#define 	_1100_0000	0xC0
#define 	_1100_0001	0xC1
#define 	_1100_0010	0xC2
#define 	_1100_0011	0xC3
#define 	_1100_0100	0xC4
#define 	_1100_0101	0xC5
#define 	_1100_0110	0xC6
#define 	_1100_0111	0xC7
#define 	_1100_1000	0xC8
#define 	_1100_1001	0xC9
#define 	_1100_1010	0xCA
#define 	_1100_1011	0xCB
#define 	_1100_1100	0xCC
#define 	_1100_1101	0xCD
#define 	_1100_1110	0xCE
#define 	_1100_1111	0xCF
#define 	_1101_0000	0xD0
#define 	_1101_0001	0xD1
#define 	_1101_0010	0xD2
#define 	_1101_0011	0xD3
#define 	_1101_0100	0xD4
#define 	_1101_0101	0xD5
#define 	_1101_0110	0xD6
#define 	_1101_0111	0xD7
#define 	_1101_1000	0xD8
#define 	_1101_1001	0xD9
#define 	_1101_1010	0xDA
#define 	_1101_1011	0xDB
#define 	_1101_1100	0xDC
#define 	_1101_1101	0xDD
#define 	_1101_1110	0xDE
#define 	_1101_1111	0xDF
#define 	_1110_0000	0xE0
#define 	_1110_0001	0xE1
#define 	_1110_0010	0xE2
#define 	_1110_0011	0xE3
#define 	_1110_0100	0xE4
#define 	_1110_0101	0xE5
#define 	_1110_0110	0xE6
#define 	_1110_0111	0xE7
#define 	_1110_1000	0xE8
#define 	_1110_1001	0xE9
#define 	_1110_1010	0xEA
#define 	_1110_1011	0xEB
#define 	_1110_1100	0xEC
#define 	_1110_1101	0xED
#define 	_1110_1110	0xEE
#define 	_1110_1111	0xEF
#define 	_1111_0000	0xF0
#define 	_1111_0001	0xF1
#define 	_1111_0010	0xF2
#define 	_1111_0011	0xF3
#define 	_1111_0100	0xF4
#define 	_1111_0101	0xF5
#define 	_1111_0110	0xF6
#define 	_1111_0111	0xF7
#define 	_1111_1000	0xF8
#define 	_1111_1001	0xF9
#define 	_1111_1010	0xFA
#define 	_1111_1011	0xFB
#define 	_1111_1100	0xFC
#define 	_1111_1101	0xFD
#define 	_1111_1110	0xFE
#define 	_1111_1111	0xFF

/* EOF */

