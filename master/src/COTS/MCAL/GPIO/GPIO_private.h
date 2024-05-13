/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 26 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  GPIO_Private.h
 *       Module:  GPIO Module
 *  Description:  Private header file for GPIO Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _GPIO_PRIVATE_H
#define _GPIO_PRIVATE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/* Register Map for GPIO */
typedef struct{
	
	volatile uint32 MODER;
	volatile uint32 OTYPER;
	volatile uint32 OSPEEDR;
	volatile uint32 PUPDR;
	volatile uint32 IDR;
	volatile uint32 ODR;
	volatile uint32 BSRR;
	volatile uint32 LCKR;
	volatile uint32 AFRL;
	volatile uint32 AFRH;
	
}GPIO_t;

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define 	GPIOA_Base_Address        0x40020000            // Base address of GPIO port A
#define 	GPIOB_Base_Address        0x40020400            // Base address of GPIO port B
#define 	GPIOC_Base_Address        0x40020800            // Base address of GPIO port C


#define 	GPIOA 		((GPIO_t *) GPIOA_Base_Address)
#define 	GPIOB 		((GPIO_t *) GPIOB_Base_Address)
#define 	GPIOC 		((GPIO_t *) GPIOC_Base_Address)


/*lock key bit*/
#define LCKK  16




#endif
