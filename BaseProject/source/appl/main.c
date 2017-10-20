/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include <board.h>
#include <app_scheduler.h>
#include <Tasks.h>    
#include <stdbool.h>
#include <stdio.h>
#include <Uart_Cfg.h>
#include <uart.h>

/** Other modules */
#include     "compiler.h"
#include     "board.h"
#include     "pmc.h"
#include     "pio.h"

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

void Serial_Cnf(){
	PMC_EnablePeripheral(ID_UART4);
	const Pin my_pins[] = PINS_UART4;
	PIO_Configure( my_pins, PIO_LISTSIZE( my_pins ) );
	Uart_Init(&UART_Config);

	/* Clear pending IRQs and Set priority of IRQs */
	NVIC_ClearPendingIRQ(UART4_IRQn);
	NVIC_SetPriority(UART4_IRQn, 1);

	/* Enables the UART to transfer and receive data. */
	Uart_SetTxEnable(0, 1);
	Uart_SetRxEnable(0, 1);

	/* Enable interrupt  */
	NVIC_EnableIRQ(UART4_IRQn);
}

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
    /*Clear HEAP*/
    Mem_Init();

	/* Disable watchdog */
	WDT_Disable( WDT ) ;

	/* Enable I and D cache */
	SCB_EnableICache();
    SCB_EnableDCache();

    /* Configure Leds */
	_ConfigureLeds() ;

	/* Configure UART */
	Serial_Cnf();
  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();
	//printf("SAM V71 \n\r");
	Uart_SendByte(0,64);
	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}

}


