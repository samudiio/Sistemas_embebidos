
#include "serial_ctrl.h"
#include <Uart.h>


uint8_t TxBuffer[] = {" Test Buffer Function ...  Tx\n\r"};
uint8_t Ascii_Buffer[] = {'0','0',' '};
uint8_t Tx_Count=0;

void vfnSerialCtrl_Configure( void )
{
  Uart_Init(Uart_Config);
  Uart_SetTxEnable(1,1);
  Uart_SetRxEnable(1,1);
  Uart_SetTxEnable(0,1);
  Uart_SetRxEnable(0,1);  
  Uart_EnableInt(0,CFG_INT_RXRDY,1);
  Uart_EnableInt(1,CFG_INT_RXRDY,1);
  //Uart_EnableInt(0,(CFG_INT_OVR_ERROR | CFG_INT_FRAME_ERROR | CFG_INT_PAR_ERROR),1);   
}


void vfnSerialCtrl_Init( void ){
    vfnSerialCtrl_Configure();
}

void vfnSerialCtrl_SendSeconds( uint8_t Seconds ){

/* Send de Decimal Value */  
  Uart_SendByte(1,Seconds); 
  
/* Send de ASCII Value */  
/*  if ( Seconds==10 || Seconds==20 || Seconds== 30 || Seconds==40 || Seconds==50){
    Ascii_Buffer[0]=(Seconds/10)+48;
    Ascii_Buffer[1]= 48;
  } 
  else if(Seconds==60){//Aqui se puede mandar el else if (Seconds==60){manda 00}
    Ascii_Buffer[0]= 48;
    Ascii_Buffer[1]= 48;
  }
  else{       
    Ascii_Buffer[0]=(Seconds/10)+48;
    Ascii_Buffer[1]= (Seconds%10)+48;
  }       
  
  Uart_SendBuffer(0,&Ascii_Buffer[0],3);   
*/
}

void vfnSerialCtrl_SendBuffer(void){
  
  if(Tx_Count<sizeof(TxBuffer)){
    Uart_SendByte(0,TxBuffer[Tx_Count++]);
  }
  else{
    Tx_Count=0;
  }
}


void vfnSerialCtr_Enable_int(uint8_t Channel, uint32_t Interupt, uint8_t enable){

  Uart_EnableInt(Channel,Interupt,enable);
}

void vfnSerialCtrl_Test( void ){
  
  uint8_t x;
  uint8_t get_byte;
  uint32_t Uart4_Status=0;
                 
  printf("  Size of TxBuffer  = %d \n\r",sizeof(TxBuffer));
  
  x = Uart_SendByte(1, '3');
  printf("UART3 --> Uart_SendByte() = %d \n\r",x);
  x = Uart_SendBuffer(1, &TxBuffer[0],sizeof(TxBuffer));
  printf("UART3 --> Uart_SendBuffer() = %d \n\r",x);
     
  x = Uart_SendByte(0, '4');
  printf("UART4 --> Uart_SendByte() = %d \n\r",x);
  x = Uart_SendBuffer(0, &TxBuffer[0],sizeof(TxBuffer));
  printf("UART4 --> Uart_SendBuffer() = %d \n\r",x);
     
}

/*
void TxNotification(void){
  printf( "End of transmission notification\n\r" );
  
}
void RxNotification(void){
  printf( "   Data reception notification\n\r" );  
  
}
void ErrorNotification(uint8_t *UartErrorType){
  printf( "Error notification\n\r" );
}
*/
  

