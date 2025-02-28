/* File        : MSDOS6A.C
   Module      : MSDOS
   System      : None
   Description : Determines the real name of a file specification.
   Modified    : 07/17/91 DWP Initial coding.
   Notes       :
*/

#include <errno.h>
#include <memory.h>
#include <string.h>

#include "msdos0.h"

/* Function    : DOS_Retrieve_Real_Name
   Description : Determines the real name (ie: full path specification) of the specified file.
   Inputs      : Source      = The file specification to examine.
   Updates     : Nothing.
   Outputs     : Destination = The destination buffer for the real name of the source file specification.
   Returns     : The type of file which was specified by Source.  See DOS_FILE_TYPES.
   Modified    : 07/17/91 DWP Initial coding.
   Notes       :
*/

DOS_FILE_TYPES DOS_Retrieve_Real_Name(char * Source, char * Destination) {

   int            copy_destination;
   DOS_FILE_TYPES result;

   if (DOS_Qualify_File_Specification(Destination, Source) != EZERO) {

      result = DOS_INVALID_FILE_SPECIFICATION;

   }
   else {

      switch (Destination[2]) {

         case '\\' :

            result = DOS_LOCAL_FILE;
            break;

         case '/'  :

            copy_destination = 0;
            result = DOS_DEVICE;
            break;

         default   :

            Destination[0] = Destination[2];
            Destination[1] = ':';
            copy_destination = 2;
            result = DOS_NETWORK_FILE;

      }

      /* Move the path/device specification to the left, if necessary. */

      if (result != DOS_LOCAL_FILE) {

         memmove(Destination + copy_destination, Destination + 3, strlen(Destination + 2));

      }

   }

   return (result);

}
