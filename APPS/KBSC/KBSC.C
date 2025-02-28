/* File        : KBSC.C
   Module      : KBSC
   System      : KBSC
   Description : This program graphically displays keystroke information, including keyboard scan code information.
   Modified    : 07/03/91 DWP Created.
   Notes       :
*/

#include <conio.h>
#include <dos.h>
#include <stdio.h>

#include "cursor\cursor.h"
#include "kb\kb.h"

/* Type Definitions. */

typedef struct _KBSC_Coordinates_Record {

   int  X_Position;
   int  Y_Position;
   char Label[20];
   char Description[20];

} KBSC_Coordinates_Record;

/* Global variables. */

BOOLEAN exit_flag;

char KBSC_Screen[] = "                                                                Caps Num  Scroll\r"
                     "ษออหออหออหออป  ษออหออหออหออป  ษอออหอออหอออหอออปษออออหออออหออออป Lock Lock Lock\r\n"
                     "บF1บF2บF3บF4บ  บF5บF6บF7บF8บ  บF9 บF10บF11บF12บบPrScบScrlบPausบ\r\n"
                     "ศออสออสออสออผ  ศออสออสออสออผ  ศอออสอออสอออสอออผศออออสออออสออออผ\r\n"
                     "ษอออหออหออหออหออหออหออหออหออหออหออหออหออหอออออปษออออหออออหออออปษอออหอออหอออหอออป\r"
                     "บESCบ 1บ 2บ 3บ 4บ 5บ 6บ 7บ 8บ 9บ 0บ -บ =บBckSpบบIns บHomeบPgUpบบNumบ / บ * บ - บ\r"
                     "ฬอออสหอสหอสหอสหอสหอสหอสหอสหอสหอสหอสหอสหอสหออออนฬออออฮออออฮออออนฬอออฮอออฮอออฮอออน\r"
                     "บTAB บ  บ  บ  บ  บ  บ  บ  บ  บ  บ  บ [บ ]บ    บบDel บEnd บPgDnบบ   บ   บ   บ   บ\r"
                     "ฬออออสหอสหอสหอสหอสหอสหอสหอสหอสหอสหอสหอสหอผ    บศออออสออออสออออผฬอออฮอออฮอออน + บ\r"
                     "บCTRL บ  บ  บ  บ  บ  บ  บ  บ  บ  บ ;บ 'บ ENTERบ                บ   บ   บ   บ   บ\r"
                     "ฬอออออสหอสหอสหอสหอสหอสหอสหอสหอสหอสหอสหอสอออหออน     ษออออป     ฬอออฮอออฮอออฮอออน\r"
                     "บSHIFT บ  บ  บ  บ  บ  บ  บ  บ ,บ .บ /บSHIFTบ \\บ     บ \x18  บ     บ   บ   บ   บ E บ\r"
                     "ฬอออออหสอหสออสอหสออสออสออสออสออสออฮออสออหออสออนษออออฮออออฮออออปฬอออสอออฮอออน N บ\r"
                     "บ ALT บ `บ Capsบ      SPACE       บCTRL บ ALT บบ \x1b  บ \x19  บ \x1a  บบ       บ   บ T บ\r"
                     "ศอออออสออสอออออสออออออออออออออออออสอออออสอออออผศออออสออออสออออผศอออออออสอออสอออผ\r";

KBSC_Coordinates_Record Enhanced_Keys[] = {{49, 15, "Ins ", "Insert"},
                                           {49, 17, "Del ", "Delete"},
                                           {54, 15, "Home", "Home"},
                                           {54, 17, "End ", "End"},
                                           {59, 15, "PgUp", "Page Up"},
                                           {59, 17, "PgDn", "Page Down"},
                                           {54, 21, " \x18  ", "Up Arrow"},
                                           {49, 23, " \x1b  ", "Left Arrow"},
                                           {54, 23, " \x19  ", "Down Arrow"},
                                           {59, 23, " \x1a  ", "Right Arrow"}};

KBSC_Coordinates_Record Function_Keys[] = {{ 2, 12, "F1",  "Function key 1"},
                                           { 5, 12, "F2",  "Function key 2"},
                                           { 8, 12, "F3",  "Function key 3"},
                                           {11, 12, "F4",  "Function key 4"},
                                           {17, 12, "F5",  "Function key 5"},
                                           {20, 12, "F6",  "Function key 6"},
                                           {23, 12, "F7",  "Function key 7"},
                                           {26, 12, "F8",  "Function key 8"},
                                           {32, 12, "F9 ", "Function key 9"},
                                           {36, 12, "F10", "Function key 10"},
                                           {40, 12, "F11", "Function key 11"},
                                           {44, 12, "F12", "Function key 12"}};

KBSC_Coordinates_Record Numeric_Keypad_Keys[] = {{65, 23, " 0     ", "0"},
                                                 {65, 21, " 1 ",     "1"},
                                                 {69, 21, " 2 ",     "2"},
                                                 {73, 21, " 3 ",     "3"},
                                                 {65, 19, " 4 ",     "4"},
                                                 {69, 19, " 5 ",     "5"},
                                                 {73, 19, " 6 ",     "6"},
                                                 {65, 17, " 7 ",     "7"},
                                                 {69, 17, " 8 ",     "8"},
                                                 {73, 17, " 9 ",     "9"},
                                                 {73, 23, " . ",     "Period"},
                                                 {65, 23, " Ins   ", "Insert"},
                                                 {65, 21, "End",     "End"},
                                                 {69, 21, " \x19 ",  "Down Arrow"},
                                                 {73, 21, "PgD",     "Page Down"},
                                                 {65, 19, " \x1b ",  "Left Arrow"},
                                                 {69, 19, "   ",     "Center/Not labeled"},
                                                 {73, 19, " \x1a ",  "Right Arrow"},
                                                 {65, 17, "Hom",     "Home"},
                                                 {69, 17, " \x18 ",  "Up Arrow"},
                                                 {73, 17, "PgU",     "Page Up"},
                                                 {73, 23, "Del",     "Delete"},
                                                 {69, 15, " / ",     "Forward Slash"},
                                                 {73, 15, " * ",     "Star"},
                                                 {77, 15, " - ",     "Minus Sign"},
                                                 {77, 17, "   \0+",  "Plus Sign"},
                                                 {77, 21, " E \0N\0\0T", "Enter"}};

KBSC_Coordinates_Record ASCII_Keys[] = {{ 0,  0, "",                   ""},
                                        { 8, 19, " A",                 "Control-A"},
                                        {21, 21, " B",                 "Control-B"},
                                        {15, 21, " C",                 "Control-C"},
                                        {14, 19, " D",                 "Control-D"},
                                        {13, 17, " E",                 "Control-E"},
                                        {17, 19, " F",                 "Control-F"},
                                        {20, 19, " G",                 "Control-G"},
                                        {23, 19, " H",                 "Control-H"},
                                        {28, 17, " I",                 "Control-I"},
                                        {26, 19, " J",                 "Control-J"},
                                        {29, 19, " K",                 "Control-K"},
                                        {32, 19, " L",                 "Control-L"},
                                        {27, 21, " M",                 "Control-M"},
                                        {24, 21, " N",                 "Control-N"},
                                        {31, 17, " O",                 "Control-O"},
                                        {34, 17, " P",                 "Control-P"},
                                        { 7, 17, " Q",                 "Control-Q"},
                                        {16, 17, " R",                 "Control-R"},
                                        {11, 19, " S",                 "Control-S"},
                                        {19, 17, " T",                 "Control-T"},
                                        {25, 17, " U",                 "Control-U"},
                                        {18, 21, " V",                 "Control-V"},
                                        {10, 17, " W",                 "Control-W"},
                                        {12, 21, " X",                 "Control-X"},
                                        {22, 17, " Y",                 "Control-Y"},
                                        { 9, 21, " Z",                 "Control-Z"},
                                        { 0,  0, "",                   ""},
                                        { 0,  0, "",                   ""},
                                        { 0,  0, "",                   ""},
                                        { 0,  0, "",                   ""},
                                        { 0,  0, "",                   ""},
                                        {17, 23, "      SPACE       ", "Space Bar"},
                                        { 6, 15, " 1",                 "Exclamation point"},
                                        {38, 19, " '",                 "Double quotes"},
                                        {12, 15, " 3",                 "Number sign"},
                                        {15, 15, " 4",                 "Dollar sign"},
                                        {18, 15, " 5",                 "Percent sign"},
                                        {24, 15, " 7",                 "Ampersand"},
                                        {38, 19, " '",                 "Single quote"},
                                        {30, 15, " 9",                 "Open parentheses"},
                                        {33, 15, " 0",                 "Close parentheses"},
                                        {27, 15, " 8",                 "Star"},
                                        {39, 15, " =",                 "Plus sign"},
                                        {30, 21, " ,",                 "Comma"},
                                        {36, 15, " -",                 "Minus sign"},
                                        {33, 21, " .",                 "Period"},
                                        {36, 21, " /",                 "Forward slash"},
                                        {33, 15, " 0",                 "0"},
                                        { 6, 15, " 1",                 "1"},
                                        { 9, 15, " 2",                 "2"},
                                        {12, 15, " 3",                 "3"},
                                        {15, 15, " 4",                 "4"},
                                        {18, 15, " 5",                 "5"},
                                        {21, 15, " 6",                 "6"},
                                        {24, 15, " 7",                 "7"},
                                        {27, 15, " 8",                 "8"},
                                        {30, 15, " 9",                 "9"},
                                        {35, 19, " ;",                 "Colon"},
                                        {35, 19, " ;",                 "Semi-colon"},
                                        {30, 21, " ,",                 "Less than sign"},
                                        {39, 15, " =",                 "Equal sign"},
                                        {33, 21, " .",                 "Greater than sign"},
                                        {36, 21, " /",                 "Question mark"},
                                        { 9, 15, " 2",                 "At sign"},
                                        { 8, 19, " A",                 "A"},
                                        {21, 21, " B",                 "B"},
                                        {15, 21, " C",                 "C"},
                                        {14, 19, " D",                 "D"},
                                        {13, 17, " E",                 "E"},
                                        {17, 19, " F",                 "F"},
                                        {20, 19, " G",                 "G"},
                                        {23, 19, " H",                 "H"},
                                        {28, 17, " I",                 "I"},
                                        {26, 19, " J",                 "J"},
                                        {29, 19, " K",                 "K"},
                                        {32, 19, " L",                 "L"},
                                        {27, 21, " M",                 "M"},
                                        {24, 21, " N",                 "N"},
                                        {31, 17, " O",                 "O"},
                                        {34, 17, " P",                 "P"},
                                        { 7, 17, " Q",                 "Q"},
                                        {16, 17, " R",                 "R"},
                                        {11, 19, " S",                 "S"},
                                        {19, 17, " T",                 "T"},
                                        {25, 17, " U",                 "U"},
                                        {18, 21, " V",                 "V"},
                                        {10, 17, " W",                 "W"},
                                        {12, 21, " X",                 "X"},
                                        {22, 17, " Y",                 "Y"},
                                        { 9, 21, " Z",                 "Z"},
                                        {37, 17, " [",                 "Open bracket"},
                                        {45, 21, " \\",                "Backslash"},
                                        {40, 17, " ]",                 "Close bracket"},
                                        {21, 15, " 6",                 "Carat"},
                                        {36, 15, " -",                 "Underline"},
                                        { 8, 23, " `",                 "Open quote"},
                                        { 8, 19, " a",                 "a"},
                                        {21, 21, " b",                 "b"},
                                        {15, 21, " c",                 "c"},
                                        {14, 19, " d",                 "d"},
                                        {13, 17, " e",                 "e"},
                                        {17, 19, " f",                 "f"},
                                        {20, 19, " g",                 "g"},
                                        {23, 19, " h",                 "h"},
                                        {28, 17, " i",                 "i"},
                                        {26, 19, " j",                 "j"},
                                        {29, 19, " k",                 "k"},
                                        {32, 19, " l",                 "l"},
                                        {27, 21, " m",                 "m"},
                                        {24, 21, " n",                 "n"},
                                        {31, 17, " o",                 "o"},
                                        {34, 17, " p",                 "p"},
                                        { 7, 17, " q",                 "q"},
                                        {16, 17, " r",                 "r"},
                                        {11, 19, " s",                 "s"},
                                        {19, 17, " t",                 "t"},
                                        {25, 17, " u",                 "u"},
                                        {18, 21, " v",                 "v"},
                                        {10, 17, " w",                 "w"},
                                        {12, 21, " x",                 "x"},
                                        {22, 17, " y",                 "y"},
                                        { 9, 21, " z",                 "z"},
                                        {37, 17, " [",                 "Open brace"},
                                        {45, 21, " \\",                "Vertical line"},
                                        {40, 17, " ]",                 "Close brace"},
                                        { 8, 23, " `",                 "Tilde"}};

KBSC_Coordinates_Record Control_Keys[] = {{ 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          {42, 15, "BckSp",  "Back Space"},
                                          { 2, 17, "TAB ",   "Tab"},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          {41, 19, " ENTER", "Enter/Return"},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 2, 15, "ESC",    "Escape"},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""},
                                          { 0,  0, "",       ""}};

/* Procedures and Functions. */

/* Procedure   : KBSC_Update_Numeric_Keypad_Keys
   Description : Displays the key labels for the numeric keypad.  The state of the num lock key affects what is displayed.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/05/91 DWP Initial coding.
   Notes       :
*/

void KBSC_Update_Numeric_Keypad_Keys(void) {

   int start, end;

   textattr(LIGHTCYAN);

   for (start = ((KB_Shift_Status() & (1 << 5)) != 0) ? 0 : 11, end = start + 11; start < end; start++) {

      gotoxy(Numeric_Keypad_Keys[start].X_Position, Numeric_Keypad_Keys[start].Y_Position);
      cprintf(Numeric_Keypad_Keys[start].Label);

   }

}

/* Procedure   : KBSC_Update_Main_Keypad_Keys
   Description : Displays the key labels for the main keyboard.  The state of the caps lock key affects what is displayed.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/05/91 DWP Initial coding.
   Notes       :
*/

void KBSC_Update_Main_Keypad_Keys(void) {

   int start, end;

   textattr(LIGHTCYAN);

   for (start = ((KB_Shift_Status() & (1 << 6)) != 0) ? 65 : 97, end = start + 26; start < end; start++) {

      gotoxy(ASCII_Keys[start].X_Position, ASCII_Keys[start].Y_Position);
      cprintf(ASCII_Keys[start].Label);

   }

}

/* Procedure   : KBSC_Draw_Screen
   Description : Clears and then draws the KBSC screen.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/

void KBSC_Draw_Screen(void) {

   int i;

   textattr((BLACK << 4) | LIGHTGRAY);
   clrscr();

   /* Print the first and last row. */

   textattr((CYAN << 4) | LIGHTCYAN);
   gotoxy(1, 1);
   cprintf(" KeyBoard Scan Code Interpreter V1.0, " COMPILE_DATE ", Copyright (c) 1991 by CSFX  ");
   gotoxy(1, 25);
   clreol();
   gotoxy(28, 25);
   cprintf("Press Ctrl-Break to exit.");

   /* Draw the line the spans the entire length of row 9. */

   textattr((BLACK << 4) | LIGHTCYAN);
   gotoxy(1, 9);

   for (i = 1; i <= 80; i++) {

      putch('อ');

   }

   /* Draw the keyboard. */

   gotoxy(1, 10);

   for (i = 0; KBSC_Screen[i] != '\0'; i++) {

      if ((unsigned int) KBSC_Screen[i] < (unsigned int) '\x7f') {

         textattr((BLACK << 4) | LIGHTCYAN);
         putch(KBSC_Screen[i]);
         textattr((BLACK << 4) | CYAN);

      }
      else {

         putch(KBSC_Screen[i]);

      }

   }

   KBSC_Update_Numeric_Keypad_Keys();
   KBSC_Update_Main_Keypad_Keys();

   /* Print the remaining portion of the screen. */

   textattr((BLACK << 4) | LIGHTCYAN);
   gotoxy(39, 3);
   cprintf("Hex Dec  Binary");
   gotoxy(26, 4);
   cprintf("Scan Code  =");
   gotoxy(26, 5);
   cprintf("ASCII Code =");
   gotoxy(26, 6);
   cprintf("Name%7s=", "");

   /* Display the type of keyboard in use. */

   gotoxy(29, 8);
   cprintf("Keyboard Type - %s", (KB_Enhanced_Keyboard_Present()) ? "Enhanced" : "Standard");

}

/* Procedure   : KBSC_Update_LEDs
   Description : Updates the keyboard LED display portion of the screen.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/

void KBSC_Update_LEDs(void) {

   WORD_16 status_word;
   int     i;

   textattr(LIGHTCYAN);
   status_word = KB_Shift_Status();

   for (i = 0; i < 3; i++) {

      gotoxy(76 - (i * 5), 12);
      putch(((status_word & (1 << (i + 4))) == (1 << (i + 4))) ? 'Û' : 'ฐ');

   }

}

/* Procedure   : KBSC_Update_Shift_Keys
   Description : Updates the keyboard shift, control, and alternate keys portion of the screen.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/

void KBSC_Update_Shift_Keys(void) {

   WORD_16 shift_status_word;
   BOOLEAN caps_lock_flag, num_lock_flag;

   shift_status_word = KB_Shift_Status();

   gotoxy(2, 21);
   textattr(((shift_status_word & 0x0002) == 0x0002) ? (7 << 4) : LIGHTCYAN);
   cprintf("SHIFT ");

   gotoxy(39, 21);
   textattr(((shift_status_word & 0x0001) == 0x0001) ? (7 << 4) : LIGHTCYAN);
   cprintf("SHIFT");

   gotoxy(2, 19);
   textattr(((shift_status_word & 0x0100) == 0x0100) ? (7 << 4) : LIGHTCYAN);
   cprintf("CRTL ");

   gotoxy(36, 23);
   textattr(((shift_status_word & 0x0400) == 0x0400) ? (7 << 4) : LIGHTCYAN);
   cprintf("CTRL ");

   gotoxy(2, 23);
   textattr(((shift_status_word & 0x0200) == 0x0200) ? (7 << 4) : LIGHTCYAN);
   cprintf(" ALT ");

   gotoxy(42, 23);
   textattr(((shift_status_word & 0x0800) == 0x0800) ? (7 << 4) : LIGHTCYAN);
   cprintf(" ALT ");

   caps_lock_flag = ((shift_status_word & 0x4000) == 0x4000) ? TRUE : FALSE;
   gotoxy(11, 23);
   textattr((caps_lock_flag) ? (7 << 4) : LIGHTCYAN);
   cprintf(" Caps");

   if (caps_lock_flag) {

      KBSC_Update_Main_Keypad_Keys();

   }

   num_lock_flag = ((shift_status_word & 0x2000) == 0x2000) ? TRUE : FALSE;
   gotoxy(65, 15);
   textattr((num_lock_flag) ? (7 << 4) : LIGHTCYAN);
   cprintf("Num");

   if (num_lock_flag) {

      KBSC_Update_Numeric_Keypad_Keys();

   }

   gotoxy(54, 12);
   textattr(((shift_status_word & 0x1000) == 0x1000) ? (7 << 4) : LIGHTCYAN);
   cprintf("Scrl");

   gotoxy(49, 12);
   textattr(((shift_status_word & 0x8000) == 0x8000) ? (7 << 4) : LIGHTCYAN);
   cprintf("PrSc");

}

/* Function    : KBSC_Display_Label
   Description : Displays the specified label, if possible.
   Inputs      : Coordinates_List           = The list of coordinates to choose from.
                 Coordinates_Of_Label       = The label to display.
                 Coordinates_Of_Description = The description to display.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : TRUE if the label was displayed, FALSE otherwise.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       : 1) Separate label and description coordinates are required so that shifted values on the numeric keypad or main
                    keyboard will show the appropriate label and description.  For shifted values, the description and keyboard
                    label are never the same.
*/

BOOLEAN KBSC_Display_Label(KBSC_Coordinates_Record * Coordinates_List, int Coordinates_Of_Label, int Coordinates_Of_Description) {

   BOOLEAN result;

   /* Exit if an invalid label has been specified. */

   if (Coordinates_Of_Label == -1) {

      result = FALSE;

   }
   else {

      /* Display the label. */

      gotoxy(Coordinates_List[Coordinates_Of_Label].X_Position, Coordinates_List[Coordinates_Of_Label].Y_Position);
      cprintf(Coordinates_List[Coordinates_Of_Label].Label);

      /* Display the description.  The description may not necessarily match the label. */

      textattr(LIGHTCYAN);
      gotoxy(40, 6);
      cprintf("%-20s", Coordinates_List[Coordinates_Of_Description].Description);
      result = TRUE;

   }

   return (result);

}

/* Function    : KBSC_Update_Numeric_Keypad_Region
   Description : Updates the numeric keypad area of the keyboard, if possible.
   Inputs      : Key = The key to process.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value of TRUE if the key was successfully processed, FALSE otherwise.
   Modified    : 07/05/91 DWP Initial coding.
   Notes       :
*/

BOOLEAN KBSC_Update_Numeric_Keypad_Region(CARDINAL_16 Key) {

   int     i, coordinates_of_label = -1, coordinates_of_description;
   BOOLEAN result;

   /* Determine if the key being processed is a numeric keypad key, if so, then properly initialize the coordinates of the label. */

   switch (Key) {

      case KB_INS :
      case KB_CTRL_INS :

         coordinates_of_label = 11;
         break;

      case KB_END :
      case KB_CTRL_END :

         coordinates_of_label = 12;
         break;

      case KB_DOWN :
      case KB_CTRL_DOWN :

         coordinates_of_label = 13;
         break;

      case KB_PGDN :
      case KB_CTRL_PGDN :

         coordinates_of_label = 14;
         break;

      case KB_LEFT :
      case KB_CTRL_LEFT :

         coordinates_of_label = 15;
         break;

      case KB_CENTER :
      case KB_CTRL_CENTER :

         coordinates_of_label = 16;
         break;

      case KB_RIGHT :
      case KB_CTRL_RIGHT :

         coordinates_of_label = 17;
         break;

      case KB_HOME :
      case KB_CTRL_HOME :

         coordinates_of_label = 18;
         break;

      case KB_UP :
      case KB_CTRL_UP :

         coordinates_of_label = 19;
         break;

      case KB_PGUP :
      case KB_CTRL_PGUP :

         coordinates_of_label = 20;
         break;

      case KB_DEL :
      case KB_CTRL_DEL :

         coordinates_of_label = 21;
         break;

      case KB_GRAY_FORWARD_SLASH :
      case KB_CTRL_GRAY_FORWARD_SLASH :
      case KB_ALT_GRAY_FORWARD_SLASH :

         coordinates_of_label = 22;
         break;

      case KB_GRAY_STAR :
      case KB_CTRL_GRAY_STAR :
      case KB_ALT_GRAY_STAR :

         coordinates_of_label = 23;
         break;

      case KB_GRAY_MINUS :
      case KB_CTRL_GRAY_MINUS :
      case KB_ALT_GRAY_MINUS :

         coordinates_of_label = 24;
         break;

      case KB_GRAY_PLUS :
      case KB_CTRL_GRAY_PLUS :
      case KB_ALT_GRAY_PLUS :

         coordinates_of_label = 25;

         /* Color the portion of the GRAY PLUS key region that is not included in the coordinates record. */

         for (i = 0; i < 3; i++) {

            gotoxy(Numeric_Keypad_Keys[coordinates_of_label].X_Position, Numeric_Keypad_Keys[coordinates_of_label].Y_Position + i);
            cprintf(" %c ", Numeric_Keypad_Keys[coordinates_of_label].Label[i * 3 + 1]);

         }

         break;

      case KB_GRAY_ENTER :
      case KB_CTRL_GRAY_ENTER :
      case KB_ALT_GRAY_ENTER :

         coordinates_of_label = 26;

         /* Color the portion of the GRAY ENTER key region that is not included in the coordinates record. */

         for (i = 0; i < 3; i++) {

            gotoxy(Numeric_Keypad_Keys[coordinates_of_label].X_Position, Numeric_Keypad_Keys[coordinates_of_label].Y_Position + i);
            cprintf(" %c ", Numeric_Keypad_Keys[coordinates_of_label].Label[i * 3 + 1]);

         }

         break;

         /* Determine if the key is one of the numeric keypad digit/decimal point keys. */

      default :

         if (Key / 256 >= '\x47' && Key / 256 <= '\x53') {

            if (Key % 256 == '.') {

               coordinates_of_label = 10;

            }
            else {

               if (Key % 256 >= '0' && Key % 256 <= '9') {

                  coordinates_of_label = (Key % 256) - '0';

               }

            }

         }

   }

   /* Display the label and description of the key, if possible. */

   if (coordinates_of_label != -1) {

      coordinates_of_description = coordinates_of_label;

      if ((KB_Shift_Status() & (1 << 5)) != 0 && coordinates_of_label > 10) {

         coordinates_of_label -= 11;

      }
      else {

         if ((KB_Shift_Status() & (1 << 5)) == 0 && coordinates_of_label < 11) {

            coordinates_of_label += 11;

         }

      }

   }

   result = KBSC_Display_Label(Numeric_Keypad_Keys, coordinates_of_label, coordinates_of_description);

   return (result);

}

/* Function    : KBSC_Update_Enhanced_Key_Region
   Description : Updates the enhanced key area of the keyboard, if possible.
   Inputs      : Key = The key to process.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value of TRUE if the key was successfully processed, FALSE otherwise.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/

BOOLEAN KBSC_Update_Enhanced_Key_Region(CARDINAL_16 Key) {

   int     coordinates_of_label = -1;
   BOOLEAN result;

   /* Determine if the key being processed is an enhanced key, if so, properly initialize the coordinates of the label. */

   switch (Key) {

      case KB_GRAY_INS :
      case KB_CTRL_GRAY_INS :
      case KB_ALT_GRAY_INS :

         coordinates_of_label = 0;
         break;

      case KB_GRAY_DEL :
      case KB_CTRL_GRAY_DEL :
      case KB_ALT_GRAY_DEL :

         coordinates_of_label = 1;
         break;

      case KB_GRAY_HOME :
      case KB_CTRL_GRAY_HOME :
      case KB_ALT_GRAY_HOME :

         coordinates_of_label = 2;
         break;

      case KB_GRAY_END :
      case KB_CTRL_GRAY_END :
      case KB_ALT_GRAY_END :

         coordinates_of_label = 3;
         break;

      case KB_GRAY_PGUP :
      case KB_CTRL_GRAY_PGUP :
      case KB_ALT_GRAY_PGUP :

         coordinates_of_label = 4;
         break;

      case KB_GRAY_PGDN :
      case KB_CTRL_GRAY_PGDN :
      case KB_ALT_GRAY_PGDN :

         coordinates_of_label = 5;
         break;

      case KB_GRAY_UP :
      case KB_CTRL_GRAY_UP :
      case KB_ALT_GRAY_UP :

         coordinates_of_label = 6;
         break;

      case KB_GRAY_LEFT :
      case KB_CTRL_GRAY_LEFT :
      case KB_ALT_GRAY_LEFT :

         coordinates_of_label = 7;
         break;

      case KB_GRAY_DOWN :
      case KB_CTRL_GRAY_DOWN :
      case KB_ALT_GRAY_DOWN :

         coordinates_of_label = 8;
         break;

      case KB_GRAY_RIGHT :
      case KB_CTRL_GRAY_RIGHT :
      case KB_ALT_GRAY_RIGHT :

         coordinates_of_label = 9;
         break;

   }

   /* Display the label and description of the key, if possible. */

   result = KBSC_Display_Label(Enhanced_Keys, coordinates_of_label, coordinates_of_label);

   return (result);

}

/* Function    : KBSC_Update_Function_Key_Region
   Description : Updates the function key area of the keyboard, if possible.
   Inputs      : Key = The key to process.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value of TRUE if the key was successfully processed, FALSE otherwise.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/

BOOLEAN KBSC_Update_Function_Key_Region(CARDINAL_16 Key) {

   int     coordinates_of_label = -1;
   BOOLEAN result;

   /* Determine if the key being processed is a function key, if so, properly initialize the coordinates of the label. */

   if (Key >= KB_F1 && Key <= KB_F10) {

      coordinates_of_label = (Key - KB_F1) >> 8;

   }
   else {

      if (Key >= KB_SHIFT_F1 && Key <= KB_SHIFT_F10) {

         coordinates_of_label = (Key - KB_SHIFT_F1) >> 8;

      }
      else {

         if (Key >= KB_CTRL_F1 && Key <= KB_CTRL_F10) {

            coordinates_of_label = (Key - KB_CTRL_F1) >> 8;

         }
         else {

            if (Key >= KB_ALT_F1 && Key <= KB_ALT_F10) {

               coordinates_of_label = (Key - KB_ALT_F1) >> 8;

            }
            else {

               if (Key >= KB_F11 && Key <= KB_ALT_F12) {

                  coordinates_of_label = (((Key - KB_F11) >> 8) % 2) + 10;

               }

            }

         }

      }

   }

   /* Display the label and description of the key, if possible. */

   result = KBSC_Display_Label(Function_Keys, coordinates_of_label, coordinates_of_label);

   return (result);

}

/* Function    : KBSC_Update_Main_Keyboard
   Description : Updates the typewriter key area of the screen, if possible.
   Inputs      : Key = The key to process.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : A value of TRUE if the key was successfully processed, FALSE otherwise.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/

BOOLEAN KBSC_Update_Main_Keyboard(CARDINAL_16 Key) {

   int     ch, i, coordinates_of_label = -1, coordinates_of_description;
   BOOLEAN control_keys_flag = TRUE, result;

   /* Determine if the key being processed is a main keyboard key, if so, properly initialize the coordinates of the label. */

   switch (Key) {

      case KB_BACKSPACE :
      case KB_CTRL_BACKSPACE :
      case KB_ALT_BACKSPACE :

         coordinates_of_label = 8;
         break;

      case KB_TAB :
      case KB_SHIFT_TAB :
      case KB_CTRL_TAB :
      case KB_ALT_TAB :

         coordinates_of_label = 9;
         break;

      case KB_ENTER :
      case KB_CTRL_ENTER :
      case KB_ALT_ENTER :

         coordinates_of_label = 13;

         /* Color the portion of the ENTER key region that is not included in the coordinates record. */

         for (i = 0; i < 2; i++) {

            gotoxy(Control_Keys[coordinates_of_label].X_Position + 2, Control_Keys[coordinates_of_label].Y_Position + i - 2);
            cprintf("%4s", "");

         }

          break;

      case KB_ESC :
      case KB_ALT_ESC :

         coordinates_of_label = 27;
         break;

      /* Determine if the key is one of the standard typewriter keys. */

      default :

         if ((Key >> 8) != 0) {

            ch = Key % 256;

            /* Continue only if the key is a valid typewriter key. */

            if (ch > 0x00 && ch < 0x7f) {

               coordinates_of_label = ch;
               control_keys_flag = FALSE;

            }

         }

   }

   /* Display the label and description of the key, if possible. */

   if (coordinates_of_label != -1) {

      coordinates_of_description = coordinates_of_label;

      if ((KB_Shift_Status() & (1 << 6)) != 0) {

         if (coordinates_of_label >= 97 && coordinates_of_label <= 122) {

            coordinates_of_label -= 32;

         }

      }
      else {

         if ((KB_Shift_Status() & (1 << 6)) == 0 && coordinates_of_label >= 65 && coordinates_of_label <= 90) {

            coordinates_of_label += 32;

         }

      }

   }

   result = KBSC_Display_Label((control_keys_flag) ? Control_Keys : ASCII_Keys, coordinates_of_label, coordinates_of_description);

  return (result);

}

/* Function    : KBSC_Convert_To_Binary
   Description : Converts the specified 8-bit value to its binary equivalent in formatted as a string.
   Inputs      : Value        = The 8-bit value to convert.
   Updates     : Nothing.
   Outputs     : Binary_Value = The value parameter formatted as a text string.  This parameter is undefined upon entry.
   Returns     : The 8-bit value formatted as a text string.
   Modified    : 04/16/91 DWP Initial coding.
   Notes       :
*/

char * KBSC_Convert_To_Binary(BYTE Value, char * Binary_Value) {

   int i, j;

   /* Loop until the entire byte has been processed. */

   for (i = 0, j = 1; i < 8; i++, j <<= 1) {

      Binary_Value[7 - i] = (Value & j) ? '1' : '0';

   }

   Binary_Value[8] = '\0';

   return (Binary_Value);

}

/* Procedure   : KBSC_Update_Keyboard
   Description : Updates the main keyboard portion of the display.
   Inputs      : Nothing.
   Updates     : Previous_Key = The last key pressed.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/

void KBSC_Update_Keyboard(CARDINAL_16 * Previous_Key) {

   CARDINAL_16 current_key;
   char        binary_value[9];
   int         i;

   /* Continue only if a key has been pressed. */

   if (KB_Preview() != 0) {

      /* Get the key.  Continue only if it is not identical to the previous key. */

      current_key = KB_Read();

      if (*(Previous_Key) != current_key) {

         textattr(LIGHTCYAN);

         /* Display the new key in hexidecimal, decimal, and binary. */

         gotoxy(40, 4);
         cprintf("%02X %3u %s", current_key / 256, current_key / 256, KBSC_Convert_To_Binary(current_key / 256, binary_value));
         gotoxy(40, 5);
         cprintf("%02X %3u %s", current_key % 256, current_key % 256, KBSC_Convert_To_Binary(current_key % 256, binary_value));

         /* Un-highlight the previous key, then highlight the new key. */

         for (i = 0; i < 2; i++) {

            if (!KBSC_Update_Numeric_Keypad_Region(*(Previous_Key))) {

               if (!KBSC_Update_Enhanced_Key_Region(*(Previous_Key))) {

                  if (!KBSC_Update_Function_Key_Region(*(Previous_Key))) {

                     if (!KBSC_Update_Main_Keyboard(*(Previous_Key))) {

                        textattr(LIGHTCYAN);
                        gotoxy(40, 6);
                        cprintf("Unknown Key");

                     }

                  }

               }

            }

            *(Previous_Key) = current_key;
            textattr(7 << 4);
         }

      }

   }

}

/* Procedure   : KBSC_Process_Keystrokes
   Description : Continuously updates the screen.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/

void KBSC_Process_Keystrokes(void) {

   CARDINAL_16 previous_key = 0;

   /* Loop continuously until Control-Break is pressed. */

   for (exit_flag = FALSE; !exit_flag;) {

      KBSC_Update_LEDs();
      KBSC_Update_Shift_Keys();
      KBSC_Update_Keyboard(&previous_key);

   }

}

/* Function    : KBSC_Ctrl_Break_Handler
   Description : This routine is meant for use with ctrlbrk().  It allows the KBSC to exit to DOS when Ctrl-Break is pressed.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of 1.
   Modified    : 04/16/91 DWP Initial coding.
   Notes       :
*/

void interrupt KBSC_Ctrl_Break_Handler(void) {

   exit_flag = TRUE;

}

/* Procedure   : KBSC_Main
   Description : The entry point to the KBSC module.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/

void KBSC_Main(void) {

   void interrupt (*int_1bh)(void);

   /* Install a new Control-Break handler. */

   int_1bh = getvect(0x1b);
   setvect(0x1b, KBSC_Ctrl_Break_Handler);

   CURSOR_Off();
   KBSC_Draw_Screen();
   KBSC_Process_Keystrokes();
   CURSOR_On();

   /* Restore the Control-Break vector and exit. */

   setvect(0x1b, int_1bh);
   textattr(LIGHTGRAY);
   gotoxy(1, 25);
   putch(' ');

}

/* Function    : main
   Description : The entry point for the KBSC program.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns a value of zero.
   Modified    : 07/03/91 DWP Initial coding.
   Notes       :
*/
int main(void) {

   KBSC_Main();

   return (0);

}