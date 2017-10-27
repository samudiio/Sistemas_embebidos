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
uint8_t Uart_phy2log_Channel[UART_MAX_NUM_CH];

// UART_IsTxReady == LocUart->UART_SR & UART_SR_TXRDY
// UART_IsRxReady == LocUart->UART_SR & UART_SR_RXRDY
// UART_IsTxSent  == LocUart->UART_SR & UART_SR_TXEMPTY

static void Uart_Isr(uint8_t Channel)
{
  uint8_t TrueChannel;
  TrueChannel = Uart_phy2log_Channel[Channel];
  Uart *LocUart;       //Variables auxiliares internas solo para asignacion
  uint8_t PhyChannel;//Variables auxiliares internas solo para asignacion
  PhyChannel = UartConfig->ChannelConfig[TrueChannel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  uint32_t Uart_Status=0;
  uint32_t Uart_IntReg=0;
  
  Uart_GetStatus(TrueChannel,&Uart_Status);
  Uart_IntReg = LocUart->UART_IMR;
  
  if ((Uart_Status & UART_MASK_TXRDY) && (Uart_IntReg & UART_MASK_TXRDY)){
    if(UartConfig->ChannelConfig[TrueChannel].Callbacks.TxNotification != NULL){
        UartConfig->ChannelConfig[TrueChannel].Callbacks.TxNotification();                  
        Uart_EnableInt(TrueChannel,CFG_INT_TXRDY,0);
    }else{            
      Uart_EnableInt(TrueChannel,CFG_INT_TXRDY,0);
    }
  }
  
  if((Uart_Status & UART_MASK_RXRDY) && (Uart_IntReg & UART_MASK_RXRDY )){
   if(UartConfig->ChannelConfig[TrueChannel].Callbacks.RxNotification != NULL){
        UartConfig->ChannelConfig[TrueChannel].Callbacks.RxNotification();                  
        printf( "%d",LocUart->UART_RHR );  
    }else{          
     printf( "%d",LocUart->UART_RHR );
   }  
  }
  
  if((Uart_Status & (CFG_INT_OVR_ERROR | CFG_INT_FRAME_ERROR | CFG_INT_PAR_ERROR))  && (Uart_IntReg & (CFG_INT_OVR_ERROR | CFG_INT_FRAME_ERROR | CFG_INT_PAR_ERROR))){
   if(UartConfig->ChannelConfig[TrueChannel].Callbacks.ErrorNotification != NULL){
        UartConfig->ChannelConfig[TrueChannel].Callbacks.ErrorNotification();          
        LocUart->UART_CR = 256; //Reset Errors
        
    }else{          
     LocUart->UART_CR = 256; //Reset Errors     
   }  
  }
  
      
}

extern void Uart_Init(const UartConfigType* Config)
{
  UartConfig = Config; //Backup 
  Uart *LocUart;       
  uint8_t PhyChannel, Uart_Idx;
  
  UartStatus = (UartStatusType*) Mem_Alloc( (sizeof(UartStatusType)) * (UartConfig->UartNumberOfChannels) );
  
  for(Uart_Idx=0; Uart_Idx< UartConfig->UartNumberOfChannels;Uart_Idx++)
  {
    PhyChannel = UartConfig->ChannelConfig[Uart_Idx].ChannelID;
    LocUart = (Uart *)UartArray[PhyChannel];
    
    // Aqui se llena el arreglo que se usa en Uart_IsR()
    Uart_phy2log_Channel[PhyChannel]= Uart_Idx;
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
    LocUart->UART_CR = UART_CR_TXEN | UART_CR_RXEN;        
/*Configure Interruptions*/
    //NVIC_ClearPendingIRQ(UartIRQnId[PhyChannel]);
	  //NVIC_SetPriority(UartIRQnId[PhyChannel], 1);
    //LocUart->UART_IER = UartConfig->ChannelConfig[Uart_Idx].IsrEn;
    //NVIC_EnableIRQ(UartIRQnId[PhyChannel]);                  
  }  /*End FOR*/
}    /*End Uart_Init*/


extern Std_ReturnType Uart_SetBaudrate(uint8_t Channel, uint32_t Baudrate)
{
  Uart *LocUart;      
  uint8_t PhyChannel;
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
  Uart *LocUart;      
  uint8_t PhyChannel;
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
  Uart *LocUart;      
  uint8_t PhyChannel;
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
  Uart *LocUart;      
  uint8_t PhyChannel;
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

extern void Uart_GetByte(uint8_t Channel, uint8_t *Byte)
{
  Uart *LocUart;       
  uint8_t PhyChannel;
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  while (!(LocUart->UART_SR & UART_SR_RXRDY));  
  
	 *Byte = LocUart->UART_RHR;
  
  
}
extern void Uart_EnableInt(uint8_t Channel, uint32_t IntMode, uint8_t Enable)
{
  Uart *LocUart;      
  uint8_t PhyChannel;
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  NVIC_ClearPendingIRQ(UartIRQnId[PhyChannel]);
	NVIC_SetPriority(UartIRQnId[PhyChannel], 1);
  
  if(1==Enable){
    LocUart->UART_IER |= IntMode;    
  }
  else{
    LocUart->UART_IDR |= IntMode;        
  }
  
  NVIC_EnableIRQ(UartIRQnId[PhyChannel]);
  
  	
  
}
extern void Uart_GetStatus(uint8_t Channel, uint32_t* Status)
{
  Uart *LocUart;       
  uint8_t PhyChannel;
  PhyChannel = UartConfig->ChannelConfig[Channel].ChannelID;
  LocUart = (Uart *)UartArray[PhyChannel];
  
  *Status = LocUart->UART_SR;
  
}


void UART0_Handler()
{  
  Uart_Isr(CFG_PHYCH_UART0);
} 
void UART1_Handler()
{
  Uart_Isr(CFG_PHYCH_UART1);
}
void UART2_Handler()
{
  Uart_Isr(CFG_PHYCH_UART2);
}
void UART3_Handler()
{
  Uart_Isr(CFG_PHYCH_UART3);    
}
void UART4_Handler()
{
  Uart_Isr(CFG_PHYCH_UART4);      
}