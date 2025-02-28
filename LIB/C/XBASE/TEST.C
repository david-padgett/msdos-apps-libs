/* File        : TEST.C
   Module      : XBASE
   System      : None
   Description : The test file for the XBASE module.
   Modified    : 02/08/91 DWP Created.
   Notes       :
*/

#include <conio.h>
#include <errno.h>
#include <stdio.h>

#include "xbase0.h"

typedef struct test_dbf_rec_type {
   char        character[11];
   double      numeric;
   BOOLEAN     logical;
   CARDINAL_32 date;
   BYTE        memo[10];
} test_dbf_rec;

/* Function    : main
   Description :
   Expects     : Nothing.
   Returns     : Always returns zero.
   Modified    : 02/08/91 DWP Initial coding.
   Notes       :
*/
int main(void) {
   test_dbf_rec    *rec;
   CARDINAL_32     current_record;
   XBASE_work_area *work_area;

   clrscr();

   if (XBASE_Constructor(10) == EZERO) {

      XBASE_Use("test", NULL, NULL);

      for (current_record = 1L; !XBASE_Eof(); current_record++) {
	 LIST_Retrieve(XBASE_work_area_list, XBASE_current_work_area_number, (void **) &work_area);
         rec = (test_dbf_rec *) work_area->c_record;
         printf("%10ld %-10s %lf %c %02lu/%02lu/%04lu\n", current_record, rec->character, rec->numeric, (rec->numeric) ? 'Y' : 'N', (rec->date % 10000) / 100, rec->date % 100L, rec->date / 10000);
         _XBASE_Convert_To_Xbase(work_area);
         XBASE_Skip(1);
      }

      XBASE_Use(NULL, NULL, NULL);
   }

   return (0);
}
