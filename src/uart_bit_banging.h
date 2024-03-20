/******************************************************************************
* File Name: uart_bit_banging.h
* Version 1.0
*
* Description:
* This file contains the structure declaration and function prototypes used in
*  the uart_bit_banging source code.
*
* Related Document: See README.md
*
*******************************************************************************
* Copyright 2023-2024, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/
#ifndef UART_BIT_BANGING_H_
#define UART_BIT_BANGING_H_

/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "cy_syslib.h"
#include "cy_gpio.h"
#include "cycfg_pins.h"
#include "stdio.h"
#include "string.h"
#include "math.h"

/*******************************************************************************
 * Macro declarations
 ******************************************************************************/
/* Baud rate */
#define BAUD_RATE           115200

/* Delay applied for any Baud rate = (SystemCoreClock / BAUD_RATE) */

/* This parameter is used to generate the period for UART data pulse.
 * It needs to be adjusted for current system clock, compiler optimizations
 * or current baud rate. Add or subtract a number to adjust the timings
 * of the UART data pulses for the required baud rate.
 */

#define DELAY               ((SystemCoreClock / BAUD_RATE)-144)

/* Array maximum length */
#define MAX_LENGTH          128

/* Parity bit*/
typedef enum
{
    PARITY_NONE = 0,
    PARITY_ODD,
    PARITY_EVEN
} parityType;

/* Number of stop bits*/
typedef enum
{
    STOP_BIT_1 = 1,
    STOP_BIT_2
} stopBitType;

/******************************************************************************
 * Global function declaration
 ******************************************************************************/
void uart_transmission(uint8_t data, parityType uartParity, stopBitType uartStopBits);
void debug_print(const char string[]);

/******************************************************************************
 * End of declaration
 ******************************************************************************/
#endif /* UART_BIT_BANGING_H_ */


