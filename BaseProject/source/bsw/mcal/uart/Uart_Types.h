/*
 * Uart_Types.h
 *
 *  Created on: Oct 2017
 *  Brief:      Types provided to the user component modules
 */
#ifndef UART_TYPES_H
#define UART_TYPES_H

#include <Std_Types.h>

typedef enum{
    UART_ERROR_OVERRUN,
    UART_ERROR_FRAMING,
    UART_ERROR_PARITY
}UartErrorType;

#endif

