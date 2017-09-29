/*
 * mem_alloctypes.h
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

/*-- Defines -----------------------------------------------------------------*/

#define MIN_SIZE    1
#define MAX_SIZE    64
#define MEM_HEAP_START      0x20450000
#define MEM_HEAP_END        0x20460000
#define HEAP_SIZE           0xFFFF


#endif /* MEM_ALLOCTYPES_H_ */
