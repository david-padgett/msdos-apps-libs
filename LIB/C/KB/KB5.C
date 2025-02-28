/* File        : KB5.C
   Module      : KB
   System      : None
   Description : Allows the Caps Lock, Num Lock, Scroll Lock, or Insert states to be altered.
   Modified    : 05/01/91 DWP Created.
   Notes       :
*/

#include <dos.h>

#include "Standard\standard.h"
#include "KB\kb.h"

/* Procedure   : KB_Modify_State
   Description : Changes the specified state to the specified condition.
   Inputs      : State     = The state to alter, [KB_CAPS_LOCK | KB_NUM_LOCK | KB_SCROLL_LOCK | KB_INSERT_LOCK].
                 Condition = The new condition for the specified state, [KB_LOCK | KB_UNLOCK | KB_TOGGLE].
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 05/01/91 DWP Initial coding.
   Notes       :
*/

void KB_Modify_State(KB_STATE_TYPES State, KB_CONDITION_TYPES Condition) {

   BYTE * keyboard_state_byte;

   keyboard_state_byte = MK_FP(0x40, 0x17);

   switch (Condition) {

      case KB_LOCK :

         * keyboard_state_byte |= (0x10 << State);
         break;

      case KB_UNLOCK :

         * keyboard_state_byte &= ~(0x10 << State);
         break;

      case KB_TOGGLE :

         KB_Modify_State(State, ((* keyboard_state_byte & (0x10 << State)) != 0) ? KB_UNLOCK : KB_LOCK);
         break;

   }

}