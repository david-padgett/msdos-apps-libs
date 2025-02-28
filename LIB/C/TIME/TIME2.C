/* File        : TIME2.C
   Module      : TIME
   System      : None
   Description : A method for retrieving the current system time.
   Modified    : 04/16/91 DWP Created.
   Notes       :
*/

#include <stdio.h>
#include <string.h>

#include "time.h"

/* Function    : TIME_Retrieve_System_Time
   Description : Retrieves the current system time and converts it to a text string in the specified format.
   Inputs      : Format              = The format to use when formatting the system time.
                 Separator_Character = The character that is to be placed in between the different fields in the formatted text
                                       string.
   Updates     : Nothing.
   Outputs     : Time                = The system time, formatted as a text string.  This parameter is undefined upon entry.
   Returns     : The current system time.
   Modified    : 04/16/91 DWP Initial coding.
   Notes       :
*/
char * TIME_Retrieve_System_Time(TIME_TYPES Format, char Separator_Character, char * Time) {

   struct time current_time;
   char        printf_format[256];
   BOOLEAN     am_flag;

   /* Retrieve the current system time. */

   gettime(&current_time);

   /* Initialize the military format indicator. */

   switch (Format) {

      case TIME_HHMMSSHH_12 :
      case TIME_HHMMSS_12 :
      case TIME_HHMM_12 :

         am_flag = TRUE;

         if (current_time.ti_hour > 12) {

            current_time.ti_hour -= 12;

               am_flag = FALSE;

            }
            else {

               if (current_time.ti_hour == 0) {

                  current_time.ti_hour = 12;

               }
            }

            break;

      default :

         am_flag = (current_time.ti_hour < 12);

   }

   if (Format <= TIME_HHMM_24) {

      /* Place the hour and minute information into the format specifier for printf(). */

      strcpy(printf_format, "%02u%c%02u");

      if (Format < TIME_HHMM_12) {

         /* Add the seconds information to the format specifier. */

         strcat(printf_format, "%c%02u");

         if (Format < TIME_HHMMSS_12) {

	    /* Add hundredth seconds information to the format specifier. */

            strcat(printf_format, "%c%02u");

         }

      }

      /* Build the formatted text string. */

      sprintf(Time, printf_format, current_time.ti_hour, Separator_Character, current_time.ti_min, Separator_Character, current_time.ti_sec, Separator_Character, current_time.ti_hund);

   }

   return (Time);

}