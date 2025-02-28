/* File        : CLE.H
   Module      : CLE
   System      : CLE
   Description : The header file for the CLE system.
   Modified    : 11/29/90 DWP Created.
*/

#include <stdio.h>

#define CLE_MAXIMUM_LINE_LENGTH 256

/* CLE1.C */

int main(int argc, char *argv[]);
int cle(int command_list_size, int synonym_list_size);
