/* File        : DIR1A.C
   Module      : DIRECTORY
   System      : None
   Description : A method for extracting the path information from a file specification.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#include <string.h>

#include "dir.h"

/* Function    : DIR_Retrieve_Path
   Description : Extracts the path information from a file specification.
   Inputs      : File_Spec = The file specification to query.
                 Size      = The maximum number of characters to place in the parameter Path.
   Updates     : Nothing.
   Outputs     : Path      = The path information which was extracted from File_Spec.
   Returns     : A reference to the parameter 'Path' if the file specification contained path information, otherwise, NULL is
                 returned.
   Modified    : 02/06/91 DWP Initial coding.
   Notes       : 1) The parameter Path will contain the path information found in the specified file specification.  If no path
                    information existed, the parameter Path will contain nothing.
*/

char * DIR_Retrieve_Path(char * File_Spec, CARDINAL_16 Size, char * Path) {

   char * result;
   int    start, end, length;

   length = strlen(File_Spec);

   /* Find the start of the path. */

   for (start = 0; File_Spec[start] != '\0'; start++) {

      if (File_Spec[start] == ':') {

         break;

      }

   }

   /* Reset the starting point if no drive information was present in the file name. */

   if (start == length) {

      start = -1;

   }

   /* Find the end of the path. */

   for (end = length; end > start; end--) {

      if (File_Spec[end] == '\\') {

         break;

      }

   }

   /* Extract the path from the file specification. */

   result = (start != end && (end - start < Size)) ? strncpy(Path, &(File_Spec[start + 1]), end - start) : NULL;
   Path[(result != NULL) ? end - start: 0] = '\0';

   return (result);

}
