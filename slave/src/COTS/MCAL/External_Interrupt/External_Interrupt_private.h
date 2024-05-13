/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 28 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  EXTERNAL_INTERRUPT_Private.h
 *       Module:  EXTERNAL_INTERRUPT Module
 *  Description:  Private header file for EXTERNAL_INTERRUPT Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _EXTERNAL_INTERRUPT_PRIVATE_H
#define _EXTERNAL_INTERRUPT_PRIVATE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
/* Register Map for EXTERNAL_INTERRUPT */
typedef struct{
	volatile uint32 EXTI_IMR;
    volatile uint32 EXTI_EMR;
    volatile uint32 EXTI_RTSR;
    volatile uint32 EXTI_FTSR;
    volatile uint32 EXTI_SWIER;
    volatile uint32 EXTI_PR;     
}EXTERNAL_INTERRUPT_MemoryMap_t;

typedef struct{
    volatile uint32 SYSCFG_MEMRMP;
	volatile uint32 SYSCFG_PMC;
    volatile uint32 SYSCFG_EXTICR[4];
    volatile uint32 SYSCFG_CMPCR;     
}SYSCFG_MemoryMap_t;


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define 	EXTERNAL_INTERRUPT_Base_Address        0x40013C00            // Base address of EXTERNAL_INTERRUPT
#define     SYSCFG_Base_Address                    0x40013800 

#define 	EXTI 		((volatile EXTERNAL_INTERRUPT_MemoryMap_t *) EXTERNAL_INTERRUPT_Base_Address)

#define     SYSCFG      ((volatile SYSCFG_MemoryMap_t*)SYSCFG_Base_Address) 


#endif
