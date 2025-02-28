/* File        : XDATE.C
   Module      : XDATE
   System      : XDATE
   Description : An enhanced date program.
   Modified    : 07/02/91 DWP Created.
   Notes       :
*/

#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#include "date\date.h"
#include "msdos\msdos.h"
#include "string\string.h"

/* Types. */

typedef enum _XDATE_OPTION_TYPES {YEAR, MONTH, DAY, DOW, DATE} XDATE_OPTION_TYPES;

/* Global variables. */

char XDATE_switch_list[] = "YMDWT";
char *XDATE_variable_list[] = {"YEAR", "MONTH", "DAY", "DOW", "DATE"};
char *XDATE_description_list[] = {"year", "month", "day", "day of week", "date"};
char *XDATE_format_list[] = {"MMYY", "MMDDYY", "MMYYYY", "MMDDYYYY", "YYMM", "YYMMDD", "YYYYMM", "YYYYMMDD", "DDMMYY", "DDMMYYYY", "DDMMMYY", "DDMMMYYYY", "MMMDDYYYY"};

/* Procedures and functions. */

/* Function    : XDATE_main
   Description : Assigns or updates the value for the specified environment variable using the specified format.
   Expects     : option = The request to process, see XDATE_OPTION_TYPES.
                 format = The format to use when creating the value for the environment variable specified by option.  If option
                          is equal to MONTH or DOW, and format is equal to STRING_TYPE, then the MONTH or DOW variable will be
                          saved as an English word, otherwise, the numeric value will be used.  If option is equal to DATE, then
                          format specified the way in which the fields in the date are to be arranged.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/02/91 DWP Initial coding.
   Notes       :
*/
int XDATE_main(XDATE_OPTION_TYPES option, DATE_TYPES format) {
   DOS_PSP       *root_PSP;
   DATE_YYYYMMDD date;
   CARDINAL_16   year, month, day, dow;
   char          str[256];
   int           result = EZERO;

   /* Get the current system date. */

   DATE_Retrieve_System_Date(DATE_YYYYMMDD_TYPE, CARDINAL_32_TYPE, '\0', &date);

   /* Decompose the date, if an error occurs then exit. */

   if (!DATE_Decompose_Date(DATE_YYYYMMDD_TYPE, CARDINAL_32_TYPE, &date, &year, &month, &day)) {
      result = EINVDAT;
   }
   else {

      /* Locate the root PSP.  If an error occurs then exit. */

      if ((root_PSP = DOS_Get_Root_PSP()) == NULL) {
         result = EINVDAT;
      }
      else {

         switch (option) {

            case YEAR  : sprintf(str, "%04u", year);
                         result = DOS_Set_Environment_Variable(root_PSP, XDATE_variable_list[0], str);
                         break;

            case MONTH : if (format == STRING_TYPE) {
			    strcpy(str, DATE_Months_List[month]);
			 }
			 else {
			    sprintf(str, "%02u", month);
			 }

			 result = DOS_Set_Environment_Variable(root_PSP, XDATE_variable_list[1], str);
			 break;

	    case DAY   : sprintf(str, "%02u", day);
			 result = DOS_Set_Environment_Variable(root_PSP, XDATE_variable_list[2], str);
			 break;

	    case DOW   : dow = DATE_Day_Of_Week(date);

			 if (format == STRING_TYPE) {
			    strcpy(str, DATE_Days_List[dow]);
			 }
			 else {
			    sprintf(str, "%1u", dow);
			 }

			 result = DOS_Set_Environment_Variable(root_PSP, XDATE_variable_list[3], str);
			 break;

	    case DATE  : result = DOS_Set_Environment_Variable(root_PSP, XDATE_variable_list[4], DATE_Retrieve_System_Date(format, STRING_TYPE, '-', str));
			 break;
	 }
      }
   }

   return (result);
}

/* Function    : main
   Description : The main entry point to the XDATE program.
   Expects     : The command-line.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/02/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   XDATE_OPTION_TYPES option;
   char               *alternate_format;
   int                i, j, format, result;

   printf("\nXDATE V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   if (argc == 1) {
      result = EINVAL;
   }
   else {

      /* Loop until all of the command-line parameters have been processed. */

      for (i = 1, result = EZERO; i < argc && result == EZERO; i++) {

         /* Determine if the next parameter is a proper switch, if it isn't a valid switch, then exit. */

         if (argv[i][0] != '-' && argv[i][0] != '/') {
            result = EINVAL;
         }
         else {

            /* Determine which switch was specified, if it is an invalid switch, then exit. */

	    option = STRING_CharPos(XDATE_switch_list, toupper(argv[i][1]));

            if (option-- == 0) {
               result = EINVAL;
            }
            else {

               /* Determine what format to use. */

               if (option != 4) {

                  switch (toupper(argv[i][2])) {

                     case 'C'  : format = STRING_TYPE;
                                 break;

                     case 'N'  :
                     case '\0' : format = CARDINAL_16_TYPE;
                                 break;

                     default   : result = EINVAL;
                  }
               }
               else {

                  /* If the 'T' switch was specified, locate the parameter that contains the new format. */

                  alternate_format = (argv[i][2] == '\0') ? argv[++i] : (toupper(argv[i][2]) != 'C') ? &(argv[i][2]) : &(argv[i][3]);
                  result = EINVAL;

                  /* Determine which format was specified. */

                  for (j = 0; j < 13; j++) {
                     if (stricmp(XDATE_format_list[j], alternate_format) == 0) {
                        format = j;
                        result = EZERO;
                        break;
                     }
                  }
               }
            }
         }

         /* Continue only if no errors occurred during parameter processing. */

         if (result == EZERO) {
            result = XDATE_main(option, format);
         }
      }
   }

   /* Display the help screen if one or more invalid command-line parameters were given. */

   if (result != EZERO) {

      printf("\n   Purpose :  Queries the system date.\n\n");
      printf("   Usage   : XDATE {[- | /][Switch]{[Format]}}\n\n   Switches\n");

      for (i = 0; i < 5; i++) {
         printf("\n%6s%c = Set the environment variable %s to the current %s", "", XDATE_switch_list[i], XDATE_variable_list[i], XDATE_description_list[i]);
      }

      printf("\n\n   Formats used with switches M and W, these are optional \n\n%6sC = Character format\n%6sN = Numeric format (default)\n\n   Formats used with switch T, one must always be present\n", "", "");

      for (i = 0; i < 13; i++) {

         if (i % 7 == 0) {
            printf("\n%6s", "");
         }

         printf("%-10s", XDATE_format_list[i]);
      }

      putchar('\n');
   }

   return (result);
}
