/*******************************************************************************/
/**
\file       Mem_Alloc.c
\author     Manuel Espinoza
\version    0.1
\date       09/27/2017
*/

/** Variable types and common definitions */

/** Mem_Alloc function prototypes definitions */

#include <Mem_Alloc.h>
#include <stdio.h>

/* -- Global Variables -----------------------*/
#define HeapSize  64000

MemHandlerType MemHandler;

/** Mem_Alloc function definitions */
void Mem_Init(void)
{
     MemHandler.freeBytes = (uintptr_t)&HEAP_SIZE;
     MemHandler.memStart = (uint32_t*) &MEM_HEAP_START;
     MemHandler.memEnd = (uint32_t *) &MEM_HEAP_END;
     MemHandler.currAddr = (uint32_t *) &MEM_HEAP_START;
     for(MemHandler.currAddr = MemHandler.memStart; MemHandler.currAddr <= MemHandler.memEnd; MemHandler.currAddr++){
         *MemHandler.currAddr = 0;
     }
     MemHandler.currAddr = (uint32_t *) &MEM_HEAP_START;
}

Mem_ReturnType Mem_Alloc(Mem_SizeType Size)
{
    Mem_ReturnType memAdrss;
    
    printf("MemSize Req = %i \n\r", Size);
    if(Size < MemHandler.freeBytes){
       
        MemHandler.freeBytes -= Size;
        memAdrss = MemHandler.currAddr;
        MemHandler.currAddr += Size;
        // uint16_t index;
        // for(index= 0;index < Size; index++){
        //     MemHandler.currAddr++;
        // }
        //Check Aligment 4byte(32bit)
        if((uintptr_t)MemHandler.currAddr & 0x03 != 0){
            // Aligning Address to 4bytes
            MemHandler.currAddr = (uint32_t *)(((uintptr_t)MemHandler.currAddr + 4) & (~0x03));
        }
    }
    printf("RetMemAdrss = %x \n\r", memAdrss);
    printf("currAddr = %x \n\r", MemHandler.currAddr);
    printf("freeBytes = %u \n\r", MemHandler.freeBytes);
    return memAdrss;
}