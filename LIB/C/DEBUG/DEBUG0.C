/* File        : DEBUG0.C
   Module      : DEBUG
   System      : None
   Description : The global variables for the DEBUG module.
   Modified    : 08/09/90 DWP Created.
   Notes       :
*/

#include "debug0.h"

LIST _DEBUG_Heap_Allocation_List;
LIST _DEBUG_Open_Stream_List;
LIST _DEBUG_Open_File_List;

char _DEBUG_Heap_Allocation_Report_File[MAXPATH] = "HEAP.RPT";
char _DEBUG_Open_Stream_Report_File[MAXPATH]     = "STREAM.RPT";
char _DEBUG_Open_File_Report_File[MAXPATH]       = "FILE.RPT";

char _DEBUG_Debug_Text[]           = "DEBUG";
char _DEBUG_Heap_Allocation_Text[] = "Heap Allocation";
char _DEBUG_Open_Stream_Text[]     = "Open Stream";
char _DEBUG_Open_File_Text[]       = "Open File";
char _DEBUG_Open_Error_Text[]      = "\n%s Error (%d):  Unable to open %s.  Press ENTER.\n";
char _DEBUG_Close_Error_Text[]     = "\nError - Unable to close file.";
