/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "board.h"
#include "app_scheduler.h"
#include "Tasks.h"
#include "uart_dma.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/*----------------------------------------------------------------------------
 *        Local definitions
 *----------------------------------------------------------------------------*/

#define RX_SIZE         30

TaskType Tasks[]={
/*  TaskPriority    TaskId   TaskFunctionPointer   */
  {      5,        TASK_1MS,       vfnTsk_1ms    },
  {      4,        TASK_2MSA,      vfnTsk_2msA   },
  {      4,        TASK_2MSB,      vfnTsk_2msB   },
  {      3,        TASK_10MS,      vfnTsk_10ms   },
  {      2,        TASK_50MS,      vfnTsk_50ms   },
  {      1,        TASK_100MS,     vfnTsk_100ms  }
};

const Pin UART4_PINS[] = {PINS_UART4};

/** Global DMA driver for all transfer */
static UartDma Uartd;
static UartChannel UartTx, UartRx;
static sXdmad dmad;

uint8_t pTxBuffer[] = {"This is UART Tx Buffer.........\n\r"};
uint8_t pRxBuffer[RX_SIZE];

/*----------------------------------------------------------------------------
 *        Local functions
 *----------------------------------------------------------------------------*/

/**
 *  \brief Handler for UART4.
 *
 *  Process UART4 interrupts
 */
void UART4_Handler(void)
{
    uint32_t Status = UART_GetStatus(UART4);

    if (Status & (UART_SR_OVRE | UART_SR_FRAME | UART_SR_PARE)) {
        UART4->UART_CR = UART_CR_RSTSTA;
        printf("Error \n\r");
    }

    printf("%c", (char)UART4->UART_RHR);
}

/**
 *  \brief Handler for XDMAC.
 *
 *  Process XDMA interrupts
 */
void XDMAC_Handler(void)
{
    XDMAD_Handler(&dmad);
}

/**
 * \brief Displays the user menu on the DBGU.
 */
static void DisplayMenu(void)
{
    printf("\n\rMenu :\n\r");
    printf("========================\n\r");
    printf(" UART is Configured in : LoopBack\n\r");
    //printf("  I: Perform UART transfer with interrupt\n\r");
    printf("  D: Perform UART DMA transfer in local loopback\n\r");
    printf("  H: Display menu \n\r\n\r");
    printf("========================\n\r");
}

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

/**
 * \brief UART transfer with DMA in UART loop back mode
 */
static void _UartdConfigLB(void)
{
    uint32_t mode = 0
        | UART_MR_CHMODE_LOCAL_LOOPBACK//UART_MR_CHMODE_NORMAL
        | UART_MR_PAR_NO
        | UART_MR_BRSRCCK_PERIPH_CLK;

    dmad.pXdmacs = XDMAC;

    memset(&UartTx, 0, sizeof(UartChannel));
    memset(&UartRx, 0, sizeof(UartChannel));
    UartTx.BuffSize = 25;
    UartTx.pBuff = pTxBuffer;
    UartRx.BuffSize= 25;
    UartRx.pBuff = pRxBuffer;
    UartTx.sempaphore = 1;
    UartRx.sempaphore = 1;

    Uartd.pRxChannel = &UartRx;
    Uartd.pTxChannel = &UartTx;
    Uartd.pXdmad = &dmad;
    PMC_EnablePeripheral(ID_UART4);
    PIO_Configure(UART4_PINS, PIO_LISTSIZE(UART4_PINS));
    UARTD_Configure(&Uartd, ID_UART4, mode, 115200, BOARD_MCK);
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
    uint8_t ucKey;

	/* Disable watchdog */
	WDT_Disable( WDT ) ;

	/* Output example information */
	printf( "\n\r-- Getting Started Example Workspace Updated!!! %s --\n\r", SOFTPACK_VERSION ) ;
	printf( "-- %s\n\r", BOARD_NAME ) ;
	printf( "-- Compiled: %s %s With %s--\n\r", __DATE__, __TIME__ , COMPILER_NAME);

	/* Enable I and D cache */
	SCB_EnableICache();
    SCB_EnableDCache();

	printf( "Configure LED PIOs.\n\r" ) ;
	_ConfigureLeds() ;

  	/* Initialize Task Scheduler */
	vfnScheduler_Init(&Tasks[0]);
	/* Start execution of task scheduler */
	vfnScheduler_Start();

	/* Display menu */
    DisplayMenu();

	/*-- Loop through all the periodic tasks from Task Scheduler --*/
	for(;;)
	{
	    ucKey = DBG_GetChar();

	    switch (ucKey)
	    {
	        case 'h':
                DisplayMenu();
                break;

	        case 'd':
	        case 'D':
	            memset(pRxBuffer,'X' ,30);
                pRxBuffer[28] = '\n';
                pRxBuffer[29] = '\r';
                printf("\n\rRx Buffer before transfer is \n\r");
                puts((char*)pRxBuffer);
                _UartdConfigLB();
                UARTD_EnableRxChannels(&Uartd, &UartRx);
                UARTD_EnableTxChannels(&Uartd, &UartTx);
                UARTD_RcvData(&Uartd);
                UARTD_SendData(&Uartd);

                printf("\n\rRx Buffer after transfer is \n\r");

                while (Uartd.pRxChannel->sempaphore == 0);

                puts((char*)pRxBuffer);
                UARTD_DisableRxChannels(&Uartd, &UartRx);
                UARTD_DisableTxChannels(&Uartd, &UartTx);
                break;

	        default :
	            break;
	    }
		/* Perform all scheduled tasks */
		vfnTask_Scheduler();
	}

}
