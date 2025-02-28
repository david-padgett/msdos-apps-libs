/* File        : KB.H
   Module      : KB
   System      : None
   Description : The C interface header file for the KB module.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#ifndef _KB_MODULE
#define _KB_MODULE

#include "Standard\standard.h"

/* Definitions of certain keyboard scan codes.  Macros starting with KB are normal key presses, macros starting with KBS are
   shifted values, macros starting with KBC are control values, and macros starting with KBA are alternate values. */

#define KB_BACKSPACE               0x0e08
#define KB_CTRL_BACKSPACE          0x0e7f
#define KB_ALT_BACKSPACE           0x0e00

#define KB_CENTER                  0x4c00
#define KB_CTRL_CENTER             0x8f00

#define KB_DEL                     0x5300
#define KB_CTRL_DEL                0x9300
#define KB_GRAY_DEL                0x53e0
#define KB_CTRL_GRAY_DEL           0x93e0
#define KB_ALT_GRAY_DEL            0xa300

#define KB_DOWN                    0x5000
#define KB_CTRL_DOWN               0x9100
#define KB_GRAY_DOWN               0x50e0
#define KB_CTRL_GRAY_DOWN          0x91e0
#define KB_ALT_GRAY_DOWN           0xa000

#define KB_ENTER                   0x1c0d
#define KB_CTRL_ENTER              0x1c0a
#define KB_ALT_ENTER               0x1c00
#define KB_GRAY_ENTER              0xe00d
#define KB_CTRL_GRAY_ENTER         0xe00a
#define KB_ALT_GRAY_ENTER          0xa600

#define KB_END                     0x4f00
#define KB_CTRL_END                0x7500
#define KB_GRAY_END                0x4fe0
#define KB_CTRL_GRAY_END           0x75e0
#define KB_ALT_GRAY_END            0x9f00

#define KB_ESC                     0x011b
#define KB_ALT_ESC                 0x0100

#define KB_F1                      0x3b00
#define KB_SHIFT_F1                0x5400
#define KB_CTRL_F1                 0x5e00
#define KB_ALT_F1                  0x6800

#define KB_F2                      0x3c00
#define KB_SHIFT_F2                0x5500
#define KB_CTRL_F2                 0x5f00
#define KB_ALT_F2                  0x6900

#define KB_F3                      0x3d00
#define KB_SHIFT_F3                0x5600
#define KB_CTRL_F3                 0x6000
#define KB_ALT_F3                  0x6a00

#define KB_F4                      0x3e00
#define KB_SHIFT_F4                0x5700
#define KB_CTRL_F4                 0x6100
#define KB_ALT_F4                  0x6b00

#define KB_F5                      0x3f00
#define KB_SHIFT_F5                0x5800
#define KB_CTRL_F5                 0x6200
#define KB_ALT_F5                  0x6c00

#define KB_F6                      0x4000
#define KB_SHIFT_F6                0x5900
#define KB_CTRL_F6                 0x6300
#define KB_ALT_F6                  0x6d00

#define KB_F7                      0x4100
#define KB_SHIFT_F7                0x5a00
#define KB_CTRL_F7                 0x6400
#define KB_ALT_F7                  0x6e00

#define KB_F8                      0x4200
#define KB_SHIFT_F8                0x5b00
#define KB_CTRL_F8                 0x6500
#define KB_ALT_F8                  0x6f00

#define KB_F9                      0x4300
#define KB_SHIFT_F9                0x5c00
#define KB_CTRL_F9                 0x6600
#define KB_ALT_F9                  0x7000

#define KB_F10                     0x4400
#define KB_SHIFT_F10               0x5d00
#define KB_CTRL_F10                0x6700
#define KB_ALT_F10                 0x7100

#define KB_F11                     0x8500
#define KB_SHIFT_F11               0x8700
#define KB_CTRL_F11                0x8900
#define KB_ALT_F11                 0x8b00

#define KB_F12                     0x8600
#define KB_SHIFT_F12               0x8800
#define KB_CTRL_F12                0x8a00
#define KB_ALT_F12                 0x8c00

#define KB_GRAY_FORWARD_SLASH      0xe02f
#define KB_CTRL_GRAY_FORWARD_SLASH 0x9500
#define KB_ALT_GRAY_FORWARD_SLASH  0xa400

#define KB_HOME                    0x4700
#define KB_CTRL_HOME               0x7700
#define KB_GRAY_HOME               0x47e0
#define KB_CTRL_GRAY_HOME          0x77e0
#define KB_ALT_GRAY_HOME           0x9700

#define KB_INS                     0x5200
#define KB_CTRL_INS                0x9200
#define KB_GRAY_INS                0x52e0
#define KB_CTRL_GRAY_INS           0x92e0
#define KB_ALT_GRAY_INS            0xa200

#define KB_LEFT                    0x4b00
#define KB_CTRL_LEFT               0x7300
#define KB_GRAY_LEFT               0x4be0
#define KB_CTRL_GRAY_LEFT          0x73e0
#define KB_ALT_GRAY_LEFT           0x9b00

#define KB_MINUS                   0x0c2d
#define KB_GRAY_MINUS              0x4a2d
#define KB_CTRL_GRAY_MINUS         0x8e00
#define KB_ALT_GRAY_MINUS          0x4a00

#define KB_PGDN                    0x5100
#define KB_CTRL_PGDN               0x7600
#define KB_GRAY_PGDN               0x51e0
#define KB_CTRL_GRAY_PGDN          0x76e0
#define KB_ALT_GRAY_PGDN           0xa100

#define KB_PGUP                    0x4900
#define KB_CTRL_PGUP               0x8400
#define KB_GRAY_PGUP               0x49e0
#define KB_CTRL_GRAY_PGUP          0x84e0
#define KB_ALT_GRAY_PGUP           0x9900

#define KB_PLUS                    0x0d2b
#define KB_GRAY_PLUS               0x4e2B
#define KB_CTRL_GRAY_PLUS          0x9000
#define KB_ALT_GRAY_PLUS           0x4e00

#define KB_RIGHT                   0x4d00
#define KB_CTRL_RIGHT              0x7400
#define KB_GRAY_RIGHT              0x4de0
#define KB_CTRL_GRAY_RIGHT         0x74e0
#define KB_ALT_GRAY_RIGHT          0x9d00

#define KB_SPACE                   0x3920

#define KB_STAR                    0x092a
#define KB_GRAY_STAR               0x372a
#define KB_CTRL_GRAY_STAR          0x9600
#define KB_ALT_GRAY_STAR           0x3700

#define KB_TAB                     0x0f09
#define KB_SHIFT_TAB               0x0f00
#define KB_CTRL_TAB                0x9400
#define KB_ALT_TAB                 0xa500

#define KB_UP                      0x4800
#define KB_CTRL_UP                 0x8d00
#define KB_GRAY_UP                 0x48e0
#define KB_CTRL_GRAY_UP            0x8de0
#define KB_ALT_GRAY_UP             0x9800

/* Valid states and conditions for KB_modify_state(). */

typedef enum _KB_STATE_TYPES {KB_INSERT_LOCK, KB_SCROLL_LOCK, KB_NUM_LOCK, KB_CAPS_LOCK} KB_STATE_TYPES;
typedef enum _KB_CONDITION_TYPES {KB_LOCK, KB_UNLOCK, KB_TOGGLE} KB_CONDITION_TYPES;

/* Procedures and Functions. */

WORD_16 pascal KB_Read(void);
WORD_16 pascal KB_Preview(void);
WORD_16 pascal KB_Shift_Status(void);
WORD_16 pascal KB_Retrieve_Shift_Status_Word(void);
WORD_16 pascal KB_Retrieve_Status_Word(void);
BOOLEAN pascal KB_Enhanced_Keyboard_Present(void);
void           KB_Modify_State(KB_STATE_TYPES State, KB_CONDITION_TYPES Condition);

#endif
