/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 28 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  NVIC_interface.h
 *       Module:  NVIC Module
 *  Description:  Interface header file for NVIC Driver
---------------------------------------------------------------------------------------------------------------------*/
#ifndef _NVIC_INTERFACE_H
#define _NVIC_INTERFACE_H

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB//Std_Types.h"
#include "../../LIB//Bit_Math.h"
#include "NVIC_Config.h"

#include "NVIC_Private.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA TYPES AND STRUCTURES
---------------------------------------------------------------------------------------------------------------------*/
typedef enum
{
    WWDG=0,
    EXTI16,
    EXTI21,
    EXTI22,
    FLASH,
	RCC_INT,
    EXTI0,
    EXTI1,
    EXTI2,
    EXTI3,
    EXTI4,
    ADC=18,
    EXTI9_5,
    EXTI15_10=40,
    EXTI17,
    EXTI18
}NVIC_InterruptType_t;


#define reg_div 32


typedef enum{
	Group16Sub0=3,
	Group8Sub2,
	Group4Sub4,
	Group2Sub8,
	Group0Sub16
}NVIC_GROUP_t;
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************
* \Syntax          : void MNVIC_VoidSetPriorityPolicy(NVIC_PriorityPolicy Copy_uint8PriorityPolicy )                                      
* \Description     : Set Priority policy of NVIC Determine number of preemption priority level and sub_priority levels                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_GROUP_t Copy_uint8PriorityPolicy : enum of group and sub_group options                  
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidSetPriorityPolicy(NVIC_GROUP_t Copy_uint8PriorityPolicy );

/******************************************************************************
* \Syntax          : void MNVIC_VoidSetPriority(NVIC_InterruptType_t Copy_uint8InterruptType , uint8 Copy_uint8Priority,uint8 Copy_uint8SubPriority)                                      
* \Description     : Set priority and sub_priority to specific interrupt                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name , uint8 Copy_uint8Priority number of group ,uint8 Copy_uint8SubPriority number of sub priority                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidSetPriority(NVIC_InterruptType_t Copy_uint8InterruptType , uint8 Copy_uint8Priority,uint8 Copy_uint8SubPriority);
/******************************************************************************
* \Syntax          : void MNVIC_VoidEnableInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)                                      
* \Description     : Enable  specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidEnableInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType);

/******************************************************************************
* \Syntax          : void MNVIC_VoidDisableInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)                                      
* \Description     : Disable  specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidDisableInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType);

/******************************************************************************
* \Syntax          : void MNVIC_VoidSetPendingInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)                                      
* \Description     : Set Pending bit of specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidSetPendingInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType);

/******************************************************************************
* \Syntax          : void MNVIC_VoidClearPendingInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType)                                      
* \Description     : Clear Pending bit of specific interrupt by enabling its mask bit                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : NVIC_InterruptType_t Copy_uint8InterruptType Interrupt name                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MNVIC_VoidClearPendingInterrupt(NVIC_InterruptType_t Copy_uint8InterruptType);


#endif
