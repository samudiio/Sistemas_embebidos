/*******************************************************************************/
/**
\file       Mem_Alloc.c
\author     Juan Campeche
\version    0.1
\date       20/09/2017
*/

/*-- Includes ----------------------------------------------------------------*/
#include "Mem_Alloc.h"

volatile MemHandlerType my_MemHandler;

void Mem_Init(void){

  my_MemHandler.memStart = &MEM_HEAP_START;
  my_MemHandler.currAddr = &MEM_HEAP_START;// este debe de ser 8 bits
  my_MemHandler.memEnd =   &MEM_HEAP_END;
 
  uint32_t *pStart;
  
  for (pStart = &MEM_HEAP_START; pStart < &MEM_HEAP_END;) {
	  *pStart++ = 0x0;
	}
}


void *Mem_Alloc(Mem_SizeType ReqSize){
  
  uint32_t my_memEnd,my_currAddr;     
  my_currAddr = (uint32_t)my_MemHandler.currAddr;
  my_memEnd   = (uint32_t)my_MemHandler.memEnd;      
  my_MemHandler.freebytes = (my_memEnd - my_currAddr);
    printf( "\n\n\r");
  printf( "Free Bytes= %x.\n\r", my_MemHandler.freebytes );
  printf( "Req Size= %x.\n\r", ReqSize );
  
  if( ReqSize < my_MemHandler.freebytes ){    
    my_MemHandler.oldAddr = my_MemHandler.currAddr;
    my_MemHandler.currAddr+=ReqSize;  
    printf( "Returned Address = %p.\n\r", (Mem_Uint8PtrType)my_MemHandler.oldAddr );
    return my_MemHandler.oldAddr;  
  }
  else{
    return NULL;
  }
}





