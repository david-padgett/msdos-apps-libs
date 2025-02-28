#include <conio.h>
#include <dos.h>
#include <mem.h>
#include <stdio.h>
#include <stdlib.h>

#include "kb\kb.h"

int main(void) {

   BOOLEAN       exitFlag = FALSE;
   unsigned int  chopperPortAddr = 0x302;
   unsigned int  value = 0;
   unsigned int  previousValue = 0;
   unsigned long total = 0;
   unsigned long count = 0;
   unsigned long changes = 0;
   unsigned long iterations = 0;
   struct time   currentTime;
   struct time   previousTime;

   clrscr();

   gettime(&currentTime);
   memcpy(&previousTime, &currentTime, sizeof(previousTime));

   while (currentTime.ti_sec == previousTime.ti_sec) {
      inportb(chopperPortAddr);
      gettime(&currentTime);
   }

   while (!exitFlag) {
      if (iterations <= 5) {
         iterations++;
      }
      switch (KB_Preview()) {
         case 0 :
            break;
         case KB_ESC :
            KB_Read();
            exitFlag = TRUE;
            break;
         default :
            KB_Read();
            break;
      }
      value = inportb(chopperPortAddr);
      if (value != previousValue) {
         changes++;
         previousValue = value;
      }
      gettime(&currentTime);
      if (currentTime.ti_sec != previousTime.ti_sec) {
         if (iterations > 5) {
            total += changes;
            count++;
            printf("Avg Frequency = %3.3f Instantaneous Frequency = %3.3u     \r", (float) total / (count * 2), changes / 2);
         }
         changes = 0;
         memcpy(&previousTime, &currentTime, sizeof(previousTime));
      }
   }
   return (0);
}
