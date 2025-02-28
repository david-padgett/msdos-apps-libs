/* File        : CAL.C
   Module      : CAL
   System      : CAL
   Description : This program generates calendars.
   Modified    : 07/01/91 DWP Created.
   Notes       : 1) Usage

                       CAL [[<Month>] <Year>]

                    Months

                       1 (or Jan) through 12 (or Dec)

                    Years

                       Any number between 0 and 9999
*/

#include <ctype.h>
#include <errno.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "date\date.h"

/* Procedure   : CAL_Generate_Calendar
   Description : Generates a calendar for the specified month and year.
   Inputs      : Date     = The date whose calendar is to be generated.
   Updates     : Nothing.
   Outputs     : Calendar = An initialized calendar.
   Returns     : Nothing.
   Modified    : 07/01/91 DWP Initial coding.
                 05/24/92 DWP Fixed February leap year bug.
   Notes       : 1) The calendar consists of an array six weeks with seven days per week.  There can be at most six different weeks
                    in one month, which is why the calendar is defined in this manner.
                 2) Unused weekdays contain a zero, while used weekdays contain the day of the month on which the weekday falls.
*/

void CAL_Generate_Calendar(DATE_YYYYMM Date, int Calendar[6][7]) {

   DATE_YYYYMMDD current_date;
   CARDINAL_16   starting_day;
   int           i;

   /* Determine what month and starting day of the specified date. */

   current_date = Date * 100 + 1;
   starting_day = DATE_Day_Of_Week(Date * 100L + 1L) - 1;

   /* Loop until the entire month has been constructed. */

   for (i = 0; DATE_IsValid(DATE_YYYYMMDD_TYPE, CARDINAL_32_TYPE, &current_date); i++, current_date++) {

      Calendar[(starting_day + i) / 7][(i + starting_day) % 7] = i + 1;

   }

}

/* Procedure   : CAL_Display_Calendar
   Description : Displays the specified calendar.
   Inputs      : Year     = The year the specified calendar was generated for.
                 Month    = The month to display.  If the value of this parameter is zero, then all of the months are displayed,
                            otherwise, only the specified month is displayed.
                 Calendar = The calendar to display.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/01/91 DWP Initial coding.
   Notes       :
*/

void CAL_Display_Calendar(int Year, int Month, int Calendar[12][6][7]) {

   char str[256];
   int  current_month, current_week, current_week_day, current_column, current_day, start_month, end_month;

   /* Display the appropriate first line.  The year is displayed when the entire calendar is printed, and the month and year are
      displayed when a single month is printed.  Also initialize the start and ending month values. */

   if (Month == 0) {

      printf("\n%38s%4d\n\n", "", Year);
      start_month = 1;
      end_month = 12;

   }
   else {

      sprintf(str, "%s %d", DATE_Months_List[Month], Year);
      printf("\n%*s%s\n\n", (30 - strlen(str)) / 2, "", str);
      start_month = end_month = Month;

   }

   /* Loop until all of the months have been displayed. */

   for (current_month = start_month; current_month <= end_month; current_month += 3) {

      /* Display the name of the month only if the entire calendar is being printed. */

      if (Month == 0) {

         /* Print the names of the three months in the current row. */

         for (current_column = 0; current_column < 3; current_column++) {

            printf("%13s%3.3s%9s", "", DATE_Months_List[current_month + current_column], "");

         }

         printf("\n\n");

      }

      /* Print the day of week header.  Print it only one time if only one month is being displayed. */

      for (current_column = (Month == 0) ? 0 : 2; current_column < 3; current_column++) {

         printf("%5sS  M  T  W  T  F  S ", "");

      }

      printf("\n\n");

      /* Loop until all of the weeks have been displayed. */

      for (current_week = 0; current_week < 6; current_week++) {

         /* Loop until an entire row in the current week has been displayed. */

         for (current_column = 0; current_column < 3; current_column++) {

            printf("%4s", "");

            /* Loop until all seven weekdays have been displayed for the current week in the current month. */

            for (current_week_day = 0; current_week_day < 7; current_week_day++) {

               /* Exit the loop if only one month is to be displayed and the month being displayed is not that month. */

               if (Month != 0 && current_month + current_column != Month) {

                  break;

               }

               /* Print either three spaces if the current week day is not occupied, otherwise print the day of the month that
                  occupies the current weekday. */

               current_day = Calendar[current_month + current_column - 1][current_week][current_week_day];

               if (current_day == 0) {

                  printf("%3s", "");

               }
               else {

                  printf("%2d ", current_day);

               }

            }

         }

         putchar('\n');

      }

   }

}

/* Function    : CAL_Main
   Description : The entry point to the CAL module.
   Inputs      : Month = The month to display.  The entire year will be displayed if Month is zero.
                 Year  = The year to display.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/01/91 DWP Initial coding.
   Notes       :
*/

int CAL_Main(int Month, int Year) {

   int         calendar[12][6][7];
   DATE_YYYYMM date;
   int         i, result = EZERO;

   /* Exit if an invalid month was specified. */

   if (Month > 12) {

      result = EINVDAT;

   }
   else {

      /* Construct the calendar. */

      setmem(calendar, sizeof(calendar), 0);

      for (i = 1; i <= 12; i++) {

         date = Year * 100L + i;
         CAL_Generate_Calendar(date, calendar[i - 1]);

      }

      CAL_Display_Calendar(Year, Month, calendar);

   }

   return (result);

}

/* Function    : main
   Description : The entry point to the CAL program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/01/91 DWP Initial coding.
   Notes       : 1) The command-line syntax is located in the file description area.
*/

int main(int argc, char * argv[]) {

   int i, month, year, result = EINVDAT;

   printf("\nCAL V1.0, " COMPILE_DATE ", Copyright (c) " COMPILE_YEAR " by CSFX\n");

   /* Initialize the control parameters. */

   switch (argc) {

      /* Only one parameter was specified, treat it as a year. */

      case 2 :

         month = 0;
         year = atoi(argv[1]);
         result = EZERO;
         break;

      /* Two parameters were given, treat the first one as a month, and treat the second one as a year.  Determine the
         format of the month, if it can't be converted directly to an integer, scan through the months list to see if
         the first 3 characters of the parameter match any of the months, if not, then exit. */

      case 3 :

         if (isdigit(argv[1][0])) {

            month = atoi(argv[1]);

         }
         else {

            /* Determine which month was specified, if a match can't be made, then exit. */

            for (month = 0, i = 1; i <= 12; i++) {

               if (strnicmp(DATE_Months_List[i], argv[1], 3) == 0) {

                  month = i;

               }

            }

         }

         year = atoi(argv[2]);

         if (month > 0) {

            result = EZERO;

         }

         break;

   }

   /* Process the request, if possible. */

   if (result == EZERO) {

      result = CAL_Main(month, year);

   }

   /* Display the help screen if one or more invalid parameters were invalid. */

   if (result != EZERO) {

      printf("\n   Purpose : Displays a calendar for a month or year.\n\n");
      printf("   Usage   : CAL [[<Month>] <Year>]\n\n");
      printf("   Months\n\n%6s1 (or %.3s) through 12 (or %.3s)\n\n   Years\n\n%6sAny number between 0 and 9999\n", "", DATE_Months_List[1], DATE_Months_List[12], "");

   }

   return (result);

}
