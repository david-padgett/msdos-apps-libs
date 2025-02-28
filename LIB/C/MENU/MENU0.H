/* File        : MENU0.H
   Module      : MENU
   System      : None
   Description : The implementation header file for the MENU module.
   Modified    : 03/05/92 DWP Created.
   Notes       :
*/

#include "List\list.h"
#include "menu.h"

typedef enum __MENU_STATUS_CODES {MENU_ACTIVE, MENU_INACTIVE} _MENU_STATUS_CODES;
typedef enum __MENU_OPTION_DISPLAY_TYPES {MENU_NORMALIZE_TEXT, MENU_HIGHLIGHT_TEXT} _MENU_OPTION_DISPLAY_TYPES;

typedef struct __MENU{

   LIST               Option_List;
   CARDINAL_16        Option_Row;
   CARDINAL_16        Option_Column;
   CARDINAL_16        Option_Primary_Color;
   CARDINAL_16        Option_Secondary_Color;
   CARDINAL_16        Option_Highlight_Primary_Color;
   CARDINAL_16        Option_Highlight_Secondary_Color;

   LIST               Description_List;
   CARDINAL_16        Description_Row;
   CARDINAL_16        Description_Column;
   CARDINAL_16        Description_Primary_Color;
   CARDINAL_16        Description_Secondary_Color;

   TEXT               Text_Descriptor;

   CARDINAL_16        Current_Option;
   _MENU_STATUS_CODES Status;
   LIST               Option_Screen_Coordinates_List;

} _MENU;

typedef struct __MENU_OPTION_COORDINATES {

   INTEGER_16 Row;
   INTEGER_16 Column;

} _MENU_OPTION_COORDINATES;

/* Procedures and Functions. */

int _MENU_Construct_List(char * List_Values, LIST * Option_List);
int _MENU_Display_Menu(_MENU * Menu_Descriptor);
int _MENU_Display_Option(_MENU * Menu_Descriptor, CARDINAL_16 Option, _MENU_OPTION_DISPLAY_TYPES Display_Type);
int _MENU_Construct_Coordinates_List(_MENU * Menu_Descriptor);
