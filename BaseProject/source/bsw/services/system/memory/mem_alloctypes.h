/*
 * Mem_AllocTypes.h
 *
 *  Created on: Sep 29, 2017
 *  Brief:      Internal data types definitions use by the memory allocation handler Module
 */

#ifndef MEM_ALLOCTYPES_H_
#define MEM_ALLOCTYPES_H_

/*-- Includes ----------------------------------------------------------------*/
#include <stdint.h>

/*-- Types Definitions -------------------------------------------------------*/

typedef uint8_t *Mem_ReturnType;
typedef uint8_t *Mem_Uint8PtrType;
typedef uint16_t Mem_SizeType;

typedef struct
{
    Mem_Uint8PtrType memStart;
    Mem_Uint8PtrType memEnd;
    Mem_Uint8PtrType currAddr;
    uint16_t freeBytes;
}MemHandlerType;


#endif /* MEM_ALLOCTYPES_H_ */
