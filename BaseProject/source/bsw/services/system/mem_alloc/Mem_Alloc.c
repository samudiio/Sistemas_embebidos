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

/* -- Global Variables -----------------------*/
MemHandlerType MemHandler;
// #define Heap_Size  64000

//static unsigned char HEAP_Buffer[HEAP_SIZE];

/** Mem_Alloc function definitions */
void Mem_Init(void)
{
     MemHandler.freeBytes = (uintptr_t)&HEAP_SIZE;
     MemHandler.memStart = (uint8_t*) &MEM_HEAP_START;
     MemHandler.memEnd = (uint8_t *) &MEM_HEAP_END;
     MemHandler.currAddr = (uint8_t *) &MEM_HEAP_START;
     for(MemHandler.currAddr = MemHandler.memStart; MemHandler.currAddr <= MemHandler.memEnd; MemHandler.currAddr++){
         *MemHandler.currAddr = 0;
     }
     MemHandler.currAddr = (uint8_t *) &MEM_HEAP_START;
}

Mem_ReturnType Mem_Alloc(Mem_SizeType Size)
{
    //Necesita revisión
    Mem_ReturnType NextAddr;
    // if(Size < MemHandler.freeBytes){
    //     NextAddr = &HEAP_Buffer[MemHandler.freeBytes];
    //     MemHandler.freeBytes -= Size;
    //     MemHandler.currAddr = (Mem_Uint8PtrType)NextAddr;
    // }
    return NextAddr;
}