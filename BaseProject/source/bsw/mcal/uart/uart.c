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

/**
 * \file
 *
 * Implementation of UART (Universal Asynchronous Receiver Transmitter)
 * controller.
 *
 */
/*------------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/
//#include "chip.h"
#include "uart.h"
#include "samv71q21.h"

#include "board.h"

//#include <assert.h>
#include <string.h>


/*------------------------------------------------------------------------------
 *         Defines
 *----------------------------------------------------------------------------*/

#define UART_MAX_NUM_CH 5

#define COMPILAR    TRUE

/*------------------------------------------------------------------------------
 *         Types Definitions
 *----------------------------------------------------------------------------*/

typedef enum
{
    Uart_NotBussy = 0,
    Uart_Bussy,
}Uart_State_Type;

/*
 * Channel-specific status parameters
 */
typedef struct
{
    uint8_t Channel;
    Uart_State_Type TxBussy;
    Uart_State_Type RxBussy;
}Uart_ChStatusType;

/*
 * Driver-specific status parameters
 */
typedef struct
{
    uint8_t ChannelNumber;
    const Uart_ChStatusType *PtrChStatus;
}Uart_StatusType;


/*------------------------------------------------------------------------------
 *         Global Variables
 *----------------------------------------------------------------------------*/

const Uart_ConfigType *UartConfigPtr;
const Uart_StatusType *UartStatusPtr;
const Uart *UartArray[UART_MAX_NUM_CH] = {UART0, UART1, UART2, UART3, UART4};
const uint32_t UartPeriphId[UART_MAX_NUM_CH] = {ID_UART0, ID_UART1, ID_UART2, ID_UART3, ID_UART4};
const Pin UartPinId[UART_MAX_NUM_CH] = {PINS_UART0, PINS_UART1, PINS_UART2, PINS_UART3, PINS_UART4};

const Uart_ChStatusType ChStatus[] =
{
    {
        UartCfg_PhyCh_0,
        Uart_NotBussy,
        Uart_NotBussy,
    }
};

const Uart_StatusType Uart_Status[] =
{
    {
        sizeof(ChStatus)/sizeof(ChStatus[0]),
        &ChStatus[0]
    }
};


/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
/*
 * Brief: Generic UART interrupt service routine
 * @Param in:
 *  Channel - UART Channel to be addressed
 * @Param out:
 *  None
 * @Return type
 *  void
 */
void Uart_Isr(uint8_t Channel)
{

}

/*------------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/*
 * Brief: Initializes the UART module
 * @Param in:
 *  Config - Pointer to Uart static configuration
 * @Param out:
 *  None
 * @Return type
 *  void
 */
void Uart_Init(const Uart_ConfigType *Config)
{
    uint8_t Uart_Idx;
    uint8_t PhyChannel;
    uint8_t Mdiv_Val;
    uint8_t Isr_Val;
    uint32_t Pck;
    Uart *LocalUart;

    UartConfigPtr = Config;

    /*Memory allocation for satus control structure*/
    UartStatusPtr = (Uart_StatusType*) Mem_Alloc( (sizeof(Uart_StatusType)) * (UartConfigPtr->UartNoOfChannels) );

    /*para los devices*/
    //for()

    for(Uart_Idx=0; Uart_Idx < UartConfigPtr->UartNoOfChannels; Uart_Idx++)
    {
        PhyChannel = UartConfigPtr->PtrChannelConfig[Uart_Idx].ChannelId;
        LocalUart = (Uart *)UartArray[PhyChannel];

        /* Reset and disable receiver & transmitter*/
        LocalUart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX
            | UART_CR_RXDIS | UART_CR_TXDIS | UART_CR_RSTSTA;

        /*Configure TxRdy, RxRdy interrupts*/
        LocalUart->UART_IDR = (0xFFFFFFFC | UartConfigPtr->PtrChannelConfig[Uart_Idx].InterruptEnable);

        /* Configure Parity type, Baud rate source clock and Channel mode*/
        LocalUart->UART_MR = (UartConfigPtr->PtrChannelConfig[Uart_Idx].TestMode << UART_MR_CHMODE_Pos) \
                           | (UartConfigPtr->PtrChannelConfig[Uart_Idx].BrSourceClk << UART_MR_BRSRCCK_Pos) \
                           | (UartConfigPtr->PtrChannelConfig[Uart_Idx].Parity << UART_MR_PAR_Pos);

        if(UartConfigPtr->PtrChannelConfig[Uart_Idx].BrSourceClk == UartCfg_Clk_Peripheral)
        {
            /* Enable the peripheral clock in the PMC*/
            PMC_EnablePeripheral(UartPeriphId[PhyChannel]);

            /* Configure Uart pins*/
            PIO_Configure( &UartPinId[PhyChannel], PIO_LISTSIZE( UartPinId[PhyChannel] ) );

            /* Configure baudrate (BRSRCCK = 0)*/
            LocalUart->UART_BRGR = (BOARD_MCK / UartConfigPtr->PtrChannelConfig[Uart_Idx].BaudRate) / 16;
        }
        else if(UartConfigPtr->PtrChannelConfig[Uart_Idx].BrSourceClk == UartCfg_Clk_PCK)
        {
            /*baud rate is independent of the processor/bus clock, processor clock can be changed while UART is enabled*/

            /* check if there is MDIV value */
            Mdiv_Val = ( (PMC->PMC_MCKR & PMC_MCKR_MDIV_Msk) >> PMC_MCKR_MDIV_Pos);

            if(Mdiv_Val == 0) {
              Pck = BOARD_MCK;
            } else if(Mdiv_Val == 3 ) {
              Pck = BOARD_MCK * Mdiv_Val;
            } else {
              Pck = BOARD_MCK * (Mdiv_Val*2);
            }

            /* Configure baudrate (BRSRCCK = 1)*/
            LocalUart->UART_BRGR = (Pck / UartConfigPtr->PtrChannelConfig[Uart_Idx].BaudRate) / 16;
        }
        else
        {
            /*Do nothing*/
        }

        /* Check interrupt configuration to enable/disable Tx or Rx */
        Isr_Val = UartConfigPtr->PtrChannelConfig[Uart_Idx].InterruptEnable;

        switch(Isr_Val)
        {
            case 1:
                /*Enable Tx*/
                Uart_SetTxEnable(Uart_Idx, ENABLE);
                /*Disable Rx*/
                Uart_SetRxEnable(Uart_Idx, DISABLE);
                break;
            case 2:
                /*Enable Rx*/
                Uart_SetRxEnable(Uart_Idx, TRUE);
                /*Disable Tx*/
                Uart_SetTxEnable(Uart_Idx, FALSE);
                break;
            case 3:
                /*Enable Tx*/
                Uart_SetTxEnable(Uart_Idx, TRUE);
                /*Enable Rx*/
                Uart_SetRxEnable(Uart_Idx, TRUE);
                break;
            default:
                break;
        }
    }
}

#if COMPILAR
/**
 * \brief Configures an UART peripheral with the specified parameters.
 *
 *
 *  \param uart  Pointer to the UART peripheral to configure.
 *  \param mode  Desired value for the UART mode register (see the datasheet).
 *  \param baudrate  Baudrate at which the UART should operate (in Hz).
 *  \param masterClock  Frequency of the system master clock (in Hz).
 */
void UART_Configure(Uart *uart, uint32_t mode, uint32_t baudrate, uint32_t masterClock)
{
    /* Reset and disable receiver & transmitter*/
    uart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX
        | UART_CR_RXDIS | UART_CR_TXDIS | UART_CR_RSTSTA;

    uart->UART_IDR = 0xFFFFFFFF;

    /* Configure mode*/
    uart->UART_MR = mode;

    /* Configure baudrate*/
    uart->UART_BRGR = (masterClock / baudrate) / 16;

    uart->UART_CR = UART_CR_TXEN | UART_CR_RXEN;

}
#endif


/*
 * Brief: Sets the requested baudrate to the addressed UART channel
 * @Param in:
 *  Channel - UART Channel to be addressed
 *  Baudrate - Baudrate to configure
 * @Param out:
 *  None
 * @Return type
 *  Std_ReturnType
 */
Std_ReturnType Uart_SetBaudrate(uint8_t Channel, uint32_t Baudrate)
{
    uint8_t PhyChannel;
    uint8_t Mdiv_Val;
    uint32_t Pck;
    Uart *LocalUart;
    Std_ReturnType RetVal = E_NOT_OK;

    /*Stop UART transmision*/

    PhyChannel = UartConfigPtr->PtrChannelConfig[Channel].ChannelId;
    LocalUart = (Uart *)UartArray[PhyChannel];


    if(UartConfigPtr->PtrChannelConfig[Channel].BrSourceClk == UartCfg_Clk_Peripheral)
    {
        /* Enable the peripheral clock in the PMC*/
        PMC_EnablePeripheral(UartPeriphId[PhyChannel]);

        /* Configure baudrate (BRSRCCK = 0)*/
        LocalUart->UART_BRGR = (BOARD_MCK / UartConfigPtr->PtrChannelConfig[Channel].BaudRate) / 16;
    }
    else if(UartConfigPtr->PtrChannelConfig[Channel].BrSourceClk == UartCfg_Clk_PCK)
    {
        /*baud rate is independent of the processor/bus clock, processor clock can be changed while UART is enabled*/

        /* check if there is MDIV value */
        Mdiv_Val = ( (PMC->PMC_MCKR & PMC_MCKR_MDIV_Msk) >> PMC_MCKR_MDIV_Pos);

        if(Mdiv_Val == 0) {
          Pck = BOARD_MCK;
        } else if(Mdiv_Val == 3 ) {
          Pck = BOARD_MCK * Mdiv_Val;
        } else {
          Pck = BOARD_MCK * (Mdiv_Val*2);
        }

        /* Configure baudrate (BRSRCCK = 1)*/
        LocalUart->UART_BRGR = (Pck / UartConfigPtr->PtrChannelConfig[Channel].BaudRate) / 16;
    }
    else
    {
        /*Do nothing*/
    }

    /*Restore UART transmision*/

    return RetVal;
}

#if COMPILAR
/**
 * \brief Enables or disables the transmitter of an UART peripheral.
 *
 *
 * \param uart  Pointer to an UART peripheral
 * \param enabled  If true, the transmitter is enabled; otherwise it is
 *  disabled.
 */
void UART_SetTransmitterEnabled(Uart *uart, uint8_t enabled)
{
    if (enabled) {
        uart->UART_CR = UART_CR_TXEN;
    } else {
        uart->UART_CR = UART_CR_TXDIS;
    }
}
#endif


/*
 * Brief: Enables or disables the transmitter of the UART module
 * @Param in:
 *  Channel - UART Channel to be addressed
 *  Enable - Enable (1)/Disable (0) information
 * @Param out:
 *  None
 * @Return type
 *  void
 */
void Uart_SetTxEnable(uint8_t Channel, uint8_t Enable)
{
    uint8_t PhyChannel;
    Uart *LocalUart;

    PhyChannel = UartConfigPtr->PtrChannelConfig[Channel].ChannelId;
    LocalUart = (Uart *)UartArray[PhyChannel];

    if(Enable == 1)
    {
        LocalUart->UART_CR = UART_CR_TXEN;
    }
    else
    {
        LocalUart->UART_CR = UART_CR_TXDIS;
    }
}

#if COMPILAR
/**
 * \brief Enables or disables the receiver of an UART peripheral
 *
 *
 * \param uart  Pointer to an UART peripheral
 * \param enabled  If true, the receiver is enabled; otherwise it is disabled.
 */
void UART_SetReceiverEnabled(Uart *uart, uint8_t enabled)
{
    if (enabled) {
        uart->UART_CR = UART_CR_RXEN;
    } else {
        uart->UART_CR = UART_CR_RXDIS;
    }
}
#endif

/*
 * Brief: Enables or disables the receiver of the UART module
 * @Param in:
 *  Channel - UART Channel to be addressed
 *  Enable - Enable (1)/Disable (0) information
 * @Param out:
 *  None
 * @Return type
 *  void
 */
void Uart_SetRxEnable(uint8_t Channel, uint8_t Enable)
{
    uint8_t PhyChannel;
    Uart *LocalUart;

    PhyChannel = UartConfigPtr->PtrChannelConfig[Channel].ChannelId;
    LocalUart = (Uart *)UartArray[PhyChannel];

    if(Enable == 1)
    {
        LocalUart->UART_CR = UART_CR_RXEN;
    }
    else
    {
        LocalUart->UART_CR = UART_CR_RXDIS;
    }
}

/*
 * Brief: Sends one packet of data through the specified UART module
 * @Param in:
 *  Channel - UART Channel to be addressed
 *  Byte - Data to be sent over the UART bus
 * @Param out:
 *  None
 * @Return type
 *  Std_ReturnType
 */
Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte)
{
    Std_ReturnType RetVal = E_NOT_OK;
    uint8_t PhyChannel;
    const Uart *LocalUart;

    PhyChannel = UartConfigPtr->PtrChannelConfig[Channel].ChannelId;

    LocalUart = UartArray[PhyChannel];

    return RetVal;
}

/*
 * Brief: Sends a packet of data through the specified UART channel
 * @Param in:
 *  Channel - UART Channel to be addressed
 *  Buffer - Pointer to the start address of the buffer to be sent over the UART bus
 *  Length - Size of the buffer to be sent
 * @Param out:
 *  None
 * @Return type
 *  Std_ReturnType
 */
Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t *Buffer, uint16_t Length)
{
    Std_ReturnType RetVal = E_NOT_OK;


    return RetVal;
}

/*
 * Brief: Reads and returns a character from the UART module
 * @Param in:
 *  Channel - UART Channel to be addressed
 *  Byte - Data received from the UART bus
 * @Param out:
 *  None
 * @Return type
 *  void
 */
void Uart_GetByte(uint8_t Channel, uint8_t Byte)
{

}

/*
 * Brief: Reads and returns the current status of the addressed UART module
 * @Param in:
 *  Channel - UART Channel to be addressed
 * @Param out:
 *  Status - Current status of the addressed UART module
 * @Return type
 *  void
 */
void Uart_GetStatus(uint8_t Channel, uint32_t *Status)
{

}

/*
 * Brief: Enable/disable the UART module interrupts according to the IntMode and Enable parameters
 * @Param in:
 *  Channel - UART Channel to be addressed
 *  IntMode - Interrupt Mode information
 *  Enable - Enable (1)/Disable (0) information
 * @Param out:
 *  None
 * @Return type
 *  void
 */
void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable)
{

}

/*
 * Brief: UART0 interrupt service routine
 * @Param in: None
 * @Param out: None
 * @Return type void
 */
void UART0_Handler()
{
    Uart_Isr(0);
}

/*
 * Brief: UART1 interrupt service routine
 * @Param in: None
 * @Param out: None
 * @Return type void
 */
void UART1_Handler()
{
    Uart_Isr(1);
}

/*
 * Brief: UART2 interrupt service routine
 * @Param in: None
 * @Param out: None
 * @Return type void
 */
void UART2_Handler()
{
    Uart_Isr(2);
}

/*
 * Brief: UART3 interrupt service routine
 * @Param in: None
 * @Param out: None
 * @Return type void
 */
void UART3_Handler()
{
    Uart_Isr(3);
}

/*
 * Brief: UART4 interrupt service routine
 * @Param in: None
 * @Param out: None
 * @Return type void
 */
void UART4_Handler()
{
    //Uart_Isr(4);
    uint32_t Status = UART_GetStatus(UART4);

    if (Status & (UART_SR_OVRE | UART_SR_FRAME | UART_SR_PARE)) {
        UART4->UART_CR = UART_CR_RSTSTA;
        printf("Error \n\r");
    }

    printf("%c", (char)UART4->UART_RHR);
}







/**
 * \brief   Return 1 if a character can be read in UART
 * \param uart  Pointer to an UART peripheral.
 */
uint32_t UART_IsRxReady(Uart *uart)
{
	return (uart->UART_SR & UART_SR_RXRDY);
}

/**
 * \brief  Reads and returns a character from the UART.
 *
 * \note This function is synchronous (i.e. uses polling).
 * \param uart  Pointer to an UART peripheral.
 * \return Character received.
 */
uint8_t UART_GetChar(Uart *uart)
{
	while (!UART_IsRxReady(uart));
	return uart->UART_RHR;
}

/**
 * \brief   Return 1 if a character can be send to UART
 * \param uart  Pointer to an UART peripheral.
 */
uint32_t UART_IsTxReady(Uart *uart)
{
	return (uart->UART_SR & UART_SR_TXRDY);
}

/**
 * \brief   Return 1 if a character can be send to UART
 * \param uart  Pointer to an UART peripheral.
 */
static uint32_t UART_IsTxSent(Uart *uart)
{
	return (uart->UART_SR & UART_SR_TXEMPTY);
}

/**
 * \brief  Sends one packet of data through the specified UART peripheral. This
 * function operates synchronously, so it only returns when the data has been
 * actually sent.
 *
 * \param uart  Pointer to an UART peripheral.
 * \param c  Character to send
 */
void UART_PutChar( Uart *uart, uint8_t c)
{
	/* Wait for the transmitter to be ready*/
	while (!UART_IsRxReady(uart) && !UART_IsTxSent(uart));

	/* Send character*/
	uart->UART_THR = c;

	/* Wait for the transfer to complete*/
	while (!UART_IsTxSent(uart));
}

/**
 * \brief   Get present status
 * \param uart  Pointer to an UART peripheral.
 */
uint32_t UART_GetStatus(Uart *uart)
{
	return uart->UART_SR;
}

/**
 * \brief   Enable interrupt
 * \param uart  Pointer to an UART peripheral.
 * \param mode  Interrupt mode.
 */
void UART_EnableIt(Uart *uart,uint32_t mode)
{
	uart->UART_IER = mode;
}

/**
 * \brief   Disable interrupt
 * \param uart  Pointer to an UART peripheral.
 * \param mode  Interrupt mode.
 */
void UART_DisableIt(Uart *uart,uint32_t mode)
{
	uart->UART_IDR = mode;
}

/**
 * \brief   Return interrupt mask
 * \param uart  Pointer to an UART peripheral.
 */
uint32_t UART_GetItMask(Uart *uart)
{
	return uart->UART_IMR;
}

void UART_SendBuffer(Uart *uart, uint8_t *pBuffer, uint32_t BuffLen)
{
	uint8_t *pData = pBuffer;
	uint32_t Len =0;

	for(Len =0; Len<BuffLen; Len++ ) {
		UART_PutChar(uart, *pData);
		pData++;
	}
}

void UART_ReceiveBuffer(Uart *uart, uint8_t *pBuffer, uint32_t BuffLen)
{
	uint32_t Len =0;

	for(Len =0; Len<BuffLen; Len++ ) {
		*pBuffer = UART_GetChar(uart);
		pBuffer++;
	}
}

void UART_CompareConfig(Uart *uart, uint8_t Val1, uint8_t Val2)
{
	uart->UART_CMPR = (UART_CMPR_VAL1(Val1) | UART_CMPR_VAL2(Val2));
}
