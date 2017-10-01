/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"    
#include <stdbool.h>
#include <stdio.h>

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
    uint8_t *prt1;
    uint8_t *prt2;
    uint8_t *prt3;
    uint8_t *prt4;
    uint8_t *prt5;

    /*Clear HEAP*/
    Mem_Init();

    // Allocate 1 byte of memory
    prt1 = (uint8_t*) Mem_Alloc(0x2800);
    printf("*ptr1 Address = %x\n\n\r", prt1);

    // Allocate 2 bytes of memory
    prt2 = (uint8_t*) Mem_Alloc(0x02);
    printf("*ptr2 Address = %x\n\n\r", prt2);

    // Allocate 3 bytes of memory
    prt3 = (uint8_t*) Mem_Alloc(0x03);
    printf("*ptr3 Address = %x\n\n\r", prt3);

    // Allocate 5 bytes of memory
    prt4 = (uint8_t*) Mem_Alloc(0x05);
    printf("*ptr4 Address = %x\n\n\r", prt4);

    // Allocate 7 bytes of memory
    prt5 = (uint8_t*) Mem_Alloc(0x07);
    printf("*ptr4 Address = %x\n\n\r", prt5);

	/* Disable watchdog */
	WDT_Disable( WDT ) ;

	/* Output example information */
	//printf( "\n\r-- Getting Started Example Workspace Updated!!! %s --\n\r", SOFTPACK_VERSION ) ;
	//printf( "-- %s\n\r", BOARD_NAME ) ;
	//printf( "-- Compiled: %s %s With %s--\n\r", __DATE__, __TIME__ , COMPILER_NAME);

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
