/* File        : DATE7.C
   Module      : DATE
   System      : None
   Description : A method for determining the difference between two dates.
   Modified    : 05/31/91 DWP Created.
   Notes       :
*/

#include "date.h"

/* Function    : DATE_Difference_In_Days
   Description : Determines how many days separate the specified dates.
   Inputs      : Date_1_Format      = The format of the first date.
                 Date_1_Type        = The data type of the first date.
                 Date_1             = The first of the two dates to compare.
                 Date_2_Format      = The format of the second date.
                 Date_2_Type        = The data type of the second date.
                 Date_2             = The second of the two dates to compare.
   Updates     : Nothing.
   Outputs     : Difference_In_Days = The difference in days between Date_1 and Date_2.
   Returns     : A value of TRUE if no errors occurred, FALSE otherwise.
   Modified    : 05/31/91 DWP Initial coding.
   Notes       : 1) The order of the two dates is unimportant.  The absolute value of the difference is always returned.
*/

BOOLEAN DATE_Difference_In_Days(DATE_TYPES Date_1_Format, DATA_TYPES Date_1_Type, void * Date_1, DATE_TYPES Date_2_Format, DATA_TYPES Date_2_Type, void * Date_2, CARDINAL_32 * Difference_In_Days) {

   DATE_YYYYMMDD converted_date_1, converted_date_2;
   CARDINAL_32   difference_in_centuries, end_of_century, exchange_value;
   BOOLEAN       result;

   if (!DATE_Convert_To_YYYYMMDD(Date_1_Format, Date_1_Type, Date_1, &converted_date_1) || !DATE_Convert_To_YYYYMMDD(Date_2_Format, Date_2_Type, Date_2, &converted_date_2)) {

      result = FALSE;

   }
   else {

      /* Exchange the two dates if the second date is less than the first date. */

      if (converted_date_2 < converted_date_1) {

	 exchange_value = converted_date_1;
	 converted_date_1 = converted_date_2;
	 converted_date_2 = exchange_value;

      }

      difference_in_centuries = converted_date_2 / 1000000L - converted_date_1 / 1000000L;

      /* If the two dates occur in the same century, compute their difference. */

      if (difference_in_centuries == 0) {

	 *(Difference_In_Days) = DATE_Convert_YYYYMMDD_To_Days(converted_date_2) - DATE_Convert_YYYYMMDD_To_Days(converted_date_1);

      }
      else {

	 end_of_century = (converted_date_1 / 1000000L) * 1000000L + 991231L;
	 *(Difference_In_Days) = DATE_Convert_YYYYMMDD_To_Days(end_of_century) - DATE_Convert_YYYYMMDD_To_Days(converted_date_1) + DATE_Convert_YYYYMMDD_To_Days(converted_date_2);

	 while (difference_in_centuries-- > 1) {

	    end_of_century += 1000000L;
	    *(Difference_In_Days) += DATE_Convert_YYYYMMDD_To_Days(end_of_century);

	 }

      }

      result = TRUE;

   }

   return (result);

}
