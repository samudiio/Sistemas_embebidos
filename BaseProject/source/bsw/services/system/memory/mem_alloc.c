/*
 * mem_alloc.c
 *
 *  Created on: Sep 27, 2017
 *  Brief:      Main functionality of the memory allocation handler
 */

/*-- Includes ----------------------------------------------------------------*/
#include "mem_alloc.h"
#include <string.h>

MemHandlerType New_Heap;

/*
* \brief    Initialize the Heap content to zero
* \param    void
* \return   void
*/
void Mem_init(void)
{
    uint32_t idx;
    uint8_t *heap_address = (uint8_t *)MEM_HEAP_START;

    for(idx = 0; idx <= (uint32_t)HEAP_SIZE; idx++)
    {
        memset(heap_address, 0x00, 1);
        heap_address++;
    }
    New_Heap.memStart = (uint8_t *)MEM_HEAP_START;
    New_Heap.memEnd = (uint8_t *)MEM_HEAP_END;
    New_Heap.currAddr = (uint8_t *)MEM_HEAP_START;
    New_Heap.freeBytes = HEAP_SIZE;
}

/*
* \brief    Allocates and returns the initial address of the memory currently being allocated
* \param    size        Size in Bytes to be allocated
* \return   init_add     Initial address of the new allocated memory space
*/
/*ie 1024 = 1K*/
Mem_ReturnType Mem_Alloc(Mem_SizeType size)
{
    Mem_ReturnType ret_val = NULL;

    if(New_Heap.freeBytes > size)
    {
        ret_val = New_Heap.currAddr;
        New_Heap.currAddr += size;

        //assure current add is aligned with 32bit addres
        if(((uint32_t)New_Heap.currAddr % (uint32_t)4 )!= 0)
        {
            do
            {
                New_Heap.currAddr += 1;
            }while(((uint32_t)New_Heap.currAddr % (uint32_t)4 )!= 0);
        }
        else
        {
            //do nothing, the address is 4-byte aligned
        }

        New_Heap.freeBytes = New_Heap.memEnd - New_Heap.currAddr;
    }

    return ret_val;
}
