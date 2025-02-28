/* File        : DEBUG2.C
   Module      : DEBUG
   System      : None
   Description : A method for DEBUG specific data to an open stream.
   Modified    : 08/09/90 DWP Created.
   Notes       :
*/

#include <dos.h>

#include "debug0.h"

/* Procedure   : _DEBUG_Write_Output
   Description : Writes the date, time, file, and line number information to the specified stream.
   Inputs      : Type       = The type of detail line being printed.
                 File       = The file which resulted in a call to the DEBUG module.
                 Line       = The source code line in the above file that invoked the DEBUG module.
                 Error_Code = The error code to display.
                 Fp         = The stream to write to.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 08/09/90 DWP Initial coding.
   Notes       :
*/
void _DEBUG_Write_Output(DEBUG_REPORT_TYPES Type, char * File, int Line, int Error_Code, FILE *Fp) {

   struct date         cd;
   struct time         ct;
   static unsigned int counter1 = 0, counter2 = 0, counter3 = 0;

   getdate(&cd);
   gettime(&ct);
   fprintf(Fp, "\n<<%5u>> Fn: %-12.12s  Ln: %5d  Er: %5d Dt: %02u/%02u/%04u  Tm: %02u:%02u:%02u\n", (Type == DEBUG_HEAP_ALLOCATION) ? counter1++ : ((Type == DEBUG_OPEN_STREAM ) ? counter2++ : counter3++), File, Line, Error_Code, cd.da_mon, cd.da_day, cd.da_year, ct.ti_hour, ct.ti_min, ct.ti_sec);
}
