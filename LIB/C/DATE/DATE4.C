/* File        : DATE4.C
   Module      : DATE
   System      : None
   Description : A method for constructing a date from year, month, and day information.
   Modified    : 10/25/91 DWP Created.
   Notes       :
*/

#include <stdio.h>

#include "date.h"

/* Function    : _DATE_Construct_CARDINAL_32_Date
   Description : Constructs a numeric date in the specified format using the specified year, month, and day.
   Inputs      : Format = The format of date desired.
                 Year   = The year of the resulting date.
                 Month  = The month of the resulting date.
                 Day    = The day of the resulting date.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A numeric date in the specified format.
   Modified    : 03/13/91 DWP Initial coding.
   Notes       :
*/

CARDINAL_32 _DATE_Construct_CARDINAL_32_Date(DATE_TYPES Format, CARDINAL_16 Year, CARDINAL_16 Month, CARDINAL_16 Day) {

   CARDINAL_32 converted_year, converted_month, converted_day, year_adjustment, result;

   /* Convert the year, month, and day parameters to unsigned 32 bit numbers.  This decreases the amount of conversion that has to
      take place later. */

   converted_year = Year;
   converted_month = Month;
   converted_day = Day;

   /* Adjust the year and initialize year_adjustment, depending on the specified format. */

   switch (Format) {

      case DATE_MMYY_TYPE :
      case DATE_MMDDYY_TYPE :
      case DATE_YYMM_TYPE :
      case DATE_YYMMDD_TYPE :
      case DATE_DDMMYY_TYPE :
      case DATE_DDMMMYY_TYPE :

         converted_year %= 100;
         year_adjustment = 100;
         break;

      default :

         year_adjustment = 10000;
   }

   /* Construct the date. */

   switch (Format) {

      case DATE_MMYY_TYPE :
      case DATE_MMYYYY_TYPE :

         result = converted_month * year_adjustment + converted_year;
         break;

      case DATE_MMDDYY_TYPE :
      case DATE_MMDDYYYY_TYPE :
      case DATE_MMMDDYYYY_TYPE :

         result = ((converted_month * 100) + converted_day) * year_adjustment + converted_year;
         break;

      case DATE_YYMM_TYPE :
      case DATE_YYYYMM_TYPE :

         result = converted_year * 100 + converted_month;
         break;

      case DATE_YYMMDD_TYPE :
      case DATE_YYYYMMDD_TYPE :

         result = ((converted_year * 100) + converted_month) * 100 + converted_day;
         break;

      case DATE_DDMMYY_TYPE :
      case DATE_DDMMYYYY_TYPE :
      case DATE_DDMMMYY_TYPE :
      case DATE_DDMMMYYYY_TYPE :

         result = ((converted_day * 100) + converted_month) * year_adjustment + converted_year;
         break;

      default :

         result = 0;

   }

   return (result);

}

/* Function    : _DATE_Construct_STRING_Date
   Description : Constructs a character string date in the specified format using the specified year, month, and day.
   Inputs      : Format    = The format in which the date is to be constructed.
                 Separator = The character which will be used to separate the fields of the date.
                 Year      = The year of the date to construct.
                 Month     = The month of the date to construct.
                 Day       = The day of the date to construct.
   Updates     : Nothing.
   Outputs     : Date      = The constructed date.
   Returns     : A character string date in the specified format.
   Modified    : 03/13/91 DWP Initial coding.
   Notes       : 1) The parameter Date must be large enough to hold a string date of the specified type, plus one byte for the
                    string terminator.
*/

char * _DATE_Construct_STRING_Date(DATE_TYPES Format, CARDINAL_16 Year, CARDINAL_16 Month, CARDINAL_16 Day, char Separator, char * Date) {

   char        year_text[6], month_text[3], day_text[3];
   CARDINAL_16 year_adjustment;

   /* Adjust the year and initialize year_adjustment, depending on the specified format. */

   switch (Format) {

      case DATE_MMYY_TYPE :
      case DATE_MMDDYY_TYPE :
      case DATE_YYMM_TYPE :
      case DATE_YYMMDD_TYPE :
      case DATE_DDMMYY_TYPE :
      case DATE_DDMMMYY_TYPE :

         Year %= 100;
         year_adjustment = 2;
         break;

      default :

         year_adjustment = 4;
   }

   /* Validate the month parameter. */

   if (Month > 12) {

      Month = 0;

   }

   /* Initialize year_text, month_text, and day_text. */

   year_text[0] = month_text[0] = day_text[0] = '\0';

   if (Month != 0) {

      sprintf(year_text, "%0*u", year_adjustment, Year);
      sprintf(month_text, "%02u", Month);

      if (Day != 0) {

         sprintf(day_text, "%02u", Day);

      }

   }

   /* Construct the formatted date string. */

   switch (Format) {

      case DATE_MMYY_TYPE :
      case DATE_MMYYYY_TYPE :

         sprintf(Date, "%2s%c%*s", month_text, Separator, year_adjustment, year_text);
         break;

      case DATE_MMDDYY_TYPE :
      case DATE_MMDDYYYY_TYPE :

         sprintf(Date, "%2s%c%2s%c%*s", month_text, Separator, day_text, Separator, year_adjustment, year_text);
         break;

      case DATE_YYMM_TYPE :
      case DATE_YYYYMM_TYPE :

         sprintf(Date, "%*s%c%2s", year_adjustment, year_text, Separator, month_text);
         break;

      case DATE_YYMMDD_TYPE :
      case DATE_YYYYMMDD_TYPE :

         sprintf(Date, "%*s%c%2s%c%2s", year_adjustment, year_text, Separator, month_text, Separator, day_text);
         break;

      case DATE_DDMMYY_TYPE :
      case DATE_DDMMYYYY_TYPE :

         sprintf(Date, "%2s%c%2s%c%*s", day_text, Separator, month_text, Separator, year_adjustment, year_text);
         break;

      case DATE_DDMMMYY_TYPE :
      case DATE_DDMMMYYYY_TYPE :

         sprintf(Date, "%2s%c%.3s%c%*s", day_text, Separator, DATE_Months_List[Month], Separator, year_adjustment, year_text);
         break;

      case DATE_MMMDDYYYY_TYPE :

         sprintf(Date, "%s %2s, %4s", DATE_Months_List[Month], day_text, year_text);
         break;

      default :

         Date[0] = '\0';

   }

   return (Date);

}

/* Function    : DATE_Construct_Date
   Description : Constructs a date of the specified format and type using the specified year, month, and day.
   Inputs      : Format    = The format of the date to construct.
                 Type      = The data type of the date to construct, either CARDINAL_32 or STRING, see DATA_TYPES.
                 Separator = The field separator for STRING type dates.  This parameter is not used for CARDINAL_32 type dates.
                 Year      = The year of the date to construct.
                 Month     = The month of the date to construct.
                 Day       = The day of the date to construct.
   Updates     : Nothing.  =
   Outputs     : Date      = The constructed date.
   Returns     : The constructed date.
   Modified    : 10/25/91 DWP Initial coding, replaces DATE_Construct_Numeric_Date() and DATE_Construct_Text_Date().
   Notes       :
*/

void * DATE_Construct_Date(DATE_TYPES Format, DATA_TYPES Type, char Separator, CARDINAL_16 Year, CARDINAL_16 Month, CARDINAL_16 Day, void * Date) {

   void * result;

   switch (Type) {

      case CARDINAL_32_TYPE :

        *((CARDINAL_32 *) Date) = _DATE_Construct_CARDINAL_32_Date(Format, Year, Month, Day);
        result = Date;

      case STRING_TYPE :

         result = _DATE_Construct_STRING_Date(Format, Separator, Year, Month, Day, Date);

      default :

         result = NULL;

   }

   return (result);

}
