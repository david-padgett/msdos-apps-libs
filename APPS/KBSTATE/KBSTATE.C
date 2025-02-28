/* File        : KBSTATE.C
   Module      : LOCK
   System      : LOCK
   Description : This program manipulates the lock and insert keys.
   Modified    : 05/01/91 DWP Created.
   Notes       :
*/

#include <stdio.h>
#include <string.h>

#include "kb\kb.h"

/* Function    : main
   Description : The main entry point for the KBSTATE program.
   Expects     : argv[1] = The action to perform.
                 argv[2] = The state to modify.
   Returns     : Always returns a value of zero.
   Modified    : 05/01/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   char        *condition_list[] = {"LOCK", "UNLOCK", "TOGGLE"};
   char        *state_list[] = {"SCROLL", "NUM", "CAPS", "INSERT"};
   char        *value_list[] = {"OFF", "ON"};
   char        str[80];
   CARDINAL_16 state, condition, i;
   BOOLEAN     state_specified_flag, condition_specified_flag;

   printf("\nKBSTATE V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   /* Determine what action and key was specified. */

   state_specified_flag = condition_specified_flag = FALSE;

   for (i = 0; i < 4; i++) {

      if (i < 3 && stricmp(argv[1], condition_list[i]) == 0) {
         condition = i;
         condition_specified_flag = TRUE;
      }

      if (stricmp(argv[2], state_list[i]) == 0) {
         state = i;
         state_specified_flag = TRUE;
      }
   }

   /* If an invalid action or key was specified, print the help screen and exit. */

   if (argc != 3 || !state_specified_flag || !condition_specified_flag) {

      printf("\n   Purpose : Modifies the states of the lock keys.\n\n");
      printf("   Usage   : KBSTATE [{State}] [{Key}]\n\n");
      printf("   States\n\n%6sLock   = Lock the key\n%6sUnlock = Unlock the key\n%6sToggle = Toggle the current state of the key\n\n   Keys\n\n%6sScroll = Scroll lock\n%6sNum%4s= Num Lock\n%6sCaps   = Caps Lock\n%6sInsert = Insert Key\n\n   Current Keyboard States\n", "", "", "", "", "", "", "", "");

      for (i = 0; i < 4; i++) {

         if ((i % 2) == 0) {
            putchar('\n');
         }

	 sprintf(str, "o %s Lock is %s", state_list[i], value_list[((KB_Retrieve_Shift_Status_Word() & (1 << (i + 4))) != 0) ? 1 : 0]);
         printf("%6s%-33s", "", str);
      }

      putchar('\n');
   }
   else {
      KB_Modify_State(state, condition);
   }

   return (0);
}