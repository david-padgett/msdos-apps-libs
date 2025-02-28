/* File        : DISK.H
   Module      : DISK
   System      : None
   Description : The header file for the DISK module.
   Modified    : 10/05/90 DWP Created.
   Notes       :
*/

#ifndef _DISK_MODULE
#define _DISK_MODULE

#include "Standard\standard.h"

/* Procedures and Functions. */

BOOLEAN DISK_Feee_Space(unsigned char drive, unsigned long *free_space);

#endif
