/* File        : STRING.H
   Module      : STRING
   System      : None
   Description : The header file for the STRING module.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#ifndef _STRING_MODULE
#define _STRING_MODULE

#include <stdio.h>

typedef enum _STRING_TRIM_TYPES {STRING_TRIM_ALNUM = -1,
                                STRING_TRIM_ALPHA = -2,
                                STRING_TRIM_DIGIT = -3,
                                STRING_TRIM_CNTRL = -4,
                                STRING_TRIM_ASCII = -5,
                                STRING_TRIM_PRINT = -6,
                                STRING_TRIM_GRAPH = -7,
                                STRING_TRIM_LOWER = -8,
                                STRING_TRIM_UPPER = -9,
                                STRING_TRIM_PUNCT = -10,
                                STRING_TRIM_SPACE = -11,
                                STRING_TRIM_XDIGIT = -12} STRING_TRIM_TYPES;

typedef enum _STRING_DELIMIT_DIRECTION_TYPES {STRING_DELIMIT_LEFT,
                                              STRING_DELIMIT_RIGHT} STRING_DELIMIT_DIRECTION_TYPES;

/* Procedures and Functions. */

char * STRING_LTrim(char * String);
char * STRING_RTrim(char * String);
char * STRING_ATrim(char * String);
char * STRING_STrim(char Ch, char * String);
char * STRING_Trim(int Ch, char * String);
char * STRING_Center(int Size, char * String);
char * STRING_Delimit(size_t Interval, STRING_DELIMIT_DIRECTION_TYPES Direction, char * Delimiter, char * String);
long   STRING_Compare(char * String1, char * String2, int Length);
size_t STRING_CharPos(const char * Source, char Ch);
int    STRING_StrPos(char * Search_String, char * Sub_String);
char * STRING_Delete_Character(size_t Position, char * String);
char * STRING_Insert_Character(size_t Position, char Character, char * String);

#endif