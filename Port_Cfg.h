/*------------------------------------------------------------------------------------------------------
 * [MODULE]: Port
 *
 * [FILE NAME]: Port_Cfg.h
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 11/1/2022
 *
 * [DESCRIPTION]: Pre-Compile Configuration Header file for TM4C123GH6PM Microcontroller - Port Driver
 ------------------------------------------------------------------------------------------------------*/

#ifndef PORT_CFG_H_
#define PORT_CFG_H_

/* Module version 1.0.0 */
#define PORT_CFG_SW_MAJOR_VERSION (1U)
#define PORT_CFG_SW_MINOR_VERSION (0U)
#define PORT_CFG_SW_PATCH_VERSION (0U)
/*-------------------------------------*/

/* AUTOSAR version 4.0.3 */
#define PORT_CFG_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_CFG_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_CFG_AR_RELEASE_PATCH_VERSION (3U)
/*---------------------------------------------*/

/* Pre-compile option for Development Error Detect */
#define PORT_DEV_ERROR_DETECT         (STD_ON)
/*-------------------------------------------------*/

/* pre-compile option for VERSION INFO API */
#define PORT_VERSION_INFO_API         (STD_ON)
/*--------------------------------------------*/

/* pre-compile option for Setting The Pin Direction API */
#define PORT_SET_PIN_DIRECTION_API    (STD_ON)
/*------------------------------------------------------*/

/* pre-compile option for Setting The Pin Direction API */
#define PORT_SET_PIN_MODE_API         (STD_ON)
/*------------------------------------------------------*/

/* No. of configured pins */
#define PORT_CONFIGURED_PINS          (43U)
/*----------------------------------------*/

/* No. of Modes */
#define PORT_AVAILABLE_MODES          (15U)


/******************************
 *       Ports IDs            *
 ******************************/
typedef enum{
PORT_A_ID,
PORT_B_ID,
PORT_C_ID,
PORT_D_ID,
PORT_E_ID,
PORT_F_ID
}port_id;
/*----------------------------*/


/******************************
 *        Pins IDs            *
 ******************************/
typedef enum{
PIN_0_ID,
PIN_1_ID,
PIN_2_ID,
PIN_3_ID,
PIN_4_ID,
PIN_5_ID,
PIN_6_ID,
PIN_7_ID
}pin_id;
/*----------------------------*/



#endif /* PORT_CFG_H_ */
