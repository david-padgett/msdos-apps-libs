/* File        : DIR.H
   Module      : DIRECTORY
   System      : None
   Description : The definition header file for the DIRECTORY module.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#ifndef _DIRECTORY_MODULE
#define _DIRECTORY_MODULE

#include <dir.h>

#include "Standard\standard.h"

char *      DIR_Retrieve_Drive(char * File_Spec, CARDINAL_16 Size, char * Drive);
char *      DIR_Retrieve_Path(char * File_Name, CARDINAL_16 Size, char * Path);
char *      DIR_Retrieve_File_Name(char * File_Spec, CARDINAL_16 Size, char * File_Name);
char *      DIR_Retrieve_File_Extension(char * File_Spec, CARDINAL_16 Size, char * File_Extension);
char *      DIR_Retrieve_File_Name_And_Extension(char * File_Spec, CARDINAL_16 Size, char * File_Name_And_Extension);
BOOLEAN     DIR_FindFirst(char far * Path, int Attribute, struct ffblk far * FFBLK);
BOOLEAN     DIR_FindNext(char far * Path, int Attribute, struct ffblk far * FFBLK);
int         DIR_Create_Directory(char * Directory);
int         DIR_Delete_Directory(char * Directory);
int pascal  DIR_Rename_Directory(char * New_Name, char * Old_Name);
CARDINAL_16 DIR_Calculate_File_Specification_Level(char * File_Spec);

#endif
