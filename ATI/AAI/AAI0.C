/*

   File        : AAI0.C
   Module      : GLOBALS
   System      : AAI
   Description : The global variables used in the AAI program.
   Modified    : 10/08/94 DWP Created.
   Notes       :

*/

#include <conio.h>
#include <stdio.h>

#include "aai.h"

char * AaiHelpIndexKeyList[] = {

   "MainM"
   "FileM"
   "MeasM"
   "ProdM"
   "CaliM"
   "SetuM"
   "HelpM"
   "FlLoa"
   "FlNew"
   "FlSav"
   "FlSvA"
   "FlDel"
   "FlRen"
   "FlQui"
   "MeMea"
   "MePur"
   "MeZer"
   "MeSam"
   "MeBat"
   "MeLab"
   "CaEdi"
   "CaZer"
   "CaCro"
   "CaPil"
   "CaBia"
   "CaVie"
   "CaMin"
   "CaSta"
   "CaGra"
   "CaCar"
   "CaPol"
   "SePri"
   "SeOut"
   "SeTem"
   "SeHea"
   "SeFoo"
   "Se1SP"
   "Se2SP"
   "SeBar"
   "SeCyc"
   "SePre"
   "SeCho"
   "HeInd"
   "HeAbo"
   "HePri"
   "NoHlp"
   ""
};

char AaiFunctionKeyMenuText[] =

   MENU_SECONDARY_COLOR "F1"  MENU_PRIMARY_COLOR "-Help"         MENU_HORIZONTAL_TAB "\x4" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "F2"  MENU_PRIMARY_COLOR "-Pipette"      MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "F3"  MENU_PRIMARY_COLOR "-Form Feed"    MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "F4"  MENU_PRIMARY_COLOR "-Clear Screen" MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "F5"  MENU_PRIMARY_COLOR "-Sleep"        MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "ESC" MENU_PRIMARY_COLOR "-Exit"         MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AaiMainMenuText[] =

   MENU_SECONDARY_COLOR "F" MENU_PRIMARY_COLOR "ile"      MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "M" MENU_PRIMARY_COLOR "easure"   MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "P" MENU_PRIMARY_COLOR "roduct"   MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "C" MENU_PRIMARY_COLOR "alibrate" MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "S" MENU_PRIMARY_COLOR "etup"     MENU_HORIZONTAL_TAB "\x3" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "H" MENU_PRIMARY_COLOR "elp"      MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AaiFileMenuText[] =

   MENU_SECONDARY_COLOR "L"     MENU_PRIMARY_COLOR "oad"                        MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "N"     MENU_PRIMARY_COLOR "ew"                         MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "S"     MENU_PRIMARY_COLOR "ave"                        MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_PRIMARY_COLOR   "Save " MENU_SECONDARY_COLOR "A" MENU_PRIMARY_COLOR "s" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "D"     MENU_PRIMARY_COLOR "elete"                      MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "R"     MENU_PRIMARY_COLOR "ename"                      MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "Q"     MENU_PRIMARY_COLOR "uit"                        MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AaiMeasureMenuText[] =

   MENU_SECONDARY_COLOR "M" MENU_PRIMARY_COLOR "easure"   MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "P" MENU_PRIMARY_COLOR "urge"     MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "Z" MENU_PRIMARY_COLOR "ero Set"  MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "S" MENU_PRIMARY_COLOR "ample Nr" MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "B" MENU_PRIMARY_COLOR "atch"     MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "L" MENU_PRIMARY_COLOR "abel"     MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AaiProductMenuText[] = MENU_END_OF_TEXT;

char AaiCalibrateMenuText[] =

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

char AaiSetupMenuText[] =

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

char AaiHelpMenuText[] =

   MENU_SECONDARY_COLOR "I" MENU_PRIMARY_COLOR "ndex"    MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "A" MENU_PRIMARY_COLOR "bout..." MENU_VERTICAL_TAB "\x1" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "P" MENU_PRIMARY_COLOR "rint" MENU_END_OF_OPTION MENU_END_OF_TEXT;

char AaiYesNoMenuText[] =

   MENU_SECONDARY_COLOR "Y" MENU_PRIMARY_COLOR "es" MENU_HORIZONTAL_TAB "\x2" MENU_END_OF_OPTION
   MENU_SECONDARY_COLOR "N" MENU_PRIMARY_COLOR "o"  MENU_END_OF_OPTION MENU_END_OF_TEXT;

char * AaiMenuTextList[AAI_TOTAL_MENUS] = {

   AaiFunctionKeyMenuText,
   AaiMainMenuText,
   AaiFileMenuText,
   AaiMeasureMenuText,
   AaiProductMenuText,
   AaiCalibrateMenuText,
   AaiSetupMenuText,
   AaiHelpMenuText,
   AaiYesNoMenuText

};

AaiMenuCharacteristics AaiMenuCharacteristicsList[AAI_TOTAL_MENUS] = {

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

char * AaiMenuKeysList[AAI_TOTAL_MENUS] = {

   "",            /* Function Key Menu                                                                                                                                                    */
   "FMPDCSH",     /* Main Menu, File, Measure, Product, Calibrate, Setup, Help                                                                                                            */
   "LNSADRQ",     /* File Menu, Load, New, Save, Save As, Delete, Rename, Quit                                                                                                            */
   "MPZSBL",      /* Measure Menu, Measure, Purge, Zero Set, Sample Nr, Batch, Label                                                                                                      */
   "123",         /* Product Menu                                                                                                                                                         */
   "EZRIBVMSGCP", /* Calibrate Menu, Edit/Measure, Zero Set, Cross Calibration, Pilot Samples, Bias & Scope, View Calibration, Mineral Bias, Statistics, Graphics, Carry Over, Polynomial */
   "POTHF12BCPS", /* Setup Menu, Printer, Output, Temp, Header, Footer, 1st Serial Port, 2nd Serial Port, Barcode Reader, Cycles, Pressure Limits, Chopper Speed                          */
   "IAP",         /* Help Menu, Index, About, Print                                                                                                                                       */
   "YN"           /* Yes/No Menu, Yes, No                                                                                                                                                 */

};

AaiProcess AaiProcessList[AAI_TOTAL_PROCESSES] = {

   {aaiDisplayTime},
   {aaiFileLoad},
   {aaiFileNew},
   {aaiFileSave},
   {aaiFileSaveAs},
   {aaiFileDelete},
   {aaiFileRename},
   {aaiFileQuit},
   {aaiMeasureMeasure},
   {aaiMeasurePurge},
   {aaiMeasureZeroSet},
   {aaiMeasureSampleNr},
   {aaiMeasureBatch},
   {aaiMeasureLabel},
   {aaiProduct},
   {aaiCalibrateEditMeasure},
   {aaiCalibrateZeroSet},
   {aaiCalibrateCrossCalibration},
   {aaiCalibratePilotSamples},
   {aaiCalibrateBiasAndSlope},
   {aaiCalibrateViewCalibration},
   {aaiCalibrateMineralBias},
   {aaiCalibrateStatistics},
   {aaiCalibrateGraphics},
   {aaiCalibrateCarryOver},
   {aaiCalibratePolynomial},
   {aaiSetupPrinter},
   {aaiSetupOutput},
   {aaiSetupTemperature},
   {aaiSetupHeader},
   {aaiSetupFooter},
   {aaiSetup1stSerialPort},
   {aaiSetup2ndSerialPort},
   {aaiSetupBarcodeReader},
   {aaiSetupCycles},
   {aaiSetupPressureLimit},
   {aaiSetupChopperSpeed},
   {aaiHelpIndex},
   {aaiHelpAbout},
   {aaiHelpPrint},
   {aaiHelpTopic},
   {aaiYesNoMenu},
   {aaiSubMenu},
   {aaiMainMenu},
   {aaiFunctionKeyMenu}

};

char AaiMainScreenUniqueCharacters[] =

   "≤‹ﬂ€";

BYTE AaiMainScreenUniqueColors[] = {

   CYAN,
   LIGHTCYAN,
   LIGHTCYAN,
   LIGHTCYAN

};

char AaiMainScreenText[] =
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