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

/** Input Image */
#include    "lena_image.h"
/** Image Processing services */
//#include    "image_processing.h"

#include "chip.h"

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/
 
 /*----------------------------------------------------------------------------
 *        Global variables
 *----------------------------------------------------------------------------*/
 
/* Auxiliary variables */
uint16_t i_index;
uint16_t j_index;

/* Image Data */
// float imageIn[2][2] =
// {
//     1, 20,   
//     3, 10
// };
char  StringFile[IMAGE_ROWS * IMAGE_COLS];

/* Averaging mask */
float AvgMask2x2[2][2] =
{
    0.25, 0.25,   
    0.25, 0.25
};

/* Intermediate scaled up image - temporary pixel calculation */     
uint16_t Filtered2x2scaled; // __attribute__((section("four_byte_aligment")));
/* Intermediate Mask in integer numbers to accelerate execution */
uint16_t AvgMask2x2scaled[2][2]; //__attribute__((section("four_byte_aligment")));
/*Output filtered image */     
uint8_t Lena_Image_Filtered[IMAGE_ROWS][IMAGE_COLS]; //__attribute__((section("four_byte_aligment")));


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

// float a = 2;
// float b = 1;
// float c = 2;
// float d = 2;
// // uint32_t e = 0;
// float e = 2;
// float f = 2;
// float g = 1;
// float h = 2;
// float i = 0;
uint16_t a = 2;
uint16_t b = 1;
uint16_t c = 2;
uint16_t d = 2;
volatile uint32_t e = 0;
uint16_t f = 2;
uint16_t h = 2;
uint32_t i = 0;
uint16_t g = 1;

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/
uint32_t * u32Lena = (uint32_t*) Lena_Image;
uint8_t * uLena = (uint8_t*) Lena_Image;
uint32_t * u32LenaFilter = (uint32_t*) Lena_Image_Filtered;
uint32_t p_index;

uint32_t MyLena1=0;
uint32_t MyLena2=0;
uint32_t MyLena3=0;
uint32_t MyLena4=0;
uint32_t MyResult1_jzero=0;
uint32_t MyResult2=0;
uint32_t MyResult3=0;
uint32_t MyResultaux=0;
uint32_t MyResult4=0;

uint32_t Final=0;

uint32_t  TempLena1;
uint32_t  TempLena2;
uint32_t  Temp8Lena1;
uint32_t  Temp8Lena2;
uint32_t  MyResult1=0;

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

  volatile uint32_t ret;
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

    __asm volatile("nop");
    i= __SMUAD((a<<16|b),(c<<16|d));
    //e= __SMUAD((1<<16|1),(1<<16|1));
    i= e+i;
    ret = __UADD8(0x10111213, 0x01010101);
  
    //Floats
    // __asm volatile ("LDR  R3, =i");
    // __asm volatile ("LDR  R4, =a");
    // __asm volatile("VLDMIA.F32 R4, {S4-S11}");
    // __asm volatile ("VMUL.F32  S3, S4, S5");
    // __asm volatile ("VMLA.F32  S3, S6, S7");
    // __asm volatile ("VMLA.F32  S3, S8, S9");
    // __asm volatile ("VMLA.F32  S3, S10, S11");
    // __asm volatile ("VSTR.F32  S3,[R3]");
    
    //1
    // __asm volatile ("LDR  R4, =a");
    // __asm volatile ("LDR  R5, =b");
    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
    // __asm volatile ("VMUL.F32  S3, S4, S5");
    // __asm volatile ("LDR  R3, =e");
    // __asm volatile ("LDR  R4, =c");
    // __asm volatile ("LDR  R5, =d");
    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
    // __asm volatile ("VMLA.F32  S3, S4, S5");
    // __asm volatile ("VCVT.U32.F32  S3, S3");
    // __asm volatile ("VSTR.F32  S3,[R3]");


    //2
    // __asm volatile ("LDR  R3, =e");
    // __asm volatile ("LDR  R4, =a");
    // __asm volatile ("LDR  R5, =b");
    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
    // __asm volatile ("VMUL.F32  S3, S4, S5");
    // __asm volatile ("LDR  R4, =c");
    // __asm volatile ("LDR  R5, =d");
    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
    // __asm volatile ("VMLA.F32  S3, S4, S5");

    //  __asm volatile ("LDR  R4, =f");
    // __asm volatile ("LDR  R5, =g");
    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
    // __asm volatile ("VMLA.F32  S3, S4, S5");
    // __asm volatile ("LDR  R4, =h");
    // __asm volatile ("LDR  R5, =i");
    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
    // __asm volatile ("VMLA.F32  S3, S4, S5");
    // __asm volatile ("VCVT.U32.F32  S3, S3");
    // __asm volatile ("VSTR.F32  S3,[R3]"); 

    //Bueno
    // __asm volatile ("LDR  R4, =a");
    // __asm volatile ("LDR  R5, =b");
    // __asm volatile ("LDR  R6, =c");
    //  __asm volatile ("LDR  R7, =d");
    // __asm volatile ("LDR  R8, =f");
    // __asm volatile ("LDR  R9, =g");
    // __asm volatile ("LDR  R10, =h");
    // __asm volatile ("LDR  R11, =i");
    //__asm volatile("VLDMIA.F32 R4, {S4,S5,S6,S7,S8,S9,S10,S11}");
    // __asm volatile("VLDMIA.F32 R4, {S4-S11}");
    
    // __asm volatile ("VMUL.F32  S3, S4, S5");
    // __asm volatile ("VMLA.F32  S3, S6, S7");
    // __asm volatile ("VMLA.F32  S3, S8, S9");
    // __asm volatile ("VMLA.F32  S3, S10, S11");
    // __asm volatile ("VCVT.U32.F32  S3, S3");
    // __asm volatile ("VSTR.F32  S3,[R3]");

    // Enteros
    // __asm volatile ("LDR  R4, =a");
    // __asm volatile ("LDR  R5, =b");
    // __asm volatile ("LDR  R6, =c");
    // __asm volatile ("LDR  R7, =d");
    // __asm volatile ("LDR  R8, =f");
    // __asm volatile ("LDR  R9, =g");
    // __asm volatile ("LDR  R10, =h");
    // __asm volatile ("LDR  R11, =i");
    // __asm volatile ("UMULL R2, R3, R4, R5");
    // __asm volatile ("UMLAL R2, R3, R6, R7");
    // __asm volatile ("UMLAL R2, R3, R8, R9");
    // __asm volatile ("UMLAL R2, R3, R10, R11");
    // __asm volatile ("STRB  R2,[R0, #1]");

    // a = imageIn[0][0];
    //__asm volatile ("ADR  R0, imageIn");
    
  
    //printf("%u\n\r", e);
    LED_Set(0);
    for (i_index = 0; i_index < 2; i_index++)
    {
    /* Convert to integer and scale up correlation mask in order to avoid loosing resolution */
        for (j_index = 0; j_index < 2; j_index++)
        {     /* Mask to be scaled up by a factor of 2^8*/
            //   AvgMask2x2scaled[i_index][j_index] = (uint32_t)(AvgMask2x2[i_index][j_index] * 0x00010000);
              AvgMask2x2scaled[i_index][j_index] = (uint16_t) (AvgMask2x2[i_index][j_index] * 0x00000100);
        }
    }
    /* Perform correlation operation */
    for (i_index = 0; i_index < IMAGE_ROWS-1; i_index++)
    {
        for (j_index = 0; j_index < IMAGE_COLS; j_index++)
        {     /* For items on the first column */
            if(j_index == 0)
            {
                // Filtered2x2scaled = 
                //     (uint32_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                //     (uint32_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][1]); 

                Filtered2x2scaled = 
                    (uint16_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                    (uint16_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][1]); 
                    // __asm volatile ("LDR  R4, =a");
                    // __asm volatile ("LDR  R5, =b");
                    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
                    // __asm volatile ("VMUL.F32  S3, S4, S5");
                    // __asm volatile ("LDR  R3, =Filtered2x2scaled");
                    // __asm volatile ("LDR  R4, =c");
                    // __asm volatile ("LDR  R5, =d");
                    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
                    // __asm volatile ("VMLA.F32  S3, S4, S5");
                    // __asm volatile ("VCVT.U32.F32  S3, S3");
                    // __asm volatile ("VSTR.F32  S3,[R3]"); 

                    // a = Lena_Image[i_index][j_index];
                    // b = AvgMask2x2scaled[0][0];
                    // c = Lena_Image[i_index+1][j_index];
                    // d = AvgMask2x2scaled[1][1];
                    // __asm volatile ("LDR  R3, =Filtered2x2scaled");
                    // __asm volatile ("LDR  R4, =a");
                    // __asm volatile("VLDMIA.F32 R4, {S4-S7}");
                    // __asm volatile ("VMUL.F32  S3, S4, S5");
                    // __asm volatile ("VMLA.F32  S3, S6, S7");
                    // // __asm volatile ("VCVT.U32.F32  S3, S3");
                    // __asm volatile ("VSTR.F32  S3,[R3]"); 
            }
            else
            {
                // Filtered2x2scaled = 
                //     (uint32_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                //     (uint32_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][0]) +
                //     (uint32_t)(Lena_Image[i_index+1][j_index-1] * AvgMask2x2scaled[1][1]) + 
                //     (uint32_t)(Lena_Image[i_index][j_index-1] * AvgMask2x2scaled[0][1]);

                Filtered2x2scaled = 
                    (uint16_t)(Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                    (uint16_t)(Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][0]) +
                    (uint16_t)(Lena_Image[i_index+1][j_index-1] * AvgMask2x2scaled[1][1]) + 
                    (uint16_t)(Lena_Image[i_index][j_index-1] * AvgMask2x2scaled[0][1]);

                // Filtered2x2scaled = 
                //     (Lena_Image[i_index][j_index] * AvgMask2x2scaled[0][0]) +
                //     (Lena_Image[i_index+1][j_index] * AvgMask2x2scaled[1][0]) +
                //     (Lena_Image[i_index+1][j_index-1] * AvgMask2x2scaled[1][1]) + 
                //     (Lena_Image[i_index][j_index-1] * AvgMask2x2scaled[0][1]);

                    // a = (float) Lena_Image[i_index][j_index];
                    // b = (float) AvgMask2x2scaled[0][0];
                    // c = (float) Lena_Image[i_index+1][j_index];
                    // d = (float) AvgMask2x2scaled[1][0];
                    // f = (float) Lena_Image[i_index+1][j_index-1];
                    // g = (float) AvgMask2x2scaled[1][1];
                    // h = (float) Lena_Image[i_index][j_index-1];
                    // i = (float) AvgMask2x2scaled[0][1];

                    // __asm volatile ("LDR  R3, =Filtered2x2scaled");
                    // __asm volatile ("LDR  R4, =a");
                    // __asm volatile ("LDR  R5, =b");
                    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
                    // __asm volatile ("VMUL.F32  S3, S4, S5");
                    // __asm volatile ("LDR  R4, =c");
                    // __asm volatile ("LDR  R5, =d");
                    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
                    // __asm volatile ("VMLA.F32  S3, S4, S5");

                    // __asm volatile ("LDR  R4, =f");
                    // __asm volatile ("LDR  R5, =g");
                    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
                    // __asm volatile ("VMLA.F32  S3, S4, S5");
                    // __asm volatile ("LDR  R4, =h");
                    // __asm volatile ("LDR  R5, =i");
                    // __asm volatile("VLDMIA.F32 R4, {S4,S5}");
                    // __asm volatile ("VMLA.F32  S3, S4, S5");
                    // __asm volatile ("VCVT.U32.F32  S3, S3");
                    // __asm volatile ("VSTR.F32  S3,[R3]");

                    // a = Lena_Image[i_index][j_index];
                    // b = AvgMask2x2scaled[0][0];
                    // c = Lena_Image[i_index+1][j_index];
                    // d = AvgMask2x2scaled[1][0];
                    // e = Lena_Image[i_index+1][j_index-1];
                    // f = AvgMask2x2scaled[1][1];
                    // g = Lena_Image[i_index][j_index-1];
                    // h = AvgMask2x2scaled[0][1];
                    

                    // __asm volatile ("LDR  R3, =Filtered2x2scaled");
                    // __asm volatile ("LDR  R4, =a");
                    // // __asm volatile ("LDR  R5, =b");
                    // // __asm volatile ("LDR  R6, =c");
                    // // __asm volatile ("LDR  R7, =d");
                    // // __asm volatile ("LDR  R8, =e");
                    // // __asm volatile ("LDR  R9, =f");
                    // // __asm volatile ("LDR  R10, =g");
                    // // __asm volatile ("LDR  R11, =h");
                    // __asm volatile("VLDMIA.F32 R4, {S4-S11}");
                    
                    // __asm volatile ("VMUL.F32  S3, S4, S5");
                    // __asm volatile ("VMLA.F32  S3, S6, S7");
                    // __asm volatile ("VMLA.F32  S3, S8, S9");
                    // __asm volatile ("VMLA.F32  S3, S10, S11");
                    // //__asm volatile ("VCVT.U32.F32  S3, S3");
                    // __asm volatile ("VSTR.F32  S3,[R3]");

                    // __asm volatile ("LDR  R4, =a");
                    // __asm volatile("VLDMIA.F32 R4, {S4-S11}");
                    // __asm volatile ("VMUL.F32  S3, S4, S5");
                    // __asm volatile ("VMLA.F32  S3, S6, S7");
                    // __asm volatile ("VMLA.F32  S3, S8, S9");
                    // __asm volatile ("VMLA.F32  S3, S10, S11");
                    // __asm volatile ("VSTR.F32  S3,[R3]");
                }
                // uint32_t result = (uint32_t)Filtered2x2scaled;
            /* Scale down result */
            // Lena_Image_Filtered[i_index][j_index] = (uint8_t)(result >> 16);
            Lena_Image_Filtered[i_index][j_index] = (uint8_t)( Filtered2x2scaled >> 8);
        }
    }
    /** End of indication for measurement */
	  LED_Clear(0);
	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
		/* Perform all scheduled tasks */
        vfnTask_Scheduler();
        my_matrix();
    }
}

void my_matrix(void){ 
  uint32_t p_index_aux;
  
  LED_Set(1);    
                                  
    for (p_index = 0; p_index < (23716) ; p_index++){ 
      p_index_aux=p_index<<8;  
      TempLena1  = u32Lena[p_index];
      TempLena2  = u32Lena[p_index+77];
      Temp8Lena1 = uLena[p_index-1];
      Temp8Lena2 = uLena[p_index+307];
      MyLena1  = ((TempLena1&0xff) | ((TempLena1&0xff00)<<8));
      MyLena2  = ((TempLena2&0xff) | ((TempLena2&0xff00)<<8));
      MyLena3   = ((((TempLena1&0xff0000)>>16)) | ((TempLena1&0xff000000)>>8));
      MyLena4   = ((((TempLena2&0xff0000)>>16)) | ((TempLena2&0xff000000)>>8));
      MyResult1_jzero = __UADD16(MyLena1,MyLena2);
      MyResult2 = ((MyResult1_jzero&0xffff0000)>>16)+(MyResult1_jzero&0xffff);            
      MyResultaux = __UADD16(MyLena3,MyLena4);
      MyResult3=((MyResult1_jzero&0xffff0000)>>16)+(MyResultaux&0xffff);
      MyResult4 = ((MyResultaux&0xffff0000)>>16)+(MyResultaux&0xffff);      
      MyResult1_jzero >>= 2;       
      MyResult2 >>= 2;
      MyResult3 >>= 2;
      MyResult4 >>= 2;        
      
        if((p_index==0) || ((p_index_aux%308)==0) ){
          Final =  (MyResult1_jzero&0xff) | ((MyResult2&0xff)<<8)| ((MyResult2&0xff)<<16) |((MyResult4&0xff)<<24); 
          u32LenaFilter[p_index] = Final;      
          //printf("%x --+-- %x  \n\r",MyResult1,MyResult2);
        }else{
          MyResult1 = Temp8Lena1 + Temp8Lena2 + (TempLena1&0xff) + (TempLena2&0xff);
          MyResult1 >>= 2;
                  
          Final =  (MyResult1&0xff) | ((MyResult2&0xff)<<8)| ((MyResult2&0xff)<<16) |((MyResult4&0xff)<<24); 
          u32LenaFilter[p_index] = Final;     
        }
    }    
      
  LED_Clear(1);
}
