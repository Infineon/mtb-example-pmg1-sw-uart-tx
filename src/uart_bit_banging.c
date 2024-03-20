/******************************************************************************
* File Name: uart_bit_banging.c
*
* Description:
*  This file provides the source code for transmission of data
*  using SW bit banging technique
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

/*******************************************************************************
 * Include header files
 ******************************************************************************/
#include "uart_bit_banging.h"

/*******************************************************************************
* Function Name: uart_transmission
********************************************************************************
* Summary:
*  - Transmission of data to the UART terminal using SW bit banging technique
*
* Parameters:
* data, uartParity, uartStopBits
*
* Return:
*  None
*
*******************************************************************************/
void uart_transmission(uint8_t data, parityType uartParity, stopBitType uartStopBits)
{
    uint8_t parityCount = 0;

    // Start bit
    Cy_GPIO_Write(TX_PORT, TX_PIN, 0);
    Cy_SysLib_DelayCycles(DELAY);

    // Sending byte
    for (int i = 0; i < 8; i++)
    {
        uint8_t bitVal = (data >> i) & 1;
        Cy_GPIO_Write(TX_PORT, TX_PIN, bitVal);
        parityCount += bitVal;
        Cy_SysLib_DelayCycles(DELAY);
    }

    // Parity bit
    if (uartParity == PARITY_ODD)
    {
        // Set the parity bit to 1 if the number of 1s in the data is even
        Cy_GPIO_Write(TX_PORT, TX_PIN, (~parityCount & 1));
        Cy_SysLib_DelayCycles(DELAY);
    }
    else if (uartParity == PARITY_EVEN)
    {
        // Set the parity bit to 1 if the number of 1s in the data is odd
        Cy_GPIO_Write(TX_PORT, TX_PIN, (parityCount & 1));
        Cy_SysLib_DelayCycles(DELAY);
    }

    // Stop bit(s)
    for (int i = 0; i < uartStopBits; i++)
    {
        Cy_GPIO_Write(TX_PORT, TX_PIN, 1);
        Cy_SysLib_DelayCycles(DELAY);
    }
}

/*******************************************************************************
* Function Name: debug_print
********************************************************************************
*
* Summary:
*  Sends a string.
*
* Parameters:
*  string
*
* Return:
*  None
*
*******************************************************************************/
void debug_print(const char string[])
{
    /* Send characters over serial terminal */
    for (int i = 0; (string[i] != '\0' && i < MAX_LENGTH); i++)
    {
        uart_transmission((uint8_t)string[i], PARITY_NONE, STOP_BIT_1);
    }
}
