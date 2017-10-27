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
#include <Uart.h>
#include <samv71q21.h>
#include <board.h>

/*------------------------------------------------------------------------------
 *         Defines
 *----------------------------------------------------------------------------*/
#define UART_MAX_NUM_CH 5
#define UART_MAX_BUFFER 18

typedef struct{
    uint8_t RxBusy;
    uint8_t TxBusy;
    uint8_t SendedBytes;
    uint8_t TxBufferSize;
    uint8_t LogicalChannel;
}Uart_CtrStatusType;

/*------------------------------------------------------------------------------
 *         Local Variables
 *----------------------------------------------------------------------------*/
const Uart_ConfigType *UartConfig;
static Uart *UartArray [UART_MAX_NUM_CH] = {UART0, UART1, UART2, UART3, UART4};
const Uart_CtrStatusType *UartStatusPtr;

/*------------------------------------------------------------------------------
 *         Local functions
 *----------------------------------------------------------------------------*/


void Uart_Isr(uint8_t Channel){
    uint8_t Uart_Idx;
    uint8_t LogChannel;
    Uart* LocUart;
    LocUart = UartArray[Channel];  
    
    LocUart = (Uart *)UartArray[Channel];
    uint32_t ISR_IMR = LocUart->UART_IMR;
    uint32_t ISR_SR = LocUart->UART_SR;
    for(Uart_Idx=0; Uart_Idx < UartConfig->UartNumberOfChannels; Uart_Idx++)
    {
        if(UartConfig->ChannelConfig[Uart_Idx].ChannelId == Channel)
        {
            LogChannel = Uart_Idx;
        }
    }
    if ((ISR_IMR & UART_MASK_RXRDY)&(ISR_SR & UART_MASK_RXRDY))
    {
        if(UartConfig->ChannelConfig[LogChannel].Callbacks.RxNotification != NULL)
        {
            UartConfig->ChannelConfig[LogChannel].Callbacks.RxNotification();
        }
    }
    else if ((ISR_IMR & UART_MASK_TXRDY)&(ISR_SR & UART_MASK_TXRDY)) {
        if(UartConfig->ChannelConfig[LogChannel].Callbacks.TxNotification != NULL)
        {

            UartConfig->ChannelConfig[LogChannel].Callbacks.TxNotification();
        }
    }
    else if (UartConfig->ChannelConfig[LogChannel].Callbacks.ErrorNotification != NULL){
        if((ISR_IMR & UART_MASK_OVRE)&(ISR_SR & UART_MASK_OVRE))
        {
            UartConfig->ChannelConfig[LogChannel].Callbacks.ErrorNotification(UART_ERROR_OVERRUN);
        }
        else if((ISR_IMR & UART_MASK_FRAME)&(ISR_SR & UART_MASK_FRAME)){
            UartConfig->ChannelConfig[LogChannel].Callbacks.ErrorNotification(UART_ERROR_FRAMING);
        }
        else if((ISR_IMR & UART_MASK_PARE)&(ISR_SR & UART_MASK_PARE)){
            UartConfig->ChannelConfig[LogChannel].Callbacks.ErrorNotification(UART_ERROR_PARITY);
        }
    }
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
uint32_t UART_IsTxSent(Uart  *uart){
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
    //  UartStatusPtr = (Uart_CtrStatusType*) Mem_Alloc()
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
        /* Configure Interruptions */
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
    if(!UART_IsRxReady(LocUart) && !UART_IsTxSent(LocUart)){
        return E_NOK;
    }

    /* Send Byte */
    LocUart->UART_THR = Byte;
    while(!UART_IsTxSent(LocUart));
    return E_OK;
}

/* Sends a packet of data through the specified UART channel */
Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t *Buffer, uint16_t Length){
    uint8_t *pData = Buffer;
    Uart* LocUart;
    Uart_ChannnelType Uart_Chnn;
    uint8_t PhyChn;
    /* Get Channel */
    Uart_Chnn = UartConfig -> ChannelConfig[Channel];
    /* Get Physical Channel */ 
    PhyChn = Uart_Chnn.ChannelId;
    LocUart = UartArray[PhyChn]; 
    uint32_t Len =0;
    
    for(Len =0; Len < Length; Len++ ) {
        Uart_SendByte(Channel, *pData);
        
        pData++;
    }
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

void Uart_GetByte(uint8_t Channel, uint8_t *Byte){
    Uart* LocUart;
    Uart_ChannnelType Uart_Chnn;
    uint8_t PhyChn;
    /* Get Channel */
    Uart_Chnn = UartConfig -> ChannelConfig[Channel];
    /* Get Physical Channel */  
    PhyChn = Uart_Chnn.ChannelId;
    LocUart = UartArray[PhyChn];
    if(!(Uart_Chnn.IsrEn & CNF_UART_RXISREN) & (Uart_Chnn.Callbacks.RxNotification == 0)){
        while(!UART_IsRxReady(LocUart));
    }
    *Byte = LocUart->UART_RHR;
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

