/*	
	=================================================================
	= Copyright(C) 2009 KEIL CORPORATION All rights reserved		=
	=================================================================
	= Header file for SFR of ABOV(C51-Core)							=
	= Micom         : ABOV[MC96Fxxxx]/xxSOP							=
	=================================================================
*/

#ifdef ROOT

#define	EXT
#else
#define	EXT		extern

#endif

typedef unsigned char	BYTE;	
typedef unsigned char	U_CHAR;	
typedef unsigned char	U08;	
typedef unsigned int	U_INT;	
typedef unsigned short	WORD;		
typedef unsigned long	DWORD;		

typedef	struct {			/* general-purpose bit-field definition */
	BYTE	p0		: 1;
	BYTE	p1		: 1;
	BYTE	p2		: 1;
	BYTE	p3		: 1;
	BYTE	p4		: 1;
	BYTE	p5		: 1;
	BYTE	p6		: 1;
	BYTE	p7		: 1;	// -Xw 
} MB_BTF;
typedef	volatile struct {	/* optimize control bit-field definition */
	BYTE	p0		: 1;	
	BYTE	p1		: 1;	
	BYTE	p2		: 1;	
	BYTE	p3		: 1;	
	BYTE	p4		: 1;	
	BYTE	p5		: 1;
	BYTE	p6		: 1;
	BYTE	p7		: 1;
} RB_BTF;

typedef	struct {			/* general-purpose bit-field definition */
	WORD	p0		: 1;
	WORD	p1		: 1;
	WORD	p2		: 1;
	WORD	p3		: 1;
	WORD	p4		: 1;
	WORD	p5		: 1;
	WORD	p6		: 1;
	WORD	p7		: 1;
	WORD	p8		: 1;
	WORD	p9		: 1;
	WORD	p10		: 1;
	WORD	p11		: 1;
	WORD	p12		: 1;
	WORD	p13		: 1;
	WORD	p14		: 1;
	WORD	p15		: 1;
} MB_WTF;

/*======= WORD IO ========*/
typedef union {
	WORD	word;
	BYTE	byte[2];
//	MB_WTF	bt;
} WORD_BTF;

typedef union {
	DWORD	dword;
	WORD	word[2];
	BYTE	byte[4];
} DWORD_BTF;

typedef	struct {		/* general-purpose bit-field definition */
	BYTE	halfL		: 4;
	BYTE	halfH		: 4;
} HALF_BTF;


