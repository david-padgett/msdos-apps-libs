/* File        : DATE.H
   Module      : DATE
   System      : None
   Description : The header file for the DATE module.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#ifndef _DATE_MODULE
#define _DATE_MODULE

#include "Standard\standard.h"

/* Standard date types. */

typedef enum _DATE_TYPES {DATE_MMYY_TYPE,
                          DATE_MMDDYY_TYPE,
                          DATE_MMYYYY_TYPE,
                          DATE_MMDDYYYY_TYPE,
                          DATE_YYMM_TYPE,
                          DATE_YYMMDD_TYPE,
                          DATE_YYYYMM_TYPE,
                          DATE_YYYYMMDD_TYPE,
                          DATE_DDMMYY_TYPE,
                          DATE_DDMMYYYY_TYPE,
                          DATE_DDMMMYY_TYPE,
                          DATE_DDMMMYYYY_TYPE,
                          DATE_MMMDDYYYY_TYPE} DATE_TYPES;

typedef CARDINAL_16 DATE_MMYY;
typedef CARDINAL_32 DATE_MMDDYY;
typedef CARDINAL_32 DATE_MMYYYY;
typedef CARDINAL_32 DATE_MMDDYYYY;
typedef CARDINAL_16 DATE_YYMM;
typedef CARDINAL_32 DATE_YYMMDD;
typedef CARDINAL_32 DATE_YYYYMM;
typedef CARDINAL_32 DATE_YYYYMMDD;
typedef CARDINAL_32 DATE_DDMMYY;
typedef CARDINAL_32 DATE_DDMMYYYY;
typedef CARDINAL_32 DATE_DDMMMYY;
typedef char *      DATE_DDMMMYYYY;
typedef char *      DATE_MMMDDYYYY;

/* Global variables. */

extern char *      DATE_Months_List[];
extern char *      DATE_Days_List[];
extern CARDINAL_16 DATE_Days_In_Month_List[];

/* Procedures and functions. */

void *        DATE_Retrieve_System_Date(DATE_TYPES Format, DATA_TYPES Type, char Separator, void * Date);
BOOLEAN       DATE_IsValid(DATE_TYPES Format, DATA_TYPES Type, void * Date);
CARDINAL_16   DATE_Day_Of_Week(DATE_YYYYMMDD Date);
void *        DATE_Construct_Date(DATE_TYPES Format, DATA_TYPES Type, char Separator, CARDINAL_16 Year, CARDINAL_16 Month, CARDINAL_16 Day, void * Date);
BOOLEAN       DATE_Decompose_Date(DATE_TYPES Format, DATA_TYPES Type, void * Date, CARDINAL_16 * Year, CARDINAL_16 * Month, CARDINAL_16 * Day);
INTEGER_32    DATE_Convert_YYYYMMDD_To_Days(DATE_YYYYMMDD Date);
DATE_YYYYMMDD DATE_Convert_Days_To_YYYYMMDD(CARDINAL_32 Date, CARDINAL_16 Century);
BOOLEAN       DATE_Difference_In_Days(DATE_TYPES Date_1_Format, DATA_TYPES Date_1_Type, void * Date_1, DATE_TYPES Date_2_Format, DATA_TYPES Date_2_Type, void * Date_2, CARDINAL_32 * Difference_In_Days);
BOOLEAN       DATE_Convert_To_YYYYMMDD(DATE_TYPES Format, DATA_TYPES Type, void * Date, DATE_YYYYMMDD * Converted_Value);

#endif
