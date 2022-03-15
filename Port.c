/*----------------------------------------------------------------------------*
 * [MODULE]: Port
 *
 * [FILE NAME]: Port.c
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 13/1/2022
 *
 * [DESCRIPTION]: Source file for TM4C123GH6PM Micro-controller - Port Driver
 *----------------------------------------------------------------------------*/

/* including Port.h */
#include "Port.h"
/*------------------*/

/* including Port_Regs.h */
#include "Port_Regs.h"
/*-----------------------*/

/* macro for calculating the real address */
#define Real_address(Base_address , Offset_address)  \
      (*(volatile uint32 *)((volatile uint8 *)Base_address + Offset_address))


#if (PORT_DEV_ERROR_DETECT == STD_ON)

#include "Det.h"
/* AUTOSAR Version checking between Det and Port Modules */
#if ((DET_AR_MAJOR_VERSION != PORT_AR_RELEASE_MAJOR_VERSION)\
||   (DET_AR_MINOR_VERSION != PORT_AR_RELEASE_MINOR_VERSION)\
||   (DET_AR_PATCH_VERSION != PORT_AR_RELEASE_PATCH_VERSION))
#error "The AR version of Det.h does not match the expected version"
#endif

#endif

STATIC const Port_ConfigType * Pin_configuration = NULL_PTR;
STATIC uint8 Port_Status = PORT_NOT_INITIALIZED;


/*****************************************************************
 * Service name: Port_Init
 *
 * Syntax: void Port_Init(
 *                         const Port_ConfigType* ConfigPtr
 *			 )
 *
 * Service ID[hex]: 0x00
 *
 * Sync/A-sync: Synchronous
 *
 * Re-entrancy: Non Reentrant
 *
 * Parameters (in): ConfigPtr Pointer to configuration set.
 *
 * Parameters(in/out): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 * Description: Initializes the Port Driver module.
 *****************************************************************/
void Port_Init(
		const Port_ConfigType* ConfigPtr
              )
{
#if (PORT_DEV_ERROR_DETECT == STD_ON)
     /* check if the input configuration pointer is not a NULL_PTR */
      if (NULL_PTR == ConfigPtr)
        {
	  Det_ReportError(PORT_MODULE_ID, PORT_INSTANCE_ID, PORT_INIT_SID,
				PORT_E_PARAM_CONFIG);
	}
      else
#endif
        {
	 /*
	  * Set the module state to initialized and point to the PB configuration structure using a global pointer.
	  * This global pointer is global to be used by other functions to read the PB configuration structures
	  */
	  Port_Status          = PORT_INITIALIZED;
	  Pin_configuration    = ConfigPtr;


	  volatile uint32 * BASE_ADDRESS = NULL_PTR; /* point to the required Port Registers base address */
	  volatile uint32 delay = 0;

	  for(Port_PinType i = 0; i < PORT_CONFIGURED_PINS ; i++)
	    {

	      switch(Pin_configuration->pin[i].port_num)
	        {
		 case  0: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS; /* PORTA Base Address */
		 break;
		 case  1: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; /* PORTB Base Address */
		 break;
		 case  2: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; /* PORTC Base Address */
		 break;
		 case  3: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; /* PORTD Base Address */
		 break;
		 case  4: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; /* PORTE Base Address */
		 break;
		 case  5: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; /* PORTF Base Address */
		 break;
		}

/*1.REGCGC2:*/
	    /* Enable clock for PORT and allow time for clock to start*/
		SYSCTL_REGCGC2_REG |= (1<<(Pin_configuration->pin[i].port_num));
		delay = SYSCTL_REGCGC2_REG;
	    /*----------------------------------------------------------------*/

		if( ((Pin_configuration->pin[i].port_num) == PORT_C_ID) && ((Pin_configuration->pin[i].pin_num) <= PIN_3_ID) ) /* PC0 to PC3 */
		  {
		    /* Do Nothing ...  this is the JTAG pins */
		    continue;
		  }
		else
		  {

/*2.GPIOLOCK:   */
		/* this is the magic number to unlock the commit register */
		    Real_address(BASE_ADDRESS , LOCK_REG_OFFSET_ADDRESS) = 0x4C4F434B;
		/*-----------------------------------------------------------------*/

/*GPIOCR:        */
		/* CR: Commit register */
		/* by setting this bit in the CR the data written in the *
		 * AFSEL, PUR, PDR, DEN is committed.                    */
		    SET_BIT(Real_address(BASE_ADDRESS , CR_REG_OFFSET_ADDRESS) , Pin_configuration->pin[i].pin_num);
		   }
		/*----------------------------------------------------------------------------------------------*/

/*3.GPIOAFSEL:*/
		/* AFSEL: Alternate Function Select register */
		if( (Pin_configuration->pin[i].mode) == MODE_0_DIO )
		  {
		    /* clearing this bit as we need it GPIO */
			CLEAR_BIT(Real_address(BASE_ADDRESS , AFSEL_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));
		  }
		else
		  {
		   /* setting this bit as we need it GPIO */
			SET_BIT(Real_address(BASE_ADDRESS , AFSEL_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));
		  }
		/*-------------------------------------------------------------------------------------------------------*/

/*4.GPIOAMSEL:*/
		/* AMSEL: Analog Mode Select register */
		if( (Pin_configuration->pin[i].mode) == MODE_0_ADC )
		  {
		   /* setting this bit as we need ADC */
		        SET_BIT(Real_address(BASE_ADDRESS , AMSEL_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));
		  }
		else
		  {
		   /* clearing this bit as we need digital */
			CLEAR_BIT(Real_address(BASE_ADDRESS , AMSEL_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));
		  }
		/*---------------------------------------------------------------------------------------------------------*/

/*5.GPIODEN:*/
		/* DEN: Digital enable */
		if( (Pin_configuration->pin[i].mode) == MODE_0_ADC )
		  {
		   /* clearing this bit as we need ADC */
			CLEAR_BIT(Real_address(BASE_ADDRESS , DEN_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));
		  }
		else
		  {
		   /* setting this bit as we need Digital mode */
                        SET_BIT(Real_address(BASE_ADDRESS , DEN_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));
		  }
                /*----------------------------------------------------------------------------------------------------------*/

/*6.GPIODIR:    */
		/* DIR: Direction register */
		if( (Pin_configuration->pin[i].direction) == PORT_PIN_IN )
		  {
                   /* Clearing a bit configures the corresponding pin as input */
		    CLEAR_BIT(Real_address(BASE_ADDRESS , DIR_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));

/*7.GPIOPUR:            */
		  /* PUR: pull-up register */
		  if((Pin_configuration->pin[i].resistor) == PULL_UP )
                    {
                     /* Setting this bit enables pull-up resistor to this pin and *
                      * automatically clears the corresponding bit in the PDR     */
                      SET_BIT(Real_address(BASE_ADDRESS , PUR_REG_OFFSET_ADDRESS) , Pin_configuration->pin[i].pin_num);
		    }
                  else
                    {         /* DO nothing */        }
                /*-----------------------------------------------------------------------------------------------------*/

/*8.GPIOPDR:    */
                /* PDR: pull-down register */
                  if((Pin_configuration->pin[i].resistor) == PULL_DOWN )
                    {
                     /* Setting this bit enables pull-down resistor to this pin and *
                      * automatically clears the corresponding bit in the PUR       */
                      SET_BIT(Real_address(BASE_ADDRESS , PDR_REG_OFFSET_ADDRESS) , Pin_configuration->pin[i].pin_num);
                    }
                  else
                    {         /* DO nothing */        }
                /*-----------------------------------------------------------------------------------------------------*/
                        
                /* checking if the internal resistor is turned off */
                   if((Pin_configuration->pin[i].resistor) == OFF )
                     {
                      /* clearing these two bits if the internal resistor is turned off */
                       CLEAR_BIT(Real_address(BASE_ADDRESS , PDR_REG_OFFSET_ADDRESS) , Pin_configuration->pin[i].pin_num);
                       CLEAR_BIT(Real_address(BASE_ADDRESS , PUR_REG_OFFSET_ADDRESS) , Pin_configuration->pin[i].pin_num);
                     }
                   else
                     {         /* DO nothing */        }
                /*-----------------------------------------------------------------------------------------------------*/

		  }
		else
		  {
	           /* Setting a bit configures the corresponding pin as output */
	           SET_BIT(Real_address(BASE_ADDRESS , DIR_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));

/*9.GPIODATA:   */
	           /* DATA: data register */
	           if( (Pin_configuration->pin[i].initial_value) == STD_HIGH )
	             {
                      /* setting this bit if initial value is STD_HIGH */
		       SET_BIT(Real_address(BASE_ADDRESS , DATA_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));
		     }
	           else
		     {
		      /* clearing this bit if initial value is STD_LOW */
		       CLEAR_BIT(Real_address(BASE_ADDRESS , DATA_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[i].pin_num));
		     }
		  }
		 /*----------------------------------------------------------------------------------------------------------*/


/*10.GPIOPCTL: */
		/* GPIOPCTL: port control register */
		 if((Pin_configuration->pin[i].mode == MODE_0_ADC) || (Pin_configuration->pin[i].mode == MODE_0_DIO))
		   {
		    /* clearing this bit as ADC mode has ID 0 */
		      Real_address(BASE_ADDRESS , PCTL_REG_OFFSET_ADDRESS) &=\
					~(0x0000000F<<((Pin_configuration->pin[i].pin_num))*4);
		   }
		 else
		   {
		    /* putting the corresponding mode number in the corresponding 4-bits   *
		     * let's consider a scenario as the following:                         *
		     * if mode is 1 , pin number is 3                                      *
		     * firstly it clears the 4 bits of pin number 3                        *
		     * then inserting the mode number(i.e. 1).                             */
		      Real_address(BASE_ADDRESS , PCTL_REG_OFFSET_ADDRESS) &=\
					~(0x0000000F<<((Pin_configuration->pin[i].pin_num))*4);
		      Real_address(BASE_ADDRESS , PCTL_REG_OFFSET_ADDRESS) |=\
					((Pin_configuration->pin[i].mode)<<((Pin_configuration->pin[i].pin_num))*4);
		   }
		/*---------------------------------------------------------------------------------------------*/
		}
	}
}


#if ( PORT_SET_PIN_DIRECTION_API == STD_ON)

/************************************************************************************
 * Service name: Port_SetPinDirection
 *
 * Syntax: void Port_SetPinDirection(
 *	               	 	      Port_PinType Pin,
 *	 	 	              Port_PinDirectionType Direction
 *                                  )
 *
 *Service ID[hex]: 0x01
 *
 *Sync/A-sync:  Synchronous
 *
 *Re-entrancy:  Reentrant
 *
 *Pin Port Pin ID number Parameters (in): Direction Port Pin Direction
 *
 *Parameters (in/out): None
 *
 *Parameters (out):   None
 *
 *Return value:       None
 *
 *Description: Sets the port pin direction
 ************************************************************************************/

void Port_SetPinDirection(
		           Port_PinType Pin,
		           Port_PinDirectionType Direction
                          )
{

/********************************** DET_ERRORS checking **********************************/
  boolean error = FALSE;
#if(PORT_DEV_ERROR_DETECT == STD_ON)

  /* no. of pins checking if this function takes more than 42                  *
   * then it will send DET_ERROR                                               *
   * with error ID: PORT_E_PARAM_PIN as stipulated by the AUTOSAR.             */

  /*1*/if(Pin >= PORT_CONFIGURED_PINS)
	 {
	   Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, \
                                 PORT_SET_PIN_DIRECTION_SID, PORT_E_PARAM_PIN );
	   error = TRUE;
	 }
       else
	 { /* No action required */ }

  /* checking if this pin is configured as direction changeable pin            *  
   * so, if this function takes a Pin which is configured                      *
   * as direction unchangeable it will send DET_ERROR                          *
   * with error ID: PORT_E_DIRECTION_UNCHANGEABLE as stipulated by the AUTOSAR.*/

  /*2*/if(Pin_configuration->pin[Pin].pin_direction_changeable == STD_OFF)
	 {
	   Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, \
                    PORT_SET_PIN_DIRECTION_SID, PORT_E_DIRECTION_UNCHANGEABLE );
	   error = TRUE;
	 }
       else
	 { /* No action required */ }

  /* checking if the port_driver is not initialized yet         *
   * so, if it'snt initialized then it will send DET_ERROR      *
   * with error ID: PORT_E_UNINIT as stipulated by the AUTOSAR. */

  /*3*/if(Port_Status == PORT_NOT_INITIALIZED)
	 {
	   Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, \
                                    PORT_SET_PIN_DIRECTION_SID, PORT_E_UNINIT );
	   error = TRUE;
	 }
       else
	 { /* No action required */ }

#endif
/*****************************************************************************************/

  if(error == FALSE)
    {
      /* point to the required Port Registers base address */
      volatile uint32 * BASE_ADDRESS = NULL_PTR; 
      switch(Pin_configuration->pin[Pin].port_num)
	    {
             /* PORTA Base Address */
              case  0: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
              break;
             /* PORTB Base Address */
              case  1: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
              break;
             /* PORTC Base Address */
              case  2: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
              break;
             /* PORTD Base Address */
              case  3: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; 
              break;
             /* PORTE Base Address */
              case  4: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
              break;
             /* PORTF Base Address */
              case  5: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; 
              break;
	    }


/*GPIODIR:*/
	/* DIR: Direction register */
	 if( (Direction) == PORT_PIN_IN )
	   {
	    /* Clearing a bit configures the corresponding pin as input */
	       CLEAR_BIT(Real_address(BASE_ADDRESS , DIR_REG_OFFSET_ADDRESS) , \
                                         (Pin_configuration->pin[Pin].pin_num));
	   }
	 else
	   {
	    /* Setting a bit configures the corresponding pin as output */
	       SET_BIT(Real_address(BASE_ADDRESS , DIR_REG_OFFSET_ADDRESS) , \
                                         (Pin_configuration->pin[Pin].pin_num));
	   }
    }
  else
    {       /*    Do nothing...    */               }
}
#endif



/****************************************************
 * Service name: Port_RefreshPortDirection
 *
 * Syntax:   void Port_RefreshPortDirection(
 *                                          void
 *                                         )
 *
 * Service ID[hex]: 0x02
 *
 * Sync/A-sync: Synchronous
 *
 * Re-entrancy: Non Reentrant
 *
 * Parameters (in): None
 *
 * Parameters (in/out): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 * Description: Refreshes port direction.
 *****************************************************/
void Port_RefreshPortDirection(
		                void
                              )
{
/********************************** DET_ERRORS checking **********************************/
   boolean error = FALSE;
#if(PORT_DEV_ERROR_DETECT == STD_ON)

   /* checking if the port_driver is not initialized yet         *
    * so, if it'snt initialized then it will send DET_ERROR      *
    * with error ID: PORT_E_UNINIT as stipulated by the AUTOSAR. */

   /*1*/if(Port_Status == PORT_NOT_INITIALIZED)
	  {
	   Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, \
                               PORT_REFRESH_PORT_DIRECTION_SID, PORT_E_UNINIT );
	   error = TRUE;
	  }
	else
	  { /* No action required */ }

#endif
/*****************************************************************************************/
   if(error == FALSE)
     {
       /* point to the required Port Registers base address */
       volatile uint32 * BASE_ADDRESS = NULL_PTR; 
       for(Port_PinType i = 0; i < PORT_CONFIGURED_PINS ; i++)
          {
	   switch(Pin_configuration->pin[i].port_num)
		{
                 /* PORTA Base Address */
                 case  0: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
                 break;
                 /* PORTB Base Address */
                 case  1: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
                 break;
                 /* PORTC Base Address */
                 case  2: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
                 break;
                 /* PORTD Base Address */
                 case  3: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; 
                 break;
                 /* PORTE Base Address */
                 case  4: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
                 break;
                 /* PORTF Base Address */
                 case  5: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; 
                 break;
		}
	   /* The function Port_RefreshPortDirection shall exclude those port  *
	    * pins from refreshing that are configured as                      *
            * 'pin direction changeable during runtime'.                       */
	   if( (Pin_configuration->pin[i].pin_direction_changeable) == STD_OFF )
	     {

/*GPIODIR:                         */
	       /* DIR: Direction register */
	        if( (Pin_configuration->pin[i].direction) == PORT_PIN_IN )
	          {
	           /*Clearing a bit configures the corresponding pin as input*/
		   CLEAR_BIT(Real_address(BASE_ADDRESS, DIR_REG_OFFSET_ADDRESS)\
                                         , (Pin_configuration->pin[i].pin_num));
	          }
	        else
	          {
		   /*Setting a bit configures the corresponding pin as output*/
		   SET_BIT(Real_address(BASE_ADDRESS , DIR_REG_OFFSET_ADDRESS) \
                                         , (Pin_configuration->pin[i].pin_num));
	          }
	     }
	   else
	     { /* Do nothing */ }
          }
     }
   else
     { /* Do nothing */ }
}


#if(PORT_SET_PIN_MODE_API == STD_ON)

/***************************************************************************
 * Service name: Port_SetPinMode
 *
 * Syntax: void Port_SetPinMode(
 *	 	 	 	 Port_PinType Pin,
 *	 	 	 	 Port_PinModeType Mode
 *			       )
 *
 * Service ID[hex]: 0x04
 *
 * Sync/A-sync: Synchronous
 *
 * Re-entrancy: Reentrant
 *
 * Pin Port Pin ID number Parameters (in): Mode New Port Pin mode to be set 
 *                                         on port pin.
 *
 * Parameters(in/out): None
 *
 * Parameters (out): None
 *
 * Return value: None
 *
 * Description: Sets the port pin mode.
 ***************************************************************************/

void Port_SetPinMode(
		     Port_PinType Pin,
		     Port_PinModeType Mode
                    )
{

/********************************** DET_ERRORS checking **********************************/
    boolean error = FALSE;
#if(PORT_DEV_ERROR_DETECT == STD_ON)

    /* no. of pins checking if this function takes more than 42 then           *
     * it will send DET_ERROR                                                  *
     * with error ID: PORT_E_PARAM_PIN as stipulated by the AUTOSAR.           */
	
  /*1*/if(Pin >= PORT_CONFIGURED_PINS)
	 {
	  Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, \
                                      PORT_SET_PIN_MODE_SID, PORT_E_PARAM_PIN );
	  error = TRUE;
	 }
       else
	 { /* No action required */ }

    /* checking if this pin is configured as mode changeable pin               *
     * so, if this function takes a Pin which is configured                    *
     * as mode unchangeable it will send DET_ERROR                             *
     * with error ID: PORT_E_MODE_UNCHANGEABLE as stipulated by the AUTOSAR.   */
	
  /*2*/if(Pin_configuration->pin[Pin].pin_mode_changeable == STD_OFF)
	 {
	  Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, \
                              PORT_SET_PIN_MODE_SID, PORT_E_MODE_UNCHANGEABLE );
	  error = TRUE;
	 }
       else
	 { /* No action required */ }

    /* checking if the mode passed to this function is available               *
     * so, if not it will send DET_ERROR                                       *
     * with error ID: PORT_E_PARAM_INVALID_MODE as stipulated by the AUTOSAR.  */
	
  /*3*/if(Mode > PORT_AVAILABLE_MODES)
	 {
	  Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID,\
                             PORT_SET_PIN_MODE_SID, PORT_E_PARAM_INVALID_MODE );
	  error = TRUE;
	 }
       else
	 { /* No action required */ }

    /* checking if the port_driver is not initialized yet         *
     * so, if it'snt initialized then it will send DET_ERROR      *
     * with error ID: PORT_E_UNINIT as stipulated by the AUTOSAR. */
	
  /*4*/if(Port_Status == PORT_NOT_INITIALIZED)
	 {
	  Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID,\
                                         PORT_SET_PIN_MODE_SID, PORT_E_UNINIT );
	  error = TRUE;
	 }
       else
	 { /* No action required */ }

#endif
/*****************************************************************************************/

    if(error == FALSE)
      {
       /* point to the required Port Registers base address */
       volatile uint32 * BASE_ADDRESS = NULL_PTR; 

       switch(Pin_configuration->pin[Pin].port_num)
	     {
              /* PORTA Base Address */
	      case  0: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTA_BASE_ADDRESS;
	      break;
	      /* PORTB Base Address */
              case  1: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTB_BASE_ADDRESS; 
	      break;
              /* PORTC Base Address */
	      case  2: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTC_BASE_ADDRESS; 
	      break;
              /* PORTD Base Address */
	      case  3: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTD_BASE_ADDRESS; 
	      break;
              /* PORTE Base Address */
	      case  4: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTE_BASE_ADDRESS; 
	      break;
              /* PORTF Base Address */
	      case  5: BASE_ADDRESS = (volatile uint32 *)GPIO_PORTF_BASE_ADDRESS; 
	      break;
	     }
		
/*GPIOAFSEL:*/
    /* AFSEL: Alternate Function Select register */
    if( Mode == MODE_0_DIO )
      {
	/* clearing this bit as we need it GPIO */
	CLEAR_BIT(Real_address(BASE_ADDRESS , AFSEL_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[Pin].pin_num));
      }
    else
      {
	/* setting this bit as we need it GPIO */
	SET_BIT(Real_address(BASE_ADDRESS , AFSEL_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[Pin].pin_num));
      }
/*-------------------------------------------------------------------------------------------------------*/

      
/*GPIOAMSEL:*/
    /* AMSEL: Analog Mode Select register */
    if( Mode == MODE_0_ADC )
      {
       /* setting this bit as we need ADC */
	 SET_BIT(Real_address(BASE_ADDRESS , AMSEL_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[Pin].pin_num));
      }
    else
      {
       /* clearing this bit as we need digital */
	CLEAR_BIT(Real_address(BASE_ADDRESS , AMSEL_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[Pin].pin_num));
      }
/*---------------------------------------------------------------------------------------------------------*/

      
/*GPIODEN:*/
    /* DEN: Digital enable */
    if( Mode == MODE_0_ADC )
      {
       /* clearing this bit as we need ADC */
	CLEAR_BIT(Real_address(BASE_ADDRESS , DEN_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[Pin].pin_num));
      }
    else
      {
       /* setting this bit as we need Digital mode */
        SET_BIT(Real_address(BASE_ADDRESS , DEN_REG_OFFSET_ADDRESS) , (Pin_configuration->pin[Pin].pin_num));
      }
/*----------------------------------------------------------------------------------------------------------*/

/*GPIOPCTL:                                */
    /* GPIOPCTL: port control register */
    if((Mode == MODE_0_ADC) || (Mode == MODE_0_DIO))
      {
      /* clearing this bit as ADC mode has ID 0 */
	Real_address(BASE_ADDRESS , PCTL_REG_OFFSET_ADDRESS) &=\
			~(0x0000000F<<((Pin_configuration->pin[Pin].pin_num))*4);
      }
    else
      {
      /* putting the corresponding mode number in the corresponding 4-bits   *
       * let's consider a scenario as the following:                         *
       * if mode is 1 , pin number is 3                                      *
       * firstly it clears the 4 bits of pin number 3                        *
       * then inserting the mode number(i.e. 1).                             */
        Real_address(BASE_ADDRESS , PCTL_REG_OFFSET_ADDRESS) &=\
		       ~(0x0000000F<<((Pin_configuration->pin[Pin].pin_num))*4);
	Real_address(BASE_ADDRESS , PCTL_REG_OFFSET_ADDRESS) |=\
			    ((Mode)<<((Pin_configuration->pin[Pin].pin_num))*4);
      }
      }
    else
      { /* Do nothing */ }
}

#endif


#if (PORT_VERSION_INFO_API == STD_ON)

/***************************************************************************
 * Service name: Port_GetVersionInfo
 *
 * Syntax: void Port_GetVersionInfo(
 *				    Std_VersionInfoType* versioninfo
 *       			   )
 *
 * Service ID[hex]: 0x03
 *
 * Sync/A-sync: Synchronous
 *
 * Re-entrancy: Non Reentrant
 *
 * Parameters (in): None
 *
 * Parameters(in/out): None
 *
 * Parameters (out): versioninfo Pointer to where to store 
 *                   the version information of this module.
 *
 * Return value: None
 *
 * Description: Returns the version information of this module.
 ***************************************************************************/

void Port_GetVersionInfo(
		         Std_VersionInfoType* versioninfo
                         )
{
    boolean error = FALSE;
#if (PORT_DEV_ERROR_DETECT == STD_ON)
    /* Check if input pointer is not Null pointer */
  /*1*/if(NULL_PTR == versioninfo)
	 {
          /* Report to DET  */
           Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, \
                              PORT_GET_VERSION_INFO_SID, PORT_E_PARAM_POINTER );
	   error = TRUE;
	 }
       else
	 { /* Do nothing */ }

    /* checking if the port_driver is not initialized yet         *
     * so, if it'snt initialized then it will send DET_ERROR      *
     * with error ID: PORT_E_UNINIT as stipulated by the AUTOSAR. */
   /*2*/if(Port_Status == PORT_NOT_INITIALIZED)
	  {
	   Det_ReportError( PORT_MODULE_ID, PORT_INSTANCE_ID, \
                                     PORT_GET_VERSION_INFO_SID, PORT_E_UNINIT );
	   error = TRUE;
	  }
	else
	  { /* No action required */ }

#endif /* (DIO_DEV_ERROR_DETECT == STD_ON) */
	
    if(error == FALSE)
      {
       /* Copy the vendor Id */
	versioninfo->vendorID = (uint16)PORT_VENDOR_ID;
       /* Copy the module Id */
	versioninfo->moduleID = (uint16)PORT_MODULE_ID;
       /* Copy Software Major Version */
	versioninfo->sw_major_version = (uint8)PORT_SW_MAJOR_VERSION;
       /* Copy Software Minor Version */
	versioninfo->sw_minor_version = (uint8)PORT_SW_MINOR_VERSION;
       /* Copy Software Patch Version */
	versioninfo->sw_patch_version = (uint8)PORT_SW_PATCH_VERSION;
      }
}

#endif










