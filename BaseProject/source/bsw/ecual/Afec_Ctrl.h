#ifndef _AFEC_CTRL_
#define _AFEC_CTRL_


//#include "afe_dma.h"
#include "board.h"
#include "afec.h"
#include "afe_dma.h"


#define AFE_CLK 2200000
#define TEST_CHANNEL 5
#define CHANNEL_OFFSET 0x200

void AFECDMA_Init(uint16_t Size,uint32_t SampPer);

void AFEC_Init(void);

void AFEC_SoftwareConversion(void);

#endif