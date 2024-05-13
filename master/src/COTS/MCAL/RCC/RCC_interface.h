/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 25 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  RCC_interface.h
 *       Module:  RCC Module
 *  Description:  interface funcions for RCC Driver
---------------------------------------------------------------------------------------------------------------------*/

#ifndef RCC_INTERFACE_H
#define RCC_INTERFACE_H


/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/
#include "../../LIB//Std_Types.h"
#include "../../LIB//Bit_Math.h"

#include "RCC_private.h"
#include "RCC_config.h"



/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
/*********** Macros Of :- RCC AHB1 CLK ENABLE ***************/

#define _PERIPHERAL_EN_GPIOA     0U
#define _PERIPHERAL_EN_GPIOB     1U
#define _PERIPHERAL_EN_GPIOC     2U
#define _PERIPHERAL_EN_GPIOD     3U
#define _PERIPHERAL_EN_GPIOE     4U
#define _PERIPHERAL_EN_GPIOH     7U
#define _PERIPHERAL_EN_CRCEN     12U
#define _PERIPHERAL_EN_DMA1EN    21U
#define _PERIPHERAL_EN_DMA2EN    22U


	/********* Macros Of :- RCC APB1 peripheral clock enable register *********/

#define PERIPHERAL_EN_TIM2						0U
#define PERIPHERAL_EN_TIM3						1U
#define PERIPHERAL_EN_TIM4						2U
#define PERIPHERAL_EN_TIM5					    3U
#define PERIPHERAL_EN_TIM6						4U
#define PERIPHERAL_EN_TIM7						5U
#define PERIPHERAL_EN_TIM12					    6U
#define PERIPHERAL_EN_TIM13					    7U
#define PERIPHERAL_EN_TIM14					    8U
#define PERIPHERAL_EN_WWDG						11U
#define PERIPHERAL_EN_SPI2						14U
#define PERIPHERAL_EN_SPI3						15U
#define PERIPHERAL_EN_UART2						17U
#define PERIPHERAL_EN_UART3						18U
#define PERIPHERAL_EN_UART4						19U
#define PERIPHERAL_EN_UART5						20U
#define PERIPHERAL_EN_I2C1						21U
#define PERIPHERAL_EN_I2C2						22U
#define PERIPHERAL_EN_I2C3						23U
#define PERIPHERAL_EN_CAN1						25U
#define PERIPHERAL_EN_CAN2						26U
#define PERIPHERAL_EN_PWR						28U
#define PERIPHERAL_EN_DAC						29U



/**********  Macros Of :- RCC APB2 peripheral clock enable register (RCC_APB2ENR) *********/

#define PERIPHERAL_EN_TIM1  				 0U
#define PERIPHERAL_EN_TIM8					 1U
#define PERIPHERAL_EN_USART1				 4U
#define PERIPHERAL_EN_USART6				 5U
#define PERIPHERAL_EN_ADC1					 8U
#define PERIPHERAL_EN_ADC2					 9U
#define PERIPHERAL_EN_ADC3					 10U
#define PERIPHERAL_EN_SDIO					 11U
#define PERIPHERAL_EN_SPI1					 12U
#define PERIPHERAL_EN_SYSCFG				 14U
#define PERIPHERAL_EN_TIM9					 16U
#define PERIPHERAL_EN_TIM10					 17U
#define PERIPHERAL_EN_TIM11 				 18U

/*****************************************************************************************/

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTION PROTOTYPES
---------------------------------------------------------------------------------------------------------------------*/ 
/******************************************************************************
* \Syntax          : void MRCC_voidInitSysClock(void)                                      
* \Description     : initialize RCC using configuration by parsing all 
*       its configurations to the RCC registers                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidInitSysClock(void);

/******************************************************************************
* \Syntax          : void MRCC_voidEnableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId)                                      
* \Description     : Enable the clock of specific peripheral on specific bus                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_uint8BusId Bus idenifier   Copy_uint8PeripheralId Peripherral identifier.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidEnableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId);

/******************************************************************************
* \Syntax          : void MRCC_voidDisableClock(uint8 Copy_uint8BusId , uint8 Copy_uint8PeripheralId)                                      
* \Description     : Disable the clock of specific peripheral on specific bus                                                                              
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : Copy_uint8BusId Bus idenifier   Copy_uint8PeripheralId Peripherral identifier.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MRCC_voidDisableClock(uint8 Copy_uint8BusId, uint8 Copy_uint8PeripheralId);


#endif
