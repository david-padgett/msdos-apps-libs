/* File        : DATE8.C
   Module      : DATE
   System      : None
   Description : A method for converting dates to a standard format.
   Modified    : 05/31/91 DWP Created.
   Notes       :
*/

#include "date.h"

/* Function    : DATE_Convert_To_YYYYMMDD
   Description : Converts the specified date to the standard CARDINAL_32 format YYYYMMDD.
   Inputs      : Format          = The current format of the date to convert.
                 Type            = The current data type of the date to convert.
                 Date            = The date to convert.
   Updates     : Nothing.
   Outputs     : Converted_Value = The converted date.
   Returns     : A value of TRUE if the date was successfully converted, FALSE otherwise.
   Modified    : 05/31/91 DWP Initial coding.
   Notes       :
*/

BOOLEAN DATE_Convert_To_YYYYMMDD(DATE_TYPES Format, DATA_TYPES Type, void * Date, DATE_YYYYMMDD * Converted_Value) {

   CARDINAL_16 year, month, day;
   BOOLEAN     result = FALSE;

   /* If the date is invalid, abort the conversion. */

   if (DATE_IsValid(Format, Type, Date)) {

      /* If the date is already in the proper format, don't bother converting it. */

      if (Format == DATE_YYYYMMDD_TYPE && Type == CARDINAL_32_TYPE) {

	 *(Converted_Value) = *((DATE_YYYYMMDD *) Date);
	 result = TRUE;

      }
      else {

	 /* Decompose the date into its basic components, and then convert it to its CARDINAL_32 YYYYMMDD form.  Exit if an error
	    occurs. */

	 if (DATE_Decompose_Date(Format, Type, Date, &year, &month, &day)) {

	    DATE_Construct_Date(DATE_YYYYMMDD_TYPE, CARDINAL_32_TYPE, '\0', year, month, day, Converted_Value);
	    result = TRUE;

	 }

      }

   }

   return (result);

}
