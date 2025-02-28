/* File        : DIR1B.C
   Module      : DIRECTORY
   System      : None
   Description : A method for extracting the file name information from a file specification.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#include <string.h>

#include "dir.h"

/* Function    : DIR_Retrieve_File_Name
   Description : Extracts the file name information from a file specification.
   Inputs      : File_Spec = The file specification to query.
                 Size      = The maximum number of characters to place in the parameter File_Name.
   Updates     : Nothing.
   Outputs     : File_Name = The file name information which was extracted from File_Spec.
   Returns     : A reference to the parameter 'File_Name' if the file specification contained file name information, otherwise,
                 NULL is returned.
   Modified    : 02/06/91 DWP Initial coding.
   Notes       : 1) The parameter File_Name will contain the file name information found in the specified file name.  If no file
                    name information existed, the parameter path will contain nothing.
*/

char * DIR_Retrieve_File_Name(char * File_Spec, CARDINAL_16 Size, char * File_Name) {

   char * result;
   int    start, end, length;

   length = strlen(File_Spec);

   /* Determine the starting position of the file name. */

   for (start = end = length; start >= 0 && File_Spec[start] != '\\' && File_Spec[start] != ':'; start--) {

      if (File_Spec[start] == '.') {

         end = start;

      }

   }

   /* Extract the file name from the file specification. */

   result = (++start != end && (end - start < Size)) ? strncpy(File_Name, &(File_Spec[start]), end - start) : NULL;
   File_Name[end - start] = '\0';

   return (result);

}
