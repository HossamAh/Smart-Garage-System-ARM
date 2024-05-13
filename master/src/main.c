
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
 *  Description:  main file for smart garage system, Master ECU which is responsible to:
 * 				1- Monitor IR sensors at garage slots and Door
 * 				2- Control Door logic according to slots and door state.
 * 				3- send slots states to ECU2 (slave) to display it.
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
#define NOT_AVAILABLE_LED_PORT	_GPIOA_PORT 	
#define NOT_AVAILABLE_LED_PIN	pin1

#define AVAILABLE_LED_PORT	_GPIOA_PORT 	
#define AVAILABLE_LED_PIN	pin0

#define MOTORIN1_PORT	_GPIOA_PORT 	
#define MOTORIN1_PIN	pin2

#define MOTORIN2_PORT	_GPIOA_PORT 	
#define MOTORIN2_PIN	pin3



/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL DATA
---------------------------------------------------------------------------------------------------------------------*/
/*Array of pins structs to be initialized*/
const GPIO_Cfg_Type  MGPIO_CONFIGURAIONS[NUM_OF_INIT_PINS]={
 /*PinMode         ,PinInitValue         ,PinOutputType          ,PinOuttpuutSpeed           ,PinPUPDType          ,AFNUM          ,Port         ,Pin*/
 {OUTPUT            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF0            ,NOT_AVAILABLE_LED_PORT       ,NOT_AVAILABLE_LED_PIN},
 {OUTPUT            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF0            ,AVAILABLE_LED_PORT       ,AVAILABLE_LED_PIN},
 {OUTPUT            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF0            ,MOTORIN1_PORT       ,MOTORIN1_PIN},
  {OUTPUT            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF0            ,MOTORIN2_PORT       ,MOTORIN2_PIN},
  {AF            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF7            ,_GPIOA_PORT       ,pin9},
  {AF            ,PIN_LOW              ,PUSHPULL               ,OUTPUT_SPEED_HIGH          ,PULL_OFF             ,AF7            ,_GPIOA_PORT       ,pin10}
};

uint8 Slot1_state,Slot2_state,Door_state;
uint8 AvailableState,NotAvailableState,Door_opened,open_door,close_door,Door_off=1;
/*---------------------------------------------------------------------------------------------------------------------
 *  GLOBAL Functions prototypes
---------------------------------------------------------------------------------------------------------------------*/
void slot1IR();
void slot2IR();
void DoorIR();
void timerFunc();


void main()
{
  // At this stage the system clock should have already been configured
  // at high speed.

	/*initialize clocks*/
		MRCC_voidInitSysClock();

		/*Enable GPIOA,B,C clock */
		MRCC_voidEnableClock(RCC_AHB1,_PERIPHERAL_EN_GPIOA);
		MRCC_voidEnableClock(RCC_AHB1,_PERIPHERAL_EN_GPIOB);
		MRCC_voidEnableClock(RCC_AHB1,_PERIPHERAL_EN_GPIOC);
		MRCC_voidEnableClock(RCC_APB2,PERIPHERAL_EN_SYSCFG);

		MGPIO_VoidInitGPIOPins(MGPIO_CONFIGURAIONS);
		
		MUSART1_voidInit();

		MNVIC_VoidSetPriorityPolicy(Group0Sub16);
		MNVIC_VoidSetPriority(EXTI0,1,0);
		MNVIC_VoidEnableInterrupt(EXTI0);
////
		MEXTERNAL_INTERRUPT_VoidSetPort(EXTERNAL_INTERRUPT_0,EXTERNAL_INTERRUPT_PORTB);
		MEXTERNAL_INTERRUPT_VoidSetTriggerType(EXTERNAL_INTERRUPT_0,ANY_CHANGE);
		MEXTERNAL_INTERRUPT_VoidInterruptCallback(EXTERNAL_INTERRUPT_0,slot1IR);
		MEXTERNAL_INTERRUPT_VoidEnableInterrupt(EXTERNAL_INTERRUPT_0);


		MNVIC_VoidSetPriority(EXTI1,1,0);
		MNVIC_VoidEnableInterrupt(EXTI1);
		MEXTERNAL_INTERRUPT_VoidSetPort(EXTERNAL_INTERRUPT_1,EXTERNAL_INTERRUPT_PORTB);
		MEXTERNAL_INTERRUPT_VoidSetTriggerType(EXTERNAL_INTERRUPT_1,ANY_CHANGE);
		MEXTERNAL_INTERRUPT_VoidInterruptCallback(EXTERNAL_INTERRUPT_1,slot2IR);
		MEXTERNAL_INTERRUPT_VoidEnableInterrupt(EXTERNAL_INTERRUPT_1);

		MNVIC_VoidSetPriority(EXTI2,1,0);
		MNVIC_VoidEnableInterrupt(EXTI2);
		MEXTERNAL_INTERRUPT_VoidSetPort(EXTERNAL_INTERRUPT_2,EXTERNAL_INTERRUPT_PORTB);
		MEXTERNAL_INTERRUPT_VoidSetTriggerType(EXTERNAL_INTERRUPT_2,ANY_CHANGE);
		MEXTERNAL_INTERRUPT_VoidInterruptCallback(EXTERNAL_INTERRUPT_2,DoorIR);
		MEXTERNAL_INTERRUPT_VoidEnableInterrupt(EXTERNAL_INTERRUPT_2);



		MSYSTICK_VoidInit(AHB_8_CLK);
		// MSYSTICK_VoidStartSYSTICK(1200000000,timerFunc);

	  // Infinite loop
	  while (1)
	    {
			/*Available & NotAvailable led state */
			if(Slot1_state && Slot2_state)
			{
				AvailableState = 0;
				NotAvailableState = 1;	
			}
			else
			{
				AvailableState = 1;
				NotAvailableState = 0;	
			}
			if(AvailableState)
				MGPIO_VoidSetPinValue(AVAILABLE_LED_PORT,AVAILABLE_LED_PIN,PIN_HIGH);
			else
				MGPIO_VoidSetPinValue(AVAILABLE_LED_PORT,AVAILABLE_LED_PIN,PIN_LOW);

			if(NotAvailableState)
				MGPIO_VoidSetPinValue(NOT_AVAILABLE_LED_PORT,NOT_AVAILABLE_LED_PIN,PIN_HIGH);
			else
				MGPIO_VoidSetPinValue(NOT_AVAILABLE_LED_PORT,NOT_AVAILABLE_LED_PIN,PIN_LOW);

			/*Motor state*/	
			if(Door_opened)
			{
				Door_off=0;
				/*open Door for 1 sec*/
				MGPIO_VoidSetPinValue(MOTORIN1_PORT,MOTORIN1_PIN,PIN_LOW);
				MGPIO_VoidSetPinValue(MOTORIN2_PORT,MOTORIN2_PIN,PIN_HIGH);
				MSYSTICK_VoidStartSYSTICK(1200000000,timerFunc);

			}
			if(Door_state && AvailableState&&Door_off)
			{
				/*open Door for 1 sec*/
				MGPIO_VoidSetPinValue(MOTORIN1_PORT,MOTORIN1_PIN,PIN_HIGH);
				MGPIO_VoidSetPinValue(MOTORIN2_PORT,MOTORIN2_PIN,PIN_LOW);
				MSYSTICK_VoidStartSYSTICK(1200000000,timerFunc);
			}


	    }
}
void slot1IR()
{
	if(Slot1_state==0)
		Slot1_state=1;
	else
		Slot1_state=0;
	MUSART1_voidEnable();
	MUSART1_voidSendString("S1");
	MUSART1_voidDisable();
}

void slot2IR()
{
	if(Slot2_state==0)
		Slot2_state=1;
	else
		Slot2_state=0;
	MUSART1_voidEnable();
	MUSART1_voidSendString("S2");
	MUSART1_voidDisable();
}

void DoorIR()
{
	if(Door_state==0)
		Door_state=1;
	else
		Door_state=0;
}

void timerFunc(void)
{
	if(Door_opened==0)/*entered here after 1 sec of opening*/
	{
		Door_opened=1;
	}
	else /*entered here after 1 sec of closing*/
	{
		Door_opened=0;
		/*stop timer*/
		MSYSTICK_VoidDisableSysTick();
		Door_off=1;
	}
}
