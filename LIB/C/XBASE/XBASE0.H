/* File        : XBASE0.H
   Module      : XBASE
   System      : None
   Description : The implementation header file for the XBASE module.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#include <dir.h>
#include <stdio.h>

#include "list\list.h"

#include "xbase.h"

/* Data type definitions. */

typedef struct XBASE_header_record_type {

   BYTE        file_id;
   BYTE        year;
   BYTE        month;
   BYTE        day;
   INTEGER_32  total_records;
   CARDINAL_16 total_bytes_in_header;
   CARDINAL_16 total_bytes_in_record;
   BYTE        reserved_bytes_1[3];
   BYTE        reserved_bytes_2[13];
   BYTE        reserved_bytes_3[4];

} XBASE_header_record;

typedef struct XBASE_field_descriptor_type {

   char        field_name[11];
   char        field_type;
   CARDINAL_32 field_data_address;
   CARDINAL_8  field_length;
   CARDINAL_8  field_decimal_count;
   BYTE        reserved_bytes_1[2];
   BYTE        work_area_id;
   BYTE        reserved_bytes_2[2];
   BYTE        set_fields_flag;
   BYTE        reserved_bytes_3[8];

} XBASE_field_descriptor;

typedef struct XBASE_work_area_type {

   BOOLEAN                in_use_flag;
   BOOLEAN                beginning_of_file_flag;
   BOOLEAN                end_of_file_flag;
   BOOLEAN                found_flag;

   FILE                   *dbf_fp;
   char                   dbf_file[MAXPATH];

   LIST                   ndx_file_list;
   LIST                   ndx_fp_list;

   char                   alias[11];

   XBASE_header_record    header_record;

   CARDINAL_32            current_record;
   CARDINAL_32            current_file_position;

   CARDINAL_16            number_of_fields;
   XBASE_field_descriptor *field_list;

   BYTE                   *xbase_record;
   BYTE                   *c_record;

} XBASE_work_area;

/* Miscellaneous definitions. */

#define XBASE_END_OF_FILE_MARKER 0x1A
#define XBASE_DELETED_RECORD     0x2A

#define XBASE_CHARACTER_FIELD    'C'
#define XBASE_NUMERIC_FIELD      'N'
#define XBASE_LOGICAL_FIELD      'L'
#define XBASE_DATE_FIELD         'D'
#define XBASE_MEMO_FIELD         'M'

/* Global Data. */

extern LIST              XBASE_work_area_list;
extern XBASE_work_area * XBASE_current_work_area;
extern int               XBASE_current_work_area_number;
extern int               XBASE_error_code;

extern char              XBASE_dbf_text[];
extern char              XBASE_ndx_text[];
extern char              XBASE_dbt_text[];
extern char              XBASE_empty_string[];

extern BOOLEAN           XBASE_century_flag;
extern char              XBASE_date_string[];
extern int               XBASE_date_type;
extern char              XBASE_default_drive;
extern char              XBASE_field_string[11];
/* Procedures and Functions. */

void        _XBASE_Close_Work_Area(int work_area_number);
int         _XBASE_Load_Record(INTEGER_32 new_record);
void        _XBASE_Convert_To_C(XBASE_work_area *work_area);
void        _XBASE_Convert_To_Xbase(XBASE_work_area *work_area);
CARDINAL_16 _XBASE_Calculate_C_Record_Size(XBASE_work_area *work_area);
