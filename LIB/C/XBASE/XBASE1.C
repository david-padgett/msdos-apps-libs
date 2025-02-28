/* File        : XBASE1.C
   Module      : XBASE
   System      : None
   Description : The constructor and destructor routines for the XBASE module.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#include <errno.h>
#include <memory.h>
#include <stdlib.h>

#include "xbase0.h"

/* Function    : XBASE_Constructor
   Description : Initializes the XBASE module.
   Expects     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 02/06/91 DWP Initial coding.
   Notes       :
*/
int XBASE_Constructor(int total_work_areas) {
   XBASE_work_area work_area;

   /* Initialize the global variables. */

   LIST_Constructor(sizeof(XBASE_work_area), &XBASE_work_area_list);
   XBASE_current_work_area_number = 0;
   XBASE_error_code = EZERO;

   /* Build the work area list. */

   setmem(&work_area, sizeof(work_area), 0);

   while (total_work_areas-- > 0) {
      if ((XBASE_error_code = LIST_Insert(&work_area, LIST_LAST, XBASE_work_area_list)) != EZERO) {
	 break;
      }
   }

   /* Register the XBASE destructor procedure with exit(). */

   if (XBASE_error_code == EZERO) {
      XBASE_error_code = atexit(XBASE_Destructor);
   }

   return (XBASE_error_code);
}

/* Procedure   : XBASE_Destructor
   Description : Shuts down the XBASE module.
   Expects     : Nothing.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 02/06/91 DWP Initial coding.
   Notes       :
*/
void XBASE_Destructor(void) {
   CARDINAL_32 work_area_list_size;

   /* Loop until all work areas have been closed. */
   LIST_Size(XBASE_work_area_list, &work_area_list_size);
   for (XBASE_current_work_area_number = work_area_list_size - 1; XBASE_current_work_area_number >= 0; XBASE_current_work_area_number--) {
      XBASE_Use(NULL, NULL, NULL);
   }

   LIST_Destructor(&XBASE_work_area_list);
}