#include <Uart.h>
#include "samv71q21.h"
#include "board.h"


#define UART_MAX_NUM_CH 5 

const UartConfigType *UartConfig;
const UartStatusType *UartStatus;

const Uart *UartArray[UART_MAX_NUM_CH] = {UART0, UART1, UART2, UART3, UART4};
const uint32_t UartPeriphId[UART_MAX_NUM_CH] = {ID_UART0, ID_UART1, ID_UART2, ID_UART3, ID_UART4};
const Pin UartPinId[UART_MAX_NUM_CH] = {PINS_UART0, PINS_UART1, PINS_UART2, PINS_UART3, PINS_UART4};



// UART_IsTxReady == LocUart->UART_SR & UART_SR_TXRDY
// UART_IsRxReady == LocUart->UART_SR & UART_SR_RXRDY
// UART_IsTxSent  == LocUart->UART_SR & UART_SR_TXEMPTY

static void Uart_Isr(uint8_t Channel)
{
}

extern void Uart_Init(const UartConfigType* Config)
{
  UartConfig = Config; //Guardamos Variable de respaldo
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel, Uart_Idx;//Variables auxiliares internas solo para asignacion
  
  UartStatus = (UartStatusType*) Mem_Alloc( (sizeof(UartStatusType)) * (UartConfig->UartNumberOfChannels) );
  
  for(Uart_Idx=0; Uart_Idx< UartConfig->UartNumberOfChannels;Uart_Idx++)
  {
    PhyChannel = UartConfig->ChannelConfig[Uart_Idx].ChannelID;
    LocUart = (Uart *)UartArray[PhyChannel];
    
    /* Reset and disable receiver & transmitter*/
	  LocUart->UART_CR = UART_CR_RSTRX | UART_CR_RSTTX | UART_CR_RXDIS | UART_CR_TXDIS | UART_CR_RSTSTA;
    /*Interrupts*/
    LocUart->UART_IDR = (0xFFFFFFFF | UartConfig->ChannelConfig[Uart_Idx].IsrEn);
    /*MODE*/
    LocUart->UART_MR = ( (UartConfig->ChannelConfig[Uart_Idx].Mode<<14) | 
                           (UartConfig->ChannelConfig[Uart_Idx].Parity<<9) |
                           (UartConfig->ClkSrc<<12)                      
                          );
    if( CFG_CLKSRC_PERIPHERAL == UartConfig->ClkSrc ){
      PMC_EnablePeripheral(UartPeriphId[PhyChannel]);      
      PIO_Configure( &UartPinId[PhyChannel], PIO_LISTSIZE( UartPinId[PhyChannel] ) );
      LocUart->UART_BRGR = (BOARD_MCK / UartConfig->ChannelConfig[Uart_Idx].Baudrate) / 16;    
    }
    else if( CFG_CLKSRC_PROGRAMMABLE == UartConfig->ClkSrc ){    
    }   
  }
}


extern Std_ReturnType Uart_SetBaudrate(uint8_t Channel, uint32_t Baudrate)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  uint8_t Mdiv_Val;
  uint32_t Pck;
  
  
  if( CFG_CLKSRC_PERIPHERAL == UartConfig->ClkSrc ){
      
    PMC_EnablePeripheral(UartPeriphId[PhyChannel]);           
    LocUart->UART_BRGR = (BOARD_MCK / UartConfig->ChannelConfig[Channel].Baudrate) / 16;    
    }
  else if( CFG_CLKSRC_PROGRAMMABLE == UartConfig->ClkSrc ){  
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
        LocUart->UART_BRGR = (Pck / UartConfig->ChannelConfig[Channel].Baudrate) / 16;
      
    }
  
    
}
extern void Uart_SetTxEnable(uint8_t Channel, uint32_t Enable)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
      
  if(Enable == 1){
    LocUart->UART_CR = UART_CR_TXEN;
  }
  else{
    LocUart->UART_CR = UART_CR_TXDIS;
  }
  
  
}
extern void Uart_SetRxEnable(uint8_t Channel, uint32_t Enable)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  if(Enable == 1){
    LocUart->UART_CR = UART_CR_RXEN;
  }
  else{
    LocUart->UART_CR = UART_CR_RXDIS;
  }
  
}
extern Std_ReturnType Uart_SendByte(uint8_t Channel, uint8_t Byte)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  if (!(LocUart->UART_SR & UART_SR_RXRDY) && !(LocUart->UART_SR & UART_SR_TXEMPTY)){
    return E_NOK;
  }
  
  LocUart->UART_THR = Byte; 
  
  while (!(LocUart->UART_SR & UART_SR_TXEMPTY));
  
  if(UartConfig->ChannelConfig[Channel].Callbacks.TxNotification != 0){
    UartConfig->ChannelConfig[Channel].Callbacks.TxNotification();
  }
    
  return E_OK;
  
  
}

extern Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t* Buffer, uint16_t Length)
{
  
  uint8_t *Data = Buffer;
	uint16_t Len =0;

	for(Len =0; Len<=Length;  ) {
		if(E_OK == Uart_SendByte(Channel, *Data)){
		Data++;
    Len++;
    }
	}
  
}

extern uint8_t Uart_GetByte(uint8_t Channel, uint8_t Byte)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  while (!(LocUart->UART_SR & UART_SR_RXRDY));
  
  if(UartConfig->ChannelConfig[Channel].Callbacks.RxNotification != 0){
    UartConfig->ChannelConfig[Channel].Callbacks.RxNotification();
  }
  
	return LocUart->UART_RHR;
  
  
}
extern void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  LocUart->UART_IER = IntMode;
  
}
extern uint32_t Uart_GetStatus(uint8_t Channel, uint32_t* Status)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  return LocUart->UART_SR;
  
}


void UART0_Handler()
{  
  Uart_Isr(0);
} 
void UART1_Handler()
{
  Uart_Isr(1);
}
void UART2_Handler()
{
  Uart_Isr(2);
}
void UART3_Handler()
{
  Uart_Isr(3);
}
void UART4_Handler()
{
  Uart_Isr(4);
}