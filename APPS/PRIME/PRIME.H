/* File        : PRIME.H
   Module      : PRIME
   System      : None
   Description : The internal header file for the PRIME module.
   Modified    : 12/24/90 DWP Created.
   Notes       :
*/

#include <dir.h>
#include <stdio.h>

typedef struct prime_parameter_rec_type {
   unsigned long start;
   unsigned long end;
   char          file_name[MAXPATH];
   FILE          *fp;
   char          mode[4];
   int           type;
   unsigned long count;
   BOOLEAN       prime_number_flag;
   unsigned long new_prime;
} prime_parameter_rec;
