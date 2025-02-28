/* File        : PRIME.C
   Module      : None
   System      : None.
   Description : This program computes prime numbers.
   Modified    : 12/21/90 DWP Created.
   Notes       :
*/

#include <alloc.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "standard\standard.h"
#include "list\list.h"
#include "kb\kb.h"
#include "string\string.h"

#include "prime.h"

/* Function    : PRIME_initialize_list
   Description : Initializes the specified prime numbers list.  The prime numbers 1, 2, and 3 are placed in the list during
		 initialization.
   Expects     : list = The list to initialize.
   Returns     : A code describing the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 12/21/90 DWP Initial coding.
   Notes       :
*/
int PRIME_initialize_list(LIST list) {
   unsigned long prime_number;
   int           result;

   for (prime_number = 2L; prime_number <= 3L; prime_number++) {
      if ((result = LIST_Insert(&(prime_number), LIST_LAST, list)) != EZERO) {
	 break;
      }
   }

   return (result);
}

/* Function    : PRIME_validate_number
   Description : Determines if the specified number is a prime number.
   Expects     : data     = The candidate prime number.
		 parms    = A record of parameters that determines the behavior of this function.
		 position = The position of the element in the list.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 12/24/90 DWP Initial coding.
   Notes       :
*/
int PRIME_validate_number(void *data, void *parms, CARDINAL_32 position) {
   unsigned long current_prime, new_prime;
   int           result;

   (void) position;
   current_prime = *((unsigned long *) data);
   new_prime = ((prime_parameter_rec *) parms)->new_prime;
   result = EZERO;

   if (current_prime != 1L && current_prime != 2L) {
      if (current_prime > (new_prime / 2L)) {
	 result = ERANGE;
      }
      else {

	 /* If the current known prime number divides evenly into the number being evaluated, the number is not prime, so stop the
	    evaluation. */

	 if (new_prime % current_prime == 0L) {
	    ((prime_parameter_rec *) parms)->prime_number_flag = FALSE;
	    result = ERANGE;
	 }
	 else {

            /* Exit if ESC was pressed. */

            if (KB_Preview() && (KB_Read() == KB_ESC)) {
               result = EFAULT;
            }
         }
      }
   }

   return (result);
}

/* Function    : PRIME_construct_list
   Description : Creates or appends to a list of prime numbers up to the specified prime number.
   Expects     : list         = A list of prime numbers.
                 prime_number = The highest value that may be in the prime numbers list.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 12/21/90 DWP Initial coding.
   Notes       :
*/
int PRIME_construct_list(LIST list, unsigned long prime_number) {
   prime_parameter_rec parms;
   unsigned long * last_prime_number;
   int                 result;

   result = EZERO;

   /* Retrieve the last number in the prime numbers list and add one to it.  This number will be the first number to evaluate. If
      this number is even, add one to it (even numbers are never prime). */

   LIST_Retrieve(list, LIST_LAST, (void **) &last_prime_number);
   if ((parms.new_prime = *(last_prime_number) + 1L) % 2L == 0) {
      parms.new_prime++;
   }

   /* Loop until the specified stopping point has been reached. */

   while (parms.new_prime <= prime_number) {

      parms.prime_number_flag = TRUE;

      /* Scan the list of known prime numbers and determine if any of them divide evenly into the number being evaluated.  Don't
	 use the first or second elements in the list (one and two, respectively).  If the return value is EFAULT, then ESC was
	 pressed, so exit. */

      if ((result = LIST_Iterate(list, PRIME_validate_number, &parms)) == EFAULT) {
	 break;
      }

      /* If the number being evaluated is prime, insert it into the list. */

      if (parms.prime_number_flag) {
         if ((result = LIST_Insert(&(parms.new_prime), LIST_LAST, list)) != EZERO) {
            break;
         }
      }

      /* Determine the next number to evaluate (even numbers are excluded). */

      parms.new_prime += 2L;
   }

   return (result);
}

/* Function    : PRIME_commands_list_comparison_operation
   Description : Compares two strings, up to four characters and returns
                 the result of strncmp().
   Expects     : obj1     = The first string.
		 obj2     = The second string.
		 position = The position of the element in the list.
   Returns     : The result of strncmp().
   Modified    : 12/24/90 DWP Initial coding.
   Notes       :
*/
int PRIME_commands_list_comparison_function(void *obj1, void *obj2, CARDINAL_32 position) {
   (void) position;
   return (strncmp((const char *) obj1, (const char *) obj2, 4));
}

/* Procedure   : PRIME_print_number
   Description : Prints the specifed prime number.  This function should be used as a parameter to LIST_print_elements().
   Expects     : data     = The prime number to print.
		 parms    = A list of parameters that determines the behavior of this function.
		 position = The position of the element in the list.
   Returns     : Always returns EZERO.
   Modified    : 12/28/90 DWP Initial coding.
   Notes       :
*/
int PRIME_print_number(void *data, void *parms, CARDINAL_32 position) {
   prime_parameter_rec *rec;
   static int          i;
   int                 result = EZERO;

   (void) position;
   rec = parms;

   if (rec->count++ == 0) {
      i = -1;
   }

   if (rec->end >= rec->count) {
      if (rec->start <= rec->count) {
         if (i++ == 6) {
            i = 0;
	    putchar('\n');
         }

         printf("%10lu ", *((unsigned long *) data));
      }
   }
   else {
      result = ERANGE;
   }

   if (KB_Preview() != 0 && KB_Read() == KB_ESC) {
      result = EFAULT;
   }

   return (result);
}

/* Procedure   : PRIME_list_numbers
   Description : Lists all or some of the prime numbers in the specified prime numbers list.
   Expects     : list  = The list of prime numbers to display.
		 parms = A list of parameters that determines the behavior of this function.
   Returns     : Nothing.
   Modified    : 12/24/90 DWP Initial coding.
   Notes       :
*/
void PRIME_list_numbers(LIST list, prime_parameter_rec *parms) {
   CARDINAL_32 list_size;

   /* Make sure start and end are in bounds. */

   LIST_Size(list, &list_size);
   parms->start = ((parms->start == 0) || (parms->start > list_size)) ? 1L : parms->start;
   parms->end = ((parms->end == 0) || (parms->end > list_size)) ? (unsigned long) list_size : parms->end;
   parms->count = 0L;
   putchar('\n');
   LIST_Iterate(list, PRIME_print_number, parms);
   putchar('\n');
}

/* Function    : PRIME_save_list
   Description : Saves all or part of the specified list.
   Expects     : data     = The next prime number in the list.
		 parms    = A record of parameters that specifies how this function is to behave.
		 position = The position of the element in the list.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 12/24/90 DWP Initial coding.
   Notes       :
*/
int PRIME_save_list(void *data, void *parms, CARDINAL_32 position) {
   prime_parameter_rec *rec;
   int                 result;

   /* Initialize the local variables. */

   (void) position;
   rec = (prime_parameter_rec *) parms;
   result = EZERO;

   /* Don't allow the current element to be output if it is not in the specified range. */

   if ((++(rec->count) >= rec->start) && (rec->count <= rec->end)) {

      /* Open the output file, if it hasn't already been opened. */

      if (rec->fp == NULL) {
         if ((rec->fp = fopen(rec->file_name, rec->mode)) == NULL) {
            result = EFAULT;
         }
      }

      /* If no errors have occurred, attempt to output the number. */

      if (result == EZERO) {
         switch (rec->type) {

                     /* BINARY */

	    case 0 : if (fwrite(data, sizeof(unsigned long), 1, rec->fp) != 1) {
                        result = EACCES;
                     }

                     break;

		     /* TEXT */

            case 1 : if (fprintf(rec->fp, "%10lu\n", *((unsigned long *) data)) == EOF) {
                        result = EACCES;
                     }

                     break;
	 }
      }
   }

   return (result);
}

int fn1(void *list_element, void* data, CARDINAL_32 position) {
   (void) data;
   printf("COMMAND: %lu %s\n", position, (char*) list_element);
   return 0;
}

int fn2(void *list_element, void* data, CARDINAL_32 position) {
   (void) data;
   printf("PRIME: %lu %lu\n", position, *((unsigned long*) list_element));
   return 0;
}


/* Function    : main
   Description : The main entry point for PRIME.
   Expects     : Nothing.
   Returns     : Always returns zero.
   Modified    : 12/21/90 DWP Initial coding.
   Notes       :
*/
int main(void) {
   BOOLEAN             exit_flag, break_flag;
   LIST                prime_numbers_list = NULL, commands_list = NULL;
   prime_parameter_rec parms;
   char                str[256], *token, *command;
   CARDINAL_32         prime_number, list_size, *first_prime_number, *last_prime_number, position;
   int                 i;

   printf("\nPRIME V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX\n");

   /* Initialize the prime numbers list and the commands list. */

   LIST_Constructor(sizeof(unsigned long), &prime_numbers_list);
   PRIME_initialize_list(prime_numbers_list);

   LIST_Constructor(5, &commands_list);
   LIST_Insert("LIST", LIST_LAST, commands_list);
   LIST_Insert("LOAD", LIST_LAST, commands_list);
   LIST_Insert("NEW", LIST_LAST, commands_list);
   LIST_Insert("QUIT", LIST_LAST, commands_list);
   LIST_Insert("SAVE", LIST_LAST, commands_list);
   LIST_Insert("STAT", LIST_LAST, commands_list);

   LIST_Iterate(prime_numbers_list, fn2, NULL);
   LIST_Iterate(commands_list, fn1, NULL);
   /* Loop until the QUIT is entered. */

   for (exit_flag = FALSE; !exit_flag;) {

      /* Display the prompt, get the response. */

      printf("\nCalculate primes up to what number (max = 2^32): ");
      gets(str);
      strupr(str);

      /* Determine what command was entered. */

      LIST_Find(commands_list, PRIME_commands_list_comparison_function, str, (void **) &command, &position);
      switch (position) {

		   /* LIST */

	 case 0  : LIST_Size(prime_numbers_list, &list_size);
		   strtok(str, " ");
		   parms.start = ((token = strtok(NULL, " ")) != NULL) ? atoi(token) : 1;
		   parms.end = ((token = strtok(NULL, " ")) != NULL) ? atoi(token) : list_size;
		   PRIME_list_numbers(prime_numbers_list, &parms);
		   break;

		   /* LOAD */

	 case 1  : strtok(str, " ");

		   if ((token = strtok(NULL, " ")) == NULL) {
		      printf("\nLoad what file : ");
		      token = gets(str);
		   }

		   /* Attempt to open the specified file. */

		   if ((parms.fp = fopen(token, "rb")) != NULL) {

		      /* Re-initialize the prime numbers list. */

		      LIST_Destructor(&prime_numbers_list);
		      LIST_Constructor(sizeof(unsigned long), &prime_numbers_list);
/*
		      PRIME_initialize_list(prime_numbers_list);
*/
		      /* Read in 256 bytes of data from the opened file. */

		      if (fread(str, sizeof(str), 1, parms.fp) == 1) {

			 /* Determine what type of file this is, either BINARY or TEXT.  Assume that the file is TEXT. */

			 parms.type = 1;

			 for (i = 0; i < sizeof(str); i++) {
			    if (str[i] == '\0') {
			       parms.type = 0;
			       break;
			    }
			 }

			 /* Reset file pointer and loop until the end of file has been encountered. */

			 fseek(parms.fp, 0, SEEK_SET);

			 for (break_flag = FALSE; !break_flag;) {

			    switch (parms.type) {

					/* BINARY */

			       case 0 : if (fread(&prime_number, sizeof(prime_number), 1, parms.fp) != 1) {
					   break_flag = TRUE;
					}

					break;

					/* TEXT */

			       case 1 : if (fgets(str, sizeof(str), parms.fp) == NULL) {
					   break_flag = TRUE;
					}
					else {
					   prime_number = atol(str);
					}

					break;
			    }

			    if (!break_flag) {
			       LIST_Insert(&prime_number, LIST_LAST, prime_numbers_list);
			    }
			 }
		      }

		      fclose(parms.fp);
		   }
		   else {
		      printf("\nError:  Unable to open %s.\n", strupr(token));
		   }

		   break;

		   /* NEW */

	 case 2  : LIST_Destructor(&prime_numbers_list);
		   LIST_Constructor(sizeof(unsigned long), &prime_numbers_list);
		   PRIME_initialize_list(prime_numbers_list);
		   break;

		   /* QUIT */

	 case 3  : exit_flag = TRUE;
		   break;

		   /* SAVE */

	 case 4  : strtok(str, " ");

		   /* Initialize the parameters record. */

		   parms.start = 0;
		   parms.end = 0;
		   parms.file_name[0] = '\0';
		   parms.fp = NULL;
		   parms.mode[0] = '\0';
		   parms.type = 0;
		   parms.count = 0L;

		   /* Scan the response and extract any valid parameters. */

		   while ((token = strtok(NULL, " ")) != NULL) {

		      strupr(token);

		      if (atoi(token) > 0) {
			 if (parms.start == 0) {
			    parms.start = atoi(token);
			 }
			 else {
			    if (parms.end == 0) {
			       parms.end = atoi(token);
			    }
			 }
		      }
		      else {
			 if ((strcmp(token, "BINARY") == 0) || (strcmp(token, "TEXT") == 0)) {
			    parms.type = (strcmp(token, "BINARY") == 0) ? 0 : 1;
			 }
			 else {
			    if (strlen(parms.file_name) == 0) {
			       for (i = 0; token[i] != ' '; i++) {
				  parms.file_name[i] = token[i];
			       }
			    }
			 }
		      }
		   }

		   /* Initialize any uninitialized parameters. */

		   if (strlen(parms.file_name) == 0) {
		      strcpy(parms.file_name, (parms.type == 0) ? "primes.bin" : "primes.txt");
		   }

		   if (parms.start == 0) {
		      parms.start = 1;
		   }

		   if (parms.end == 0) {
		      LIST_Size(prime_numbers_list, &list_size);
		      parms.end = list_size;
		   }

		   strcpy(parms.mode, (parms.type == 0) ? "wb" : "wt");
		   LIST_Iterate(prime_numbers_list, PRIME_save_list, &parms);

		   if (parms.fp != NULL) {
		      fclose(parms.fp);
		   }

		   break;

		   /* STAT */

	 case 5  : sprintf(str, "%lu", coreleft());
		   LIST_Size(prime_numbers_list, &list_size);
		   LIST_Retrieve(prime_numbers_list, LIST_FIRST, (void **) &first_prime_number);
		   LIST_Retrieve(prime_numbers_list, LIST_LAST, (void **) &last_prime_number);
		   printf("\nStatus:\n\n%3sFirst Element%4s: %lu\n%3sLast Element%5s: %lu\n%3sTotal Elements%3s: %u\n%3sMemory Available : %s\n", "", "", *first_prime_number, "", "", *last_prime_number, "", "", list_size, "", STRING_Delimit(3, STRING_DELIMIT_RIGHT, ",", str));
		   break;

		   /* If the response is a number, build a list of prime numbers up to and including the response, otherwise,
		      print an error message. */

	 default : if (atol(str) > 0) {
		      PRIME_construct_list(prime_numbers_list, atol(str));
		   }
		   else {

		      printf("\nError:  Invalid Command.\n\n%3sValid Commands:\n\n", "");

		      LIST_Size(commands_list, &list_size);
		      for (i = 0; i < list_size; i++) {
			 LIST_Retrieve(commands_list, i, (void **) &command);
			 printf("%6s%-s\n", "", command);
                      }
                   }
      }
   }

   LIST_Destructor(&prime_numbers_list);
   LIST_Destructor(&commands_list);

   return (0);
}
