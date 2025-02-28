/* File        : XBASE3A.C
   Module      : XBASE
   System      : None
   Description : A method for selecting a new work area in the XBASE module.
   Modified    : 02/07/91 DWP Created.
   Notes       :
*/

#include "xbase0.h"

/* Procedure   : XBASE_Select
   Description : Switches to a new work area.
   Expects     : work_area = The work area to switch to.
   Returns     : Nothing.
   Modified    : 02/07/91 DWP Initial coding.
   Notes       : If the specified work area is invalid, no new work area is selected.
*/
void XBASE_Select(int work_area) {
   CARDINAL_32 work_area_list_size;

   LIST_Size(XBASE_work_area_list, &work_area_list_size);
   if (work_area > 0 && work_area <= work_area_list_size) {
      XBASE_current_work_area_number = work_area - 1;
   }
}
