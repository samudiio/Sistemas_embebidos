/*
 * Uart.h
 *
 *  Created on: Oct 2017
 *  Brief:      Types provided to the user component modules
 */

#ifndef Uart_H_   /*prevent duplicated includes*/
#define Uart_H_

//  Includes 
 #include <Std_Types.h>
 #include <Uart_Cfg.h>
 #include <Uart_Types.h>

//  Defines
 #define UART_MASK_RXRDY = 1
 #define UART_MASK_TXRDY = 2
 #define UART_MASK_OVRE = 32
 #define UART_MASK_FRAME = 64
 #define UART_MASK_PARE = 128
 #define UART_MASK_TXEMPTY = 512


//  Function Protypes

// Initializes the UART module
 void Uart_Init(const Uart_ConfigType *Config);

//  Sets the requested baudrate to the addressed UART channel
 Std_ReturnType Uart_SetBaurate(uint8_t Channel, uint32_t Baudrate);

//  Enables or disables the transmitter of the UART module
void Uart_SetTxEnable(uint8_t Channel, uint32_t Enable);

// Enables or disables the receiver of the UART module
void Uart_SetRxEnable (uint8_t Channel, uint32_t Enable);

// Sends one packet of data through the specified UART module
Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte );

// Sends a packet of data through the specified UART channel
Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t *Buffer, uint16_t Length);

// Reads and returns a character from the UART module
void Uart_GetByte (uint8_t Channel, uint8_t Byte);

// Reads and returns the current status of the addressed UART module
void Uart_GetStatus (uint8_t Channel, uint32_t *Status);

// Reads and returns the current status of the addressed UART module.
// Enable/disable the UART module interrupts according to the IntMode and Enable parameters.
void Uart_EnableInt (uint8_t Channel, uint32_t IntMode, uint8_t Enabl );
 #endif /* Uart_H_ */