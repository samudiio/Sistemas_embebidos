/*
 * mem_alloc.h
 *
 *  Created on: Sep 27, 2017
 *  Brief:      Interfaces provided to the user component modules
 */

#ifndef MEM_ALLOC_H_   /*prevent duplicated includes*/
#define MEM_ALLOC_H_

/*-- Includes ----------------------------------------------------------------*/
#include "mem_alloctypes.h"


/*
* \brief    Initialize the Heap content to zero
* \param    void
* \return   void
*/
void Mem_init(void);

/*
* \brief    Allocates and returns the initial address of the memory currently being allocated
* \param    size        Size in Bytes to be allocated
* \return   init_add     Initial address of the new allocated memory space
*/
Mem_ReturnType Mem_Alloc(Mem_SizeType size);

#endif /* MEM_ALLOC_H_ */
