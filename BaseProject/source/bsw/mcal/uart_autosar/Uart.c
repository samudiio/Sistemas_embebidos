#include <Uart.h>
#include "samv71q21.h"
#include "board.h"


#define UART_MAX_NUM_CH 5 

const UartConfigType *UartConfig;
const UartStatusType *UartStatus;

const Uart *UartArray[UART_MAX_NUM_CH] = {UART0, UART1, UART2, UART3, UART4};
const uint32_t UartPeriphId[UART_MAX_NUM_CH] = {ID_UART0, ID_UART1, ID_UART2, ID_UART3, ID_UART4};
const Pin UartPinId[UART_MAX_NUM_CH] = {PINS_UART0, PINS_UART1, PINS_UART2, PINS_UART3, PINS_UART4};
const IRQn_Type UartIRQnId[UART_MAX_NUM_CH] = {UART0_IRQn, UART1_IRQn, UART2_IRQn, UART3_IRQn, UART4_IRQn};



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
    /*Disable all UART Interrupts during configuration*/
    LocUart->UART_IDR = 0xFFFFFFFF; 
    
/* ***** Start Configuration ***** */
    
/*Pins Configure */
    PIO_Configure( &UartPinId[PhyChannel], PIO_LISTSIZE( UartPinId[PhyChannel] ) );
   
    
/*Configure MODE*/
    LocUart->UART_MR = ( (UartConfig->ChannelConfig[Uart_Idx].Mode<<14) | 
                         (UartConfig->ChannelConfig[Uart_Idx].Parity<<9)|
                         (UartConfig->ClkSrc<<12)                      
                       );    
    
/*Configure Baudrate*/
    if( CFG_CLKSRC_PERIPHERAL == UartConfig->ClkSrc ){
      
      /*Enable Clock Peripheral */
      PMC_EnablePeripheral(UartPeriphId[PhyChannel]);
      /*Set Baudrate*/            
      LocUart->UART_BRGR = (BOARD_MCK / UartConfig->ChannelConfig[Uart_Idx].Baudrate) / 16;    
    }
    else if( CFG_CLKSRC_PROGRAMMABLE == UartConfig->ClkSrc ){ 
        /*baud rate is independent of the processor/bus clock, processor clock can be changed while UART is enabled*/
        /* check if there is MDIV value */
      uint8_t Mdiv_Val;
      uint32_t Pck;  
      Mdiv_Val = ( (PMC->PMC_MCKR & PMC_MCKR_MDIV_Msk) >> PMC_MCKR_MDIV_Pos);
        if(Mdiv_Val == 0) {
          Pck = BOARD_MCK;
        } else if(Mdiv_Val == 3 ) {
          Pck = BOARD_MCK * Mdiv_Val;
        } else {
          Pck = BOARD_MCK * (Mdiv_Val*2);
        }
        LocUart->UART_BRGR = (Pck /UartConfig->ChannelConfig[Uart_Idx].Baudrate) / 16;      
    }
/*Configure Control Register*/    
    //LocUart->UART_CR = UART_CR_TXEN | UART_CR_RXEN;        
/*Configure Interruptions*/
    //NVIC_ClearPendingIRQ(UartIRQnId[PhyChannel]);
	  //NVIC_SetPriority(UartIRQnId[PhyChannel], 1);
    //LocUart->UART_IER = UartConfig->ChannelConfig[Uart_Idx].IsrEn;
    //NVIC_EnableIRQ(UartIRQnId[PhyChannel]);                  
  }  /*End FOR*/
}    /*End Uart_Init*/


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
    LocUart->UART_BRGR = (BOARD_MCK /Baudrate) / 16; 
    return E_OK;
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
    LocUart->UART_BRGR = (Pck /Baudrate) / 16;
    return E_OK;
  }
  else{
     return E_NOK;
  }
  
    
}
extern void Uart_SetTxEnable(uint8_t Channel, uint32_t Enable)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
      
  if(1 == Enable){
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
  
  if(1 == Enable){
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
  else{
    LocUart->UART_THR = Byte;     
    while (!(LocUart->UART_SR & UART_SR_TXEMPTY)); //Wait until TX is Empty    
    return E_OK;   
  }
}

extern Std_ReturnType Uart_SendBuffer(uint8_t Channel, uint8_t* Buffer, uint16_t Length)
{
  
  uint8_t *Data = Buffer;
	uint16_t Len =0;
  
  	for(Len =0; Len<Length; Len++) {
  		if(E_OK == Uart_SendByte(Channel, *Data)){
  		Data++;      
      }
      else{
        return E_NOK;  
      }
  	}  
    return E_OK;  
  
}

extern void Uart_GetByte(uint8_t Channel, uint8_t* Byte)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  while (!(LocUart->UART_SR & UART_SR_RXRDY));  
  
	 *Byte = LocUart->UART_RHR;
  
  
}
extern void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  NVIC_ClearPendingIRQ(UartIRQnId[PhyChannel]);
	NVIC_SetPriority(UartIRQnId[PhyChannel], 1);
  
  if(1==Enable){
    LocUart->UART_IER = IntMode;
  }
  else{
    LocUart->UART_IDR = IntMode;
  }
  
  NVIC_EnableIRQ(UartIRQnId[PhyChannel]);	
  
}
extern void Uart_GetStatus(uint8_t Channel, uint32_t* Status)
{
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  *Status = LocUart->UART_SR;
  
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
  Uart_EnableInt(1,CFG_INT_PAR_ERROR,0);  
  printf( "PARITY_ERROR INTERRUPT\n\r" );
  Uart_SendByte(1, 'P');
}
void UART4_Handler()
{
  Uart_EnableInt(0,CFG_INT_RXRDY,0);
  Uart_Isr(4);
  printf( "UART4 INTERRUPT\n\r" );
  Uart_SendByte(0, 'I');
}