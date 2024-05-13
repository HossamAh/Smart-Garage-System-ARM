/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 26 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  GPIO_interface.h
 *       Module:  GPIO Module
 *  Description:  Interface header file for GPIO Driver
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/

#include "../../LIB//Std_Types.h"
#include "../../LIB//Bit_Math.h"


#include "GPIO_config.h"
#include "GPIO_private.h"
#include "GPIO_interface.h"
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL FUNCTIONS
---------------------------------------------------------------------------------------------------------------------*/
/******************************************************************************
* \Syntax          : void MGPIO_VoidInitGPIOPins(const GPIO_Cfg_Type *ConfigPtr)                                      
* \Description     : initialize GPIO port using configuration struct by parsing all 
*       its configurations to the port registers                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : ConfigPtr  pointer to port initalization configurations.                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidInitGPIOPins(const GPIO_Cfg_Type *ConfigPtr)
{
    uint8 pinsItr = 0;
    /* configuration structure content variables defination*/
    GPIO_PinModeType PinMode;
    GPIO_PinLevel PinInitLevel;
    GPIO_PinOutputType PinOutputType;
    GPIO_PinOutputSpeedType PinOutputSpeed;
    GPIO_PinPUPDType PinPUPDType;
    GPIO_PinAFType AFNum;
    GPIO_Num Port;
    GPIO_PinNum Pin;
    GPIO_t* PortReg;
    for (pinsItr = 0; pinsItr < NUM_OF_INIT_PINS; pinsItr++)
    {
        PinMode = ConfigPtr[pinsItr].PinMode;
        PinOutputType = ConfigPtr[pinsItr].PinOutputType;
        Pin = ConfigPtr[pinsItr].Pin;
        PinInitLevel = ConfigPtr[pinsItr].PinInitLevel;
        Port = ConfigPtr[pinsItr].Port;
        PinOutputSpeed = ConfigPtr[pinsItr].PinOutputSpeed;
        PinPUPDType = ConfigPtr[pinsItr].PinPUPDType;
        AFNum = ConfigPtr[pinsItr].AFNum;
        /*Get port Register*/
        switch(Port)
        {
            case _GPIOA_PORT:
            PortReg = GPIOA;
            break;
            case _GPIOB_PORT:
            PortReg = GPIOB;
            break;
            case _GPIOC_PORT:
            PortReg = GPIOC;
            break;
            default:
            break;
        }

        /*Set pin mode*/
        PortReg->MODER &= ~(0x3<<(Pin*2));
        PortReg->MODER |= (PinMode<<(Pin*2));

        if(PinMode == OUTPUT)
        {
            /*Set pin Output type*/
            PinOutputType == OPENDRAIN?SET_BIT(PortReg->OTYPER,Pin):CLEAR_BIT(PortReg->OTYPER,Pin);

            /*Set Pin Output speed*/
            PortReg->OSPEEDR &= ~(0x3<<(Pin*2));
            PortReg->OSPEEDR |= (PinOutputSpeed<<(Pin*2));
        
        }
        else if(PinMode == OUTPUT || PinMode == INPUT)
        {
			/*Set pin Pull up or pull down for both input and output*/
			PortReg->PUPDR &= ~(0x3<<(Pin*2));
			PortReg->PUPDR |= (PinPUPDType<<(Pin*2));
        }
        /*set pin initial value in output case*/
        if(PinMode == OUTPUT)
        {
            PinInitLevel == PIN_HIGH?SET_BIT(PortReg->BSRR,Pin):SET_BIT(PortReg->BSRR,(Pin+16));
        }
        else if(PinMode == AF)
        {
            if(Pin<=7)/*pins from 0 to 7 configured by AFRL Register*/
            {
                PortReg->AFRL &= ~(0xF<<(Pin*4));
                PortReg->AFRL |= (AFNum<<(Pin*4));
            }
            else /*pins from 8 to 15 configured by AFRH Register*/
            {
            	Pin = Pin-8;
                PortReg->AFRH &= ~(0xF<<(Pin*4));
                PortReg->AFRH |= (AFNum<<(Pin*4));
            }
            
        }
        else{}

    }
}

/******************************************************************************
* \Syntax          : void MGPIO_VoidSetPinMode(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinModeType Copy_u8Mode)
* \Description     : initialize GPIO pin mode
* 					output
* 					input
* 					AF
* 					Analog
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_u8Port: port number , Copy_u8Pin: pin number , Copy_u8Mode: mode of operation
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidSetPinMode(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinModeType Copy_u8Mode)
{
	GPIO_t* PortReg=NULL;
	switch(Copy_u8Port)
	{
		case _GPIOA_PORT:
		PortReg = GPIOA;
		break;
		case _GPIOB_PORT:
		PortReg = GPIOB;
		break;
		case _GPIOC_PORT:
		PortReg = GPIOC;
		break;
		default:
		break;
	}
    /*Set pin mode*/
    PortReg->MODER &= ~(0x3<<(Copy_u8Pin*2));
    PortReg->MODER |= (Copy_u8Mode<<(Copy_u8Pin*2));
}


/******************************************************************************
* \Syntax          : void MGPIO_VoidSetPinOutputType(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinOutputType Copy_u8OutputType)
* \Description     : initialize GPIO pin ouput type
* 						opendrain
* 						pushpull
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_u8Port: port number , Copy_u8Pin: pin number , Copy_u8Mode: mode of operation
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidSetPinOutputType(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinOutputType Copy_u8OutputType)
{
	GPIO_t* PortReg=NULL;
	switch(Copy_u8Port)
	{
		case _GPIOA_PORT:
		PortReg = GPIOA;
		break;
		case _GPIOB_PORT:
		PortReg = GPIOB;
		break;
		case _GPIOC_PORT:
		PortReg = GPIOC;
		break;
		default:
		break;
	}
	/*Set pin Output type*/
	Copy_u8OutputType == OPENDRAIN?SET_BIT(PortReg->OTYPER,Copy_u8Pin):CLEAR_BIT(PortReg->OTYPER,Copy_u8Pin);
}

/******************************************************************************
* \Syntax          : void MGPIO_VoidSetPinOutputSpeed(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinOutputSpeedType Copy_u8OutputSpeed)
* \Description     : initialize GPIO pin ouput speed
* 						OUTPUT_SPEED_LOW,
*						OUTPUT_SPEED_MEDUIM,
*						OUTPUT_SPEED_HIGH,
*						OUTPUT_SPEED_VERY_HIGH
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_u8Port: port number , Copy_u8Pin: pin number , Copy_u8Mode: mode of operation
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidSetPinOutputSpeed(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinOutputSpeedType Copy_u8OutputSpeed)
{
	GPIO_t* PortReg=NULL;
	switch(Copy_u8Port)
	{
		case _GPIOA_PORT:
		PortReg = GPIOA;
		break;
		case _GPIOB_PORT:
		PortReg = GPIOB;
		break;
		case _GPIOC_PORT:
		PortReg = GPIOC;
		break;
		default:
		break;
	}
    /*Set Pin Output speed*/
    PortReg->OSPEEDR &= ~(0x3<<(Copy_u8Pin*2));
    PortReg->OSPEEDR |= (Copy_u8OutputSpeed<<(Copy_u8Pin*2));
}


/******************************************************************************
* \Syntax          : void MGPIO_VoidSetPullType(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinPUPDType Copy_u8PullType)
* \Description     : initialize GPIO pin pull
* 					    PULL_OFF,
*						PULL_UP,
*						PULL_DOWN
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_u8Port: port number , Copy_u8Pin: pin number , Copy_u8Mode: mode of operation
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidSetPullType(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinPUPDType Copy_u8PullType)
{
	GPIO_t* PortReg=NULL;
	switch(Copy_u8Port)
	{
		case _GPIOA_PORT:
		PortReg = GPIOA;
		break;
		case _GPIOB_PORT:
		PortReg = GPIOB;
		break;
		case _GPIOC_PORT:
		PortReg = GPIOC;
		break;
		default:
		break;
	}
	/*Set pin Pull up or pull down for both input and output*/
	PortReg->PUPDR &= ~(0x3<<(Copy_u8Pin*2));
	PortReg->PUPDR |= (Copy_u8PullType<<(Copy_u8Pin*2));
}


/******************************************************************************
* \Syntax          : void MGPIO_VoidSetPinAlternativeFunction(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinAFType Copy_u8AF )
* \Description     : initialize GPIO pin alternative function
* \Sync\Async      : Synchronous
* \Reentrancy      : Non Reentrant
* \Parameters (in) : Copy_u8Port: port number , Copy_u8Pin: pin number , Copy_u8Mode: mode of operation
* \Parameters (out): None
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidSetPinAlternativeFunction(GPIO_Num Copy_u8Port , GPIO_PinNum Copy_u8Pin , GPIO_PinAFType Copy_u8AF )
{
	GPIO_t* PortReg=NULL;
	switch(Copy_u8Port)
	{
		case _GPIOA_PORT:
		PortReg = GPIOA;
		break;
		case _GPIOB_PORT:
		PortReg = GPIOB;
		break;
		case _GPIOC_PORT:
		PortReg = GPIOC;
		break;
		default:
		break;
	}

	if(Copy_u8Pin<=7)/*pins from 0 to 7 configured by AFRL Register*/
	{
		PortReg->AFRL &= ~(0xF<<(Copy_u8Pin*4));
		PortReg->AFRL |= (Copy_u8AF<<(Copy_u8Pin*4));
	}
	else /*pins from 8 to 15 configured by AFRH Register*/
	{
		Copy_u8Pin = Copy_u8Pin - 8;
		PortReg->AFRH &= ~(0xF<<(Copy_u8Pin*4));
		PortReg->AFRH |= (Copy_u8AF<<(Copy_u8Pin*4));
	}

}
/******************************************************************************
* \Syntax          : void MGPIO_VoidSetPinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin ,GPIO_PinLevel  Copy_uint8Value)                                      
* \Description     : Set pin value in GPIO Port                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPIO_Num Port Name , GPIO_PinNum pin number in port ,GPIO_PinLevel  High or LOW                   
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidSetPinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin ,GPIO_PinLevel  Copy_uint8Value)
{
    switch(Copy_uint8Port)
    {
        case _GPIOA_PORT:
        	Copy_uint8Value == PIN_HIGH?SET_BIT(GPIOA->BSRR,Copy_uint8Pin):SET_BIT(GPIOA->BSRR,(Copy_uint8Pin+16));
        break;
        case _GPIOB_PORT:
        	Copy_uint8Value == PIN_HIGH?SET_BIT(GPIOB->BSRR,Copy_uint8Pin):SET_BIT(GPIOB->BSRR,(Copy_uint8Pin+16));
        break;
        case _GPIOC_PORT:
        	Copy_uint8Value == PIN_HIGH?SET_BIT(GPIOC->BSRR,Copy_uint8Pin):SET_BIT(GPIOC->BSRR,(Copy_uint8Pin+16));
        break;
        default:
        break;
    }
    
}
/******************************************************************************
* \Syntax          : GPIO_PinLevel MGPIO_GPIO_PinLevelGetPinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin)                                      
* \Description     : Get pin value in GPIO Port                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPIO_Num Port Name , GPIO_PinNum pin number in port                    
* \Parameters (out): None                                                      
* \Return value:   : GPIO_PinLevel  High or LOW
*******************************************************************************/
GPIO_PinLevel MGPIO_GPIO_PinLevelGetPinValue(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin)
{
    uint8 LOC_uint8ReturnValue = PIN_LOW;
    switch(Copy_uint8Port)
    {
        case _GPIOA_PORT:
        LOC_uint8ReturnValue = READ_BIT(GPIOA->IDR,Copy_uint8Pin);
        break;
        case _GPIOB_PORT:
        LOC_uint8ReturnValue = READ_BIT(GPIOB->IDR,Copy_uint8Pin);
        break;
        case _GPIOC_PORT:
        LOC_uint8ReturnValue = READ_BIT(GPIOC->IDR,Copy_uint8Pin);
        break;
        default:
        LOC_uint8ReturnValue = PIN_LOW;
        break;
    }
    return  LOC_uint8ReturnValue;

}

/******************************************************************************
* \Syntax          : void MGPIO_VoidLockPin(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin)                                      
* \Description     : Lock pin value in GPIO Port                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : GPIO_Num Port Name , GPIO_PinNum pin number in port                    
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void MGPIO_VoidLockPin(GPIO_Num Copy_uint8Port , GPIO_PinNum Copy_uint8Pin)
{
    switch(Copy_uint8Port)	
  {
	  case _GPIOA_PORT  :
            SET_BIT(GPIOA->LCKR,Copy_uint8Pin );
            SET_BIT(GPIOA->LCKR,LCKK );
            while(!(READ_BIT(GPIOA->LCKR,LCKK)));
	  
	  break ; 
	  /*************************************************/
	  case _GPIOB_PORT  :
            SET_BIT(GPIOB->LCKR,Copy_uint8Pin );
            SET_BIT(GPIOB->LCKR,LCKK );
            while(!(READ_BIT(GPIOB->LCKR,LCKK)));
	  
	  break ; 
	  /*************************************************/
	    case _GPIOC_PORT  :
            SET_BIT(GPIOC->LCKR,Copy_uint8Pin );
            SET_BIT(GPIOC->LCKR,LCKK );
            while(!(READ_BIT(GPIOC->LCKR,LCKK)));

	  break ; 
  }
}
