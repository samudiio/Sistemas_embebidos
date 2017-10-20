/*
 * Uart.c
 *
 *  Created on: Oct 2017
 * \file
 *
 * Implementation of UART (Universal Asynchronous Receiver Transmitter)
 * controller.
 *
 */
/*------------------------------------------------------------------------------
 *         Headers
 *----------------------------------------------------------------------------*/
#include <Uart_Types.h>
#include <Uart.h>
#include <samv71q21.h>
#include <board.h>
#include <led.h>

/*------------------------------------------------------------------------------
 *         Defines
 *----------------------------------------------------------------------------*/
#define UART_MAX_NUM_CH 5

/*------------------------------------------------------------------------------
 *         Local Variables
 *----------------------------------------------------------------------------*/
const Uart_ConfigType *UartConfig;
static Uart *UartArray [UART_MAX_NUM_CH] = {UART0, UART1, UART2, UART3, UART4};

/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/


void Uart_Isr(uint8_t Channel){
    Uart* LocUart;
    LocUart = UartArray[Channel];
    uint32_t *status;
    Uart_GetStatus(Channel, status);
    // printf("ISRCH_%u ->IMR: %u\n\r", Channel, LocUart->UART_IMR);
    printf("ISRCH_%u ->SR: %u\n\r", Channel, status);
    // LocUart->UART_IDR = UART_IDR_TXRDY;
    LED_Toggle(1);
}


/**
 * \brief   Return 1 if a character can be read in UART
 * \param Chanel   UART Physical peripheral Channel.
 */
uint8_t UART_IsRxReady(Uart  *uart){
    return (uart->UART_SR & UART_SR_RXRDY);
}

/**
 * \brief   Return 1 if a character can be send to UART
 * \param Chanel   UART Physical peripheral Channel.
 */
uint8_t UART_IsTxReady(Uart  *uart){
    return (uart->UART_SR  & UART_SR_TXRDY);
}

/**
 * \brief   Return 1 if a character can be send to UART
 * \param Chanel   UART Physical peripheral Channel.
 */
uint8_t UART_IsTxSent(Uart  *uart){
    return (uart->UART_SR  & UART_SR_TXEMPTY);
}

/*------------------------------------------------------------------------------
 *         Exported functions
 *----------------------------------------------------------------------------*/

/**
 * \brief Configures an UART peripheral with the specified parameters.
 *  \param Config  Pointer to the UART peripheral to configure.
 * Initializes the UART module   */
 void Uart_Init(const Uart_ConfigType *Config){
     UartConfig = Config;
     uint8_t Uart_idx = 0;
     Uart* LocUart;
     uint8_t PhyChn;
     Uart_ChannnelType Uart_Chnn;
     for(Uart_idx= 0; Uart_idx < UartConfig ->UartNumberOfChannels; Uart_idx++){
        /* Get Channel */
        Uart_Chnn = UartConfig -> ChannelConfig[Uart_idx];
        /* Get Physical Channel */  
        PhyChn = Uart_Chnn.ChannelId;
        LocUart = UartArray[PhyChn];
        /* Reset and disable receiver & transmitter*/
        LocUart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX
        | UART_CR_RXDIS | UART_CR_TXDIS | UART_CR_RSTSTA; 

        /* Disable Interruptions */
        LocUart->UART_IDR = 0xFFFFFFFF;

        /* Configure mode*/
        LocUart->UART_MR = (Uart_Chnn.Mode | Uart_Chnn.Parity | UartConfig -> ClkSrc);
        /* Configure baudrate*/
        LocUart->UART_BRGR = (BOARD_MCK/Uart_Chnn.Baudrate) / 16;
        /* COnfigure Interruptions */
        Uart_EnableInt(Uart_idx, Uart_Chnn.IsrEn, 1);
     }
 }

 /* Re-configuration of the Uart channel to the specified baudrate parameter. */
 Std_ReturnType Uart_SetBaurate(uint8_t Channel, uint32_t Baudrate){
    Uart* LocUart;
    Uart_ChannnelType Uart_Chnn;
    uint8_t PhyChn;
    /* Get Channel */
    Uart_Chnn = UartConfig -> ChannelConfig[Channel];
    /* Get Physical Channel */  
    PhyChn = Uart_Chnn.ChannelId;
    LocUart = UartArray[PhyChn];
    /* Reset and disable receiver & transmitter*/
    LocUart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX
    | UART_CR_RXDIS | UART_CR_TXDIS | UART_CR_RSTSTA; 

    /* Disable Interruptions */
    LocUart->UART_IDR = 0xFFFFFFFF;

    /* Configure mode*/
    LocUart->UART_MR = (Uart_Chnn.Mode | Uart_Chnn.Parity | UartConfig -> ClkSrc);
    /* Configure baudrate*/
    LocUart->UART_BRGR = (BOARD_MCK/Baudrate) / 16;
    /* COnfigure Interruptions */
    Uart_EnableInt(Channel, Uart_Chnn.IsrEn, 1);
 }

/*  The Uart_SetTxEnable function shall support runtime enable/disable of the Uart transmitter specified by the Enable parameter. */
void Uart_SetTxEnable(uint8_t Channel, uint32_t Enable){
    Uart* LocUart;
    Uart_ChannnelType Uart_Chnn;
    uint8_t PhyChn;
    /* Get Channel */
    Uart_Chnn = UartConfig -> ChannelConfig[Channel];
    /* Get Physical Channel */  
    PhyChn = Uart_Chnn.ChannelId;
    LocUart = UartArray[PhyChn];
    if(Enable)
    { 
        LocUart->UART_CR = UART_CR_TXEN;
    }
    else{
        LocUart->UART_CR = UART_CR_TXDIS;
    }
}

/* Enables or disables the receiver of the UART module */
void Uart_SetRxEnable (uint8_t Channel, uint32_t Enable){
    Uart* LocUart;
    Uart_ChannnelType Uart_Chnn;
    uint8_t PhyChn;
    /* Get Channel */
    Uart_Chnn = UartConfig -> ChannelConfig[Channel];
    /* Get Physical Channel */  
    PhyChn = Uart_Chnn.ChannelId;
    LocUart = UartArray[PhyChn];
    if(Enable)
    { 
        LocUart->UART_CR = UART_CR_RXEN;
    }
    else{
        LocUart->UART_CR = UART_CR_RXDIS;
    }
}

/* Sends one packet of data through the specified UART module */
Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte ){
    Uart* LocUart;
    Uart_ChannnelType Uart_Chnn;
    uint8_t PhyChn;
    /* Get Channel */
    Uart_Chnn = UartConfig -> ChannelConfig[Channel];
    /* Get Physical Channel */  
    PhyChn = Uart_Chnn.ChannelId;
    LocUart = UartArray[PhyChn];
    /* Check If the transmitter is ready*/
    if(!UART_IsRxReady(LocUart) && !UART_IsTxReady(LocUart)){
        return E_NOK;
    }

    /* Send Byte */
    LocUart->UART_THR = Byte;

    /* Wait for the transfer to complete*/
    //while (!UART_IsTxReady(LocUart));
    //printf("RXREADY %u\n\r", *status);
    // if(Uart_Chnn.Callbacks.TxNotification != 0){
    //     Uart_Chnn.Callbacks.TxNotification();
    // }
    //printf("SendByteCH_%u ->IMR: %u\n\r", Channel, LocUart->UART_IMR);
    return E_OK;
}

/* Sends a packet of data through the specified UART channel */
Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t *Buffer, uint16_t Length){
    return E_OK;
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
    Uart* LocUart;
    Uart_ChannnelType Uart_Chnn;
    uint8_t PhyChn;
    /* Get Channel */
    Uart_Chnn = UartConfig -> ChannelConfig[Channel];
    /* Get Physical Channel */  
    PhyChn = Uart_Chnn.ChannelId;
    LocUart = UartArray[PhyChn];

    if(Enable == 1)
    {
        LocUart->UART_IER = IntMode;
    }
    else
    {
        LocUart->UART_IDR = IntMode;
    }
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
    Uart* LocUart;
    Uart_ChannnelType Uart_Chnn;
    uint8_t PhyChn;
    /* Get Channel */
    Uart_Chnn = UartConfig -> ChannelConfig[Channel];
    /* Get Physical Channel */  
    PhyChn = Uart_Chnn.ChannelId;
    LocUart = UartArray[PhyChn];

    *Status = LocUart->UART_SR;
}

void UART0_Handler(){
    Uart_Isr(0);
}
void UART1_Handler(){
    Uart_Isr(1);
}
void UART2_Handler(){
    Uart_Isr(2);
}
void UART3_Handler(){
    Uart_Isr(3);
}
void UART4_Handler(){
    Uart_Isr(4);
} 

