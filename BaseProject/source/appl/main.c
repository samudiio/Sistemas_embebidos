/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"
#include "Mem_Alloc.h"
#include "Afec_Ctrl.h"
#include <stdbool.h>
#include <stdio.h>
/**  Fast fourier transform */
#include "fft.h"
#include "ecg_data.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
/*~~~~~~  Local definitions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#define TEST_LENGTH_SAMPLES 2048

/*~~~~~~  Global variables ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/** Auxiliary input buffer to accomodate data as FFT function expects it */
float       fft_inputData[TEST_LENGTH_SAMPLES];
/** Output magnitude data */
float       fft_signalPower[TEST_LENGTH_SAMPLES/2];
/** Auxiliary output variable that holds the frequency bin with the highest level of signal power */
uint32_t    u32fft_maxPowerIndex;
/** Auxiliary output variable that holds the maximum level of signal power */
float       fft_maxPower;


TaskType Tasks[]={
/*  TaskPriority    TaskId   TaskFunctionPointer   */
  {      5,        TASK_1MS,       vfnTsk_1ms    },
  {      4,        TASK_2MSA,      vfnTsk_2msA   },
  {      4,        TASK_2MSB,      vfnTsk_2msB   },
  {      3,        TASK_10MS,      vfnTsk_10ms   },
  {      2,        TASK_50MS,      vfnTsk_50ms   },
  {      1,        TASK_100MS,     vfnTsk_100ms  }
};


Mem_ReturnType ptr_a,ptr_b,ptr_c,ptr_d;

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
uint32_t *BUFF_ADDR;
uint16_t size = 512;
uint32_t SAMP_PER = 100;
float ecg_resampled2[512];

extern int main( void )
{
	/** Auxiliary array index */
    uint16_t    u16index;
	/* Disable watchdog */
	WDT_Disable( WDT ) ;

	/* Output example information */
	/*printf( "\n\r-- Getting Started Example Workspace Updated!!! %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s--\n\r", __DATE__, __TIME__ , COMPILER_NAME);
  */
	/* Enable I and D cache */
	SCB_EnableICache();
  SCB_EnableDCache();
  
  Mem_Init();

	//printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;
  
  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();
   /* Enable Floating Point Unit */
    vfnFpu_enable();
  //printf( "size of uint8_t = %d.\n\r", sizeof(uint8_t));
  
  //ptr_a = (Mem_ReturnType)Mem_Alloc(1*sizeof(uint8_t));  
  //ptr_b = (Mem_ReturnType)Mem_Alloc(1*sizeof(uint16_t));  
  //ptr_c = (Mem_ReturnType)Mem_Alloc(1*sizeof(uint32_t));
  //ptr_d = (Mem_ReturnType)Mem_Alloc(1*sizeof(uint32_t));
  
 	AFEC_Init();
  
  
  BUFF_ADDR = (uint32_t *)Mem_Alloc(size*sizeof(uint32_t));
  
  SET_AFEC_SAMPLING(size,SAMP_PER,BUFF_ADDR);      

  uint16_t indx;
  uint32_t *BuffAdd;
  float factor;
  float temp;
  uint32_t *fft_SP_result = (uint32_t*) fft_signalPower;
  float temp_res1;
  float temp_res2;
  float temp_res3;
  float temp_res4;

  uint8_t coef[4] = {5, 7, 4, 6};

  BuffAdd = BUFF_ADDR;

  for(indx = 0; indx < 512; indx++)
  {
      factor = 3.3/1024;
      temp = *(BuffAdd + indx*4);
      ecg_resampled2[indx] = temp*factor;
  }

	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/*Prepare data for FFT operation */
        for (u16index = 0; u16index < (TEST_LENGTH_SAMPLES/2); u16index++)
        {
            fft_inputData[(2*u16index)] = ecg_resampled[u16index];
            fft_inputData[(2*u16index) + 1] = 0;
        }
        /** Perform FFT on the input signal */
        fft(fft_inputData, fft_signalPower, TEST_LENGTH_SAMPLES/2, &u32fft_maxPowerIndex, &fft_maxPower);
        

        for(indx = 30; indx < 255; indx++)
        {
            temp_res1 = fft_signalPower[indx];
            temp_res2 = fft_signalPower[indx-1];
            temp_res3 = fft_signalPower[indx-2];
            temp_res4 = fft_signalPower[indx-3];
            temp_res2*=coef[indx];
            temp_res3*=coef[indx+1];
            temp_res4*=coef[indx+2];

        }



        /* Publish through emulated Serial the byte that was previously sent through the regular Serial channel */
		printf("%5d  %5.4f \r\n", u32fft_maxPowerIndex, fft_maxPower);
		
		/* Perform all scheduled tasks */    
		vfnTask_Scheduler();
	}

}
