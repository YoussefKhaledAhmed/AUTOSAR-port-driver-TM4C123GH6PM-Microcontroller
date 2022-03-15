/*----------------------------------------------------------------------------*
 * [MODULE]: Port
 *
 * [FILE NAME]: Port.h
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 12/1/2022
 *
 * [DESCRIPTION]: Header file for TM4C123GH6PM Microcontroller - Port Driver
 *----------------------------------------------------------------------------*/

#ifndef PORT_H_
#define PORT_H_


/* Vendor ID */
#define PORT_VENDOR_ID (2000U)
/*---------------------------*/

/* Module ID */
#define PORT_MODULE_ID (124U)
/*--------------------------*/

/* Instance ID */
#define PORT_INSTANCE_ID (0U)
/*--------------------------*/

/* Module version 1.0.0 */
#define PORT_SW_MAJOR_VERSION (1U)
#define PORT_SW_MINOR_VERSION (0U)
#define PORT_SW_PATCH_VERSION (0U)
/*-------------------------------------*/

/* AUTOSAR version 4.0.3 */
#define PORT_AR_RELEASE_MAJOR_VERSION (4U)
#define PORT_AR_RELEASE_MINOR_VERSION (0U)
#define PORT_AR_RELEASE_PATCH_VERSION (3U)
/*---------------------------------------------*/

/* macros of PORT status */
#define PORT_INITIALIZED     (1U)
#define PORT_NOT_INITIALIZED (0U)
/*--------------------------------*/

/* AUTOSAR standard types */
#include "Std_Types.h"
/*------------------------*/

/* AUTOSAR version checking between std Types and PORT modules */
#if(  (STD_TYPES_AR_RELEASE_MAJOR_VERSION) != (PORT_AR_RELEASE_MAJOR_VERSION)\
	||(STD_TYPES_AR_RELEASE_MINOR_VERSION) != (PORT_AR_RELEASE_MINOR_VERSION)\
	||(STD_TYPES_AR_RELEASE_PATCH_VERSION) != (PORT_AR_RELEASE_PATCH_VERSION))
	#error "The AR version of Std_Types.h does not match the expected version"
#endif
/*-----------------------------------------------------------------------------*/

/* PORT pre-compile configuration header file */
#include "Port_Cfg.h"
/*-------------------------------------------*/

/* AUTOSAR version checking between Port_Cfg.h and Port.h modules */
#if(  (PORT_CFG_AR_RELEASE_MAJOR_VERSION) != (PORT_AR_RELEASE_MAJOR_VERSION)\
	||(PORT_CFG_AR_RELEASE_MINOR_VERSION) != (PORT_AR_RELEASE_MINOR_VERSION)\
	||(PORT_CFG_AR_RELEASE_PATCH_VERSION) != (PORT_AR_RELEASE_PATCH_VERSION))
	#error "The AR version of Port_Cfg.h does not match the expected version"
#endif
/*-----------------------------------------------------------------------------*/

/* Software Version checking between Port_Cfg.h and Port.h files */
#if ((PORT_CFG_SW_MAJOR_VERSION != PORT_SW_MAJOR_VERSION)\
 ||  (PORT_CFG_SW_MINOR_VERSION != PORT_SW_MINOR_VERSION)\
 ||  (PORT_CFG_SW_PATCH_VERSION != PORT_SW_PATCH_VERSION))
  #error "The SW version of Port_Cfg.h does not match the expected version"
#endif
/*-----------------------------------------------------------------------------*/

/* including Common_Macros.h (non-AUTOSAR file) */
#include "Common_Macros.h"
/*----------------------------------------------*/

/******************************************************************
 *                      API Service Id Macros                     *
 ******************************************************************/

/* service ID for Port_init */
#define PORT_INIT_SID                      (uint8)0x00
/*----------------------------------------------------*/

/* service ID for Port_SetPinDirection */
#define PORT_SET_PIN_DIRECTION_SID         (uint8)0x01
/*----------------------------------------------------*/

/* service ID for Port_RefreshPortDirection */
#define PORT_REFRESH_PORT_DIRECTION_SID    (uint8)0x02
/*----------------------------------------------------*/

/* service ID for Port_GetVersionInfo */
#define PORT_GET_VERSION_INFO_SID          (uint8)0x03
/*----------------------------------------------------*/

/* service ID for Port_SetPinMode */
#define PORT_SET_PIN_MODE_SID              (uint8)0x04
/*----------------------------------------------------*/

/******************************************************************
 *                      DET Error Codes                           *
 ******************************************************************/

/* Invalid Port Pin ID requested */
#define PORT_E_PARAM_PIN               (uint8)0x0A
/*-------------------------------------------------*/

/* Port Pin not configured as changeable */
#define PORT_E_DIRECTION_UNCHANGEABLE  (uint8)0x0B
/*-------------------------------------------------*/

/* API Port_Init service called with wrong parameter */
#define PORT_E_PARAM_CONFIG            (uint8)0x0C
/*---------------------------------------------------*/

/* API Port_SetPinMode service called when mode is unavailable */
#define PORT_E_PARAM_INVALID_MODE      (uint8)0x0D
/*-------------------------------------------------------------*/

/* API Port_SetPinMode service called when mode is unchangeable */
#define PORT_E_MODE_UNCHANGEABLE       (uint8)0x0E
/*--------------------------------------------------------------*/

/*API service called without module initialization */
#define PORT_E_UNINIT                  (uint8)0x0F
/*-------------------------------------------------*/

/*APIs called with a Null Pointer */
#define PORT_E_PARAM_POINTER           (uint8)0x10
/*-------------------------------------------------*/

/************************************************************
 *                  Module data types                       *
 ************************************************************/

/* it's range is from 0:no. of port pins */
typedef uint8   Port_PinType;
/*---------------------------------------*/

/* enum for direction of pin */
typedef enum
{
	PORT_PIN_IN,
	PORT_PIN_OUT
}Port_PinDirectionType;
/*--------------------------*/

/* there are 14 modes */
typedef uint8   Port_PinModeType;

typedef enum{
	MODE_0_DIO , MODE_1 , MODE_2 , MODE_3 , MODE_4 , MODE_5 ,\
	MODE_6 , MODE_7 , MODE_8 , MODE_9 , MODE_10 , MODE_11 , MODE_12 , MODE_13 , MODE_14 , MODE_0_ADC
}pin_mode;
/*--------------------------------*/

/* enum for internal resistor types */
typedef enum
{
	OFF,
	PULL_UP ,
	PULL_DOWN
}Port_InternalResistor;
/*---------------------------------*/


/* structure for configuration of pins */
typedef struct
{
  /*1*/  uint8 port_num;                     /* range: 0(port A) to 5(port F)  */
  /*2*/  pin_id pin_num;                      /* range: 0(PA0) to 42(PF4) */
  /*3*/  Port_PinModeType mode;              /* range: 0(mode 0) to 14(mode 14) */
  /*4*/  Port_PinDirectionType direction;    /* PORT_PIN_IN, PORT_PIN_OUT */
  /*5*/  Port_InternalResistor resistor;     /* OFF, PULL_UP, PULL_DOWN */
  /*6*/  uint8 initial_value;                /* 0 , 1 */
  /*7*/  uint8 pin_direction_changeable;     /* STD_ON/STD_OFF */
  /*8*/  uint8 pin_mode_changeable;          /* STD_ON/STD_OFF */
}Pin_ConfigType;
/*------------------------------------------------------------------------------*/

/* structure that contains array of 43 structures */
typedef struct
{
	Pin_ConfigType pin[PORT_CONFIGURED_PINS];
}Port_ConfigType;
/*------------------------------------------------*/

/***********************************************************************
 *                      Function Prototypes                            *
 ***********************************************************************/

/* Initializes the Port Driver module. */
void Port_Init(
				const Port_ConfigType* ConfigPtr
			  );
/*----------------------------------------------*/

/* Sets the port pin direction. */
#if (PORT_SET_PIN_DIRECTION_API == STD_ON)
void Port_SetPinDirection(
						  Port_PinType Pin,
						  Port_PinDirectionType Direction
						 );
#endif
/*-------------------------------------------------------*/

/* Refreshes port direction. */
void Port_RefreshPortDirection(
								void
							  );
/*----------------------------------*/

/* Returns the version information of this module. */
#if (PORT_VERSION_INFO_API == STD_ON)
void Port_GetVersionInfo(
						 Std_VersionInfoType* versioninfo
						);
#endif
/*-------------------------------------------------------*/

/* Sets the port pin mode. */
#if (PORT_SET_PIN_MODE_API == STD_ON)
void Port_SetPinMode(
					 Port_PinType Pin,
					 Port_PinModeType Mode
					);
#endif
/*-----------------------------------------*/

/**********************************************************************
 *                       External Variables                           *
 **********************************************************************/

extern const Port_ConfigType configuration;


#endif /* PORT_H_ */
