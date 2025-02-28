/* File        : BMI0.C
   Module      : GLOBALS
   System      : BMI
   Description : The global variables used in the BMI program.
   Modified    : 08/18/92 DWP Created.
   Notes       :
*/

#include <conio.h>
#include <stdio.h>

#include "bmi.h"

char *                   BMI_Help_Index_Key_List[] = {"MAINM",
                                                      "FILEM",
                                                      "EDITM",
                                                      "REPTM",
                                                      "COMMM",
                                                      "HELPM",
                                                      "LODFM",
                                                      "NEWFM",
                                                      "SAVFM",
                                                      "SVAFM",
                                                      "DELFM",
                                                      "RENFM",
                                                      "QUIFM",
                                                      "EDTEM",
                                                      "MAREM",
                                                      "CLEEM",
                                                      "DDPRM",
                                                      "ACGRM",
                                                      "SNDCM",
                                                      "RECCM",
                                                      "TERCM",
                                                      "INDHM",
                                                      "ABOHM",
                                                      "PRIHM",
                                                      ""};

char                     BMI_Function_Key_Menu_Text[] = MENU_SECONDARY_COLOR "F1"  MENU_PRIMARY_COLOR "-Help"     MENU_HORIZONTAL_TAB "\x4" MENU_END_OF_OPTION
                                                        MENU_SECONDARY_COLOR "F2"  MENU_PRIMARY_COLOR "-Load"     MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
                                                        MENU_SECONDARY_COLOR "F3"  MENU_PRIMARY_COLOR "-Save"     MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
                                                        MENU_SECONDARY_COLOR "F8"  MENU_PRIMARY_COLOR "-Terminal" MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
                                                        MENU_SECONDARY_COLOR "F9"  MENU_PRIMARY_COLOR "-Send"     MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
                                                        MENU_SECONDARY_COLOR "F10" MENU_PRIMARY_COLOR "-Receive"  MENU_HORIZONTAL_TAB "\x4" MENU_END_OF_OPTION
                                                        MENU_SECONDARY_COLOR "ESC" MENU_PRIMARY_COLOR "-Exit"     MENU_END_OF_OPTION MENU_END_OF_TEXT;

char                     BMI_Main_Menu_Text[] = MENU_SECONDARY_COLOR "F" MENU_PRIMARY_COLOR "ile"           MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "E" MENU_PRIMARY_COLOR "dit"           MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "R" MENU_PRIMARY_COLOR "eports"        MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "C" MENU_PRIMARY_COLOR "ommunications" MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "H" MENU_PRIMARY_COLOR "elp"           MENU_END_OF_OPTION MENU_END_OF_TEXT;

char                     BMI_File_Menu_Text[] = MENU_SECONDARY_COLOR "L"     MENU_PRIMARY_COLOR "oad"                        MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "N"     MENU_PRIMARY_COLOR "ew"                         MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "S"     MENU_PRIMARY_COLOR "ave"                        MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                                                MENU_PRIMARY_COLOR   "Save " MENU_SECONDARY_COLOR "A" MENU_PRIMARY_COLOR "s" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "D"     MENU_PRIMARY_COLOR "elete"                      MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "R"     MENU_PRIMARY_COLOR "ename"                      MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "Q"     MENU_PRIMARY_COLOR "uit"                        MENU_END_OF_OPTION MENU_END_OF_TEXT;

char                     BMI_Edit_Menu_Text[] = MENU_SECONDARY_COLOR "E" MENU_PRIMARY_COLOR "dit..." MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "M" MENU_PRIMARY_COLOR "ark  F5"    MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                                                MENU_SECONDARY_COLOR "C" MENU_PRIMARY_COLOR "lear F6"   MENU_END_OF_OPTION MENU_END_OF_TEXT;

char                     BMI_Report_Menu_Text[] = MENU_SECONDARY_COLOR "D" MENU_PRIMARY_COLOR "ata Dump" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
                                                  MENU_SECONDARY_COLOR "A" MENU_PRIMARY_COLOR "vail Cfg"  MENU_END_OF_OPTION MENU_END_OF_TEXT;

char                     BMI_Communications_Menu_Text[] = MENU_SECONDARY_COLOR "S" MENU_PRIMARY_COLOR "end"     MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
							  MENU_SECONDARY_COLOR "R" MENU_PRIMARY_COLOR "eceive"  MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
							  MENU_SECONDARY_COLOR "T" MENU_PRIMARY_COLOR "erminal" MENU_END_OF_OPTION MENU_END_OF_TEXT;

char                     BMI_Help_Menu_Text[] = MENU_SECONDARY_COLOR "I" MENU_PRIMARY_COLOR "ndex"    MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
						MENU_SECONDARY_COLOR "A" MENU_PRIMARY_COLOR "bout..." MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
						MENU_SECONDARY_COLOR "P" MENU_PRIMARY_COLOR "rint" MENU_END_OF_OPTION MENU_END_OF_TEXT;

char                     BMI_Yes_No_Menu_Text[] = MENU_SECONDARY_COLOR "Y" MENU_PRIMARY_COLOR "es" MENU_HORIZONTAL_TAB "\x2" MENU_END_OF_OPTION
						  MENU_SECONDARY_COLOR "N" MENU_PRIMARY_COLOR "o"  MENU_END_OF_OPTION MENU_END_OF_TEXT;

char *                   BMI_Menu_Text_List[BMI_TOTAL_MENUS] = {BMI_Function_Key_Menu_Text,
								BMI_Main_Menu_Text,
								BMI_File_Menu_Text,
								BMI_Edit_Menu_Text,
								BMI_Report_Menu_Text,
								BMI_Communications_Menu_Text,
								BMI_Help_Menu_Text,
								BMI_Yes_No_Menu_Text};

BMI_MENU_CHARACTERISTICS BMI_Menu_Characteristics_List[BMI_TOTAL_MENUS] = {{25, 2,  0,  0, 0, 0},  /* Function Key Menu   */
                                                                           {1,  2,  0,  0, 1, 5},  /* Main Menu           */
                                                                           {2,  2,  9, 11, 1, 7},  /* File Menu           */
                                                                           {2,  9,  5, 12, 1, 3},  /* Edit Menu           */
                                                                           {2, 16,  4, 14, 1, 2},  /* Reports Menu        */
                                                                           {2, 26,  5, 12, 1, 3},  /* Communications Menu */
                                                                           {2, 43,  5, 12, 1, 3},  /* Help Menu           */
                                                                           {0,  0,  0,  0, 0, 0}}; /* Yes/No Menu         */

char *                   BMI_Menu_Keys_List[BMI_TOTAL_MENUS] = {"",        /* Function Key Menu                                               */
                                                                "FERCH",   /* Main Menu, File, Edit, Communications, Help                     */
                                                                "LNSADRQ", /* File Menu, Load, New, Save, Save As, Delete, Rename, Quit       */
                                                                "EMC",     /* Edit Menu, Edit, Mark, Clear                                    */
                                                                "DR",      /* Reports Menu,                                                   */
                                                                "SRT",     /* Communications Menu, Send, Receive, Terminal                    */
                                                                "IAP",     /* Help Menu, Index, About, Print                                  */
                                                                "YN"};     /* Yes/No Menu, Yes, No                                            */

BMI_PROCESS_LIST         BMI_Process_List[BMI_TOTAL_PROCESSES] = {{BMI_Display_Time},                     /* BMI_DISPLAY_TIME_PROCESS             */
                                                                  {BMI_File_Load},                        /* BMI_FILE_LOAD_PROCESS                */
                                                                  {BMI_File_New},                         /* BMI_FILE_NEW_PROCESS                 */
                                                                  {BMI_File_Save},                        /* BMI_FILE_SAVE_PROCESS                */
                                                                  {BMI_File_Save_As},                     /* BMI_FILE_SAVE_AS_PROCESS             */
                                                                  {BMI_File_Delete},                      /* BMI_FILE_DELETE_PROCESS              */
                                                                  {BMI_File_Rename},                      /* BMI_FILE_RENAME_PROCESS              */
                                                                  {BMI_File_Quit},                        /* BMI_FILE_QUIT_PROCESS                */
                                                                  {BMI_Edit},                             /* BMI_EDIT_RESUME_PROCESS              */
                                                                  {BMI_Mark},                             /* BMI_EDIT_MARK_PROCESS                */
                                                                  {BMI_Clear},                            /* BMI_EDIT_CLEAR_PROCESS               */
                                                                  {BMI_Reports_Data_Dump},                /* BMI_REPORTS_DATA_DUMP_PROCESS        */
                                                                  {BMI_Reports_Available_Configurations}, /* BMI_REPORTS_REPORT2_PROCESS          */
                                                                  {BMI_Send},                             /* BMI_COMMUNICATIONS_SEND_PROCESS      */
                                                                  {BMI_Receive},                          /* BMI_COMMUNICATIONS_RECEIVE_PROCESS   */
                                                                  {BMI_Terminal},                         /* BMI_COMMUNICATIONS_TERMINAL_PROCESS  */
                                                                  {BMI_Help_Index},                       /* BMI_HELP_INDEX_PROCESS               */
                                                                  {BMI_Help_About},                       /* BMI_HELP_ABOUT_PROCESS               */
                                                                  {BMI_Help_Print},                       /* BMI_HELP_TOPIC_PROCESS               */
                                                                  {BMI_Help_Topic},                       /* BMI_HELP_PRINT_PROCESS               */
                                                                  {BMI_Yes_No_Menu},                      /* BMI_YES_NO_MENU_PROCESS              */
                                                                  {BMI_Sub_Menu},                         /* BMI_SUB_MENU_PROCESS                 */
                                                                  {BMI_Main_Menu},                        /* BMI_MAIN_MENU_PROCESS                */
                                                                  {BMI_Function_Key_Menu}};               /* BMI_FUNCTION_KEY_MENU_PROCESS        */

char                     BMI_Main_Screen_Unique_Characters[] = "≤‹ﬂ€";
BYTE                     BMI_Main_Screen_Unique_Colors[] = {CYAN, LIGHTCYAN, LIGHTCYAN, LIGHTCYAN};

char                     BMI_Main_Screen_Text[] =
   "\r\n"
   "                  ≤≤≤≤≤≤≤≤‹   ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹\r\n"
   "                   ≤≤€ﬂﬂ≤≤€   ≤≤€ﬂ≤≤€ ≤≤€ﬂﬂﬂﬂ  ﬂ≤≤€ﬂﬂ ≤≤€ﬂﬂﬂﬂ\r\n"
   "                   ≤≤≤≤≤≤≤≤≤‹ ≤≤≤≤≤≤€ ≤≤≤≤≤≤‹   ≤≤€   ≤≤€\r\n"
   "                   ≤≤€ﬂﬂﬂﬂ≤≤€ ≤≤€ﬂ≤≤€  ﬂﬂﬂ≤≤€   ≤≤€   ≤≤€\r\n"
   "                   ≤≤€    ≤≤€ ≤≤€ ≤≤€ ≤≤≤≤≤≤€ ≤≤≤≤≤≤€ ≤≤≤≤≤≤‹\r\n"
   "                  ≤≤≤≤≤≤≤≤≤≤€  ﬂﬂ  ﬂﬂ  ﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂﬂ\r\n"
   "                   ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ\r\n"
   "\r\n"
   "              ≤≤≤≤≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤‹  ≤≤‹ ≤≤‹ ≤≤‹     ≤≤≤≤≤≤‹\r\n"
   "              ≤≤€ﬂ≤≤€ﬂ≤≤€ ≤≤€ﬂ≤≤€ ≤≤€ﬂ≤≤‹ ≤≤€ ≤≤€ ≤≤€     ≤≤€ﬂﬂﬂﬂ\r\n"
   "              ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€     ≤≤≤≤‹\r\n"
   "              ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€     ≤≤€ﬂﬂ\r\n"
   "              ≤≤€ ≤≤€ ≤≤€ ≤≤≤≤≤≤€ ≤≤≤≤≤€ﬂ ≤≤≤≤≤≤€ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹\r\n"
   "              ≤≤€ ≤≤€ ≤≤€  ﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂ   ﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂﬂ\r\n"
   "               ﬂﬂ  ﬂﬂ  ﬂﬂ\r\n"
   "  ≤≤≤≤≤≤≤≤≤≤‹\r\n"
   "   ﬂﬂﬂ≤≤€ﬂﬂﬂﬂ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹\r\n"
   "      ≤≤€     ≤≤€ﬂ≤≤€   ≤≤€ﬂﬂ ≤≤€ﬂﬂﬂﬂ ≤≤€ﬂ≤≤€ ≤≤€ﬂﬂﬂﬂ ≤≤€ﬂ≤≤€ ≤≤€ﬂﬂﬂﬂ ≤≤€ﬂﬂﬂﬂ\r\n"
   "      ≤≤€     ≤≤€ ≤≤€   ≤≤€   ≤≤≤≤‹   ≤≤≤≤≤≤€ ≤≤≤≤‹   ≤≤≤≤≤≤€ ≤≤€     ≤≤≤≤‹  \r\n"
   "      ≤≤€     ≤≤€ ≤≤€   ≤≤€   ≤≤€ﬂﬂ   ≤≤€≤≤€ﬂ ≤≤€ﬂﬂ   ≤≤€ﬂ≤≤€ ≤≤€     ≤≤€ﬂﬂ  \r\n"
   "  ≤≤≤≤≤≤≤≤≤≤‹ ≤≤€ ≤≤€   ≤≤€   ≤≤≤≤≤≤‹ ≤≤€ ≤≤‹ ≤≤€     ≤≤€ ≤≤€ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹\r\n"
   "   ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ  ﬂﬂ  ﬂﬂ    ﬂﬂ    ﬂﬂﬂﬂﬂﬂ  ﬂﬂ  ﬂﬂ  ﬂﬂ      ﬂﬂ  ﬂﬂ  ﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂﬂ\r\n";
