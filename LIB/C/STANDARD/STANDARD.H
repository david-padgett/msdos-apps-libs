/* File        : STANDARD.H
   Module      : None
   System      : None
   Description : A general-purpose, standard header file.
   Modified    : 08/01/90 DWP Created.
                 12/14/90 DWP Added several new types.
   Notes       :
*/

#ifndef _STANDARD_H
#define _STANDARD_H

/* Standard data type symbols.  The numbers following the underscore in several of these symbols indicates the bit length of the
   actual data type associated with that symbol. */

typedef enum _DATA_TYPES {BYTE_TYPE,
                          WORD_8_TYPE,
                          WORD_16_TYPE,
                          WORD_32_TYPE,
                          BOOLEAN_TYPE,
                          CHARACTER_TYPE,
                          STRING_TYPE,
                          INTEGER_8_TYPE,
                          INTEGER_16_TYPE,
                          INTEGER_32_TYPE,
                          CARDINAL_8_TYPE,
                          CARDINAL_16_TYPE,
                          CARDINAL_32_TYPE,
                          REAL_32_TYPE,
                          REAL_64_TYPE,
                          REAL_80_TYPE} DATA_TYPES;

/* The number following the underscore in several of these types indicates the bit length of that type. */

typedef unsigned char BYTE;
typedef unsigned char WORD_8;
typedef unsigned int  WORD_16;
typedef unsigned long WORD_32;
typedef enum _BOOLEAN {FALSE, TRUE} BOOLEAN;
typedef char          CHARACTER;
typedef char *        STRING;
typedef char          INTEGER_8;
typedef int           INTEGER_16;
typedef long          INTEGER_32;
typedef unsigned char CARDINAL_8;
typedef unsigned int  CARDINAL_16;
typedef unsigned long CARDINAL_32;
typedef float         REAL_32;
typedef double        REAL_64;
typedef long double   REAL_80;

#endif
