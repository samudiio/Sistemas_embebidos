/*
 * Uart_Types.h
 *
 *  Created on: Oct 5, 2017
 *  Brief: Types used by uper layers
 */

#ifndef UART_TYPES_H
#define UART_TYPES_H

#include "Std_Types.h"

typedef enum
{
    UART_ERROR_OVERRUN = 0,
    UART_ERROR_FRAMING = 1,
    UART_ERROR_PARITY = 2
}UartErrorType;

#endif /* UART_TYPES_H */
