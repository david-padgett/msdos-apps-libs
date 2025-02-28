/*

   File        : AAI.H
   Module      : AAI
   System      : AAI
   Description : The header file for the AAI program.
   Modified    : 08/18/92 DWP Created.
                 02/13/93 DWP Added Display_Length Maximum_Loadable_Value fields to AAI_INPUT_DESCRIPTOR.  Updated for Winchester 
                          Version.
   Notes       :

*/

#include <dir.h>

#include "\Dev\DOS\Lib\C\List\list.h"
#include "\Dev\DOS\Lib\C\Menu\menu.h"
#include "\Dev\DOS\Lib\C\Port\port.h"

/*

   Macros.

*/

#define AAI_TITLE_1                   "ATI's Acudairy Interface Version 1.0A"
#define AAI_TITLE_2                   "Copyright (C) " COMPILE_YEAR " by Analytical Technologies, Inc."
#define AAI_TITLE_3                   "and CSFX Computing Services"
#define AAI_TITLE_4                   "All Rights Reserved."
#define AAI_TITLE_5                   "Last Modified on " COMPILE_DATE
#define AAI_TITLE_6                   "Press Any Key To Continue"
#define AAI_CONFIG_FILE_TITLE         "AAI Version 1.0A Configuration File\x1a"
#define AAI_CONFIG_FILE_NAME          "AAI.CFG"
#define AAI_TOTAL_EDIT_FIELDS        165
#define AAI_TOTAL_UNIQUE_EDIT_FIELDS   6
#define AAI_TOTAL_PROCESSES           28
#define AAI_TOTAL_MENUS                9

/*

	Type Definitions.

*/

typedef enum _AAI_PROCESS_TYPES {

	AAI_DISPLAY_TIME_PROCESS,
	AAI_FILE_LOAD_PROCESS,
	AAI_FILE_NEW_PROCESS,
	AAI_FILE_SAVE_PROCESS,
	AAI_FILE_SAVE_AS_PROCESS,
	AAI_FILE_DELETE_PROCESS,
	AAI_FILE_RENAME_PROCESS,
	AAI_FILE_QUIT_PROCESS,
	AAI_EDIT_EDIT_PROCESS,
	AAI_EDIT_MARK_PROCESS,
	AAI_EDIT_CLEAR_PROCESS,
	AAI_REPORTS_DATA_DUMP_PROCESS,
	AAI_REPORTS_AVAIL_CFG_PROCESS,
   AAI_COMMUNICAAIONS_SEND_PROCESS,
   AAI_COMMUNICAAIONS_RECEIVE_PROCESS,
   AAI_COMMUNICAAIONS_TERMINAL_PROCESS,
   AAI_HELP_INDEX_PROCESS,
   AAI_HELP_ABOUT_PROCESS,
   AAI_HELP_PRINT_PROCESS,
   AAI_HELP_TOPIC_PROCESS,
   AAI_YES_NO_MENU_PROCESS,
   AAI_SUB_MENU_PROCESS,
   AAI_MAIN_MENU_PROCESS,
	AAI_FUNCTION_KEY_MENU_PROCESS

} AAI_PROCESS_TYPES;

typedef enum _AAI_DISPLAY_TYPES {

   AAI_COLOR,
   AAI_MONOCHROME,
   AAI_LCD

} AAI_DISPLAY_TYPES;

typedef enum _AAI_VERSION_TYPES {

	AAI_WINCHESTER_VERSION,
   AAI_PLANT_VERSION

} AAI_VERSION_TYPES;

typedef enum _AAI_MENU_TYPES {

   AAI_FUNCTION_KEY_MENU,
   AAI_MAIN_MENU,
   AAI_FILE_MENU,
	AAI_MEASURE_MENU,
	AAI_PRODUCT_MENU,
	AAI_CALIBRATE_MENU,
	AAI_SETUP_MENU,
	AAI_HELP_MENU,
	AAI_YES_NO_MENU

} AAI_MENU_TYPES;

typedef enum _AAI_HELP_INDEX_KEY_LIST_VALUES {

	AAI_HELP_MAINM,
	AAI_HELP_FILEM,
	AAI_HELP_EDITM,
	AAI_HELP_REPTM,
	AAI_HELP_COMMM,
	AAI_HELP_HELPM,
	AAI_HELP_LODFM,
	AAI_HELP_NEWFM,
	AAI_HELP_SAVFM,
	AAI_HELP_SVAFM,
	AAI_HELP_DELFM,
	AAI_HELP_RENFM,
	AAI_HELP_QUIFM,
	AAI_HELP_EDTEM,
	AAI_HELP_MAREM,
	AAI_HELP_CLEEM,
	AAI_HELP_DDPRM,
   AAI_HELP_ACGRM,
   AAI_HELP_SNDCM,
   AAI_HELP_RECCM,
   AAI_HELP_TERCM,
   AAI_HELP_INDHM,
	AAI_HELP_ABOHM,
   AAI_HELP_PRIHM,
	AAI_HELP_NO_HELP

} AAI_HELP_INDEX_KEY_LIST_VALUES;

typedef struct _AAI_MENU_CHARACTERISTICS {

   CARDINAL_16 Starting_Row;
   CARDINAL_16 Starting_Column;
   CARDINAL_16 Height;
   CARDINAL_16 Width;
   CARDINAL_16 Option;
   CARDINAL_16 Total_Options;

} AAI_MENU_CHARACTERISTICS;

typedef struct _AAI_COLORS {

   CARDINAL_16 Primary_Color;
   CARDINAL_16 Secondary_Color;
   CARDINAL_16 Primary_Highlight_Color;
   CARDINAL_16 Secondary_Highlight_Color;

} AAI_COLORS;

typedef struct _AAI_INPUT_DESCRIPTOR {

	TEXT *          Text;
   CARDINAL_16     Edit_Length;
   CARDINAL_16     Display_Length;
   CARDINAL_16     Decimal;
   DATA_TYPES      Type;
   AAI_COLORS      Colors;
   CARDINAL_16     Current_Row;
   CARDINAL_16     Current_Column;
   BOOLEAN         Marked_Flag;
   BOOLEAN         Refresh_Flag;
   BOOLEAN         Display_Cursor_Flag;
   BOOLEAN         Color_Indicator_Flag;
	BOOLEAN         First_Pass_Flag;
   char            Value[25];
	INTEGER_16      Integer_Value;
   INTEGER_16      Minimum_Value;
   INTEGER_16      Maximum_Editable_Value;
   INTEGER_16      Maximum_Loadable_Value;
   CARDINAL_16     Current_Offset;
   CARDINAL_16     Previous_Offset;

} AAI_INPUT_DESCRIPTOR;

typedef struct _AAI_DEFAULT_PARAMETERS {

   char              ID[50];

   AAI_DISPLAY_TYPES Display_Type;

   AAI_COLORS        Function_Key_Menu_Colors;
   AAI_COLORS        Main_Menu_Colors;
   AAI_COLORS        Sub_Menu_Colors;
   AAI_COLORS        Yes_No_Menu_Colors;
   AAI_COLORS        Edit_Colors;

	int               Port_No;

} AAI_DEFAULT_PARAMETERS;

typedef struct _AAI_PROCESS_DESCRIPTOR {

   CARDINAL_16 Process_Number;
	BOOLEAN     Process_Active_Flag;
	void *      Process_Parameters;
   int         (* Process)(void ** Process_Parameters, CARDINAL_16 * Key);

} AAI_PROCESS_DESCRIPTOR;

typedef struct _AAI_PARAMETERS_LIST {

   AAI_DISPLAY_TYPES        Display_Type;
   BOOLEAN                  Display_Type_Specified;
   int                      Port_No;
   BOOLEAN                  Port_No_Specified;
   AAI_DEFAULT_PARAMETERS   Default_Parameters;
   AAI_VERSION_TYPES	    Version;

   TEXT                     Text;

   AAI_MENU_CHARACTERISTICS Menu_Characteristics_List[AAI_TOTAL_MENUS];
   char *                   Menu_Text_List[AAI_TOTAL_MENUS];
   char *                   Menu_Keys_List[AAI_TOTAL_MENUS];
   char *                   Main_Screen_Text;
   char *                   Main_Screen_Characters;
   BYTE *                   Main_Screen_Character_Colors;

	AAI_PROCESS_DESCRIPTOR   Process_Descriptor[AAI_TOTAL_PROCESSES];
   CARDINAL_16              Total_Processes;

} AAI_PARAMETERS_LIST;

typedef struct _AAI_PROCESS_LIST {

   int (* Process)(void ** Process_Parameters, CARDINAL_16 * Key);

} AAI_PROCESS_LIST;

/*

   Process parameter list definitions.

*/

typedef struct _AAI_SETUP_LOAD_SETUP_PARAMETERS {

   char                   Config_File_Name[13];
   AAI_DEFAULT_PARAMETERS Default_Parameters;
   BOOLEAN                Bypass_Interface_Flag;

} AAI_SETUP_LOAD_SETUP_PARAMETERS, AAI_SETUP_SAVE_SETUP_PARAMETERS;

typedef struct _AAI_YES_NO_MENU_PARAMETERS {

   AAI_PARAMETERS_LIST * Parameters_List;
   PORT                  Port;
   TEXT                  Text;
   AAI_COLORS            Colors;
   MENU                  Menu;
	char *                Menu_Text;
   char *                Menu_Keys_List;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   char *                Display_Message;
   CARDINAL_16           Option;
	AAI_PROCESS_TYPES     Invoking_Process;
   BOOLEAN *             Yes_Selected_Flag;

} AAI_YES_NO_MENU_PARAMETERS;

typedef struct _AAI_DISPLAY_TIME_PARAMETERS {

   TEXT        Text;
	AAI_COLORS  Colors;
   CARDINAL_16 Row;
   CARDINAL_16 Column;
   int         Minutes_Value;
   int         Seconds_Value;
   char        Separator_Character;

} AAI_DISPLAY_TIME_PARAMETERS;

typedef struct _AAI_EDIT_EDIT_PARAMETERS {

   AAI_PARAMETERS_LIST *  Parameters_List;
   PORT                   Port;
   TEXT                   Text;
	AAI_COLORS             Colors;
	CARDINAL_16            Starting_Row;
   CARDINAL_16            Starting_Column;
   CARDINAL_16            Height;
   CARDINAL_16            Width;
   CARDINAL_16            Field;
   CARDINAL_16            Total_Fields;

   AAI_INPUT_DESCRIPTOR * Current_Field_Descriptor;

   AAI_INPUT_DESCRIPTOR   Part_Number;
   AAI_INPUT_DESCRIPTOR   Valve_Pack_Number;
   AAI_INPUT_DESCRIPTOR   Multiple_Part_Number;
   AAI_INPUT_DESCRIPTOR   Last_Bin_Sensor;
	AAI_INPUT_DESCRIPTOR   Total_Cycle_Time;
   AAI_INPUT_DESCRIPTOR   Advance_Time[80];
   AAI_INPUT_DESCRIPTOR   Retract_Time[80];

   CARDINAL_16            Top_Row_Starting_Number;
   BOOLEAN                Redraw_Timing_Values_Flag;

} AAI_EDIT_EDIT_PARAMETERS;

typedef struct _AAI_EDIT_MARK_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
   AAI_EDIT_EDIT_PARAMETERS * Edit_Parameters;

} AAI_EDIT_MARK_PARAMETERS;

typedef struct _AAI_EDIT_CLEAR_PARAMETERS {

	AAI_PARAMETERS_LIST *      Parameters_List;
   AAI_EDIT_EDIT_PARAMETERS * Edit_Parameters;

} AAI_EDIT_CLEAR_PARAMETERS;

typedef struct _AAI_FILE_LOAD_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
   AAI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   PORT                       Port;
	TEXT                       Text;
   AAI_COLORS                 Colors;
   CARDINAL_16                Starting_Row;
   CARDINAL_16                Starting_Column;
   CARDINAL_16                Height;
	CARDINAL_16                Width;
   LIST                       File_List;
   char                       File_Name[MAXFILE];
   CARDINAL_32                Current_File_Number;
   CARDINAL_32                Previous_File_Number;
   CARDINAL_32                First_File_Number;
   CARDINAL_16                Current_Row;

} AAI_FILE_LOAD_PARAMETERS;

typedef struct _AAI_FILE_NEW_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
   AAI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   AAI_FILE_LOAD_PARAMETERS * Load_Parameters;
   BOOLEAN                    Clear_Memory_Flag;
   BOOLEAN                    Process_In_Progress_Flag;

} AAI_FILE_NEW_PARAMETERS;

typedef struct _AAI_FILE_SAVE_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
	AAI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   AAI_FILE_LOAD_PARAMETERS * Load_Parameters;
   TEXT                       Text;
   PORT                       Port;
   AAI_COLORS                 Colors;
   CARDINAL_16                Starting_Row;
   CARDINAL_16                Starting_Column;
   CARDINAL_16                Height;
	CARDINAL_16                Width;
   AAI_INPUT_DESCRIPTOR       File_Name;

} AAI_FILE_SAVE_PARAMETERS;

typedef struct _AAI_FILE_SAVE_AS_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
   AAI_FILE_LOAD_PARAMETERS * Load_Parameters;

} AAI_FILE_SAVE_AS_PARAMETERS;

typedef struct _AAI_FILE_DELETE_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
	PORT                       Port;
   TEXT                       Text;
   AAI_COLORS                 Colors;
   CARDINAL_16                Starting_Row;
   CARDINAL_16                Starting_Column;
	CARDINAL_16                Height;
   CARDINAL_16                Width;
   LIST                       File_List;
	char                       File_Name[MAXFILE];
   CARDINAL_32                Current_File_Number;
   CARDINAL_32                Previous_File_Number;
   CARDINAL_32                First_File_Number;
   CARDINAL_16                Current_Row;
   BOOLEAN                    Delete_File_Flag;
   BOOLEAN                    Process_In_Progress_Flag;

} AAI_FILE_DELETE_PARAMETERS;

typedef struct _AAI_FILE_RENAME_PARAMETERS {

   AAI_PARAMETERS_LIST *       Parameters_List;
   PORT                        Port;
   TEXT                        Text;
	AAI_COLORS                  Colors;
   CARDINAL_16                 Starting_Row;
   CARDINAL_16                 Starting_Column;
   CARDINAL_16                 Height;
   CARDINAL_16                 Width;
   PORT                        New_File_Port;
   CARDINAL_16                 New_File_Starting_Row;
   CARDINAL_16                 New_File_Starting_Column;
	CARDINAL_16                 New_File_Height;
   CARDINAL_16                 New_File_Width;
	LIST                        File_List;
   char                        Current_File_Name[MAXFILE];
   AAI_INPUT_DESCRIPTOR        New_File_Name;
   CARDINAL_32                 Current_File_Number;
   CARDINAL_32                 Previous_File_Number;
   CARDINAL_32                 First_File_Number;
   CARDINAL_16                 Current_Row;

} AAI_FILE_RENAME_PARAMETERS;

typedef struct _AAI_FILE_QUIT_PARAMETERS {

   AAI_PARAMETERS_LIST * Parameters_List;

} AAI_FILE_QUIT_PARAMETERS;

typedef struct _AAI_REPORTS_DATA_DUMP_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
   AAI_FILE_LOAD_PARAMETERS * Load_Parameters;
   AAI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
	BOOLEAN                    Print_Report_Flag;
   BOOLEAN                    Process_In_Progress_Flag;
   BOOLEAN                    Stop_Process_Flag;

} AAI_REPORTS_DATA_DUMP_PARAMETERS;

typedef struct _AAI_REPORTS_AVAIL_CFG_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
   AAI_FILE_LOAD_PARAMETERS * Load_Parameters;
   AAI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   LIST                       File_List;
   BOOLEAN                    Print_Report_Flag;
   BOOLEAN                    Process_In_Progress_Flag;
   BOOLEAN                    Stop_Process_Flag;

} AAI_REPORTS_AVAIL_CFG_PARAMETERS;

typedef struct _AAI_COMMUNICAAIONS_SEND_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
	AAI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   PORT                       Port;
	TEXT                       Text;
   AAI_COLORS                 Colors;
   CARDINAL_16                Starting_Row;
   CARDINAL_16                Starting_Column;
   CARDINAL_16                Height;
   CARDINAL_16                Width;
   AAI_INPUT_DESCRIPTOR       Unit_Number;
   AAI_INPUT_DESCRIPTOR       Save_Timing_Values;
   BOOLEAN                    Get_Parameters_Flag;
   CARDINAL_16                Field;
   CARDINAL_16                Valve_Packs;

	int                        Port_No;
   int                        IQ_Size;
   int                        OQ_Size;
	int                        Int_Level;
   int                        Port_Ads;
   char                       Pbuffer[8196];

   BOOLEAN                    First_Pass_Flag;
   BOOLEAN                    Exit_Flag;
   BOOLEAN                    Abort_Flag;
   CARDINAL_16                Parameter_Number;
	char                       Send_String[256];

   FILE *                     Send_Raw_Data_File;

} AAI_COMMUNICAAIONS_SEND_PARAMETERS;

typedef struct _AAI_COMMUNICAAIONS_RECEIVE_PARAMETERS {

   AAI_PARAMETERS_LIST *      Parameters_List;
   AAI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   PORT                       Port;
   TEXT                       Text;
   AAI_COLORS                 Colors;
   CARDINAL_16                Starting_Row;
   CARDINAL_16                Starting_Column;
	CARDINAL_16                Height;
   CARDINAL_16                Width;
	int                        Port_No;
   int                        IQ_Size;
   int                        OQ_Size;
   int                        Int_Level;
   int                        Port_Ads;
   char                       Pbuffer[8196];

   BOOLEAN                    First_Pass_Flag;
   BOOLEAN                    Exit_Flag;
   CARDINAL_16                Parameter_Number;
   char                       Receive_String[256];
   CARDINAL_16                Receive_String_Offset;
   char                       Error_Message[51];
   CARDINAL_16                Lines_Received;

   FILE *                     Receive_Raw_Data_File;

} AAI_COMMUNICAAIONS_RECEIVE_PARAMETERS;

typedef struct _AAI_COMMUNICAAIONS_TERMINAL_PARAMETERS {

	AAI_PARAMETERS_LIST * Parameters_List;
   PORT                  Port;
   TEXT                  Text;
   AAI_COLORS            Colors;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   CARDINAL_16           Height;
	CARDINAL_16           Width;
	int                   Port_No;
   int                   IQ_Size;
   int                   OQ_Size;
   int                   Int_Level;
   int                   Port_Ads;
   char                  Pbuffer[8196];
   BOOLEAN               First_Pass_Flag;
   BOOLEAN               Exit_Flag;

} AAI_COMMUNICAAIONS_TERMINAL_PARAMETERS;

typedef struct _AAI_HELP_TEXT_LIST {

	CARDINAL_8 Length;
   char       Help_Text[60];

} AAI_HELP_TEXT_LIST;

typedef struct _AAI_HELP_INDEX_LIST {

   char Index_Key[5];
   char Index_Description[60];
   LIST Help_Text_List;

} AAI_HELP_INDEX_LIST;

typedef struct _AAI_HELP_INDEX_PARAMETERS {

   AAI_PARAMETERS_LIST * Parameters_List;
   PORT                  Port;
   TEXT                  Text;
   AAI_COLORS            Colors;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   CARDINAL_16           Height;
   CARDINAL_16           Width;
   FILE *                Help_File;
   BOOLEAN               End_Of_File;
	AAI_HELP_INDEX_LIST   Help_Index;
   BOOLEAN               Help_Available_Flag;
   BOOLEAN               Help_Loaded_Flag;

   LIST                  Help_List;

   CARDINAL_32           First_Row_Line;
   CARDINAL_16           Current_Row;
	CARDINAL_16           Previous_Row;
   BOOLEAN               Redraw_Screen_Flag;
   BOOLEAN               Exit_Flag;

} AAI_HELP_INDEX_PARAMETERS;

typedef struct _AAI_HELP_ABOUT_PARAMETERS {

   AAI_PARAMETERS_LIST * Parameters_List;
	PORT                  Port;
   TEXT                  Text;
   AAI_COLORS            Colors;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   CARDINAL_16           Height;
	CARDINAL_16           Width;

} AAI_HELP_ABOUT_PARAMETERS;

typedef struct _AAI_HELP_PRINT_PARAMETERS {

   AAI_PARAMETERS_LIST *       Parameters_List;
   AAI_HELP_INDEX_PARAMETERS * Index_Parameters;
	AAI_HELP_INDEX_LIST *       Help_Index;
   AAI_HELP_TEXT_LIST *        Help_Text;
   BOOLEAN                     Exit_Flag;
   FILE *                      Report_File;
   BOOLEAN                     Print_Report_Flag;
   CARDINAL_16                 Page_Number;
   CARDINAL_16                 Line_Number;
   BOOLEAN                     New_Page_Flag;
   BOOLEAN                     Process_In_Progress_Flag;
   BOOLEAN                     First_Index_Node_Flag;
   BOOLEAN                     First_Text_Node_Flag;

} AAI_HELP_PRINT_PARAMETERS;

typedef struct _AAI_HELP_TOPIC_PARAMETERS {

   AAI_PARAMETERS_LIST *       Parameters_List;
   AAI_HELP_INDEX_PARAMETERS * Index_Parameters;
   AAI_HELP_INDEX_LIST *       Help_Index;
   AAI_HELP_TEXT_LIST *        Help_Text;
   PORT                        Port;
   TEXT                        Text;
   AAI_COLORS                  Colors;
	CARDINAL_16                 Starting_Row;
   CARDINAL_16                 Starting_Column;
   CARDINAL_16                 Height;
   CARDINAL_16                 Width;
   char *                      Key;
	CARDINAL_32                 First_Row_Line;
   BOOLEAN                     Redraw_Screen_Flag;
   BOOLEAN                     Exit_Flag;

} AAI_HELP_TOPIC_PARAMETERS;

typedef struct _AAI_SUB_MENU_PARAMETERS {

   AAI_PARAMETERS_LIST * Parameters_List;
   PORT                  Port;
	TEXT                  Text;
   AAI_COLORS            Colors;
   MENU                  Menu;
   char *                Menu_Text;
	char *                Menu_Keys_List;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   CARDINAL_16           Height;
	CARDINAL_16           Width;
   CARDINAL_16           Option;
   CARDINAL_16           Total_Options;
   BOOLEAN               Refresh_Flag;

} AAI_SUB_MENU_PARAMETERS;

typedef struct _AAI_MAIN_MENU_PARAMETERS {

   AAI_PARAMETERS_LIST * Parameters_List;
	TEXT                  Text;
   AAI_COLORS            Colors;
   MENU                  Menu;
   char *                Menu_Text;
   char *                Menu_Keys_List;
	CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   CARDINAL_16           Option;
   CARDINAL_16           Total_Options;
   BOOLEAN               Exit_Flag;

} AAI_MAIN_MENU_PARAMETERS;

typedef struct _AAI_FUNCTION_KEY_MENU_PARAMETERS {

   AAI_PARAMETERS_LIST * Parameters_List;
   TEXT                  Text;
   AAI_COLORS            Colors;
   MENU                  Menu;
   char *                Menu_Text;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;

   BOOLEAN               Hide_Function_Keys_Flag;

} AAI_FUNCTION_KEY_MENU_PARAMETERS;

/*

   Global Variable Definitions.

*/

/*

   AAI0.C

*/

extern char                     AAI_Main_Screen_Unique_Characters[];
extern BYTE                     AAI_Main_Screen_Unique_Colors[];
extern char                     AAI_Main_Screen_Text[];
extern char                     AAI_Main_Menu_Text[];
extern char                     AAI_Main_Menu_Descriptions_Text[];
extern char                     AAI_Function_Key_List_Text[];
extern char                     AAI_File_Menu_Text[];
extern char                     AAI_Measure_Menu_Text[];
extern char                     AAI_Product_Menu_Text[];
extern char                     AAI_Calibration_Menu_Text[];
extern char                     AAI_Setup_Menu_Text[];
extern char                     AAI_Help_Menu_Text[];
extern char *                   AAI_Menu_Text_List[];
extern AAI_MENU_CHARACTERISTICS AAI_Menu_Characteristics_List[];
extern char *                   AAI_Menu_Keys_List[];
extern AAI_PROCESS_LIST         AAI_Process_List[];
extern char *                   AAI_Help_Index_Key_List[];

/*

   Procedure and Function Prototypes.

*/

/*

   AAI1.C

*/

int  AAI_Sub_Menu(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Main_Menu(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Function_Key_Menu(void ** Process_Parameters, CARDINAL_16 * Key);

/*

   AAI2.C

*/

int  AAI_File_Load(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_File_New(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_File_Save(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_File_Save_As(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_File_Delete(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_File_Rename(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_File_Quit(void ** Process_Parameters, CARDINAL_16 * Key);

int  AAI_Edit(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Mark(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Clear(void ** Process_Parameters, CARDINAL_16 * Key);

int  AAI_Reports_Data_Dump(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Reports_Available_Configurations(void ** Process_Parameters, CARDINAL_16 * Key);

int  AAI_Send(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Receive(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Terminal(void ** Process_Parameters, CARDINAL_16 * Key);

int  AAI_Help_Index(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Help_About(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Help_Topic(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Help_Print(void ** Process_Parameters, CARDINAL_16 * Key);

/*

   AAI3.C

*/

void AAI_Activate_Process(AAI_PARAMETERS_LIST * Parameters_List, AAI_PROCESS_TYPES Process);
void AAI_Halt_Process(AAI_PARAMETERS_LIST * Parameters_List, AAI_PROCESS_TYPES Process);
int  AAI_Validate_Parameters(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Allocate_Parameters_List(CARDINAL_16 Process_Parameters_Size, void ** Process_Parameters);
int  AAI_Display_Time(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Load_Configuration(char * Config_File_Name, AAI_DEFAULT_PARAMETERS * Default_Parameters);
int  AAI_Save_Configuration(char * Config_File_Name, AAI_DEFAULT_PARAMETERS * Default_Parameters);
int  AAI_Yes_No_Menu(void ** Process_Parameters, CARDINAL_16 * Key);
int  AAI_Input(AAI_INPUT_DESCRIPTOR * Input, CARDINAL_16 * Key);
void AAI_Clear_Edit_Parameters(AAI_EDIT_EDIT_PARAMETERS * Process_Parameters);
int  AAI_Load_Edit_Parameters(char * File_Name, AAI_EDIT_EDIT_PARAMETERS * Process_Parameters);
int  AAI_Save_Edit_Parameters(char * File_Name, AAI_EDIT_EDIT_PARAMETERS * Process_Parameters);
void AAI_Set_Help_Screen(AAI_PARAMETERS_LIST * Process_Parameters, char * Key);
