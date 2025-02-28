/* File        : DIR1.C
   Module      : DIRECTORY
   System      : None
   Description : A method for extracting the drive information from a file specification.
   Modified    : 02/06/91 DWP Created.
   Notes       :
*/

#include <string.h>

#include "dir.h"

/* Function    : DIR_Retrieve_Drive
   Description : Extracts the drive information from a file specification.
   Inputs      : File_Spec = The file specification to query.
                 Size      = The maximum number of characters to place in the parameter Drive.
   Updates     : Nothing.
   Outputs     : Drive     = The drive information which was extracted from File_Spec.
   Returns     : A reference to the parameter 'Drive' if the file specification contained drive information, otherwise, NULL is
                 returned.
   Modified    : 02/06/91 DWP Initial coding.
   Notes       : 1) The parameter Drive will contain the drive information found in the specified file name.  If no drive
                    information existed, the parameter Drive will contain nothing.
*/

char * DIR_Retrieve_Drive(char * File_Spec, CARDINAL_16 Size, char * Drive) {

   char *      result;
   CARDINAL_16 i;

   /* Determine the starting and ending positions of the drive information. */

   for (i = 0; File_Spec[i] != '\0'; i++) {

      if (File_Spec[i] == ':') {

         break;

      }

   }

   /* Extract the drive information from the file specification. */

   result = ((File_Spec[i] != '\0' && i < Size) ? strncpy(Drive, File_Spec, ++i) : NULL);
   Drive[(result != NULL) ? i : 0] = '\0';

   return (result);

}
