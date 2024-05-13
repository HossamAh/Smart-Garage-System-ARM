/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 25 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  RCC_private.h
 *       Module:  RCC Module
 *  Description:  private header file for RCC Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef RCC_PRIVATE_H
#define RCC_PRIVATE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/* Register Map */
typedef struct{
	
	volatile uint32 CR;
	volatile uint32 PLLCFGR;
	volatile uint32 CFGR;
	volatile uint32 CIR;
	volatile uint32 AHB1RSTR;
	volatile uint32 AHB2RSTR;
	volatile uint32 RESERVED1;
	volatile uint32 RESERVED2;
	volatile uint32 APB1RSTR;
	volatile uint32 APB2RSTR;
	volatile uint32 RESERVED3;
	volatile uint32 RESERVED4;
	volatile uint32 AHB1ENR;
	volatile uint32 AHB2ENR;
	volatile uint32 RESERVED5;
	volatile uint32 RESERVED6;
	volatile uint32 APB1ENR;
	volatile uint32 APB2ENR;
	volatile uint32 RESERVED7;
	volatile uint32 RESERVED8;
	volatile uint32 AHB1LPENR;
	volatile uint32 AHB2LPENR;
	volatile uint32 RESERVED9;
	volatile uint32 RESERVED10;
	volatile uint32 APB1LPENR;
	volatile uint32 APB2LPENR;
	volatile uint32 RESERVED11;
	volatile uint32 RESERVED12;
	volatile uint32 BDCR;
	volatile uint32 CSR;
	volatile uint32 RESERVED13;
	volatile uint32 RESERVED14;
	volatile uint32 SSCGR;
	volatile uint32 PLLI2SCFGR;
	volatile uint32 RESERVED15;
	volatile uint32 DCKCFGR;
}RCC_t;


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL CONSTANT MACROS
---------------------------------------------------------------------------------------------------------------------*/

#define 	RCC_Base_Address		(0x40023800)

#define 	RCC 		((volatile RCC_t*) RCC_Base_Address)
//#define RCC ((volatile RCC_t*) RCC_Base_Address)

/* Clock Types */
#define RCC_HSE_CRYSTAL      0
#define RCC_HSE_RC           1
#define RCC_HSI              2
#define RCC_PLL              3

/* PLL Options */
#define RCC_PLL_IN_HSI       0
#define RCC_PLL_IN_HSE       1

/*RCC_CFGR Register Bits*/
#define SW0        			 0
#define SW1        			 1
#define PLLSRC     			 22

/*RCC_CR Register Bits*/
#define PLL_ON     			 24


/*Bus Id*/
#define RCC_AHB1      0 
#define RCC_AHB2      1 
#define RCC_APB1      2
#define RCC_APB2      3

#endif
