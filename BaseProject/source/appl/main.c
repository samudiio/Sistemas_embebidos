/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h" 
#include "fpu.h"   
#include <stdbool.h>
#include <stdio.h>
#include "timetick.h"

#include "chip.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
 
 /*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/
 
float spf_result;
float spf_result1;
float spf_result2;
float spf_int1 = 256;
float spf_int2 = 10;
uint32_t u32_result;
uint32_t u32_int1;
uint32_t u32_int2;
int32_t  s32_result;
int32_t  s32_int1;
int32_t  s32_int2;

volatile uint32_t cyclesCount = 0;

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

static void _ResetCounter(void) { 
	CoreDebug->DEMCR = CoreDebug_DEMCR_TRCENA_Msk;
	__DSB(); 
	DWT->LAR = 0xC5ACCE55; __DSB();
	DWT->CTRL &= ~DWT_CTRL_CYCCNTENA_Msk;
	DWT->CYCCNT = 0;
	DWT->CTRL = DWT_CTRL_CYCCNTENA_Msk;
}

static uint32_t _GetCount(void){
	return DWT->CYCCNT;
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
    /* Enable Floating Point Unit */
  vfnFpu_enable();
	printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;
  
  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();
  	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		__asm ( "nop" );
		// /* Float operations */
		// spf_result = spf_int1 - spf_int2;
		// spf_result1 = spf_int1 + spf_int2;
		// spf_result2  =   spf_result  * spf_result1;
		// spf_result = spf_int1 * spf_int2;
		// spf_result = spf_int1 / spf_int2;
		// /* Float to int conversion operations */
		// u32_int1 = spf_int1;
		// u32_int2 = spf_int2;

		// s32_int1 = spf_int1;
		// s32_int2 = spf_int2;
		// /* Int to Float conversion operations */
		// spf_result = u32_result;
		// spf_result = s32_result;
		// /* Integer operations */
		// u32_result = u32_int1 - u32_int2;
		// u32_result = u32_int1 + u32_int2;
		// u32_result = u32_int1 * u32_int2;
		// u32_result = u32_int1 / u32_int2;
		// s32_result = s32_int1 - s32_int2;
		// s32_result = s32_int1 + s32_int2;
		// s32_result = s32_int1 * s32_int2;
		// s32_result = s32_int1 / s32_int2;


		/* Subtraction Operation 55 */
		__asm volatile ("LDR  R3, =spf_int1");
		__asm volatile ("VLDR.32  s14, [R3]");
		__asm volatile ("LDR  R2, =spf_int2");
		__asm volatile ("VLDR.32  s15, [R2]");
		__asm volatile ("VSUB.F32  s15,s14,s15");
		__asm volatile ("LDR  R4, =spf_result");
		__asm volatile ("VSTR.F32  s15,[R4]");
		
		/* Sum Operation */
		__asm volatile ("LDR  R3, =spf_int1");
		__asm volatile ("VLDR.32  s14, [R3]");
		__asm volatile ("LDR  R2, =spf_int2");
		__asm volatile ("VLDR.32  s15, [R2]");
		__asm volatile ("VADD.F32  s15,s14,s15");
		__asm volatile ("LDR  R4, =spf_result1");
		__asm volatile ("VSTR.F32  s15,[R4]");
    
		/* Mult Operation */
		__asm volatile ("LDR  R3, =spf_result");
		__asm volatile ("VLDR.32  s14, [R3]");
		__asm volatile ("LDR  R4, =spf_result1");
		__asm volatile ("VLDR.32  s15, [R4]");
		__asm volatile ("VMUL.F32  s15,s14,s15");
		__asm volatile ("LDR  R2, =spf_result2");
		__asm volatile ("VSTR.F32  s15,[R2]");

		__asm volatile ("LDR  R3, =spf_int2");
		__asm volatile ("VLDR.32  s14, [R3]");
		__asm volatile ("LDR  R4, =spf_int1");
		__asm volatile ("VLDR.32  s15, [R4]");
		__asm volatile ("VMUL.F32  s15,s14,s15");
		__asm volatile ("LDR  R2, =spf_result");
		__asm volatile ("VSTR.F32  s15,[R2]");

		/* Div Operation */
		__asm volatile ("LDR  R3, =spf_int2");
		__asm volatile ("VLDR.32  s14, [R3]");
		__asm volatile ("LDR  R4, =spf_int1");
		__asm volatile ("VLDR.32  s15, [R4]");
		__asm volatile ("VDIV.F32  s15,s14,s15");
		__asm volatile ("LDR  R2, =spf_result");
		__asm volatile ("VSTR.F32  s15,[R2]");


		/* Float to int conversion operations */
		__asm volatile ("LDR  R4, =spf_int1");
		__asm volatile ("VLDR.32  s14, [R4]");
		__asm volatile ("VCVTR.F32.S32  s13, S14");
		__asm volatile ("LDR  R3, =u32_int1");
		__asm volatile ("VSTR.F32  s13,[R3]");

		__asm volatile ("LDR  R4, =spf_int2");
		__asm volatile ("VLDR.32  s14, [R4]");
		__asm volatile ("VCVTR.F32.S32  s13, S14");
		__asm volatile ("LDR  R3, =u32_int2");
		__asm volatile ("VSTR.F32  s13,[R3]");


		__asm volatile ("LDR  R4, =spf_int1");
		__asm volatile ("VLDR.32  s14, [R4]");
		__asm volatile ("VCVTR.F32.S32  s13, S14");
		__asm volatile ("LDR  R3, =s32_int1");
		__asm volatile ("VSTR.F32  s13,[R3]");

		__asm volatile ("LDR  R4, =spf_int2");
		__asm volatile ("VLDR.32  s14, [R4]");
		__asm volatile ("VCVTR.F32.S32  s13, S14");
		__asm volatile ("LDR  R3, =s32_int2");
		__asm volatile ("VSTR.F32  s13,[R3]");


		// /* Int to Float conversion operations */
		__asm volatile ("LDR  R4, =u32_result");
		__asm volatile ("VLDR.32  s14, [R4]");
		__asm volatile ("VCVT.F32.U32  s13, S14");
		__asm volatile ("LDR  R3, =spf_result");
		__asm volatile ("VSTR.F32  s13,[R3]");

		__asm volatile ("LDR  R4, =u32_result");
		__asm volatile ("VLDR.32  s14, [R4]");
		__asm volatile ("VCVT.F32.S32 s13, S14");
		__asm volatile ("LDR  R3, =spf_result");
		__asm volatile ("VSTR.F32  s13,[R3]");

		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}
}

