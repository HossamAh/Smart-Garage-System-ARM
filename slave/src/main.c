
/*********************************************************************************/
/* Author    : Hossam Ahmed                                                     */
/* Version   : V01                                                               */
/* Data      : 26 OCT 2023                                                       */
/*********************************************************************************/
/*---------------------------------------------------------------------------------------------------------------------
 *  *  FILE DESCRIPTION
 *  --------------------
 *         File:  main.c
 *       Module:  Main Module
 *  Description:  main file for smart garage system, Slave ECU which is responsible to:display Slot status.
---------------------------------------------------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------------------------------------------------
 *  INCLUDES
---------------------------------------------------------------------------------------------------------------------*/

#include "COTS/LIB/Bit_Math.h"
#include "COTS/LIB/Std_Types.h"

#include "COTS/MCAL/RCC/RCC_interface.h"
#include "COTS/MCAL/GPIO/GPIO_interface.h"
#include "COTS/MCAL/External_Interrupt/External_Interrupt_interface.h"
#include "COTS/MCAL/NVIC/NVIC_Interface.h"
#include "COTS/MCAL/SYSTick/SYSTick_interface.h"
#include "COTS/MCAL/UART/UART_interface.h"

/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL MACROS
---------------------------------------------------------------------------------------------------------------------*/
#define SLOT1_LED_PORT	_GPIOA_PORT
#define SLOT1_LED_PIN	pin0

#define SLOT2_LED_PORT	_GPIOA_PORT
#define SLOT2_LED_PIN	pin1


/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
/*Array of pins structs to be initialized*/
const GPIO_Cfg_Type  MGPIO_CONFIGURAIONS[NUM_OF_INIT_PINS]={
 /*PinMode         ,PinInitValue         ,PinOutputType          ,PinOuttpuutSpeed           ,PinPUPDType          ,AFNUM          ,Port         ,Pin*/
 {OUTPUT            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF0            ,SLOT1_LED_PORT       ,SLOT1_LED_PIN},
 {OUTPUT            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF0            ,SLOT2_LED_PORT       ,SLOT2_LED_PIN},
  {AF            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF7            ,_GPIOA_PORT       ,pin9},
  {AF            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF7            ,_GPIOA_PORT       ,pin10}
};
void main()
{
		uint8 loc_slot_state[3],slot1_state=0,slot2_state=0;

		/*initialize clocks*/
		MRCC_voidInitSysClock();

		/*Enable GPIOA,B,C clock */
		MRCC_voidEnableClock(RCC_AHB1,_PERIPHERAL_EN_GPIOA);
		MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_SYSCFG);

		MGPIO_VoidInitGPIOPins(MGPIO_CONFIGURAIONS);
		
		MUSART1_voidInit();
		MUSART1_voidEnable();
	  // Infinite loop
	  while (1)
	    {
		  	MUSART1_u8ReceiveDataBlock(loc_slot_state);
		    if(loc_slot_state[0]=='S')
		    {
		    	if(loc_slot_state[1]=='1')
		    	{
				    if(slot1_state)
				    	slot1_state = 0;
				    else
				    	slot1_state = 1;
		    	}
		    	else if(loc_slot_state[1]=='2')
		    	{
				    if(slot2_state)
				    	slot2_state = 0;
				    else
				    	slot2_state = 1;
		    	}
		    }
		    if(slot1_state)
		    	MGPIO_VoidSetPinValue(SLOT1_LED_PORT,SLOT1_LED_PIN,PIN_HIGH);
		    else
		    	MGPIO_VoidSetPinValue(SLOT1_LED_PORT,SLOT1_LED_PIN,PIN_LOW);

		    if(slot2_state)
		    	MGPIO_VoidSetPinValue(SLOT2_LED_PORT,SLOT2_LED_PIN,PIN_HIGH);
		    else
		    	MGPIO_VoidSetPinValue(SLOT2_LED_PORT,SLOT2_LED_PIN,PIN_LOW);

	    }
}
