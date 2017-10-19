/*
 * Std_Types.h
 *
 *  Created on: Oct 5, 2017
 *  Brief: Provision of Standard Types
 */

#ifndef STD_TYPES_H
#define STD_TYPES_H

/**************************************
 * Includes
 **************************************/

#include "compiler.h"
#include "Platform_Types.h"

/**************************************
 * Global Constan Macros
 **************************************/

#define STD_HIGH    1u  /*Physical state 5V or 3.3V*/
#define STD_LOW     0u  /*Physical state 0V*/

#define STD_ACTIVE  1u  /*Logical state active*/
#define STD_IDLE    0u  /*Logical state idle*/

#define STD_ON      1u
#define STD_OFF     0u

/**************************************
 * Global Data Types
 **************************************/
//typedef uint8_t Std_ReturnType;


typedef enum{
    E_OK,
    E_NOK
}Std_ReturnType;



typedef struct
{
    uint16_t vendorID;
    uint16_t modeuleID;
    uint8_t  sw_major_version;
    uint8_t  sw_minor_version;
    uint8_t  sw_patch_version;
}Std_VersionInfoType;

#endif /* STD_TYPES_H */
