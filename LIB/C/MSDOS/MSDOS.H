/* File        : DOS.H
   Module      : DOS
   System      : None
   Description : The definition header file for the DOS module.
   Modified    : 03/19/91 DWP Created.
   Notes       :
*/

#ifndef _DOS_MODULE
#define _DOS_MODULE

#include "Standard\standard.h"

/* Type definitions. */

typedef struct _DOS_PSP {

   BYTE        Program_Exit_Point[2];
   CARDINAL_16 Memory_Size;
   BYTE        Unused1;
   BYTE        CPM_Entry_Point[5];
   CARDINAL_16 Terminate_Address_Segment;
   CARDINAL_16 Terminate_Address_Offset;
   CARDINAL_16 Break_Address_Segment;
   CARDINAL_16 Break_Address_Offset;
   CARDINAL_16 Critical_Error_Handler_Segment;
   CARDINAL_16 Critical_Error_Handler_Offset;
   CARDINAL_16 Parent_PSP_Segment;
   BYTE        Open_File_Table[20];
   CARDINAL_16 Environment_Segment;
   CARDINAL_16 SS_Reg;
   CARDINAL_16 SP_Reg;
   CARDINAL_16 Max_Open_Files;
   CARDINAL_16 Open_File_Table_Segment;
   CARDINAL_16 open_File_Table_Offset;
   CARDINAL_16 Previous_PSP_Segment;
   CARDINAL_16 Previous_PSP_Offset;
   BYTE        Unused2[20];
   BYTE        Function_Dispatcher[3];
   BYTE        Unused3[9];
   BYTE        FCB_1[16];
   BYTE        FCB_2[20];
   BYTE        Command_Tail[128];

} DOS_PSP;

typedef struct _DOS_PARAMETER_LIST {

   WORD_16 AX;
   WORD_16 BX;
   WORD_16 CX;
   WORD_16 DX;
   WORD_16 SI;
   WORD_16 DI;
   WORD_16 DS;
   WORD_16 ES;
   WORD_16 Reserved;    /* Should always be 0. */
   WORD_16 Computer_ID; /* Current system is 0. */
   WORD_16 Process_ID;  /* PSP segment on specified computer. */

} DOS_PARAMETER_LIST;

typedef enum _DOS_FILE_TYPES {DOS_INVALID_FILE_SPECIFICATION, DOS_LOCAL_FILE, DOS_NETWORK_FILE, DOS_DEVICE} DOS_FILE_TYPES;

/* Procedures and functions. */

int            DOS_Get_Current_Size_Of_Environment(char * Environment);
DOS_PSP *      DOS_Get_Root_PSP(void);
int            DOS_Get_Environment_Size(char * Environment);
int            DOS_Get_Remaining_Space_In_Environment(char * Environment);
char *         DOS_Get_Environment_Variable(DOS_PSP far * PSP, char * Variable, char * Value);
int            DOS_Set_Environment_Variable(DOS_PSP far * PSP, char * Variable, char * Value);
int            DOS_Alter_Environment_Variable(char * Environment, char * Variable, char * Value);
int            DOS_Add_Environment_Variable(char * Environment, char * Variable, char * Value);
int            DOS_Delete_Environment_Variable(char * Environment, char * Variable);
char           DOS_Get_SwitchChar(void);
int            DOS_Set_SwitchChar(char SwitchChar);
int            DOS_Qualify_File_Specification(char * Source, char * Destination);
DOS_FILE_TYPES DOS_Retrieve_Real_Name(char * Source, char * Destination);

#endif
