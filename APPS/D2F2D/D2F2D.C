/* File        : D2F2D.C
   Module      : D2F2D
   System      : D2F2D
   Description : Turns floppy and fixed disks into files and vice versa.
   Modified    : 08/28/91 DWP Created.
   Notes       : 1)
*/

#include <errno.h>

#include "standard\standard.h"

typedef enum _D2F2D_ACTION_TYPES {D2F2D_CREATE_FILE, D2F2D_CREATE_DISK, D2F2D_SAVE_DISK, D2F2D_RESTORE_DISK} D2F2D_ACTION_TYPES;

/* Function    : D2F2D_Create_File
   Description : Converts the contents of the specified disk drive to a file disk file.
   Expects     : File_Name  = The name of the file to create.
		 Disk_Drive = The drive letter of the disk drive to archive.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/28/91 DWP Initial coding.
   Notes       : 1) The parameter Disk_Drive must refer to local drives only, network drives are not allowed.
		 2) The parameter File_Name must not be located on the drive specified by the parameter Disk_Drive.
*/
int D2F2D_Create_File(char * File_Name, char Disk_Drive) {
   int result;


   return (result);
}

/* Function    : D2F2D_Create_Disk
   Description : Converts the contents of the specified file to its original form.
   Expects     : Disk_Drive = The drive letter of the disk drive to restore.
		 File_Name  = The name of the file which contains data to write to the destination disk drive.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/28/91 DWP Initial coding.
   Notes       : 1) The specified file must have been created with D2F2D_Create_File().
                 2) The specified file must not reside on the disk specified by the parameter Disk_Drive.
                 3) The destination drive specified by the parameter Disk_Drive must be identical to the disk drive from which the
                    file specified by File_Name was created.
*/
int D2F2D_Create_Disk(char Disk_Drive, char * File_Name) {
   int result;


   return (result);
}

/* Function    : D2F2D_Main
   Description : The entry point to the D2F2D module.
   Expects     : Action             = The action to perform, see D2F2D_ACTION_TYPES.
                 File_Name          = The name of the file being manipulated.
                 Disk_Drive         = The drive letter of the disk drive being manipulated.
                 UDF                = A user-defined function.  If the value of this parameter is non-NULL, then it is assumed to
                                      be a function that adheres to PASCAL-like calling conventions with the following
                                      characteristics:
                                         Expects : Data_Buffer        =
                                                   Data_Buffer_Size   = The size, in bytes, of the parameter Data_Buffer.
                                                   UDF_Parameter_List = A user-defined list of process control parameters.
                                         Returns : The value of the last error that occurred.  A value of zero indicates that no
                                                   errors occurred.  Non-zero values will cause the D2F2D module to immediately
                                                   terminate all activities.
                 UDF_Parameter_List = A list of parameters for the user-defined function.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/28/91 DWP Initial coding.
   Notes       :
*/
int D2F2D_Main(D2F2D_ACTION_TYPES Action, char * File_Name, char Disk_Drive, int pascal (*UDF)(BYTE * Data_Buffer, CARDINAL_16 Data_Buffer_Size, void * UDF_Parameter_List)) {
   int result;

   switch (Action) {

      case D2F2D_CREATE_FILE : result = D2F2D_Create_File(File_Name, Disk_Drive /*, UDF, UDF_Parameter_List*/);
			       break;

      case D2F2D_CREATE_DISK : result = D2F2D_Create_Disk(Disk_Drive, File_Name /*, UDF, UDF_Parameter_List*/);
			       break;
   }

   return (result);
}

/* Function    : main
   Description : The entry point to the D2F2D program.
   Expects     : The command line.
   Returns     : The value of the last error that occurred.  A value of zero indicates that no errors occurred.
   Modified    : 08/28/91 DWP Initial coding.
   Notes       :
*/
int main(int argc, char *argv[]) {
   int result;

   if (argc == 1) {
      printf("\nD2F2D V1.0\n\n");
      result = EINVAL;
   }
   else {





   }

   return (result);
}
