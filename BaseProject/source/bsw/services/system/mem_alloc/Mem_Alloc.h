/*******************************************************************************/
/**
\file       Mem_Alloc.h
\author     Manuel Espinoza
\version    0.1
\date       09/27/2017
*/
#ifndef __Mem_Alloc_H
#define __Mem_Alloc_H

/*-- Includes ----------------------------------------------------------------*/
#include <Mem_AllocTypes.h>

extern uint32_t MEM_HEAP_START;
extern uint32_t MEM_HEAP_END;
extern uint32_t HEAP_SIZE;

/*-- Function Prototypes -----------------------------------------------------*/

/* Mem_Init Initialize the Heap content to zero */
void Mem_Init(void);

/* Allocates and returns the initial address of the memory currently being allocated */
/* Definition -> Mem_ReturnType Mem_Alloc ( Mem_SizeType Size ) */
/* Param in -> Mem_SizeType Size : Size in Bytes to be allocated */
/* Return Value -> Mem_ReturnType Initial address of the new allocated memory space */
Mem_ReturnType Mem_Alloc(Mem_SizeType Size);

#endif /*__Mem_Alloc_H */