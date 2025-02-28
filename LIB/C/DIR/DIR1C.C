/* File        : DIR1C.C
   Module      : DIRECTORY
   System      : None
   Description : A method for extracting the file extension information from a file specification.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#include <string.h>

#include "dir.h"

/* Function    : DIR_Retrieve_File_Extension
   Description : Extracts the file extension information from a file specification.
   Inputs      : File_Spec      = The file specification to query.
                 Size           = The maximum number of characters to place in the parameter File_Extension.
   Updates     : Nothing.
   Outputs     : File_Extension = The file extension information which was extracted from File_Spec.
   Returns     : A reference to the parameter 'File_Extension' if the file specification contained file extension information,
                 otherwise, NULL is returned.
   Modified    : 02/06/91 DWP Initial coding.
   Notes       : 1) The parameter File_Extension will contain the file name information found in the specified file name.  If no
                    file name information existed, the parameter path will contain nothing.
*/

char * DIR_Retrieve_File_Extension(char * File_Spec, CARDINAL_16 Size, char * File_Extension) {

   char * result;
   int    start, length;

   length = strlen(File_Spec);

   /* Determine the starting position of the file extension. */

   for (start = length; start >= 0 && File_Spec[start] != '.'; start--);

   /* Extract the file extension from the file specification. */

   if ((result = (start != -1 && length - start < Size) ? strcpy(File_Extension, &(File_Spec[start + 1])) : NULL) == NULL) {

      File_Extension[0] = '\0';

   }

   return (result);

}
