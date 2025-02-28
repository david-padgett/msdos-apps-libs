/* File        : DIR1D.C
   Module      : DIRECTORY
   System      : None
   Description : A method for extracting the file name and extension information from a file specification.
   Modified    : 04/19/91 DWP Created.
   Notes       :
*/

#include <stdio.h>
#include <string.h>

#include "dir.h"

/* Function    : DIR_Retrieve_File_Name_And_Extension
   Description : Extracts the file name and extension information from the specified file specification.
   Inputs      : File_Spec               = The file specification to query.

                 Size                    = The maximum number of characters to place in the parameter File_Name_And_Extension.
   Updates     : Nothing.
   Outputs     : File_Name_And_Extension = The file name and extension information which was extracted from File_Spec.
   Returns     : A reference to the parameter 'File_Name_And_Extension' if the file specification contained file extension
                 information and the size of the parameter File_Name_And_Extension was large enough to hold the result.  Otherwise,
                 NULL is returned.
   Modified    : 04/19/91 DWP Initial coding.
   Notes       :
*/

char * DIR_Retrieve_File_Name_And_Extension(char * File_Spec, CARDINAL_16 Size, char * File_Name_And_Extension) {

   char * result;
   int    start, length;

   length = strlen(File_Spec);

   /* Determine the starting position of the file name and extension. */

   for (start = length; start >= 0 && File_Spec[start] != '\\' && File_Spec[start] != ':'; start--);

   /* Extract the file name and extension from the file specification. */

   if ((result = (start != -1 && length - start < Size) ? strcpy(File_Name_And_Extension, &(File_Spec[start + 1])) : NULL) == NULL) {

      File_Name_And_Extension[0] = '\0';

   }

   return (result);

}
