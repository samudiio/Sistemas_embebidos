/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"    
#include <stdbool.h>
#include <stdio.h>
#include <Mem_Alloc.h>

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

	/*Initialize Mem_Alloc */
	 Mem_Init();
	/* Disable watchdog */
	WDT_Disable( WDT ) ;

	/* Output example information */
	// printf( "\n\r-- Getting Started Example Workspace Updated!!! %s --\n\r", SOFTPACK_VERSION ) ;
	// printf( "-- %s\n\r", BOARD_NAME ) ;
	// printf( "-- Compiled: %s %s With %s--\n\r", __DATE__, __TIME__ , COMPILER_NAME);

	/* Enable I and D cache */
	SCB_EnableICache();
    SCB_EnableDCache();

	// printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;

  printf("\n\r");
	uint8_t *ptr1;
	// Initial memory allocation
	ptr1 = (uint8_t*) Mem_Alloc(sizeof(uint8_t));
	printf("*ptr1 Address = %x\n\r", ptr1);

	printf("\n\r");

	uint32_t *ptr2;
	// Initial memory allocation
	ptr2 = (uint32_t*) Mem_Alloc(sizeof(uint32_t));
	printf("*ptr2 Address = %x\n\r", ptr2);

	printf("\n\r"); 
	uint8_t *ptr3; 
	ptr3 = (uint8_t*) Mem_Alloc(sizeof(uint8_t)); 
	printf("*ptr3 Address = %x\n\r", ptr3); 
	printf("\n\r");

	/* uint8_t *ptr1;
	// Initial memory allocation
	ptr1 = (uint8_t*) malloc(sizeof(uint8_t));
	printf("*ptr1 Address = %x\n\r", ptr1);

	uint32_t *ptr2;
	// Initial memory allocation
	ptr2 = (uint32_t*) mal
	loc(sizeof(uint32_t));
	printf("*ptr2 Address = %x\n\r", ptr2); */

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
