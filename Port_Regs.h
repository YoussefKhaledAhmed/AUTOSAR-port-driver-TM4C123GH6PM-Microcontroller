/* ---------------------------------------------------------------------------------------
 * [MODULE]: Port
 *
 * [FILE NAME]: Port_Regs.h
 *
 * [AUTHOR]: YOUSEF KHALED AHMED ZAYED
 *
 * [DATE CREATED]: 11/1/2022
 *
 * [DESCRIPTION]: Header file for TM4C123GH6PM Microcontroller - Port Driver Registers
 ---------------------------------------------------------------------------------------*/

#ifndef PORT_REGS_H /* Guarding for this header file */
#define PORT_REGS_H


/* Ports BASE address */
#define GPIO_PORTA_BASE_ADDRESS  0X40004000     /* PORTA base address*/
#define GPIO_PORTB_BASE_ADDRESS  0X40005000     /* PORTB base address*/
#define GPIO_PORTC_BASE_ADDRESS  0X40006000     /* PORTC base address*/
#define GPIO_PORTD_BASE_ADDRESS  0X40007000     /* PORTD base address*/
#define GPIO_PORTE_BASE_ADDRESS  0X40024000    /* PORTE base address*/
#define GPIO_PORTF_BASE_ADDRESS  0X40025000    /* PORTF base address*/
/*-----------------------------------------*/

/* Registers offset address */
#define DATA_REG_OFFSET_ADDRESS    0X000  /* Data register offset address */
#define DIR_REG_OFFSET_ADDRESS     0X400  /* Direction register offset address */
#define AFSEL_REG_OFFSET_ADDRESS   0X420  /* Alternate function select register offset address */
#define PUR_REG_OFFSET_ADDRESS     0X510  /* Pull-up select register offset address */
#define PDR_REG_OFFSET_ADDRESS     0X514  /* Pull-down select register offset address */
#define DEN_REG_OFFSET_ADDRESS     0X51C  /* Digital enable register offset address */
#define LOCK_REG_OFFSET_ADDRESS    0X520  /* Lock register offset address */
#define CR_REG_OFFSET_ADDRESS      0X524  /* Commit register offset address */
#define AMSEL_REG_OFFSET_ADDRESS   0X528  /* Analog mode select register offset address */
#define PCTL_REG_OFFSET_ADDRESS    0X52C  /* Port control register offset address */

#define SYSCTL_REGCGC2_REG        (*((volatile unsigned long *)0x400FE108))
/*--------------------------------------------------------------------------------------------*/


#endif /*PORT_REGS_H*/











