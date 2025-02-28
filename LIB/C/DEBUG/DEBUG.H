/* File        : DEBUG.H
   Module      : DEBUG
   System      : None
   Description : The header file for the DEBUG module.
   Modified    : 08/09/90 DWP Created.
   Notes       :
*/

#ifndef _DEBUG_MODULE
#define _DEBUG_MODULE

#include <stdio.h>

/* DEBUG.LIB */

int    DEBUG_Constructor(char * File, int Line, char * Rpt_File_1, char * Rpt_File_2, char * Rpt_File_3);
void   DEBUG_Destructor(void);

void * _DEBUG_Malloc(size_t Size, char * File, unsigned int Line);
void * _DEBUG_Realloc(void * Block, size_t Size, char * File, unsigned int Line);
void   _DEBUG_Free(void * Block, char * File, unsigned int Line);
FILE * _DEBUG_Fopen(char * File_Name, char * Mode, char * File, unsigned int Line);
int    _DEBUG_Fclose(FILE * File_Pointer, char * File, unsigned int Line);
int    _DEBUG_Open(const char * Pathname, int Access, unsigned int Mode, char * File, unsigned int Line);
int    _DEBUG_Creat(const char * Path, int Amode, char * File, unsigned int Line);
int    _DEBUG_Close(int Handle, char * File, unsigned int Line);

/* The re-definitions of the memory management functions of C. */

#define malloc(X)     _DEBUG_Malloc(X, __FILE__, __LINE__)
#define calloc(X, N)  _DEBUG_Malloc(X * N, __FILE__, __LINE__)
#define realloc(B, X) _DEBUG_Realloc(B, (x), __FILE__, __LINE__)
#define free(B)       _DEBUG_Free(B, __FILE__, __LINE__)

/* The re-definitions of some of the file management functions of C. */

#define fopen(F, M)   _DEBUG_Fopen(F, M, __FILE__, __LINE__)
#define fclose(F)     _DEBUG_Fclose(F, __FILE__, __LINE__)

#define open(F, A, M) _DEBUG_Open(F, A, M, __FILE__, __LINE__)
#define close(H)      _DEBUG_Close(H, __FILE__, __LINE__)

#endif
