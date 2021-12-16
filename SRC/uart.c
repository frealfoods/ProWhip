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
#include "uart.h"


/*
#define INT_RXMODE	1
#define INT_TXMODE	0

//#define INT_MODE	0

#define BUF_SIZE	16

#define RXBUF_SIZE	BUF_SIZE
#define TXBUF_SIZE	BUF_SIZE

char _rxq[RXBUF_SIZE];
char _txq[TXBUF_SIZE];
int _rxcnt,_rxicnt,_rxocnt;
int _txcnt,_txicnt,_txocnt;
*/

/*
	9600 Baudrate = 1byte = 1ms
	38400 Baudrate = 1byte = 1ms/4 = 256us
*/
#if cRS232C
void UART_init()
{
	// initialize UART interface
	// ASync. 38461bps N 8 1
//	_rxcnt=_rxicnt=_rxocnt=0;
//	_txcnt=_txicnt=_rxocnt=0;
	
	TX_DATA_counter = 0;
	RX_DATA_counter = 0;
	RX_CHECKSUM = 0;

	UARTCR2 = 0x02; 	// activate UART
	UARTCR1 = 0x06; 	// bit count, parity
	UARTCR2 |= 0xAC;	// interrupt, speed
	UARTCR3 = 0x00; 	// stop bit
//	UARTBD = 0x19;  	// baud rate = fsclk/(16*(ubaud+1)) 16000000/(16*38400) -1= 25(38461)
	UARTBD = 0x67;  	// baud rate = 9600
	IE1=0 
//		|(1<<5)	// ADC Wake-up
		|(1<<4)	// UART Tx
		|(1<<3)	// UART Rx
//		|(1<<2)	// I2C
//		|(1<<1)	// EINT6
//		|(1<<0)	// EINT5		
		;
	UARTCR2&=~(UDRIE+TXCIE);	

}

void UART_write(unsigned char dat)
{
	while(!(UARTST & 0x80));	// wait
	UARTDR = dat;   	// write
}

unsigned char UART_read()
{
	unsigned char dat;
	
	while(!(UARTST & 0x20));	// wait
	dat = UARTDR;   			// read
	return	dat;
}

#endif

void RX_Int(void) interrupt 9
{
	RX_DATA = UARTDR;
	
	RXCOMM_BUFF[RX_DATA_counter] = RX_DATA;
	switch( RX_DATA_counter )
	{
		case 0:
			if( RX_DATA == cHEADER_CODE )
			{
				RX_CHECKSUM = RX_DATA;
				++RX_DATA_counter;
			}else RX_DATA_counter = 0;
			break;
		case 1:
		case 2:
		case 3:
			RX_CHECKSUM += RX_DATA;
			++RX_DATA_counter;
			break;
		case 4:
			RX_DATA_counter = 0;
			if( RX_CHECKSUM == RX_DATA )
			{
				fRX_COMPLETED = ON;
				RX_COMMAND = RXCOMM_BUFF[1];
				RX_DATA1 = RXCOMM_BUFF[2];
				RX_TEMP = RXCOMM_BUFF[3];
				RX_CHECKSUM = 0;
				TX_DATA1 = 0x55;
				TX_DELAY = cS10MS020mS;
				RX_Watchdog = 0;			// watchdog clear
			}else 
			{
				RX_CHECKSUM = 0;				
				TX_DATA1 = 0x49;
			}		
			break;
	}
}
/*

void RX_Int(void) interrupt 9
{
	char ch;
	
	ch=UARTDR;

	if (_rxcnt<RXBUF_SIZE)
	{
		_rxcnt++;
		_rxq[_rxicnt]=ch;
		_rxicnt++;
		if (_rxicnt==RXBUF_SIZE)
			_rxicnt=0;
	}
}
*/

void TX_Int(void) interrupt 10
{
	UARTDR=TXCOMM_BUFF[TX_DATA_counter];

	TX_DATA_counter++;
	if (TX_DATA_counter==TXBUF_SIZE)
	{	
		TX_DATA_counter = 0;
		RX_DATA_counter = 0;
		UARTCR2&=~(UDRIE+TXCIE);	
	}	
//	UARTCR2&=~(UDRIE+TXCIE);	
}

/*
void TX_Int(void) interrupt 10
{
	if (_txcnt){
		_txcnt--;
		UARTDR=_txq[_txocnt];

		_txocnt++;
		if (_txocnt==TXBUF_SIZE)
			_txocnt=0;
		if (_txcnt==0)
			UARTCR2&=~(UDRIE+TXCIE);	
	}
}
*/

/*
void uputch(char ch)
{
#if INT_TXMODE
	while(_txcnt==TXBUF_SIZE);
	
	cli();
	_txcnt++;
	_txq[_txicnt]=ch;
	_txicnt++;
	if (_txicnt==TXBUF_SIZE)
		_txicnt=0;
	// TX interrtup enable
	UARTCR2|=(TXCIE+UDRIE);

	sei();	
#else
	while(!(UARTST&0x80));
	UARTDR=ch;	
	
#endif
}

void uputs(char *s)
{
	while(*s)
		uputch(*s++);	
}

char ugetch(void)
{
	char ch;
#if INT_RXMODE
	while(_rxcnt==0);
	
	cli();
	_rxcnt--;
	ch=_rxq[_rxocnt++];
	if (_rxocnt==RXBUF_SIZE)
		_rxocnt=0;
	sei();
#else
	while((UARTST&0x20)!=0x20);
	ch=UARTDR;	
#endif 
	return ch;
}

char ugetchar(char *ch)
{
#if INT_RXMODE	
	if(_rxcnt){
		cli();
		_rxcnt--;
		*ch=_rxq[_rxocnt++];
		if (_rxocnt==RXBUF_SIZE)
			_rxocnt=0;
		sei();
		return 1;
	}

	*ch=0;
	return 0;
#else
	while((UARTST&0x20)!=0x20);
	*ch=UARTDR;	
	return 1;
#endif 

}

void uputhex(unsigned char ch)
{
	unsigned int temp;
	char i;

	for (i=1;i>=0;i--){
		temp=ch;
		temp>>=4*i;
		temp&=0x0f;

		if (temp>=10) {
			temp-=10;
			temp+='a';
		}
		else 
			temp+='0';
		uputch(temp);
	}
}



*/


