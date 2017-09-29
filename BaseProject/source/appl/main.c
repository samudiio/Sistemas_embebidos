/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"
#include "Mem_Alloc.h"
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


Mem_Uint8PtrType ptr_a,ptr_b,ptr_c,ptr_d;
Mem_Uint8PtrType ptr_a_aux,ptr_b_aux,ptr_c_aux;
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

	/* Disable watchdog */
	WDT_Disable( WDT ) ;

	/* Output example information */
	printf( "\n\r-- Getting Started Example Workspace Updated!!! %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s--\n\r", __DATE__, __TIME__ , COMPILER_NAME);

	/* Enable I and D cache */
	SCB_EnableICache();
  SCB_EnableDCache();
  
  Mem_Init();

	printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;
  
  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();
  
  //printf( "size of uint8_t = %d.\n\r", sizeof(uint8_t));
  
  ptr_a = (Mem_Uint8PtrType)Mem_Alloc(1*sizeof(uint8_t));
  ptr_a_aux = ptr_a;
  
  ptr_b = (Mem_Uint8PtrType)Mem_Alloc(1*sizeof(uint16_t));
  ptr_b_aux = ptr_b;
  
  ptr_c = (Mem_Uint8PtrType)Mem_Alloc(1*sizeof(uint32_t));
  ptr_c_aux = ptr_c;
  ptr_d = (Mem_Uint8PtrType)Mem_Alloc(1*sizeof(uint32_t));
  
  printf("Address = %x\n\r", ptr_a);
  printf("Address = %x\n\r", ptr_b);
  printf("Address = %x\n\r", ptr_c);
  printf("Address = %x\n\r", ptr_d);
  
  
  
  

	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}

}
