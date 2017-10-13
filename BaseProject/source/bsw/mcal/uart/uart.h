/* ----------------------------------------------------------------------------
 *         SAM Software Package License
 * ----------------------------------------------------------------------------
 * Copyright (c) 2011, Atmel Corporation
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Atmel's name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY ATMEL "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL ATMEL BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ----------------------------------------------------------------------------
 */


#ifndef UART_H
#define UART_H

#include "Uart_Cfg.h"
#include "Uart_Types.h"

//extern const Uart_ConfigType Uart_Config[];

#define UART_MASK_RXRDY     1
#define UART_MASK_TXRDY     2
#define UART_MASK_OVRE      32
#define UART_MASK_FRAME     64
#define UART_MASK_PARE      128
#define UART_MASK_TXEMPTY   512

//------------------------------------------------------------------------------
//         Global functions
//------------------------------------------------------------------------------

/*
 * Brief: Initializes the UART module
 */
void Uart_Init(const Uart_ConfigType *Config);

/*
 * Brief: Sets the requested baudrate to the addressed UART channel
 */
Std_ReturnType Uart_SetBaudrate(uint8_t Channel, uint32_t Baudrate);

/*
 * Brief: Enables or disables the transmitter of the UART module
 */
void Uart_SetTxEnable(uint8_t Channel, uint8_t Enable);

/*
 * Brief: Enables or disables the receiver of the UART module
 */
void Uart_SetRxEnable(uint8_t Channel, uint8_t Enable);

/*
 * Brief: Sends one packet of data through the specified UART module
 */
Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte);

/*
 * Brief: Sends a packet of data through the specified UART channel
 */
Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t *Buffer, uint16_t Length);

/*
 * Brief: Reads and returns a character from the UART module
 */
void Uart_GetByte(uint8_t Channel, uint8_t Byte);

/*
 * Brief: Reads and returns the current status of the addressed UART module
 */
void Uart_GetStatus(uint8_t Channel, uint32_t *Status);

/*
 * Brief: Enable/disable the UART module interrupts according to the IntMode and Enable parameters
 */
void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable);







void UART_Configure(Uart *uart, uint32_t mode, uint32_t baudrate, uint32_t masterClock);

void UART_SetTransmitterEnabled(Uart *uart, uint8_t enabled);

void UART_SetReceiverEnabled(Uart *uart, uint8_t enabled);

void UART_PutChar( Uart *uart, uint8_t c);

uint32_t UART_IsRxReady(Uart *uart);

uint8_t UART_GetChar(Uart *uart);

uint32_t UART_GetStatus(Uart *uart);

void UART_EnableIt(Uart *uart,uint32_t mode);

void UART_DisableIt(Uart *uart,uint32_t mode);

uint32_t UART_GetItMask(Uart *uart);

void UART_SendBuffer(Uart *uart, uint8_t *pBuffer, uint32_t BuffLen);

void UART_ReceiveBuffer(Uart *uart, uint8_t *pBuffer, uint32_t BuffLen);

void UART_CompareConfig(Uart *uart, uint8_t Val1, uint8_t Val2);

uint32_t UART_IsTxReady(Uart *uart);

#endif //#ifndef UART_H

