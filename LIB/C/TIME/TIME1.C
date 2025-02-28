/* File        : TIME1.C
   Module      : TIME
   System      : None
   Description : A method for determining the difference between two times.
   Modified    : 08/01/90 DWP Created from "TIME.C".
   Notes       :
*/

#include "time.h"

/* Function    : TIME_Elapsed
   Description : Calculates the elapsed time between two reads of the system clock.
   Inputs      : Time_1 = The initial, or starting, time.
                 Time_2 = The final, or ending, time.
   Updates     : Nothing.
   Outputs     : Elapsed_Time = The difference between Time_1 and Time_2.
   Returns     : Number of hundredths of seconds that have passed.
   Modified    : 02/07/90 DWP Initial Coding.
   Notes       :
*/

unsigned long TIME_Elapsed(struct time * Time_1, struct time * Time_2, struct time * Elapsed_Time) {

   int hour, min, sec, hund;

   hour = Time_2->ti_hour - Time_1->ti_hour;
   min  = Time_2->ti_min  - Time_1->ti_min;
   sec  = Time_2->ti_sec  - Time_1->ti_sec;
   hund = Time_2->ti_hund - Time_1->ti_hund;

   Elapsed_Time->ti_hund = (hund < 0) ? hund + 100 + sec - (sec--) : hund;
   Elapsed_Time->ti_sec  = (sec < 0)  ? sec + 60 + min - (min--)   : sec;
   Elapsed_Time->ti_min  = (min < 0)  ? min + 60 + hour - (hour--) : min;
   Elapsed_Time->ti_hour = (hour < 0) ? hour + 24                  : hour;

   return (((unsigned long) Elapsed_Time->ti_hund) + ((unsigned long) Elapsed_Time->ti_sec * 100) + ((unsigned long )Elapsed_Time->ti_min * 100 * 60) + ((unsigned long) Elapsed_Time->ti_hour * 100 * 60 * 60));

}
