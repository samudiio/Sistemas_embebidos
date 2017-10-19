/*******************************************************************************/
/**
\file       Mem_Alloc.c
\author     Juan Campeche
\version    0.1
\date       20/09/2017
*/

/*-- Includes ----------------------------------------------------------------*/
#include "Mem_Alloc.h"

MemHandlerType my_MemHandler;


void Mem_Init(void){

  my_MemHandler.memStart = &MEM_HEAP_START;
  my_MemHandler.currAddr = &MEM_HEAP_START;
  my_MemHandler.memEnd =   &MEM_HEAP_END;  
  my_MemHandler.freeBytes = (my_MemHandler.memEnd - my_MemHandler.currAddr)-1;    
 
  uint8_t *pStart;
  
  for (pStart = &MEM_HEAP_START; pStart < &MEM_HEAP_END;) {
	  *pStart++ = 0x0;
	}
}


Mem_ReturnType Mem_Alloc(Mem_SizeType Size){
  
  Mem_ReturnType ret_val = NULL;
  
  printf( "\n\n\r");
  printf( "Free Bytes= %x.\n\r", my_MemHandler.freeBytes );
  printf( "Req Size= %x.\n\r", Size );      

    if(my_MemHandler.freeBytes > Size)
    {
        ret_val = my_MemHandler.currAddr;
        my_MemHandler.currAddr += Size;

        //assure current add is aligned with 32bit addres
        if(((uint32_t)my_MemHandler.currAddr % (uint32_t)4 )!= 0)
        {
            do
            {
                my_MemHandler.currAddr += 1;
            }while(((uint32_t)my_MemHandler.currAddr % (uint32_t)4 )!= 0);
        }
        else
        {
            //do nothing, the address is 4-byte aligned
        }
        
        my_MemHandler.freeBytes = my_MemHandler.memEnd - my_MemHandler.currAddr;
    }

    printf( "Returned Address = %p.\n\r", (Mem_Uint8PtrType)ret_val );
    return ret_val;
}





