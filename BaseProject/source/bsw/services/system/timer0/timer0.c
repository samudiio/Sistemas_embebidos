/*-- Includes ----------------------------------------------------------------*/
#include "timer0.h"
#include "Afec_Ctrl.h"




void Timer0_Init(void)
{
    uint32_t div;
    uint32_t tcclks;

    /** Enable peripheral clock. */
    PMC_EnablePeripheral(ID_TC0);

    /** Configure TC for a 1Hz frequency and trigger on RC compare. */
    TC_FindMckDivisor(500, BOARD_MCK/2, &div, &tcclks, BOARD_MCK);

    //Se configura para que TIOA active el ADC
	
	/*
	2<<13-->Wave mode selected
	TC_CMR_ACPA_SET--> when Timer == RA => TIOA is set
	TC_CMR_ACPC_CLEAR--> when Timer == RC => TIOA is Clear
	*/
	
    TC_Configure(TC0, 0, tcclks | TC_CMR_WAVE|2<<13|TC_CMR_ACPA_SET|TC_CMR_ACPC_CLEAR|TC_CMR_CPCTRG);//TC_CMR_WAVE - TC_CMR_CPCTRG
    TC0->TC_CHANNEL[0].TC_RC = (BOARD_MCK / div);
    TC0->TC_CHANNEL[0].TC_RA = (BOARD_MCK / div)-0xFF;

    /* Configure and enable interrupt on RC compare */
    NVIC_ClearPendingIRQ(TC0_IRQn);
    NVIC_EnableIRQ(TC0_IRQn);
    NVIC_SetPriority(TC0_IRQn ,2);
    TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;

    Timer0_Start();
    

}

void Timer0_Start(void)
{  
  TC_Start(TC0, 0);
}




void TC0_Handler(void)
{
    volatile uint32_t dummy;
    /* Clear status bit to acknowledge interrupt */
    dummy = TC0->TC_CHANNEL[ 0 ].TC_SR;
    //NVIC_DisableIRQ(TC0_IRQn);      
    LED_Toggle(0);
    //AFEC_SoftwareConversion();
    
}







