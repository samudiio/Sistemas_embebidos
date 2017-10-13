/*
 * Uart_Types.h
 *
 *  Created on: Oct 5, 2017
 *  Brief: Types used by uper layers
 */

#ifndef UART_TYPES_H
#define UART_TYPES_H

#include "Std_Types.h"

#define UART_LOGCH0    0
#define UART_LOGCH1    1
#define UART_LOGCH2    2
#define UART_LOGCH3    3
#define UART_LOGCH4    4


typedef enum
{
    UART_ERROR_OVERRUN = 0,
    UART_ERROR_FRAMING = 1,
    UART_ERROR_PARITY = 2
}UartErrorType;

#endif /* UART_TYPES_H */
