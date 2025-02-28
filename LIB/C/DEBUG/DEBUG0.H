/* File        : DEBUG0.H
   Module      : DEBUG
   System      : None
   Description : The prototype file for the DEBUG module.  This header file is for only with the source files of the DEBUG module.
   Modified    : 08/09/90 DWP Initial coding.
   Notes       :
*/

#include <dir.h>
#include <stdio.h>

#include "List\list.h"

/* Defines used to identify the calling DEBUG module sub-module. */

typedef enum _DEBUG_REPORT_TYPES {DEBUG_HEAP_ALLOCATION, DEBUG_OPEN_STREAM, DEBUG_OPEN_FILE} DEBUG_REPORT_TYPES;

/* Macros for strings that are used several times, will aid in reducing total size of object file (using the -d option of
   Turbo C). */

/* The definition for the record stored in _DEBUG_Heap_Allocation_List. */

typedef struct __DEBUG_Heap_Allocation_Record {

   void *       Memory_Address;
   size_t       Size;
   char         Source_File[MAXPATH + MAXEXT];
   unsigned int Source_Line;

} _DEBUG_Heap_Allocation_Record;

/* The definition for the record stored in _DEBUG_Open_Stream_List. */

typedef struct __DEBUG_Open_Stream_Record {

   FILE *       File_Pointer;
   char         File_Name[MAXPATH];
   char         Mode[4];
   char         Source_File[MAXPATH + MAXEXT];
   unsigned int Source_Line;

} _DEBUG_Open_Stream_Record;

typedef struct __DEBUG_Open_File_Record {

   int          File_Handle;
   char         Pathname[MAXPATH];
   int          Access;
   unsigned int Mode;
   char         Source_File[MAXPATH + MAXEXT];
   unsigned int Source_Line;

} _DEBUG_Open_File_Record;

typedef struct __DEBUG_Parms_Record {

   FILE *        Fp;
   unsigned long Elements;

} _DEBUG_Parms_Record;

/* Global variable definitions. */

extern LIST     _DEBUG_Heap_Allocation_List;
extern LIST     _DEBUG_Open_Stream_List;
extern LIST     _DEBUG_Open_File_List;
extern char     _DEBUG_Heap_Allocation_Report_File[];
extern char     _DEBUG_Open_Stream_Report_File[];
extern char     _DEBUG_Open_File_Report_File[];
extern char     _DEBUG_Debug_Text[];
extern char     _DEBUG_Heap_Allocation_Text[];
extern char     _DEBUG_Open_Stream_Text[];
extern char     _DEBUG_Open_File_Text[];
extern char     _DEBUG_Open_Error_Text[];
extern char     _DEBUG_Close_Error_Text[];

/* Procedures and Functions. */

int    DEBUG_Constructor(char * File, int Line, char * Rpt_File_1, char * Rpt_File_2, char * Rpt_File_3);
int    _DEBUG_Heap_Allocation_Summary(void * Data, void * Parms, CARDINAL_32 Position);
int    _DEBUG_Open_Stream_Summary(void * Data, void * Parms, CARDINAL_32 Position);
void   DEBUG_Destructor(void);
void   _DEBUG_Write_Output(DEBUG_REPORT_TYPES Type, char * File, int Line, int Error_Code, FILE * Fp);
int    _DEBUG_Heap_Allocation_Key_Compare(void * Key1, void * Key2, CARDINAL_32 Position);
int    _DEBUG_Open_Stream_Key_Compare(void * Key1, void * Key2, CARDINAL_32 Position);
int    _DEBUG_Open_File_Key_Compare(void * Key1, void * Key2, CARDINAL_32 Position);
void * _DEBUG_Malloc(size_t Size, char * File, unsigned int Line);
void * _DEBUG_Realloc(void * Block, size_t Size, char * File, unsigned int Line);
void   _DEBUG_Free(void * Block, char * File, unsigned int Line);
FILE * _DEBUG_Fopen(char * File_Name, char * Mode, char * File, unsigned int Line);
int    _DEBUG_Fclose(FILE * File_Pointer, char * File, unsigned int Line);
int    _DEBUG_Open(const char * Pathname, int Access, unsigned int Mode, char * File, unsigned int Line);
int    _DEBUG_Close(int Handle, char * File, unsigned int Line);
