/*
 * Platform_Types.h
 *
 *  Created on: Oct 5, 2017
 *      Author: Samuel
 */

#ifndef PLATFORM_TYPES_H
#define PLATFORM_TYPES_H

/***********************************
 * GLOBAL DATA TYPES
 ***********************************/

#ifndef __int8_t_defined
typedef signed char int8_t ;
typedef unsigned char uint8_t ;
#define __int8_t_defined 1
#endif

#ifndef __int16_t_defined
typedef signed short int16_t ;
typedef unsigned short uint16_t ;
#define __int16_t_defined 1
#endif

#ifndef __int32_t_defined
typedef signed int int32_t ;
typedef unsigned int uint32_t ;
#define __int32_t_defined 1
#endif

#ifndef __int64_t_defined
typedef signed long long int64_t ;
typedef unsigned long long uint64_t ;
#define __int64_t_defined 1
#endif


#endif /* PLATFORM_TYPES_H */
