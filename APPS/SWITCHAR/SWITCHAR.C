/* File        : SWITCHAR.C
   Module      : SWITCHAR
   System      : SWITCHAR
   Description : This program displays or modifies the DOS switch character.
   Modified    : 05/02/91 DWP Created.
   Notes       :
*/

#include <dos.h>
#include <stdio.h>

#include "msdos\msdos.h"

/* Global data. */

char DOS_switch_character_text[] = "DOS Switch Character";

/* Procedures and Functions. */

/* Procedure   : SWITCHAR_display_error_message
   Description : Displays the specified error message.
   Expects     : error_message = The error message to display.
   Returns     : Nothing.
   Modified    : 05/02/91 DWP Initial coding.
   Notes       :
*/
void SWITCHAR_display_error_message(char *error_message) {

   printf("\nSWITCHAR ERROR:  The %s%s.\n", DOS_switch_character_text, error_message);
}

/* Function    : main
   Description : This program allows the DOS switch character to be displayed or altered.
   Expects     : argv[1] = The new DOS switch character.  This is an optional parameter.  If no switch character is given, the
			   current DOS switch character is displayed.
   Returns     : Always returns a value of zero.
   Modified    : 05/02/91 DWP Initial coding.
   Notes       : 1) Available only under DOS 2.xx and greater.
*/
int main(int argc, char *argv[]) {
   char switchar;

   printf("\nSWITCHAR V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   /* Make sure that the current DOS version is at least 2.xx.  If it isn't, display an error message and exit. */

   if (_osmajor < 2) {
      SWITCHAR_display_error_message(" Program requires DOS 2.0 or greater");
   }
   else {

      /* If no command-line arguments were given, or if an incorrect argument was given, display the current DOS switch
         character. */

      if (argc == 1 || argv[1][1] != '\0') {

         /* If the DOS switch character can't be retrieved, display an error message and exit. */

         if ((switchar = DOS_Get_SwitchChar()) == '\0') {
            SWITCHAR_display_error_message(" can't be modified");
         }
         else {

            /* Display the help screen and the current DOS switch character. */

            printf("\n   Purpose : Modifies the %s.\n\n", DOS_switch_character_text);
            printf("   Usage   : SWITCHAR {[NewSwitchCharacter]}\n\n");
            printf("\tThe current %s is '%c'.\n", DOS_switch_character_text, switchar);
         }
      }
      else {

         /* Attempt to alter the current DOS switch character, if an error occurs, display an error message. */

         if (!DOS_Set_SwitchChar(argv[1][0])) {
            SWITCHAR_display_error_message(" can't be modified");
         }
      }
   }

   return (0);
}