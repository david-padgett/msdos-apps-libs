/* File        : DATE0.C
   Module      : DATE
   System      : None
   Description : Global variables for the DATE module.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#include "date.h"

char * DATE_Months_List[] = {"", "January", "February", "March",
                                 "April", "May", "June",
                                 "July", "August", "September",
                                 "October", "November", "December"};

CARDINAL_16 DATE_Days_In_Month_List[] = {0, 31, 28, 31,
                                            30, 31, 30,
                                            31, 31, 30,
                                            31, 30, 31};
