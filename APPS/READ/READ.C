/* File        : READ.C
   Module      : READ
   System      : READ
   Description : Allows the interactive user to input values into environment variables.
   Modified    : 07/17/91 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <ctype.h>
#include <dos.h>
#include <errno.h>
#include <memory.h>
#include <stdio.h>

#include "msdos\msdos.h"

/* Function    : READ_input_value
   Description :
   Expects     : value   = The current value of the variable being entered.
                 picture = A description of how the data is to be entered (optional).
                 row           = The row on which to input the data.  If a value of zero is specified, then the current row is
                                 used.
                 column        = The starting column on which to input the data.  If a value of zero is specified, then the
                                 current column is used.
   Returns     : A value of TRUE if the field was successfully entered, FALSE otherwise.
   Modified    :
   Notes       :
*/
BOOLEAN READ_input_value(char *value, char *picture, int row, int column) {
   BOOLEAN result;


   return (result);
}

/* Function    : READ_initialize_input_buffer
   Description : Initializes the specified buffer with the current value of the specified environment variable.
   Expects     : buffer        = The buffer to initialize.
                 variable_name = The variable whose value is being altered.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/17/91 DWP Initial coding.
   Notes       :
*/
int READ_initialize_input_buffer(char **buffer, char *variable_name) {
   DOS_PSP *root_PSP;
   int     size_of_environment, result;

   /* Locate the root PSP, exit if it cannot be found. */

   if ((root_PSP = DOS_Get_Root_PSP()) == NULL) {
      result = EINVMEM;
   }
   else {

      /* Allocate heap space for the input buffer, exit if there is not enough memory available. */

      size_of_environment = DOS_Get_Environment_Size(MK_FP(root_PSP->Environment_Segment, 0));

      if ((*buffer = malloc(size_of_environment)) == NULL) {
         result = ENOMEM;
      }
      else {

         /* Retrieve the current value of the specified variable, if the variable does not exist, zero-fill the input buffer. */

         if (DOS_Get_Environment_Variable(root_PSP, variable_name, *buffer) == NULL) {
            setmem(*buffer, size_of_environment, 0);
         }

         result = EZERO;
      }
   }

   return (result);
}

/* Function    : READ_main
   Description : The entry point to the READ module.
   Expects     : variable_name = The name of the variable to input.
                 picture       = A description of how the data is to be entered (optional).
                 row           = The row on which to input the data.  If a value of zero is specified, then the current row is
                                 used.
                 column        = The starting column on which to input the data.  If a value of zero is specified, then the
                                 current column is used.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/17/91 DWP Initial coding.
   Notes       :
*/
int READ_main(char *variable_name, char *picture, int row, int column) {
   char *value = NULL;
   int  result;

   if ((result = READ_initialize_input_buffer(&value, variable_name)) == EZERO) {
      if (READ_input_value(value, picture, row, column)) {
//         result = READ_save_value(variable_name, value);
      }

      if (value != NULL) {
         free(value);
      }
   }

   return (result);
}

/* Function    : main
   Description : The entry point to the READ program.
   Expects     : See Notes above.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/17/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   int i, result;

   printf("\nREAD V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   if (argc == 1) {
      printf("\n   Purpose : Input/set values for master environment variables\n");
      printf("\n   Usage   : READ {[Variable] {[- | /][Switch]}}\n");
      printf("\n   Switches\n\n%6sP = Set data entry picture\n%6sL = Set the input length (default = 10)\n%6sC = Set coordinates (default = current coordinates)\n\n", "", "", "");
   }
   else {

      for (i = 1; i < argc; i++) {

         if (argv[i][0] == '-' || argv[i][0] == '/') {

            switch (toupper(argv[i][1])) {

               case 'P' :
                          break;

               case 'L' :
                          break;

               case 'C' :
                          break;
            }
         }
         else {

            result = READ_main(NULL, NULL, 0, 0);

            if (result != EZERO) {
               break;
            }
         }
      }
   }

   return (result);
}