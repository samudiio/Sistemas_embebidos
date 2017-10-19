/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"    
#include "uart.h"
#include <stdbool.h>
#include <stdio.h>

/******************* Testing macros **********************************/
#define   UART_MR_PAR_NO (0x4u << 9) /**< \brief (UART_MR) No parity */
#define   UART_MR_CHMODE_NORMAL (0x0u << 14) /**< \brief (UART_MR) Normal mode */

#define UART_IER_RXRDY (0x1u << 0) /**< \brief (UART_IER) Enable RXRDY Interrupt */
#define UART_IER_OVRE (0x1u << 5) /**< \brief (UART_IER) Enable Overrun Error Interrupt */
#define UART_IER_FRAME (0x1u << 6) /**< \brief (UART_IER) Enable Framing Error Interrupt */
#define UART_IER_PARE (0x1u << 7) /**< \brief (UART_IER) Enable Parity Error Interrupt */

#define UART_PINS           {PINS_UART4}
#define COMPILAR 1
/******************* End of testing macros ***************************/


/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

TaskType Tasks[]={
/*  TaskPriority    TaskId   TaskFunctionPointer   */
  {      5,        TASK_1MS,       vfnTsk_1ms    },
  {      4,        TASK_2MSA,      vfnTsk_2msA   },
  {      4,        TASK_2MSB,      vfnTsk_2msB   },
  {      3,        TASK_10MS,      vfnTsk_10ms   },
  {      2,        TASK_50MS,      vfnTsk_50ms   },
  {      1,        TASK_100MS,     vfnTsk_100ms  }
};

uint8_t pTxBuffer2[] = {"Please type a character:\n\r"};
uint8_t pTxBufferTks[] = {"Thank you!\n\r"};

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Configure LEDs
 *
 *  Configures LEDs \#1 and \#2 (cleared by default).
 */
static void _ConfigureLeds( void )
{
	LED_Configure( 0 ) ;
	LED_Configure( 1 ) ;
}

#if COMPILAR
/* Init UART4 example function*/
void vfnSerialCtrl_Configure( void )
{
    PMC_EnablePeripheral(ID_UART4);

    const Pin my_pins[] = UART_PINS;
    PIO_Configure( my_pins, PIO_LISTSIZE( my_pins ) );

    UART_Configure(UART4, (UART_MR_PAR_NO | UART_MR_CHMODE_NORMAL), 115200, BOARD_MCK);

    NVIC_ClearPendingIRQ(UART4_IRQn);
    NVIC_SetPriority(UART4_IRQn ,1);

    /* Enables the UART to transfer and receive data. */
    UART_SetTransmitterEnabled (UART4 , 1);
    UART_SetReceiverEnabled (UART4 , 1);

    //UART_EnableIt(UART4, (UART_IER_RXRDY | UART_IER_OVRE | UART_IER_FRAME | UART_IER_PARE));
    /* Enable interrupt  */
    NVIC_EnableIRQ(UART4_IRQn);

}
#endif

/*----------------------------------------------------------------------------
 *        Exported functions
 *----------------------------------------------------------------------------*/
/**
 *  \brief getting-started Application entry point.
 *
 *  \return Unused (ANSI-C compatibility).
 */
extern int main( void )
{
    uint8_t *pBuffer2 = &pTxBuffer2[0];
    uint8_t *pBufferTks = &pTxBufferTks[0];
    uint8_t character = 0;

    /* Disable watchdog */
    WDT_Disable( WDT ) ;

    /*Clear HEAP*/
    Mem_Init();

    //vfnSerialCtrl_Configure();
    Uart_Init(Uart_Config);

   	/* Output example information */
	//printf( "\n\r-- UART with interrupts example!!! %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s using UART\n\r", BOARD_NAME ) ;
	//printf( "-- Compiled: %s %s With %s--\n\r", __DATE__, __TIME__ , COMPILER_NAME);

	//UART_SendBuffer(UART4, pBuffer2, sizeof(pTxBuffer2));
  // Uart_SendBuffer(UART_LOGCH0, pBuffer2, sizeof(pTxBuffer2)); //Please type a character

    //character = UART_GetChar(UART4);
    //Uart_GetByte(UART_LOGCH0, &character);
    //Uart_SendBuffer(UART_LOGCH0, pBufferTks, sizeof(pTxBufferTks));
    //printf("Character received by uart = %c\n\r", character);

	/* Enable I and D cache */
	SCB_EnableICache();
    SCB_EnableDCache();

	//printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;
	


  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();
    
	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}

}
