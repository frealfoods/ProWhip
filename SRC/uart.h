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


#ifndef _USART_H_
#define _USART_H_

extern void usart_init(void);
extern void uputch(char ch);
extern void uputs(char *s);
extern char ugetch(void);
extern char ugetchar(char *ch);
extern void uputhex(unsigned char ch);
extern void Comm_Proc(void);

#define	cHEADER_CODE	0xAE

// UCTRL1 reg
#define UART_MODE		0x00

#define NOPARITY		0x00
#define EVENPARITY		0x20
#define ODDPARITY		0x30

#define USIZE5			0x00
#define USIZE6			0x02
#define USIZE7			0x04
#define USIZE8			0x06
#define USIZE9			0x0e

// UCTRL2 reg
#define UDRIE			0x80
#define TXCIE			0x40
#define RXCIE			0x20
#define WAKEIE			0x10
#define TXE				0x08
#define RXE				0x04
#define USARTEN			0x02
#define U2X				0x01

// UCTRL3 reg
#define MASTER			0x80
#define LOOPS			0x40
#define DISXCK			0x20
#define SPISS			0x10
#define SOFTRST			0x08
#define USBS			0x04

// USTAT reg
#define UDRE			0x80
#define TXC				0x40
#define RXC				0x20
#define WAKE			0x10
#define DOR				0x04
#define FE				0x02
#define PE				0x01

#endif	// _USART_H_

