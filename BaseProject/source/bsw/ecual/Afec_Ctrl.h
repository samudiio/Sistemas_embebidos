#ifndef _AFEC_CTRL_
#define _AFEC_CTRL_


#define AFE_CLK 2200000
#define TEST_CHANNEL 5
#define CHANNEL_OFFSET 0x200


void AFEC_Init(void);

void AFEC_SoftwareConversion(void);

#endif