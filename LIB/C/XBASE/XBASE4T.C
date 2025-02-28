/* File        : XBASE4T.C
   Module      : XBASE
   System      : None
   Description : A method for verifying the existence of a file.
   Modified    : 02/19/91 DWP Created.
*/

#include <io.h>

#include "xbase0.h"

/* Function    : XBASE_File
   Description : Determines whether or not the specified file exists.
   Expects     : file = The file to search for.
   Returns     : TRUE if the file exists, FALSE otherwise.
   Modified    : 02/19/91 DWP Initial coding.
   Notes       :
*/
BOOLEAN XBASE_File(const char *file) {

   return (access(file, 0) == 0 ? TRUE : FALSE);
}
