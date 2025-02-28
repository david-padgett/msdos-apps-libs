/* File        : MENU.H
   Module      : MENU
   System      : None
   Description : The definition header file for the MENU module.
   Modified    : 03/05/92 DWP Created.
   Notes       :
*/

#ifndef _MENU_MODULE
#define _MENU_MODULE

#include "Text\text.h"

/* Definitions. */

#define MENU_CONTROL_SEQUENCE_LENGTH (2 * sizeof(char))
#define MENU_END_OF_TEXT             "\xff\x00"
#define MENU_END_OF_OPTION           "\xff\x01"
#define MENU_VERTICAL_TAB            "\xff\x02"
#define MENU_HORIZONTAL_TAB          "\xff\x03"
#define MENU_PRIMARY_COLOR           "\xff\x04"
#define MENU_SECONDARY_COLOR         "\xff\x05"

/* Type definitions. */

typedef enum _MENU_ERROR_CODES {MENU_NOERR, MENU_NOMEM, MENU_PARAM, MENU_INTRN, MENU_EXTRN} MENU_ERROR_CODES;

typedef void * MENU;

/* Procedures and Functions. */

int MENU_Constructor(char * Option_List, CARDINAL_16 Option_Row, CARDINAL_16 Option_Column, CARDINAL_16 Option_Primary_Color, CARDINAL_16 Option_Secondary_Color, CARDINAL_16 Option_Highlight_Primary_Color, CARDINAL_16 Option_Highlight_Secondary_Color, char * Description_List, CARDINAL_16 Description_Row, CARDINAL_16 Description_Column, CARDINAL_16 Description_Primary_Color, CARDINAL_16 Description_Secondary_Color, TEXT Text_Descriptor, MENU * Menu);
int MENU_Destructor(MENU * Menu);
int MENU_Display(MENU Menu, CARDINAL_16 Selected_Option);

#endif
