#ifndef _CSLIST_CONF_H_
#define _CSLIST_CONF_H_

/*
 * Define types and functions depends on your system.
*/
#include <stdlib.h>
#define CSList_malloc malloc
#define CSList_free free
#include <string.h>
#define CSList_memcmp memcmp
#define CSList_null NULL
#define CSList_type_int int
#define CSList_type_char char
#define CSList_true 1
#define CSList_false 0

/* Exceptions. */
#define CSList_Exceptions_NotImplementedException "NotImplementedException"
#define CSList_Exceptions_ArgumentOutOfRangeException "ArgumentOutOfRangeException"
#define CSList_Exceptions_ArgumentNullException "ArgumentNullException"
#define CSList_Exceptions_InvalidOperationException "InvalidOperationException"

/*
 * Define exception handler.
*/
#include <stdio.h>
#define CSList_onException(type) static void CSList_onException_##type(CSList_type_char* Exception){\
    printf("%s.\n",Exception);\
    while(1){;};\
}\

#endif /* _CSLIST_CONF_H_ */