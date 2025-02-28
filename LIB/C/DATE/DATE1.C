/* File        : DATE1.C
   Module      : DATE
   System      : None
   Description : A method for formatting the system date.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#include <dos.h>
#include <stdio.h>

#include "date.h"

/* Function    : DATE_Retrieve_System_Date
   Description : Retrieves the current system date.  The date is returned in the specified format and data type.
   Inputs      : Format    = The format of the returned date.
                 Type      = The data type of the retrieved date, either CARDINAL_32 or STRING, see DATA_TYPES.
                 Separator = The field separator character for STRING dates.
   Updates     : Nothing.
   Outputs     : Date      = The current system date.
   Returns     : The current system date.
   Modified    : 10/25/91 DWP Created, replacement for DATE_Retrieve_Numeric_System_Date and DATE_Retrieve_Text_System_Date.
   Notes       :
*/

void * DATE_Retrieve_System_Date(DATE_TYPES Format, DATA_TYPES Type, char Separator, void * Date) {

   struct date current_date;
   void *      result;

   /* Get the current date and construct the specified numeric date. */

   getdate(&current_date);

   if (Type == CARDINAL_32_TYPE || Type == STRING_TYPE) {

      DATE_Construct_Date(Format, Type, Separator, current_date.da_year, current_date.da_mon, current_date.da_day, Date);

   }
   else {

      result = NULL;

   }

   return (result);

}
