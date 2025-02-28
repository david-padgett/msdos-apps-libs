/* File        : XBASE0.C
   Module      : XBASE
   System      : None
   Description : The global variable definitions for the XBASE module.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#include "xbase0.h"

LIST              XBASE_work_area_list;
XBASE_work_area * XBASE_current_work_area;
int               XBASE_current_work_area_number;
int               XBASE_error_code;

char              XBASE_dbf_text[] = ".dbf";
char              XBASE_ndx_text[] = ".ndx";
char              XBASE_dbt_text[] = ".dbt";
char              XBASE_empty_string[] = "";

BOOLEAN           XBASE_century_flag;
char              XBASE_date_string[11];
int               XBASE_date_type;
char              XBASE_default_drive;
char              XBASE_field_string[11];
