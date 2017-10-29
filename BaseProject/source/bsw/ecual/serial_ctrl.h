#ifndef __SERIAL_CTRL_H        /*prevent duplicated includes*/
#define __SERIAL_CTRL_H


//#include "typedefs.h"
#include <Uart_Cfg.h>
#include <stdio.h>




void vfnSerialCtrl_Init( void );

void vfnSerialCtrl_Transfer(void);

void vfnSerialCtrl_Test( void );

void vfnSerialCtrl_SendSeconds( uint8_t );

void vfnSerialCtrl_SendBuffer( void );

void vfnSerialCtr_Enable_int(uint8_t , uint32_t, uint8_t );


/*
 * Brief: End of transmission notification
 */
//extern void vfnTxNotification(void);

/*
 * Brief: Data reception notification
 */
//extern void vfnRxNotification(void);

/*
 * Brief: Error notification
 */
//extern void vfnErrorNotification(uint8_t Error_Type);


/**************************************************************************************************/

#endif /* __SERIAL_CTRL_H */