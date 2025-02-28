/*

   File        : AAI0.C
   Module      : GLOBALS
   System      : AAI
   Description : The global variables used in the AAI program.
   Modified    : 08/18/92 DWP Created.
                 02/13/93 DWP Reformatted during the Winchester Version.
   Notes       :

*/

#include <conio.h>
#include <stdio.h>

#include "aai.h"

char * AAI_Help_Index_Key_List[] = {

   "MAINM",
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
	""
};

char AAI_Function_Key_Menu_Text[] =

	MENU_SECONDARY_COLOR "F1"  MENU_PRIMARY_COLOR "-Help"         MENU_HORIZONTAL_TAB "\x4" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "F2"  MENU_PRIMARY_COLOR "-Pipette"      MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "F3"  MENU_PRIMARY_COLOR "-Form Feed"    MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "F4"  MENU_PRIMARY_COLOR "-Clear Screen" MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "F5"  MENU_PRIMARY_COLOR "-Sleep"        MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "ESC" MENU_PRIMARY_COLOR "-Exit"         MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AAI_Main_Menu_Text[] =

	MENU_SECONDARY_COLOR "F" MENU_PRIMARY_COLOR "ile"      MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "M" MENU_PRIMARY_COLOR "easure"   MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "P" MENU_PRIMARY_COLOR "roduct"   MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "C" MENU_PRIMARY_COLOR "alibrate" MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "S" MENU_PRIMARY_COLOR "etup"     MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "H" MENU_PRIMARY_COLOR "elp"      MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AAI_File_Menu_Text[] =

	MENU_SECONDARY_COLOR "L"     MENU_PRIMARY_COLOR "oad"                        MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "N"     MENU_PRIMARY_COLOR "ew"                         MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "S"     MENU_PRIMARY_COLOR "ave"                        MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_PRIMARY_COLOR   "Save " MENU_SECONDARY_COLOR "A" MENU_PRIMARY_COLOR "s" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "D"     MENU_PRIMARY_COLOR "elete"                      MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "R"     MENU_PRIMARY_COLOR "ename"                      MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "Q"     MENU_PRIMARY_COLOR "uit"                        MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AAI_Measure_Menu_Text[] =

	MENU_SECONDARY_COLOR "M" MENU_PRIMARY_COLOR "easure"   MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "P" MENU_PRIMARY_COLOR "urge"     MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "Z" MENU_PRIMARY_COLOR "ero Set"  MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "S" MENU_PRIMARY_COLOR "ample Nr" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "B" MENU_PRIMARY_COLOR "atch"     MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "L" MENU_PRIMARY_COLOR "abel"     MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AAI_Product_Menu_Text[] =

	MENU_SECONDARY_COLOR "1" MENU_PRIMARY_COLOR "st Opt" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "2" MENU_PRIMARY_COLOR "nd Opt" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "3" MENU_PRIMARY_COLOR "rd Opt" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AAI_Calibrate_Menu_Text[] =

	MENU_SECONDARY_COLOR "E" MENU_PRIMARY_COLOR   "dit/Measure"                            MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "Z" MENU_PRIMARY_COLOR   "ero Set"                                MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_PRIMARY_COLOR   "C" MENU_SECONDARY_COLOR "r" MENU_PRIMARY_COLOR "oss Calibration" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_PRIMARY_COLOR   "P" MENU_SECONDARY_COLOR "i" MENU_PRIMARY_COLOR "lot Samples"     MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "B" MENU_PRIMARY_COLOR   "ias & Slope"                            MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "V" MENU_PRIMARY_COLOR   "iew Calibration"                        MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "M" MENU_PRIMARY_COLOR   "ineral Bias"                            MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "S" MENU_PRIMARY_COLOR   "tatistics"                              MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "G" MENU_PRIMARY_COLOR   "raphics"                                MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "C" MENU_PRIMARY_COLOR   "arry Over"                              MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "P" MENU_PRIMARY_COLOR   "olynomial"                              MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AAI_Setup_Menu_Text[] =

	MENU_SECONDARY_COLOR "P"                                  MENU_PRIMARY_COLOR "rinter"         MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "O"                                  MENU_PRIMARY_COLOR "utput"          MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "T"                                  MENU_PRIMARY_COLOR "emperature"     MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "H"                                  MENU_PRIMARY_COLOR "eader"          MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "F"                                  MENU_PRIMARY_COLOR "ooter"          MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "1"                                  MENU_PRIMARY_COLOR "st Serial Port" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "2"                                  MENU_PRIMARY_COLOR "nd Serial Port" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "B"                                  MENU_PRIMARY_COLOR "arcode Reader"  MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "C"                                  MENU_PRIMARY_COLOR "ycles"          MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_PRIMARY_COLOR   "Pressure " MENU_SECONDARY_COLOR "L" MENU_PRIMARY_COLOR "imits"          MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_PRIMARY_COLOR   "Chopper "  MENU_SECONDARY_COLOR "S" MENU_PRIMARY_COLOR "peed"           MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AAI_Help_Menu_Text[] =

	MENU_SECONDARY_COLOR "I" MENU_PRIMARY_COLOR "ndex"    MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "A" MENU_PRIMARY_COLOR "bout..." MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "P" MENU_PRIMARY_COLOR "rint" MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AAI_Yes_No_Menu_Text[] =

	MENU_SECONDARY_COLOR "Y" MENU_PRIMARY_COLOR "es" MENU_HORIZONTAL_TAB "\x2" MENU_END_OF_OPTION
	MENU_SECONDARY_COLOR "N" MENU_PRIMARY_COLOR "o"  MENU_END_OF_OPTION MENU_END_OF_TEXT;

char * AAI_Menu_Text_List[AAI_TOTAL_MENUS] = {

	AAI_Function_Key_Menu_Text,
	AAI_Main_Menu_Text,
	AAI_File_Menu_Text,
	AAI_Measure_Menu_Text,
	AAI_Product_Menu_Text,
	AAI_Calibrate_Menu_Text,
	AAI_Setup_Menu_Text,
	AAI_Help_Menu_Text,
	AAI_Yes_No_Menu_Text

};

AAI_MENU_CHARACTERISTICS AAI_Menu_Characteristics_List[AAI_TOTAL_MENUS] = {

	{25, 2,  0,  0, 0,  0}, /* Function Key Menu   */
	{1,  2,  0,  0, 1,  6}, /* Main Menu           */
	{2,  2,  9, 11, 1,  7}, /* File Menu           */
	{2,  9,  8, 13, 1,  6}, /* Measure Menu        */
	{2, 19,  5, 11, 1,  3}, /* Product Menu        */
	{2, 29, 13, 21, 1, 11}, /* Calibrate Menu      */
	{2, 41, 13, 19, 1, 11}, /* Setup Menu          */
	{2, 49,  5, 12, 1,  3}, /* Help Menu           */
	{0,  0,  0,  0, 0,  0}  /* Yes/No Menu         */

};

char * AAI_Menu_Keys_List[AAI_TOTAL_MENUS] = {

	"",            /* Function Key Menu                                                                                                                                                    */
	"FMPDCSH",     /* Main Menu, File, Measure, Product, Calibrate, Setup, Help                                                                                                            */
	"LNSADRQ",     /* File Menu, Load, New, Save, Save As, Delete, Rename, Quit                                                                                                            */
	"MPZSBL",      /* Measure Menu, Measure, Purge, Zero Set, Sample Nr, Batch, Label                                                                                                      */
	"123",            /* Product Menu                                                                                                                                                         */
	"EZRIBVMSGCP", /* Calibrate Menu, Edit/Measure, Zero Set, Cross Calibration, Pilot Samples, Bias & Scope, View Calibration, Mineral Bias, Statistics, Graphics, Carry Over, Polynomial */
	"POTHF12BCPS", /* Setup Menu, Printer, Output, Temp, Header, Footer, 1st Serial Port, 2nd Serial Port, Barcode Reader, Cycles, Pressure Limits, Chopper Speed                          */
	"IAP",         /* Help Menu, Index, About, Print                                                                                                                                       */
	"YN"           /* Yes/No Menu, Yes, No                                                                                                                                                 */

};

AAI_PROCESS_LIST AAI_Process_List[AAI_TOTAL_PROCESSES] = {

	{AAI_Display_Time},                     /* AAI_DISPLAY_TIME_PROCESS            */
	{AAI_File_Load},                        /* AAI_FILE_LOAD_PROCESS               */
	{AAI_File_New},                         /* AAI_FILE_NEW_PROCESS                */
	{AAI_File_Save},                        /* AAI_FILE_SAVE_PROCESS               */
	{AAI_File_Save_As},                     /* AAI_FILE_SAVE_AS_PROCESS            */
	{AAI_File_Delete},                      /* AAI_FILE_DELETE_PROCESS             */
	{AAI_File_Rename},                      /* AAI_FILE_RENAME_PROCESS             */
	{AAI_File_Quit},                        /* AAI_FILE_QUIT_PROCESS               */
	{AAI_Edit},                             /* AAI_EDIT_RESUME_PROCESS             */
	{AAI_Mark},                             /* AAI_EDIT_MARK_PROCESS               */
	{AAI_Clear},                            /* AAI_EDIT_CLEAR_PROCESS              */
	{AAI_Reports_Data_Dump},                /* AAI_REPORTS_DATA_DUMP_PROCESS       */
	{AAI_Reports_Available_Configurations}, /* AAI_REPORTS_REPORT2_PROCESS         */
	{AAI_Send},                             /* AAI_COMMUNICAAIONS_SEND_PROCESS     */
	{AAI_Receive},                          /* AAI_COMMUNICAAIONS_RECEIVE_PROCESS  */
	{AAI_Terminal},                         /* AAI_COMMUNICAAIONS_TERMINAL_PROCESS */
	{AAI_Help_Index},                       /* AAI_HELP_INDEX_PROCESS              */
	{AAI_Help_About},                       /* AAI_HELP_ABOUT_PROCESS              */
	{AAI_Help_Print},                       /* AAI_HELP_TOPIC_PROCESS              */
	{AAI_Help_Topic},                       /* AAI_HELP_PRINT_PROCESS              */
	{AAI_Yes_No_Menu},                      /* AAI_YES_NO_MENU_PROCESS             */
	{AAI_Sub_Menu},                         /* AAI_SUB_MENU_PROCESS                */
	{AAI_Main_Menu},                        /* AAI_MAIN_MENU_PROCESS               */
	{AAI_Function_Key_Menu}                 /* AAI_FUNCTION_KEY_MENU_PROCESS       */

};

char AAI_Main_Screen_Unique_Characters[] =

	"≤‹ﬂ€";

BYTE AAI_Main_Screen_Unique_Colors[] = {

	CYAN,
	LIGHTCYAN,
	LIGHTCYAN,
	LIGHTCYAN

};

char AAI_Main_Screen_Text[] =
	"\r\n"
	"                    ≤≤≤≤≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤‹ ≤≤≤≤≤≤‹\r\n"
	"                    ≤≤€ﬂﬂﬂﬂﬂ≤≤€   ≤≤€ﬂﬂ  ﬂ≤≤€ﬂﬂ ≤≤€ ≤≤€ﬂﬂﬂﬂ\r\n"
	"                    ≤≤€     ≤≤€   ≤≤€     ≤≤€    ﬂﬂ ≤≤≤≤≤≤‹\r\n"
	"                    ≤≤≤≤≤≤≤≤≤≤€   ≤≤€     ≤≤€        ﬂﬂﬂ≤≤€\r\n"
	"                    ≤≤€ﬂﬂﬂﬂﬂ≤≤€   ≤≤€   ≤≤≤≤≤≤€     ≤≤≤≤≤≤€\r\n"
	"                    ≤≤€     ≤≤€    ﬂﬂ    ﬂﬂﬂﬂﬂﬂ      ﬂﬂﬂﬂﬂﬂ\r\n"
	"                     ﬂﬂ      ﬂﬂ\r\n"
	"\r\n"
	"      ≤≤≤≤≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤‹ ≤≤‹ ≤≤≤≤≤‹  ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤‹ ≤≤‹\r\n"
	"      ≤≤€ﬂﬂﬂﬂﬂ≤≤€ ≤≤€ﬂﬂﬂﬂ ≤≤€ ≤≤€ ≤≤€ﬂ≤≤‹ ≤≤€ﬂ≤≤€  ﬂ≤≤€ﬂﬂ ≤≤€ﬂ≤≤€ ≤≤€ ≤≤€\r\n"
	"      ≤≤€     ≤≤€ ≤≤€     ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤≤≤≤≤€   ≤≤€   ≤≤≤≤≤≤€ ≤≤≤≤≤≤€\r\n"
	"      ≤≤≤≤≤≤≤≤≤≤€ ≤≤€     ≤≤€ ≤≤€ ≤≤€ ≤≤€ ≤≤€ﬂ≤≤€   ≤≤€   ≤≤€≤≤€ﬂ   ≤≤€\r\n"
	"      ≤≤€ﬂﬂﬂﬂﬂ≤≤€ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤€ ≤≤≤≤≤€ﬂ ≤≤€ ≤≤€ ≤≤≤≤≤≤€ ≤≤€ ≤≤‹   ≤≤€\r\n"
	"      ≤≤€     ≤≤€  ﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂ   ﬂﬂ  ﬂﬂ  ﬂﬂﬂﬂﬂﬂ  ﬂﬂ  ﬂﬂ    ﬂﬂ\r\n"
	"       ﬂﬂ      ﬂﬂ\r\n"
	"  ≤≤≤≤≤≤≤≤≤≤‹\r\n"
	"      ≤≤€ﬂﬂﬂﬂ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹\r\n"
	"      ≤≤€     ≤≤€ﬂ≤≤€   ≤≤€ﬂﬂ ≤≤€ﬂﬂﬂﬂ ≤≤€ﬂ≤≤€ ≤≤€ﬂﬂﬂﬂ ≤≤€ﬂ≤≤€ ≤≤€ﬂﬂﬂﬂ ≤≤€ﬂﬂﬂﬂ\r\n"
	"      ≤≤€     ≤≤€ ≤≤€   ≤≤€   ≤≤≤≤‹   ≤≤≤≤≤≤€ ≤≤≤≤‹   ≤≤≤≤≤≤€ ≤≤€     ≤≤≤≤‹\r\n"
	"      ≤≤€     ≤≤€ ≤≤€   ≤≤€   ≤≤€ﬂﬂ   ≤≤€≤≤€ﬂ ≤≤€ﬂﬂ   ≤≤€ﬂ≤≤€ ≤≤€     ≤≤€ﬂﬂ\r\n"
	"  ≤≤≤≤≤≤≤≤≤≤‹ ≤≤€ ≤≤€   ≤≤€   ≤≤≤≤≤≤‹ ≤≤€ ≤≤‹ ≤≤€     ≤≤€ ≤≤€ ≤≤≤≤≤≤‹ ≤≤≤≤≤≤‹\r\n"
	"   ﬂﬂﬂﬂﬂﬂﬂﬂﬂﬂ  ﬂﬂ  ﬂﬂ    ﬂﬂ    ﬂﬂﬂﬂﬂﬂ  ﬂﬂ  ﬂﬂ  ﬂﬂ      ﬂﬂ  ﬂﬂ  ﬂﬂﬂﬂﬂﬂ  ﬂﬂﬂﬂﬂﬂ\r\n";

