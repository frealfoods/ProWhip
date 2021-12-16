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

EXT void Main_Proc(void);
EXT void Key_Proc(void);
EXT void Key_Proc1(void);
EXT void BUZZER_Proc(void); 
EXT void ADC_Proc(void);
EXT void Disp_Proc(void);

EXT void Clock_init( void );
EXT	void Port_init(void);
EXT	void ExINT_init();            		// initialize external interrupt
EXT	void Ram_init(void);

EXT	void JIG_Proc(void);

EXT void WT_init(void);
EXT	void ADC_init(void);              	// initialize A/D convertor
EXT	void ADC_start(unsigned char ch);	// start A/D convertor
EXT	unsigned int ADC_read();      		// read A/D convertor
EXT	unsigned int ADC_Cal(unsigned int *adbuff);

EXT void Buz_Beep(U_CHAR n);
EXT void BUZ_init();
EXT void BUZ_OnOff(unsigned char On);

EXT void UART_init();             		// initialize UART interface
EXT void UART_write(unsigned char dat);	// write UART
EXT unsigned char UART_read();    		// read UART


void WDT_init(void);              		// initialize Watch-dog timer
void WDT_clear(void);             		// Clear Watch-dog timer
void WDT_enable(void);
void WDT_disable(void);

/* Timer0 timer function */
EXT void Timer0_init(void);
EXT void Timer0_start(void);
EXT void Timer0_stop(void);
EXT void Timer0_porten(void);
EXT void Timer0_portdis(void);

// 16bit timer1 mode set
EXT void Timer1_init(void);
EXT void timer1_start(void);
EXT void timer1_stop(void);

// 16bit timer1 mode set
EXT void Timer2_init(void);
EXT void timer2_start(void);
EXT void timer2_stop(void);


/* Flash memory function */
EXT void EEPROM_Proc(void); 
EXT char CodeFlash_Erase(unsigned int ss, unsigned char no);
EXT char CodeFlash_Write(unsigned char *dt, unsigned int ss, unsigned char no);
EXT int CodeFlash_Read(unsigned char *dt, unsigned int ss, unsigned char no);

EXT void Lflash_read(unsigned int sector);
EXT char Lflash_write(unsigned int sector);
EXT char Lflash_erase(unsigned int sector);

EXT void delay(int dly);
EXT void delay_xms(U_CHAR time);

/* EOF	*/

