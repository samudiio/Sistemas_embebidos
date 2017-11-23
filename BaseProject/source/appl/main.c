/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h" 
#include "fpu.h"   
#include <stdbool.h>
#include <stdio.h>

/** Input Image */
#include    "lena_image.h"


/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
 
 /*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/

/* Auxiliary variables */
uint16_t i_index;
uint16_t j_index;

/* Averaging mask */
float AvgMask2x2[2][2] =
{
    0.25, 0.25,
    0.25, 0.25
};

/* Intermediate scaled up image - temporary pixel calculation */
uint32_t Filtered2x2scaled; //__attribute__((section("four_byte_aligment")));
/* Intermediate Mask in integer numbers to accelerate execution */
uint32_t AvgMask2x2scaled[2][2];// __attribute__((section("four_byte_aligment")));
/*Output filtered image */
uint8_t Lena_Image_Filtered[IMAGE_ROWS][IMAGE_COLS];// __attribute__((section("four_byte_aligment")));


float       spf_result;
float       spf_result1;
float       spf_result2;
float       spf_int1 = 256;
float       spf_int2 = 10;
uint32_t    u32_result;
uint32_t    u32_int1;
uint32_t    u32_int2;
int32_t     s32_result;
int32_t     s32_int1;
int32_t     s32_int2;


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

	/** Indication for measurement */
	LED_Set(1);

	/* Convert to integer and scale up correlation mask in order to avoid loosing resolution */
    for (i_index = 0; i_index < 2; i_index++)
    {
        for (j_index = 0; j_index < 2; j_index++)
        {     /* Mask to be scaled up by a factor of 2^16*/
              AvgMask2x2scaled[i_index][j_index] = (uint32_t)(AvgMask2x2[i_index][j_index] * 0x00010000);
        }
    }
    /* Perform correlation operation */
    for (i_index = 0; i_index < IMAGE_ROWS-1; i_index++)
    {
        for (j_index = 0; j_index < IMAGE_COLS; j_index++)
        {     /* For items on the first column */
            if(j_index == 0)
            {
                Filtered2x2scaled =
                    (uint32_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                    (uint32_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][1]);
            }
            else
            {
                Filtered2x2scaled =
                    (uint32_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                    (uint32_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][0]) +
                    (uint32_t)(Lena_Image[i_index+1][j_index-1] * AvgMask2x2scaled[1][1]) +
                    (uint32_t)(Lena_Image[i_index][j_index-1] * AvgMask2x2scaled[0][1]);
            }
            /* Scale down result */
            Lena_Image_Filtered[i_index][j_index] = (uint8_t)( Filtered2x2scaled >> 16);
        }
    }
    /** End of indication for measurement */
    LED_Clear(1);

	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
		//vfnTask_Scheduler();
	}

}
