/*******************************************************************************/
/**
\file       Mem_AllocTypes.h
\author     Manuel Espinoza
\version    0.1
\date       09/27/2017
*/

#ifndef __MemAlloc_Types
#define __MemAlloc_Types

#include <stdint.h>

/*-- Types Definitions -------------------------------------------------------*/
typedef uint32_t* Mem_ReturnType;
typedef uint32_t* Mem_Uint8PtrType;
typedef uint16_t Mem_SizeType;

typedef struct{
    Mem_Uint8PtrType memStart;
    Mem_Uint8PtrType memEnd;
    Mem_Uint8PtrType currAddr;
    Mem_SizeType freeBytes;
}MemHandlerType;

#endif /*__MemAlloc_Types */