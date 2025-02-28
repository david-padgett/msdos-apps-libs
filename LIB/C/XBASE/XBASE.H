/* File        : XBASE.H
   Module      : XBASE
   System      : None
   Description : The definition file for the XBASE module.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#ifndef _XBASE_MODULE
#define _XBASE_MODULE

#include "standard\standard.h"
#include "date\date.h"

#define TOP     0L
#define BOTTOM -1L

#define AMERICAN 0
#define ANSI     1
#define BRITISH  2
#define FRENCH   3
#define GERMAN   4
#define ITALIAN  5

/* Global variables. */

extern int XBASE_error_code;

/* Procedures and Functions. */

int           XBASE_Constructor(int total_work_areas);
void          XBASE_Destructor(void);

int           XBASE_Use(char *dbf_file, char *ndx_file_list[], char *alias);
void          XBASE_Select(int work_area);
int           XBASE_Skip(INTEGER_32 offset);
int           XBASE_Goto(INTEGER_32 position);

double        XBASE_Abs(double real_number);
unsigned int  XBASE_Asc(char *string);
unsigned int  XBASE_At(char *string_1, char *string_2);
int           XBASE_Bof(void);
const char    *XBASE_Cdow(DATE_YYYYMMDD date);
char          XBASE_Chr(unsigned int value);
int           XBASE_Cmonth(DATE_YYYYMMDD date);
int           XBASE_Col(void);
unsigned long XBASE_Ctod(char *date);
char          *XBASE_Date(void);
unsigned int  XBASE_Day(unsigned long date);
char          *XBASE_Dbf(void);
int           XBASE_Deleted(void);
unsigned long XBASE_Diskspace(void);
unsigned int  XBASE_Dow(void);
char          *XBASE_Dtoc(unsigned long date);
unsigned int  XBASE_Eof(void);
unsigned int  XBASE_Error(void);

#endif