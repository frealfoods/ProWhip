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

#include <string.h>
#include <intrins.h>
#include "Typech.h"
#include "mc96f8316.h"
#include "define.h"
#include "func.h"
#include "ram.h"


/*---------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------*/
/*-------------------------[ FLASH Selp Program ] ---------------------------------------------*/
/*---------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------------------------*/
/*
	Data Memory(IDATA)  : 00~7F / 80~FF
	SFR					: 80~FF
	00~7F				: Bank0~3(Bank per 8Byte Total = 00~1F
	20~2F				: Bit Addressable
	30~7F				: General purpose register(80Byte)
	Data Memory(XDATA)  : 1B~2FF(768Byte)
	Flash Memory		: 0000~7FFFFH(32kbyte)
	Sector				: 0~511(512) / 1Sector = 0~3F(64Byte)
	Flash page buffer	: 8000~803F(64byte)
*/

#define coderom  ((unsigned char volatile code  *) 0)
#define pagebuff ((unsigned char volatile xdata  *) 0x8000)

#if cEEPROM

/**/
/*			  			EEPROM_Proc					 			*/
/**/
// 첫번재 바이트가
// 0x55 : 실효데이타..
// 0x00또는 0xff는 무효데이타..

void EEPROM_Proc(void)
{
	if(	Motor_RPM_old != Motor_RPM  || Mode_Key_old != Mode_Key )
	{
		Motor_RPM_old = Motor_RPM;
		Mode_Key_old = Mode_Key;

		fFLASH_SET = OFF;

		Write_Data[0] = 0x55;
		Write_Data[1] = Motor_RPM;
		Write_Data[2] = Mode_Key;

		flash_status = Lflash_erase(cSector);
		NOP();
		NOP();
		NOP();
		flash_status = Lflash_write(cSector);
		NOP();
		NOP();
		NOP();
		Lflash_read(cSector);
	}
}		
//=============================================================================
// Function Name: CodeFlash_Erase
// Description	: page buff(64byte) 단위로 지운다.  총 512 sector
// input		: start sector[500], number of sector[2]
// output		: true/false
//=============================================================================
char CodeFlash_Erase(unsigned int ss, unsigned char no)		// page buff = 64byte
{
	unsigned int add;
	unsigned int lp;
	unsigned char lp2;
	
	for(lp=0; lp<no; lp++)
	{
		FMCR=0x01; // page buffer clear
		
		for(lp2=0; lp2<32; lp2++)
		{
			pagebuff[lp2]=0x00;			
		}
	
		add = (unsigned int)(32*(ss+lp));		
		FSADRL = (unsigned char)(add);
		FSADRM = (unsigned char)(add>>8);
		FSADRH = 0x00;
		
		FIDR = 0xA5; //dentification value
		FMCR = 0x02; //Start flash erase mode
		_nop_();
		_nop_();
		_nop_();		
	}
	
	// read data
	add = (unsigned int)(32*ss);
	//coderom = (unsigned char *)add;
	for(lp=add; lp<(add+(32*no)); lp++)	// Read flash data.
	{
		if( coderom[lp] != 0x00) return -1;
	}
	
	return 0;
}

//=============================================================================
// Function Name: CodeFlash_Write
// Description	: page buff(32byte) 단위로 쓴다.  총 512 sector
// input		: data, start sector, number of sector
// output		: true/false
//=============================================================================
char CodeFlash_Write(unsigned char *dt, unsigned int ss, unsigned char no)
{
	unsigned int add;
	unsigned int lp;
	unsigned char lp2;
	unsigned char *pdt = dt;
	
	for(lp=0; lp<no; lp++)
	{
		FMCR=0x01; // page buffer clear
		
		for(lp2=0; lp2<32; lp2++)
		{
			pagebuff[lp2]=dt[lp2];			
		}
	
		add = (unsigned int)(32*(ss+lp));		
		FSADRL = (unsigned char)(add&0xff);
		FSADRM = (unsigned char)(add>>8);
		FSADRH = 0x00;
		
		FIDR = 0xA5; //dentification value
		FMCR = 0x03; //Start sector write
		_nop_();
		_nop_();
		_nop_();		
	}
	
	// read data
	add = (unsigned int)(32*ss);
	//coderom = (unsigned char *)add;
	pdt = dt;
	for(lp=add; lp<(add+(32*no)); lp++)	// Read flash data.
	{
		if( coderom[lp] != *pdt) return -1;
		pdt++;
	}
	
	return 0;
}

//=============================================================================
// Function Name: CodeFlash_Read
// Description	: page buff(32byte) 단위로 읽는다.  총 512 sector(0~511)
// input		: data, start sector, number of sector
// output		: 읽은 갯수
//=============================================================================
int CodeFlash_Read(unsigned char *dt, unsigned int ss, unsigned char no)
{
	unsigned int add;
	unsigned int lp;
	unsigned char *pdt = dt;
	
	// read data
	add = (unsigned int)(32*ss);
	for(lp=add; lp<(add+(32*no)); lp++)	// Read flash data.
	{
		*pdt = coderom[lp];
		pdt++;
	}
	
	return (pdt-add);
}

void Lflash_read(unsigned int sector)
{
	unsigned char dt[32];
	unsigned char lp;
	unsigned int ss;				// start sector
	
	memset(dt, 0, sizeof(dt));
	
	ss = sector&0x1ff;				// Erase sector[000-1ff] / 512 sector

	CodeFlash_Read(&dt[0], ss, 1);	//org
	for(lp=0; lp<32; lp++) Read_Data[lp] = dt[lp];
}

char Lflash_write(unsigned int sector)
{
	unsigned char dt[32];
	unsigned char lp;
	unsigned int ss;				// start sector
	char ret;
	
	cli();
	ss = sector&0x1ff;				// Erase sector[000-1ff] / 512 sector
	
	for(lp=0; lp<32; lp++) dt[lp] = Write_Data[lp];
	
	ret  = CodeFlash_Write(dt, ss, 1);
	sei();

	if( ret == -1) return(1);		// False write
	else  return(0);
}


char Lflash_erase(unsigned int sector)
{
	unsigned int ss;				// start sector
	char ret;	
	ss = sector&0x1ff;				// Erase sector[000-1ff] / 512 sector
	
	ret = CodeFlash_Erase(ss, 1);
	if( ret == -1) return(1);		// False erase
	else  return(0);
}
#endif

/* EOF */	
