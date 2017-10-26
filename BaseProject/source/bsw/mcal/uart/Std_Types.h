/*
 * Std_Types.h
 *
 *  Created on: Oct 2017
 *  Brief:      Types provided to the user component modules
 */
#ifndef Std_Types_h   /*prevent duplicated includes*/
#define Std_Types_h

#include <stdint.h>

typedef enum{
    E_OK,
    E_NOK
}Std_ReturnType;

#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#endif