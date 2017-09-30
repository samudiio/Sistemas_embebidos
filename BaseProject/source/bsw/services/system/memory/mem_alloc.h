/*
 * Mem_Alloc.h
 *
 *  Created on: Sep 27, 2017
 *  Brief:      Interfaces provided to the user component modules
 */

#ifndef MEM_ALLOC_H_   /*prevent duplicated includes*/
#define MEM_ALLOC_H_

/*-- Includes ----------------------------------------------------------------*/
#include "Mem_AllocTypes.h"

extern uint32_t MEM_HEAP_START;
extern uint32_t MEM_HEAP_END;

/*
* \brief    Initialize the Heap content to zero
* \param    void
* \return   void
*/
void Mem_Init(void);

/*
* \brief    Allocates and returns the initial address of the memory currently being allocated
* \param    size        Size in Bytes to be allocated
* \return   init_add     Initial address of the new allocated memory space
*/
Mem_ReturnType Mem_Alloc(Mem_SizeType Size);

#endif /* MEM_ALLOC_H_ */
