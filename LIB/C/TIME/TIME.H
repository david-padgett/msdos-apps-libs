/* File        : TIME.H
   Module      : TIME
   System      : None
   Description : The header file for the TIME module.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#ifndef _TIME_MODULE
#define _TIME_MODULE

#include <dos.h>

#include "Standard\standard.h"

/* Valid/supported formats. */

typedef enum TIME_TYPES {TIME_HHMMSSHH_12, TIME_HHMMSSHH_24, TIME_HHMMSS_12, TIME_HHMMSS_24, TIME_HHMM_12, TIME_HHMM_24} TIME_TYPES;

/* Procedures and Functions. */

unsigned long TIME_Elapsed(struct time * Time_1, struct time * Time_2, struct time * Elapsed_Time);
char *        TIME_Retrieve_System_Time(TIME_TYPES Format, char Separator_Character, char * Time);

#endif
