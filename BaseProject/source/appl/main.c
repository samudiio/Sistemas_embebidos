/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h" 
#include "fpu.h"   
#include <stdbool.h>
#include <stdio.h>
#include <arm_math.h>

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
//float AvgMask2x2[2][2] =
//{
//    0.25, 0.25,
//    0.25, 0.25
//};

/* Averaging mask */
const float32_t AvgMask2x2[4] =
{
  0.25,     0.25,
  0.25,     0.25,
};

/* Averaging mask */
float AvgMask2x2_original[2][2] =
{
    0.25, 0.25,
    0.25, 0.25
};


/* Intermediate Mask in integer numbers to accelerate execution */
float32_t AvgMask2x2scaled2[4];

uint32_t FilteredTemp1;
uint32_t FilteredTemp2;

uint32_t Filtered2x2scaled2;

/* Averaging mask */
/*float AvgMask2x2[2][2] =
{
    0.25, 0.25,
    0.25, 0.25
};
*/

float a = 2;
float b = 1;
float c = 2;
float d = 2;
uint32_t e = 0;


uint16_t Filtered2x2scaled_t1;
uint16_t Filtered2x2scaled_t2;

/* Intermediate scaled up image - temporary pixel calculation */
uint16_t Filtered2x2scaled; //__attribute__((section("four_byte_aligment")));
/* Intermediate Mask in integer numbers to accelerate execution */
uint16_t AvgMask2x2scaled[2][2];// __attribute__((section("four_byte_aligment")));
/*Output filtered image */
uint8_t Lena_Image_Filtered[IMAGE_ROWS][IMAGE_COLS];// __attribute__((section("four_byte_aligment")));
uint8_t Lena_Image_Filtered2[IMAGE_ROWS][IMAGE_COLS];

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
    uint32_t x = 0x2634;
    uint32_t y = 0x4782;
    uint32_t z;
    uint8_t centi = 1;

    volatile uint32_t ret, ret2;

    arm_matrix_instance_f32 AvgMask;        /* AvgMask Matrix Instance */
    arm_matrix_instance_f32 AvgMaskScaled;  /*AvgMaskScaled Matrix Instance */
    uint32_t srcRows, srcColumns;  /* Temporary variables */
    arm_status status;

    uint32_t A = 0;
    uint32_t B = 0;
    uint32_t C = 0;
    uint32_t D = 0;
    uint32_t E = 0;
    uint32_t F = 0;

	/* Disable watchdog */
	WDT_Disable( WDT ) ;

	/* Enable I and D cache */
	SCB_EnableICache();
    SCB_EnableDCache();
    /* Enable Floating Point Unit */
    vfnFpu_enable();
	
	_ConfigureLeds() ;
  
  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();

	printf("AvgMask2x2 matrix: \n\r");
	printf("%0.02f  %0.02f \n\r", AvgMask2x2[0], AvgMask2x2[1]);
	printf("%0.02f  %0.02f \n\r", AvgMask2x2[2], AvgMask2x2[3]);

	//z = x + y;
	//z = __SADD16(x, y);
	//printf("\n\rz = %d\n\r", z);


	//z = __SMUAD(0x1234, 0x8362);
    //printf("ret = %d\n\r\n", ret);

    //__UQADD16
	ret = __UADD16(0x68EF54CD, 0x72AB9674);
  ret2 = __UADD16(0xAEF2FC07, 0x46387A8D);
  //printf("ret = %x\n\r\n", ret);
  //printf("ret2 = %x\n\r\n", ret2);


	/** Indication for measurement */
	LED_Set(0);

	/* Initialise A Matrix Instance with numRows, numCols and data array(A_f32) */
    srcRows = 2;
    srcColumns = 2;
    arm_mat_init_f32(&AvgMask, srcRows, srcColumns, (float32_t *)AvgMask2x2);
    arm_mat_init_f32(&AvgMaskScaled, srcRows, srcColumns, (float32_t *)AvgMask2x2scaled2);

    /* Scale up correlation mask in order to avoid loosing resolution */
    /* Mask to be scaled up by a factor of 2^8*/
    status = arm_mat_scale_f32(&AvgMask, 0x00000100, &AvgMaskScaled);


    printf("AvgMask2x2scaled2 matrix: \n\r");
    printf("%0.02f  %0.02f \n\r", AvgMask2x2scaled2[0], AvgMask2x2scaled2[1]);
    printf("%0.02f  %0.02f \n\r", AvgMask2x2scaled2[2], AvgMask2x2scaled2[3]);

    /* Convert to integer and scale up correlation mask in order to avoid loosing resolution */
////	printf("AvgMask2x2scaled = \n\r");
//    for (i_index = 0; i_index < 2; i_index++)
//    {
//        for (j_index = 0; j_index < 2; j_index++)
//        {     /* Mask to be scaled up by a factor of 2^8*/
//              //AvgMask2x2scaled[i_index][j_index] = (uint32_t)(AvgMask2x2[i_index][j_index] * 0x00010000);
//              AvgMask2x2scaled[i_index][j_index] = (uint16_t)(AvgMask2x2[i_index][j_index] * 0x00000100);
//        }
//    }
////    printf("%d  %d \n\r%d  %d", AvgMask2x2scaled[0][0], AvgMask2x2scaled[0][1], AvgMask2x2scaled[1][0], AvgMask2x2scaled[1][1]);

    /* Perform correlation operation */
    for (i_index = 0; i_index < IMAGE_ROWS-1; i_index++)
    {
        for (j_index = 0; j_index < IMAGE_COLS; j_index++)
        {     /* For items on the first column */
            if(j_index == 0)
            {
                /*Filtered2x2scaled =
                    (int16_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                    (int16_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][1]);
*/

                //Filtered2x2scaled = __UADD16((int16_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]), (int16_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][1]));

              /*  Filtered2x2scaled2 =
                    (uint16_t)(Lena_Image[i_index][j_index] * (uint16_t)AvgMask2x2scaled2[0]) +
                    (uint16_t)(Lena_Image[i_index+1][j_index] * (uint16_t)AvgMask2x2scaled2[3]);
*/
                A = ((Lena_Image[i_index][j_index]) << 16 | (uint16_t)(AvgMask2x2scaled2[0]));
                B = ((Lena_Image[i_index+1][j_index]) << 16 | (uint16_t)(AvgMask2x2scaled2[3]));
                Filtered2x2scaled2 = __SMUAD(A , B);


/*            if(centi == 1)
              {
                centi = 5;
                printf("A = %d\n\r", Lena_Image[i_index][j_index]);
                printf("B = %0.02f\n\r", AvgMask2x2scaled2[0]);
                printf("C = %d\n\r", Lena_Image[i_index+1][j_index]);
                printf("B = %0.02f\n\r", AvgMask2x2scaled2[3]);

                printf("A or = %d\n\r", A);
              }
              */
            }
            else
            {
//                Filtered2x2scaled =
//                    (int16_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
//                    (int16_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][0]) +
//                    (int16_t)(Lena_Image[i_index+1][j_index-1] * AvgMask2x2scaled[1][1]) +
//                    (int16_t)(Lena_Image[i_index][j_index-1] * AvgMask2x2scaled[0][1]);


//                Filtered2x2scaled_t1 = __UADD16((int16_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]), (int16_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][0]));
//                Filtered2x2scaled_t2 = __UADD16((int16_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[1][1]), (int16_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[0][1]));
//                Filtered2x2scaled = __UADD16(Filtered2x2scaled_t1, Filtered2x2scaled_t2);

             /*   Filtered2x2scaled2 =
                    (uint16_t)(Lena_Image[i_index][j_index] * (uint16_t)AvgMask2x2scaled2[0]) +
                    (uint16_t)(Lena_Image[i_index+1][j_index] * (uint16_t)AvgMask2x2scaled2[2]) +
                    (uint16_t)(Lena_Image[i_index+1][j_index-1] * (uint16_t)AvgMask2x2scaled2[3]) +
                    (uint16_t)(Lena_Image[i_index][j_index-1] * (uint16_t)AvgMask2x2scaled2[1]);
*/

                C = ((Lena_Image[i_index][j_index]) << 16 | (uint16_t)(AvgMask2x2scaled2[0]));
                D = ((Lena_Image[i_index+1][j_index]) << 16 | (uint16_t)(AvgMask2x2scaled2[2]));
                FilteredTemp1 = __SMUAD(C , D);

                E = ((Lena_Image[i_index+1][j_index-1]) << 16 | (uint16_t)(AvgMask2x2scaled2[3]));
                F = ((Lena_Image[i_index][j_index-1]) << 16 | (uint16_t)(AvgMask2x2scaled2[1]));
                FilteredTemp2 = __SMUAD(E , F);

                Filtered2x2scaled2 = FilteredTemp1 + FilteredTemp2;

            }
            /* Scale down result */
            //Lena_Image_Filtered[i_index][j_index] = (uint8_t)( Filtered2x2scaled >> 8);

            Lena_Image_Filtered2[i_index][j_index] = (uint8_t)( Filtered2x2scaled2 >> 8);
        }
    }




    /** End of indication for measurement */
    LED_Clear(0);

	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
		//vfnTask_Scheduler();
	}

}
