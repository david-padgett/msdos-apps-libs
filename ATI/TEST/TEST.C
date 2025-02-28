
#include <dos.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kb\kb.h"

int main(int argc, char * argv[]) {

   unsigned int x;
   unsigned int base = 0x300;
   unsigned int monitors = 8;
   unsigned int outputValue = 0;
   char         str[80];
   char         tempStr[80];
   BOOLEAN      pause = FALSE;
   BOOLEAN      exitFlag = FALSE;
   BOOLEAN      inputOnly[8];

   sprintf(tempStr, "%d %s\n", argc, argv[1]);

   for (x = 0; x < sizeof(inputOnly); x++) {
      inputOnly[x] = TRUE;
   }

   while (!exitFlag) {
      if (KB_Preview() != 0) {
         switch (KB_Preview()) {
            case KB_F1 :
               inputOnly[0] = !inputOnly[0];
               break;
            case KB_F2 :
               inputOnly[1] = !inputOnly[1];
               break;
            case KB_F3 :
               inputOnly[2] = !inputOnly[2];
               break;
            case KB_F4 :
               inputOnly[3] = !inputOnly[3];
               break;
            case KB_F5 :
               inputOnly[4] = !inputOnly[4];
               break;
            case KB_F6 :
               inputOnly[5] = !inputOnly[5];
               break;
            case KB_F7 :
               inputOnly[6] = !inputOnly[6];
               break;
            case KB_F8 :
               inputOnly[7] = !inputOnly[7];
               break;
            case KB_F11 :
               monitors = (monitors == 1) ? 8 : monitors - 1;
               break;
            case KB_F12 :
               monitors = (monitors == 8) ? 1 : monitors + 1;
               break;
            case KB_TAB :
               outputValue = (outputValue == 255) ? 0 : outputValue + 1;
               break;
            case KB_SHIFT_TAB :
               outputValue = (outputValue == 0) ? 255 : outputValue - 1;
               break;
            case KB_SPACE :
               pause = !pause;
               break;
            case KB_ESC :
               exitFlag = TRUE;
               break;
            case KB_PGUP :
            case KB_GRAY_PGUP :
               base += monitors;
               break;
            case KB_PGDN :
            case KB_GRAY_PGDN :
               base -= monitors;
               break;
            default :
               break;
         }
         KB_Read();
      }

      if (!pause) {
         sprintf(str, "out=%3.3u ", outputValue);
         for (x = 0; x < sizeof(inputOnly); x++) {
            if (!inputOnly[x]) {
               strcat(str, ultoa(x, tempStr, 10));
            }
         }
         for (x = 0; x < monitors; x++) {
            if (!inputOnly[x]) {
               outportb(x + base, outputValue);
            }
            printf("%3.3x=%3.3u ", x + base, (int) inportb(x + base));
         }
         printf("%s\n", str);
      }
   }

   return (0);

}