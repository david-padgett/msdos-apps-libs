/* File        : DUMP.C
   Module      : DUMP
   System      : DUMP
   Description : Displays the contents of a file or memory in any base.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/

#include <ctype.h>
#include <dir.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "standard\standard.h"
#include "convert\convert.h"
#include "msdos\msdos.h"

/* Type Definitions. */

typedef enum _DUMP_SOURCE_TYPES {DUMP_FILE, DUMP_MEMORY, DUMP_DISK} DUMP_SOURCE_TYPES;

typedef struct _DUMP_file_rec {
   char file_name[MAXPATH];
} DUMP_file_rec;

typedef struct _DUMP_memory_rec {
   CARDINAL_32 start_address;
   CARDINAL_32 end_address;
} DUMP_memory_rec;

typedef struct _DUMP_disk_rec {
   CARDINAL_16 disk_number;
   CARDINAL_32 start_sector;
   CARDINAL_32 end_sector;
} DUMP_disk_rec;

typedef union _DUMP_overlay_rec {
   DUMP_file_rec   file_rec;
   DUMP_memory_rec memory_rec;
   DUMP_disk_rec   disk_rec;
} DUMP_overlay_rec;

typedef struct _DUMP_parameter_rec {
   DUMP_SOURCE_TYPES source_type;
   CARDINAL_16       base;
   BOOLEAN           display_ASCII_flag;
   DUMP_overlay_rec  parameter_list;
} DUMP_parameter_rec;

/* Procedures and Functions. */

/* Procedure   : DUMP_display_line
   Description : Displays the contents of the specified buffer.
   Expects     : buffer             = The buffer that is to be displayed.  The buffer is always assumed to be 16 bytes in length.
                 offset             = The reference number which is associated with the buffer.  Either an offset from the
                                      beginning of a file, a memory location, or an offset from the beginning of a disk sector.
                 base               = The base in which to display the contents of the file.
                 display_ASCII_flag = A flag indicating whether or not the ASCII equivalent of the data being dumped is to be
                                      displayed.
   Returns     : Nothing.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/
void DUMP_display_line(BYTE *buffer, CARDINAL_32 *offset, CARDINAL_16 base, BOOLEAN display_ASCII_flag) {
   int i;

   for (i = 0; i < 16; i++) {



   }
}

/* Function    : DUMP_process_file
   Description :
   Expects     : file               = The file to process.
                 base               = The base in which to display the contents of the file.
                 display_ASCII_flag = A flag indicating whether or not the ASCII equivalent of the data being dumped is to be
                                      displayed.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/
int DUMP_process_file(FILE *file, CARDINAL_16 base, BOOLEAN display_ASCII_flag) {
   CARDINAL_32 offset;
   BYTE        buffer[16];
   int         result;

   for (result = EZERO, offset = 0; fread(&buffer, sizeof(buffer), 1, file) == 1; offset++) {
      DUMP_display_line(buffer, &offset, base, display_ASCII_flag);
   }

   return (result);
}

/* Function    : DUMP_file
   Description : Dumps the contents of the specified file.
   Expects     : file_name          = The name of the file which is to be dumped.
                 base               = The base in which to display the contents of the file.
                 display_ASCII_flag = A flag indicating whether or not the ASCII equivalent of the data being dumped is to be
                                      displayed.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/
int DUMP_file(char *file_name, CARDINAL_16 base, BOOLEAN display_ASCII_flag) {
   FILE *file;
   char *buffer;
   int  result = EZERO;

   if ((file = fopen(file_name, "rb")) == NULL) {
      result = ENOFILE;
   }
   else {

      if ((buffer = malloc(32767)) != NULL) {
         result = setvbuf(file, buffer, _IOFBF, 32767);
      }

      if (result == EZERO) {
         result = DUMP_process_file(file, base, display_ASCII_flag);
      }

      if (buffer != NULL) {
         free(buffer);
      }

      fclose(file);
   }

   return (result);
}

/* Function    : DUMP_memory
   Description : Dumps the contents of the specified block of memory.
   Expects     : start_address      = The starting address of the block of memory which is to be dumped.
                 end_address        = The ending address of the block of memory which is to be dumped.
                 base               = The primary base in which to display the file.
                 display_ASCII_flag = The optional secondary base in which to display the file.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/
int DUMP_memory(CARDINAL_32 start_address, CARDINAL_32 end_address, CARDINAL_16 base, BOOLEAN display_ASCII_flag) {
   int result = EZERO;

   return (result);
}

/* Function    : DUMP_disk
   Description : Dumps the contents of the specified disk sectors.
   Expects     : disk_number        = The disk that is to be examined.
                 start_sector       = The starting sector which is to be dumped.
                 end_sector         = The ending sector which is to be dumped.
                 base               = The primary base in which to display the file.
                 display_ASCII_flag = The optional secondary base in which to display the file.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/
int DUMP_disk(CARDINAL_16 disk_number, CARDINAL_32 start_sector, CARDINAL_32 end_sector, CARDINAL_16 base, BOOLEAN display_ASCII_flag) {
   int result = EZERO;

   return (result);
}

/* Function    : DUMP_main
   Description : The entry point to the DUMP module.
   Expects     : parm_rec = A description of the event and its control parameters which is to take place.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/
int DUMP_main(DUMP_parameter_rec *parm_rec) {
   BOOLEAN display_ASCII_flag;
   int     base, result;

   base = parm_rec->base;
   display_ASCII_flag = parm_rec->display_ASCII_flag;

   switch (parm_rec->source_type) {

      case DUMP_FILE   : result = DUMP_file(parm_rec->parameter_list.file_rec.file_name, base, display_ASCII_flag);
                         break;

      case DUMP_MEMORY : result = DUMP_memory(parm_rec->parameter_list.memory_rec.start_address, parm_rec->parameter_list.memory_rec.end_address, base, display_ASCII_flag);
                         break;

      case DUMP_DISK   : result = DUMP_disk(parm_rec->parameter_list.disk_rec.disk_number, parm_rec->parameter_list.disk_rec.start_sector, parm_rec->parameter_list.disk_rec.end_sector, base, display_ASCII_flag);
                         break;
   }

   return (result);
}

/* Function    : main
   Description : The entry point to the DUMP program.
   Expects     : See Notes for a complete description of the available command-line parameters.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 07/09/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   DUMP_parameter_rec parm_rec;
   BOOLEAN            process_request_flag;
   int                i, result;

   printf("\nDUMP V1.0a, 28-JUN-1991, Copyright (c) 1991 by CSFX.\n\n");

   if (argc == 1) {
      printf("   Purpose : Displays the contents of a file, memory, or disk.\n\n");
      printf("   Usage   : DUMP\n\n");
   }
   else {

      parm_rec.source_type = DUMP_FILE;
      parm_rec.base = 16;
      parm_rec.display_ASCII_flag = FALSE;
      process_request_flag = FALSE;

      for (i = 1; i < argc; i++) {

         if (strchr("-/", argv[i][0]) == NULL) {

            switch (parm_rec.source_type) {

	       case DUMP_FILE   : result = DOS_Qualify_File_Specification(argv[i], parm_rec.parameter_list.file_rec.file_name);
                                  process_request_flag = (result == EZERO) ? TRUE : FALSE;
                                  break;

               case DUMP_MEMORY :
                                  break;

               case DUMP_DISK   :
                                  break;
            }
         }
         else {

            switch (toupper(argv[i][1])) {

               case 'P' :
                          break;

               case 'A' :
                          break;

               case 'F' :
                          break;

               case 'M' :
                          break;

               case 'D' :
                          break;
            }
         }

         if (process_request_flag) {
            result = DUMP_main(&parm_rec);
         }
      }
   }

   return (result);
}