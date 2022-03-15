/*------------------------------------------------------------------------------------------------------
 * [MODULE]: Port
 *
 * [FILE NAME]: Port_PBcfg.c
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 13/1/2022
 *
 * [DESCRIPTION]: Post build configuration source file for TM4C123GH6PM Microcontroller - Port Driver
 ------------------------------------------------------------------------------------------------------*/

/* including port.h */
#include "Port.h"
/*------------------*/

/* Module version 1.0.0 */
#define PORT_PBCFG_SW_MAJOR_VERSION (1U)
#define PORT_PBCFG_SW_MINOR_VERSION (0U)
#define PORT_PBCFG_SW_PATCH_VERSION (0U)
/*-------------------------------------*/

/* AUTOSAR version 4.0.3 */
#define PORT_PBCFG_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_PBCFG_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_PBCFG_AR_RELEASE_PATCH_VERSION (3U)
/*---------------------------------------------*/


/* AUTOSAR version checking between Port_Cfg.h and Port.h modules */
#if(  (PORT_PBCFG_AR_RELEASE_MAJOR_VERSION) != (PORT_AR_RELEASE_MAJOR_VERSION)\
	||(PORT_PBCFG_AR_RELEASE_MINOR_VERSION) != (PORT_AR_RELEASE_MINOR_VERSION)\
	||(PORT_PBCFG_AR_RELEASE_PATCH_VERSION) != (PORT_AR_RELEASE_PATCH_VERSION))
	#error "The AR version of Port_PBcfg.h does not match the expected version"
#endif
/*-----------------------------------------------------------------------------*/

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_PBCFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_PBCFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_PBCFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Dio_PBcfg.h does not match the expected version"
#endif
/*-----------------------------------------------------------------------------*/


const Port_ConfigType configuration =
{

		/*                              PORT_A                                       */
/*0*/	 PORT_A_ID, PIN_0_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*1*/	 PORT_A_ID, PIN_1_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*2*/	 PORT_A_ID, PIN_2_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*3*/	 PORT_A_ID, PIN_3_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*4*/	 PORT_A_ID, PIN_4_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*5*/	 PORT_A_ID, PIN_5_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*6*/	 PORT_A_ID, PIN_6_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*7*/	 PORT_A_ID, PIN_7_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,

		/*                              PORT_B                                       */
/*8*/	 PORT_B_ID, PIN_0_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*9*/	 PORT_B_ID, PIN_1_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*10*/	 PORT_B_ID, PIN_2_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*11*/	 PORT_B_ID, PIN_3_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*12*/	 PORT_B_ID, PIN_4_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*13*/	 PORT_B_ID, PIN_5_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*14*/	 PORT_B_ID, PIN_6_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*15*/	 PORT_B_ID, PIN_7_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,

		/*                              PORT_C                                       */
/*16*/	 PORT_C_ID, PIN_0_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*17*/	 PORT_C_ID, PIN_1_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*18*/	 PORT_C_ID, PIN_2_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*19*/	 PORT_C_ID, PIN_3_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*20*/	 PORT_C_ID, PIN_4_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*21*/	 PORT_C_ID, PIN_5_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*22*/	 PORT_C_ID, PIN_6_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*23*/	 PORT_C_ID, PIN_7_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,

		/*                              PORT_D                                       */
/*24*/	 PORT_D_ID, PIN_0_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*25*/	 PORT_D_ID, PIN_1_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*26*/	 PORT_D_ID, PIN_2_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*27*/	 PORT_D_ID, PIN_3_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*28*/	 PORT_D_ID, PIN_4_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*29*/	 PORT_D_ID, PIN_5_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*30*/	 PORT_D_ID, PIN_6_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*31*/	 PORT_D_ID, PIN_7_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,

		/*                              PORT_E                                       */
/*32*/	 PORT_E_ID, PIN_0_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*33*/	 PORT_E_ID, PIN_1_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*34*/	 PORT_E_ID, PIN_2_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*35*/	 PORT_E_ID, PIN_3_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*36*/	 PORT_E_ID, PIN_4_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,
/*37*/	 PORT_E_ID, PIN_5_ID, MODE_0_DIO, PORT_PIN_IN, PULL_DOWN, STD_LOW, STD_ON, STD_OFF,

		/*                              PORT_F                                       */
/*38*/	 PORT_F_ID, PIN_0_ID, MODE_0_DIO, PORT_PIN_IN, PULL_UP, STD_LOW, STD_ON, STD_OFF,/*SW2*/
/*39*/	 PORT_F_ID, PIN_1_ID, MODE_0_DIO, PORT_PIN_OUT, OFF, STD_LOW, STD_ON, STD_OFF,/*RED led*/
/*40*/	 PORT_F_ID, PIN_2_ID, MODE_0_DIO, PORT_PIN_OUT, OFF, STD_LOW, STD_ON, STD_OFF,/*BLUE led*/
/*41*/	 PORT_F_ID, PIN_3_ID, MODE_0_DIO, PORT_PIN_OUT, OFF, STD_LOW, STD_ON, STD_OFF,/*GREEN led*/
/*42*/	 PORT_F_ID, PIN_4_ID, MODE_0_DIO, PORT_PIN_IN, PULL_UP, STD_LOW, STD_ON, STD_OFF,/*SW1*/

};





