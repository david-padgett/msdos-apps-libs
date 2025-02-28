/* File        : CLE1.C
   Module      : MAIN
   System      : CLE
   Description : The main module for the CLE (Command-Line Editor) system.
   Modified    : 11/29/90 Created.
*/

#include <alloc.h>
#include <ctype.h>
#include <dir.h>
#include <errno.h>
#include <mem.h>
#include <stdlib.h>
#include <string.h>

#include "standard\standard.h"
#include "kb\kb.h"
#include "list\list.h"

#include "cle.h"

/* Function    : main
   Description : The main entry point for the CLE program.
   Expects     : argc = The number of command-line arguments given.
		 argv = A list of the command-line arguments.
   Returns     : The code of the last error which occurred.  A value of 0
                 indicates no errors occurred.
   Modified    : 11/29/90 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   size_t   command_list_size = 0, synonym_list_size = 0;
   int      i, result;

   /* Process command-line arguments. */

   if (argc > 1) {
      for (i = 1; argv[i][0] != '\0'; i++) {
         switch (argv[i][1]) {
            case 'c' : command_list_size = atoi(&(argv[i][2]));
                       break;
            case 's' : synonym_list_size = atoi(&(argv[i][2]));
                       break;
         }
      }
   }

   if (command_list_size == 0) {
      command_list_size = 512;
   }
   if (synonym_list_size == 0) {
      synonym_list_size = 512;
   }

   result = cle(command_list_size, synonym_list_size);

   return (result);
}

/* Function    : cle_compare_commands
   Description : Compares two commands to see if they are identical.
   Expects     : obj1 = The first command.
		 obj2 = The second command.
   Returns     : The result of strcmp().
   Modified    : 12/03/90 DWP Initial coding.
   Notes       : 1) This function is for use with the LIST module,
                    specifically, list_get_position().
*/
int cle_compare_commands(void *obj1, void *obj2, CARDINAL_32 position) {

   (void) position;
   return (strcmp(obj1, obj2));
}

/* Procedure   : cle_move_cursor
   Description : Moves the cursor backwards the specified amount of columns.
   Expects     : displacement = The number of columns to move the cursor.
   Returns     : Nothing.
   Modified    : 12/03/90 DWP Initial coding.
   Notes       :
*/
void cle_move_cursor(size_t displacement) {
   size_t i;

   for (i = 0; i < displacement; i++) {
      putchar('\b');
   }
}

/* Function    : cle_get_command
   Description : Allows a command string to be entered into CLE.
   Expects     :
   Returns     : The scancode of the last key pressed.
   Modified    : 12/03/90 DWP Initial coding.
   Notes       :
*/
unsigned int cle_get_command(char *command, size_t maximum_length) {
   BOOLEAN      exit_flag, break_flag, insert_flag, move_flag;
   size_t       length, current_position, i;
   unsigned int key;

   for (exit_flag = FALSE; !exit_flag;) {

      length = strlen(command);
      current_position = length;
      insert_flag = FALSE;

      for (break_flag = FALSE; !break_flag;) {

	 switch ((key = KB_Read())) {
            case KB_ENTER     : break_flag = TRUE;
                                exit_flag = TRUE;
                                break;
            case KB_ESC       : while (current_position != length) {
                                   putchar(command[current_position++]);
				}
                                for (i = 0; i < current_position; i++) {
                                   printf("\b \b");
                                }
                                break_flag = TRUE;
                                command[0] = '\0';
                                break;
            case KB_LEFT      : if (current_position > 0) {
                                   current_position--;
                                   putchar('\b');
                                }
                                break;
            case KB_RIGHT     : if (current_position < length) {
				   putchar(command[current_position++]);
                                }
                                break;
	    case KB_CTRL_LEFT : for (move_flag = FALSE; current_position != 0;) {
				   current_position--;
				   putchar('\b');
				   if (isspace(command[current_position - 1])) {
				      if (move_flag) {
					 break;
				      }
				   }
				   else {
				      move_flag = TRUE;
				   }
				}
				break;
	    case KB_CTRL_RIGHT : for (move_flag = FALSE; current_position < length;) {
				   putchar(command[current_position++]);
                                   if (isspace(command[current_position])) {
                                      move_flag = TRUE;
                                   }
                                   else {
                                      if (move_flag) {
                                         break;
                                      }
                                   }
				}
                                break;
            case KB_HOME      : cle_move_cursor(current_position);
                                current_position = 0;
                                break;
            case KB_END       : while (current_position < length) {
                                   putchar(command[current_position++]);
                                }
                                break;
            case KB_UP        : exit_flag = TRUE;
                                break;
            case KB_DOWN      : exit_flag = TRUE;
                                break;
	    case KB_INS       : insert_flag = (insert_flag) ? FALSE : TRUE;
                                break;
            case KB_DEL       : if (length > 0) {
                                   memmove(&(command[current_position]), &(command[current_position + 1]), length - current_position);
                                   printf("%s ", &(command[current_position]));
                                   cle_move_cursor(length - current_position);
                                   length--;
                                }
                                break;
            case KB_BACKSPACE : if (current_position > 0) {
                                   memmove(&(command[current_position - 1]), &(command[current_position]), length - current_position + 1);
                                   length--;
                                   printf("\b%s ", &(command[--current_position]));
				   cle_move_cursor(length - current_position + 1);
                                }
                                break;
            default           : if (insert_flag) {
                                   if (length < maximum_length) {
                                      memmove(&(command[current_position + 1]), &(command[current_position]), length - current_position + 1);
                                      command[current_position] = (char) key;
                                      length++;
                                      printf("%s", &(command[current_position++]));
                                      cle_move_cursor(length - current_position);
                                   }
                                }
                                else {
				   command[current_position++] = (char) key;
                                   if (length < current_position) {
                                      length++;
                                      command[length + 1] = '\0';
                                   }
                                   putchar(key);
                                }
         }
      }
   }

   command[length] = '\0';

   return (key);
}

/* Function    : cle
   Description :
   Expects     : command_list_size =
                 synonym_list_size =
   Returns     : The code of the last error which occurred.  A value of 0
                 indicates that no errors occurred.
   Modified    : 11/29/90 DWP Initial coding.
   Notes       :
*/
int cle(int command_list_size, int synonym_list_size) {
   LIST         command_list, synonym_list;
   CARDINAL_32  new_command_list_size, new_synonym_list_size;
   BOOLEAN      exit_flag, break_flag;
   char         *token, str[CLE_MAXIMUM_LINE_LENGTH], command[CLE_MAXIMUM_LINE_LENGTH], *list_element;
   unsigned int key;
   int          token_hash_value, total_commands, current_command;
   int          i, result = EZERO;
   char *       command_list_buffer = NULL;
   char *       synonym_list_buffer = NULL;
   CARDINAL_32  list_position;

   /* Initialize the command and synonym lists. */

   LIST_Constructor(CLE_MAXIMUM_LINE_LENGTH, &command_list);
   LIST_Constructor(CLE_MAXIMUM_LINE_LENGTH, &synonym_list);

   /* Allocate space for the command and synonym list buffers. */

   setmem(command, CLE_MAXIMUM_LINE_LENGTH, 0);

   for (i = 0; (result == EZERO) && (i < command_list_size); i++) {
      result = LIST_Insert(command, LIST_LAST, command_list);
   }

   for (i = 0; (result == EZERO) && (i < synonym_list_size); i++) {
      result = LIST_Insert(command, LIST_LAST, synonym_list);
   }

   LIST_Size(command_list, &new_command_list_size);
   LIST_Size(synonym_list, &new_synonym_list_size);
   if ((new_command_list_size == command_list_size) && (new_synonym_list_size == synonym_list_size)) {

      total_commands = 0;
      current_command = 0;

      for (exit_flag = FALSE; !exit_flag;) {

	 /* Display the prompt. */

	 if (getcwd(str, sizeof(str)) != NULL) {
	    printf("\n%s>", str);
	 }
	 else {
	    result = errno;
	    break;
	 }

	 /* Get the next command. */

	 for (break_flag = FALSE; !break_flag;) {
	    switch (cle_get_command(command, CLE_MAXIMUM_LINE_LENGTH)) {
	       case KB_ENTER : break_flag = TRUE;
			       break;
	       case KB_UP    : LIST_Retrieve(command_list, (current_command != 0) ? --current_command : (current_command = total_commands), (void **) list_element);
			       strcpy(command, list_element);
			       break;
	       case KB_DOWN  : LIST_Retrieve(command_list, (current_command == total_commands) ? (current_command = 0) : ++current_command, (void **) list_element);
			       strcpy(command, list_element);
                               break;
            }
         }

         if (strlen(command) > 0) {

            putchar('\n');
            strcpy(str, command);
            token = strtok(str, " ");
            if ((token != NULL) && (strcmp(strupr(token), "CLE") == 0)) {

               token = strtok(NULL, " ");
               if ((token != NULL) && (strlen(strupr(token)) == 3)) {

                  token_hash_value = (token[0] + token[1]) - (2 * 'A');

                  switch (token_hash_value) {

                               /* CLE ADD */

                     case 3  :
                               break;

                               /* CLE DEL */

                     case 7  :
                               break;

                               /* CLE CLR */

                     case 13 :
                               break;

                               /* CLE NEW */

                     case 17 :
                               break;

                               /* CLE LST */

                     case 29 :
                               break;

                               /* CLE SRT */

                     case 35 :
                               break;

                               /* CLE LOD */

                     case 25 :
                               break;

                               /* CLE SAV */

                     case 18 :
                               break;

                               /* CLE APP */

                     case 15 :
                               break;

                               /* CLE PRO */

                     case 32 :
                               break;

                               /* CLE EXT */

                     case 27 : exit_flag = TRUE;
                               break;

                     default : printf("\nCLE : Invalid Command.\n");
                  }
               }
               else {
                  printf("\nCLE : Invalid Command.\n");
               }
            }
	    else {
	       LIST_Find(command_list, cle_compare_commands, command, (void **) list_element, &list_position);
	       if (list_element == NULL) {
		  LIST_Find(command_list, cle_compare_commands, "", (void **) list_element, &list_position);
		  if (list_element == NULL) {
		     LIST_Retrieve(command_list, LIST_FIRST, (void **) list_element);
		  }
		  strcpy(list_element, command);
		  if (current_command == total_commands) {
		     current_command++;
		  }
		  total_commands++;
	       }
	       system(command);
	    }
	 }
      }
   }
   else {
      result = ENOMEM;
   }

   if (command_list_buffer != NULL) {
      free(command_list_buffer);
   }
   if (synonym_list_buffer != NULL) {
      free(synonym_list_buffer);
   }

   LIST_Destructor(&command_list);
   LIST_Destructor(&synonym_list);

   return (result);
}
