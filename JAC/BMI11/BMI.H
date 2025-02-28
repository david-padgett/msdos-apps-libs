/*

   File        : BMI.H
   Module      : BMI
   System      : BMI
   Description : The header file for the BMI program.
   Modified    : 08/18/92 DWP Created.
                 02/13/93 DWP Added Display_Length Maximum_Loadable_Value fields to BMI_INPUT_DESCRIPTOR.  Updated for Winchester 
                          Version.
   Notes       :

*/

#include <dir.h>

#include "List\list.h"
#include "Menu\menu.h"
#include "Port\port.h"

/*

   Macros.

*/

#define BMI_TITLE_1A                  "Basic Module Interface - Winchester Version 1.1A"
#define BMI_TITLE_1B                  "Basic Module Interface - Plant Version 1.1A"
#define BMI_TITLE_2                   "Copyright (C) "COMPILE_YEAR" by Jedco Automation Corporation"
#define BMI_TITLE_3                   "and CSFX Computing Services"
#define BMI_TITLE_4                   "All Rights Reserved."
#define BMI_TITLE_5                   "Last Modified on "COMPILE_DATE
#define BMI_TITLE_6                   "Press Any Key To Continue"
#define BMI_CONFIG_FILE_TITLE         "BMI Version 1.1 Configuration File\x1a"
#define BMI_CONFIG_FILE_NAME          "BMI.CFG"
#define BMI_TOTAL_EDIT_FIELDS        165
#define BMI_TOTAL_UNIQUE_EDIT_FIELDS   6
#define BMI_TOTAL_PROCESSES           28
#define BMI_TOTAL_MENUS                8

/*

   Type Definitions.

*/

typedef enum _BMI_PROCESS_TYPES {

   BMI_DISPLAY_TIME_PROCESS,
   BMI_FILE_LOAD_PROCESS,
   BMI_FILE_NEW_PROCESS,
   BMI_FILE_SAVE_PROCESS,
   BMI_FILE_SAVE_AS_PROCESS,
   BMI_FILE_DELETE_PROCESS,
   BMI_FILE_RENAME_PROCESS,
   BMI_FILE_QUIT_PROCESS,
   BMI_EDIT_EDIT_PROCESS,
   BMI_EDIT_MARK_PROCESS,
   BMI_EDIT_CLEAR_PROCESS,
   BMI_REPORTS_DATA_DUMP_PROCESS,
   BMI_REPORTS_AVAIL_CFG_PROCESS,
   BMI_COMMUNICATIONS_SEND_PROCESS,
   BMI_COMMUNICATIONS_RECEIVE_PROCESS,
   BMI_COMMUNICATIONS_TERMINAL_PROCESS,
   BMI_HELP_INDEX_PROCESS,
   BMI_HELP_ABOUT_PROCESS,
   BMI_HELP_PRINT_PROCESS,
   BMI_HELP_TOPIC_PROCESS,
   BMI_YES_NO_MENU_PROCESS,
   BMI_SUB_MENU_PROCESS,
   BMI_MAIN_MENU_PROCESS,
   BMI_FUNCTION_KEY_MENU_PROCESS

} BMI_PROCESS_TYPES;

typedef enum _BMI_DISPLAY_TYPES {

   BMI_COLOR,
   BMI_MONOCHROME,
   BMI_LCD

} BMI_DISPLAY_TYPES;

typedef enum _BMI_VERSION_TYPES {

   BMI_WINCHESTER_VERSION,
   BMI_PLANT_VERSION

} BMI_VERSION_TYPES;

typedef enum _BMI_MENU_TYPES {

   BMI_FUNCTION_KEY_MENU,
   BMI_MAIN_MENU,
   BMI_FILE_MENU,
   BMI_EDIT_MENU,
   BMI_REPORT_MENU,
   BMI_COMMUNICATIONS_MENU,
   BMI_HELP_MENU,
   BMI_YES_NO_MENU

} BMI_MENU_TYPES;

typedef enum _BMI_HELP_INDEX_KEY_LIST_VALUES {

   BMI_HELP_MAINM,
   BMI_HELP_FILEM,
   BMI_HELP_EDITM,
   BMI_HELP_REPTM,
   BMI_HELP_COMMM,
   BMI_HELP_HELPM,
   BMI_HELP_LODFM,
   BMI_HELP_NEWFM,
   BMI_HELP_SAVFM,
   BMI_HELP_SVAFM,
   BMI_HELP_DELFM,
   BMI_HELP_RENFM,
   BMI_HELP_QUIFM,
   BMI_HELP_EDTEM,
   BMI_HELP_MAREM,
   BMI_HELP_CLEEM,
   BMI_HELP_DDPRM,
   BMI_HELP_ACGRM,
   BMI_HELP_SNDCM,
   BMI_HELP_RECCM,
   BMI_HELP_TERCM,
   BMI_HELP_INDHM,
   BMI_HELP_ABOHM,
   BMI_HELP_PRIHM,
   BMI_HELP_NO_HELP

} BMI_HELP_INDEX_KEY_LIST_VALUES;

typedef struct _BMI_MENU_CHARACTERISTICS {

   CARDINAL_16 Starting_Row;
   CARDINAL_16 Starting_Column;
   CARDINAL_16 Height;
   CARDINAL_16 Width;
   CARDINAL_16 Option;
   CARDINAL_16 Total_Options;

} BMI_MENU_CHARACTERISTICS;

typedef struct _BMI_COLORS {

   CARDINAL_16 Primary_Color;
   CARDINAL_16 Secondary_Color;
   CARDINAL_16 Primary_Highlight_Color;
   CARDINAL_16 Secondary_Highlight_Color;

} BMI_COLORS;

typedef struct _BMI_INPUT_DESCRIPTOR {

   TEXT *          Text;
   CARDINAL_16     Edit_Length;
   CARDINAL_16     Display_Length;
   CARDINAL_16     Decimal;
   DATA_TYPES      Type;
   BMI_COLORS      Colors;
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

} BMI_INPUT_DESCRIPTOR;

typedef struct _BMI_DEFAULT_PARAMETERS {

   char              ID[50];

   BMI_DISPLAY_TYPES Display_Type;

   BMI_COLORS        Function_Key_Menu_Colors;
   BMI_COLORS        Main_Menu_Colors;
   BMI_COLORS        Sub_Menu_Colors;
   BMI_COLORS        Yes_No_Menu_Colors;
   BMI_COLORS        Edit_Colors;

   int               Port_No;

} BMI_DEFAULT_PARAMETERS;

typedef struct _BMI_PROCESS_DESCRIPTOR {

   CARDINAL_16 Process_Number;
   BOOLEAN     Process_Active_Flag;
   void *      Process_Parameters;
   int         (* Process)(void ** Process_Parameters, CARDINAL_16 * Key);

} BMI_PROCESS_DESCRIPTOR;

typedef struct _BMI_PARAMETERS_LIST {

   BMI_DISPLAY_TYPES        Display_Type;
   BOOLEAN                  Display_Type_Specified;
   int                      Port_No;
   BOOLEAN                  Port_No_Specified;
   BMI_DEFAULT_PARAMETERS   Default_Parameters;
   BMI_VERSION_TYPES	    Version;

   TEXT                     Text;

   BMI_MENU_CHARACTERISTICS Menu_Characteristics_List[BMI_TOTAL_MENUS];
   char *                   Menu_Text_List[BMI_TOTAL_MENUS];
   char *                   Menu_Keys_List[BMI_TOTAL_MENUS];
   char *                   Main_Screen_Text;
   char *                   Main_Screen_Characters;
   BYTE *                   Main_Screen_Character_Colors;

   BMI_PROCESS_DESCRIPTOR   Process_Descriptor[BMI_TOTAL_PROCESSES];
   CARDINAL_16              Total_Processes;

} BMI_PARAMETERS_LIST;

typedef struct _BMI_PROCESS_LIST {

   int (* Process)(void ** Process_Parameters, CARDINAL_16 * Key);

} BMI_PROCESS_LIST;

/*

   Process parameter list definitions.

*/

typedef struct _BMI_SETUP_LOAD_SETUP_PARAMETERS {

   char                   Config_File_Name[13];
   BMI_DEFAULT_PARAMETERS Default_Parameters;
   BOOLEAN                Bypass_Interface_Flag;

} BMI_SETUP_LOAD_SETUP_PARAMETERS, BMI_SETUP_SAVE_SETUP_PARAMETERS;

typedef struct _BMI_YES_NO_MENU_PARAMETERS {

   BMI_PARAMETERS_LIST * Parameters_List;
   PORT                  Port;
   TEXT                  Text;
   BMI_COLORS            Colors;
   MENU                  Menu;
   char *                Menu_Text;
   char *                Menu_Keys_List;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   char *                Display_Message;
   CARDINAL_16           Option;
   BMI_PROCESS_TYPES     Invoking_Process;
   BOOLEAN *             Yes_Selected_Flag;

} BMI_YES_NO_MENU_PARAMETERS;

typedef struct _BMI_DISPLAY_TIME_PARAMETERS {

   TEXT        Text;
   BMI_COLORS  Colors;
   CARDINAL_16 Row;
   CARDINAL_16 Column;
   int         Minutes_Value;
   int         Seconds_Value;
   char        Separator_Character;

} BMI_DISPLAY_TIME_PARAMETERS;

typedef struct _BMI_EDIT_EDIT_PARAMETERS {

   BMI_PARAMETERS_LIST *  Parameters_List;
   PORT                   Port;
   TEXT                   Text;
   BMI_COLORS             Colors;
   CARDINAL_16            Starting_Row;
   CARDINAL_16            Starting_Column;
   CARDINAL_16            Height;
   CARDINAL_16            Width;
   CARDINAL_16            Field;
   CARDINAL_16            Total_Fields;

   BMI_INPUT_DESCRIPTOR * Current_Field_Descriptor;

   BMI_INPUT_DESCRIPTOR   Part_Number;
   BMI_INPUT_DESCRIPTOR   Valve_Pack_Number;
   BMI_INPUT_DESCRIPTOR   Multiple_Part_Number;
   BMI_INPUT_DESCRIPTOR   Last_Bin_Sensor;
   BMI_INPUT_DESCRIPTOR   Total_Cycle_Time;
   BMI_INPUT_DESCRIPTOR   Advance_Time[80];
   BMI_INPUT_DESCRIPTOR   Retract_Time[80];

   CARDINAL_16            Top_Row_Starting_Number;
   BOOLEAN                Redraw_Timing_Values_Flag;

} BMI_EDIT_EDIT_PARAMETERS;

typedef struct _BMI_EDIT_MARK_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_EDIT_EDIT_PARAMETERS * Edit_Parameters;

} BMI_EDIT_MARK_PARAMETERS;

typedef struct _BMI_EDIT_CLEAR_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_EDIT_EDIT_PARAMETERS * Edit_Parameters;

} BMI_EDIT_CLEAR_PARAMETERS;

typedef struct _BMI_FILE_LOAD_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   PORT                       Port;
   TEXT                       Text;
   BMI_COLORS                 Colors;
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

} BMI_FILE_LOAD_PARAMETERS;

typedef struct _BMI_FILE_NEW_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   BMI_FILE_LOAD_PARAMETERS * Load_Parameters;
   BOOLEAN                    Clear_Memory_Flag;
   BOOLEAN                    Process_In_Progress_Flag;

} BMI_FILE_NEW_PARAMETERS;

typedef struct _BMI_FILE_SAVE_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   BMI_FILE_LOAD_PARAMETERS * Load_Parameters;
   TEXT                       Text;
   PORT                       Port;
   BMI_COLORS                 Colors;
   CARDINAL_16                Starting_Row;
   CARDINAL_16                Starting_Column;
   CARDINAL_16                Height;
   CARDINAL_16                Width;
   BMI_INPUT_DESCRIPTOR       File_Name;

} BMI_FILE_SAVE_PARAMETERS;

typedef struct _BMI_FILE_SAVE_AS_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_FILE_LOAD_PARAMETERS * Load_Parameters;

} BMI_FILE_SAVE_AS_PARAMETERS;

typedef struct _BMI_FILE_DELETE_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   PORT                       Port;
   TEXT                       Text;
   BMI_COLORS                 Colors;
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

} BMI_FILE_DELETE_PARAMETERS;

typedef struct _BMI_FILE_RENAME_PARAMETERS {

   BMI_PARAMETERS_LIST *       Parameters_List;
   PORT                        Port;
   TEXT                        Text;
   BMI_COLORS                  Colors;
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
   BMI_INPUT_DESCRIPTOR        New_File_Name;
   CARDINAL_32                 Current_File_Number;
   CARDINAL_32                 Previous_File_Number;
   CARDINAL_32                 First_File_Number;
   CARDINAL_16                 Current_Row;

} BMI_FILE_RENAME_PARAMETERS;

typedef struct _BMI_FILE_QUIT_PARAMETERS {

   BMI_PARAMETERS_LIST * Parameters_List;

} BMI_FILE_QUIT_PARAMETERS;

typedef struct _BMI_REPORTS_DATA_DUMP_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_FILE_LOAD_PARAMETERS * Load_Parameters;
   BMI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   BOOLEAN                    Print_Report_Flag;
   BOOLEAN                    Process_In_Progress_Flag;
   BOOLEAN                    Stop_Process_Flag;

} BMI_REPORTS_DATA_DUMP_PARAMETERS;

typedef struct _BMI_REPORTS_AVAIL_CFG_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_FILE_LOAD_PARAMETERS * Load_Parameters;
   BMI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   LIST                       File_List;
   BOOLEAN                    Print_Report_Flag;
   BOOLEAN                    Process_In_Progress_Flag;
   BOOLEAN                    Stop_Process_Flag;

} BMI_REPORTS_AVAIL_CFG_PARAMETERS;

typedef struct _BMI_COMMUNICATIONS_SEND_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   PORT                       Port;
   TEXT                       Text;
   BMI_COLORS                 Colors;
   CARDINAL_16                Starting_Row;
   CARDINAL_16                Starting_Column;
   CARDINAL_16                Height;
   CARDINAL_16                Width;
   BMI_INPUT_DESCRIPTOR       Unit_Number;
   BMI_INPUT_DESCRIPTOR       Save_Timing_Values;
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

} BMI_COMMUNICATIONS_SEND_PARAMETERS;

typedef struct _BMI_COMMUNICATIONS_RECEIVE_PARAMETERS {

   BMI_PARAMETERS_LIST *      Parameters_List;
   BMI_EDIT_EDIT_PARAMETERS * Edit_Parameters;
   PORT                       Port;
   TEXT                       Text;
   BMI_COLORS                 Colors;
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

} BMI_COMMUNICATIONS_RECEIVE_PARAMETERS;

typedef struct _BMI_COMMUNICATIONS_TERMINAL_PARAMETERS {

   BMI_PARAMETERS_LIST * Parameters_List;
   PORT                  Port;
   TEXT                  Text;
   BMI_COLORS            Colors;
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

} BMI_COMMUNICATIONS_TERMINAL_PARAMETERS;

typedef struct _BMI_HELP_TEXT_LIST {

   CARDINAL_8 Length;
   char       Help_Text[60];

} BMI_HELP_TEXT_LIST;

typedef struct _BMI_HELP_INDEX_LIST {

   char Index_Key[5];
   char Index_Description[60];
   LIST Help_Text_List;

} BMI_HELP_INDEX_LIST;

typedef struct _BMI_HELP_INDEX_PARAMETERS {

   BMI_PARAMETERS_LIST * Parameters_List;
   PORT                  Port;
   TEXT                  Text;
   BMI_COLORS            Colors;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   CARDINAL_16           Height;
   CARDINAL_16           Width;
   FILE *                Help_File;
   BOOLEAN               End_Of_File;
   BMI_HELP_INDEX_LIST   Help_Index;
   BOOLEAN               Help_Available_Flag;
   BOOLEAN               Help_Loaded_Flag;

   LIST                  Help_List;

   CARDINAL_32           First_Row_Line;
   CARDINAL_16           Current_Row;
   CARDINAL_16           Previous_Row;
   BOOLEAN               Redraw_Screen_Flag;
   BOOLEAN               Exit_Flag;

} BMI_HELP_INDEX_PARAMETERS;

typedef struct _BMI_HELP_ABOUT_PARAMETERS {

   BMI_PARAMETERS_LIST * Parameters_List;
   PORT                  Port;
   TEXT                  Text;
   BMI_COLORS            Colors;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   CARDINAL_16           Height;
   CARDINAL_16           Width;

} BMI_HELP_ABOUT_PARAMETERS;

typedef struct _BMI_HELP_PRINT_PARAMETERS {

   BMI_PARAMETERS_LIST *       Parameters_List;
   BMI_HELP_INDEX_PARAMETERS * Index_Parameters;
   BMI_HELP_INDEX_LIST *       Help_Index;
   BMI_HELP_TEXT_LIST *        Help_Text;
   BOOLEAN                     Exit_Flag;
   FILE *                      Report_File;
   BOOLEAN                     Print_Report_Flag;
   CARDINAL_16                 Page_Number;
   CARDINAL_16                 Line_Number;
   BOOLEAN                     New_Page_Flag;
   BOOLEAN                     Process_In_Progress_Flag;
   BOOLEAN                     First_Index_Node_Flag;
   BOOLEAN                     First_Text_Node_Flag;

} BMI_HELP_PRINT_PARAMETERS;

typedef struct _BMI_HELP_TOPIC_PARAMETERS {

   BMI_PARAMETERS_LIST *       Parameters_List;
   BMI_HELP_INDEX_PARAMETERS * Index_Parameters;
   BMI_HELP_INDEX_LIST *       Help_Index;
   BMI_HELP_TEXT_LIST *        Help_Text;
   PORT                        Port;
   TEXT                        Text;
   BMI_COLORS                  Colors;
   CARDINAL_16                 Starting_Row;
   CARDINAL_16                 Starting_Column;
   CARDINAL_16                 Height;
   CARDINAL_16                 Width;
   char *                      Key;
   CARDINAL_32                 First_Row_Line;
   BOOLEAN                     Redraw_Screen_Flag;
   BOOLEAN                     Exit_Flag;

} BMI_HELP_TOPIC_PARAMETERS;

typedef struct _BMI_SUB_MENU_PARAMETERS {

   BMI_PARAMETERS_LIST * Parameters_List;
   PORT                  Port;
   TEXT                  Text;
   BMI_COLORS            Colors;
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

} BMI_SUB_MENU_PARAMETERS;

typedef struct _BMI_MAIN_MENU_PARAMETERS {

   BMI_PARAMETERS_LIST * Parameters_List;
   TEXT                  Text;
   BMI_COLORS            Colors;
   MENU                  Menu;
   char *                Menu_Text;
   char *                Menu_Keys_List;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;
   CARDINAL_16           Option;
   CARDINAL_16           Total_Options;
   BOOLEAN               Exit_Flag;

} BMI_MAIN_MENU_PARAMETERS;

typedef struct _BMI_FUNCTION_KEY_MENU_PARAMETERS {

   BMI_PARAMETERS_LIST * Parameters_List;
   TEXT                  Text;
   BMI_COLORS            Colors;
   MENU                  Menu;
   char *                Menu_Text;
   CARDINAL_16           Starting_Row;
   CARDINAL_16           Starting_Column;

   BOOLEAN               Hide_Function_Keys_Flag;

} BMI_FUNCTION_KEY_MENU_PARAMETERS;

/*

   Global Variable Definitions.

*/

/*

   BMI0.C

*/

extern char                     BMI_Main_Screen_Unique_Characters[];
extern BYTE                     BMI_Main_Screen_Unique_Colors[];
extern char                     BMI_Main_Screen_Text[];
extern char                     BMI_Main_Menu_Text[];
extern char                     BMI_Main_Menu_Descriptions_Text[];
extern char                     BMI_Function_Key_List_Text[];
extern char                     BMI_File_Menu_Text[];
extern char                     BMI_Edit_Menu_Text[];
extern char                     BMI_Report_Menu_Text[];
extern char                     BMI_Communications_Menu_Text[];
extern char                     BMI_Help_Menu_Text[];
extern char *                   BMI_Menu_Text_List[];
extern BMI_MENU_CHARACTERISTICS BMI_Menu_Characteristics_List[];
extern char *                   BMI_Menu_Keys_List[];
extern BMI_PROCESS_LIST         BMI_Process_List[];
extern char *                   BMI_Help_Index_Key_List[];

/*

   Procedure and Function Prototypes.

*/

/*

   BMI1.C

*/

int  BMI_Sub_Menu(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Main_Menu(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Function_Key_Menu(void ** Process_Parameters, CARDINAL_16 * Key);

/*

   BMI2.C

*/

int  BMI_File_Load(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_File_New(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_File_Save(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_File_Save_As(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_File_Delete(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_File_Rename(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_File_Quit(void ** Process_Parameters, CARDINAL_16 * Key);

int  BMI_Edit(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Mark(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Clear(void ** Process_Parameters, CARDINAL_16 * Key);

int  BMI_Reports_Data_Dump(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Reports_Available_Configurations(void ** Process_Parameters, CARDINAL_16 * Key);

int  BMI_Send(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Receive(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Terminal(void ** Process_Parameters, CARDINAL_16 * Key);

int  BMI_Help_Index(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Help_About(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Help_Topic(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Help_Print(void ** Process_Parameters, CARDINAL_16 * Key);

/*

   BMI3.C

*/

void BMI_Activate_Process(BMI_PARAMETERS_LIST * Parameters_List, BMI_PROCESS_TYPES Process);
void BMI_Halt_Process(BMI_PARAMETERS_LIST * Parameters_List, BMI_PROCESS_TYPES Process);
int  BMI_Validate_Parameters(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Allocate_Parameters_List(CARDINAL_16 Process_Parameters_Size, void ** Process_Parameters);
int  BMI_Display_Time(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Load_Configuration(char * Config_File_Name, BMI_DEFAULT_PARAMETERS * Default_Parameters);
int  BMI_Save_Configuration(char * Config_File_Name, BMI_DEFAULT_PARAMETERS * Default_Parameters);
int  BMI_Yes_No_Menu(void ** Process_Parameters, CARDINAL_16 * Key);
int  BMI_Input(BMI_INPUT_DESCRIPTOR * Input, CARDINAL_16 * Key);
void BMI_Clear_Edit_Parameters(BMI_EDIT_EDIT_PARAMETERS * Process_Parameters);
int  BMI_Load_Edit_Parameters(char * File_Name, BMI_EDIT_EDIT_PARAMETERS * Process_Parameters);
int  BMI_Save_Edit_Parameters(char * File_Name, BMI_EDIT_EDIT_PARAMETERS * Process_Parameters);
void BMI_Set_Help_Screen(BMI_PARAMETERS_LIST * Process_Parameters, char * Key);
