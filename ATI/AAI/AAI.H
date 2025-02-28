/*

   File        : AAI.H
   Module      : Definitions
   System      : AAI
   Description : The header file for the AAI program.
   Modified    : 10/08/94 DWP Created.
   Notes       :

*/

#include <dir.h>

#include "List\list.h"
#include "Menu\menu.h"
#include "Port\port.h"

/*

   Macros.

*/

#define AAI_TITLE_1                   "ATI's Acudairy Interface Version 1.0A"
#define AAI_TITLE_2                   "Copyright (C) " COMPILE_YEAR " by Analytical Technologies, Inc."
#define AAI_TITLE_3                   "and CSFX Computing Services"
#define AAI_TITLE_4                   "All Rights Reserved."
#define AAI_TITLE_5                   "Last Modified on " COMPILE_DATE
#define AAI_TITLE_6                   "Press Any key To Continue"
#define AAI_CONFIG_FILE_TITLE         "AAI Version 1.0A Configuration File\x1a"
#define AAI_CONFIG_FILE_NAME          "AAI.CFG"
#define AAI_TOTAL_PROCESSES           45
#define AAI_TOTAL_MENUS                9

#define AAI_TOTAL_MEASURE_BATCH_FIELDS 6

/*

   Type Definitions.

*/

typedef enum _AaiAdcChannels {

   AaiLactoseReference,
   AaiLactose,
   AaiProtein,
   AaiFat,
   AaiNotUsed,
   AaiCuvetteTemperature,
   AaiHValveTemperature,
   AaiPumpPressure

} AaiAdcChannels;

typedef enum _AaiProcessTypes {

   AaiDisplayTimeProcess,
   AaiFileLoadProcess,
   AaiFileNewProcess,
   AaiFileSaveProcess,
   AaiFileSaveAsProcess,
   AaiFileDeleteProcess,
   AaiFileRenameProcess,
   AaiFileQuitProcess,
   AaiMeasureMeasureProcess,
   AaiMeasurePurgeProcess,
   AaiMeasureZeroSetProcess,
   AaiMeasureSampleNrProcess,
   AaiMeasureBatchProcess,
   AaiMeasureLabelProcess,
   AaiProductProcess,
   AaiCalibrateEditMeasureProcess,
   AaiCalibrateZeroSetProcess,
   AaiCalibrateCrossCalibrationProcess,
   AaiCalibratePilotSamplesProcess,
   AaiCalibrateBiasAndSlopeProcess,
   AaiCalibrateViewCalibrationProcess,
   AaiCalibrateMineralBiasProcess,
   AaiCalibrateStatisticsProcess,
   AaiCalibrateGraphicsProcess,
   AaiCalibrateCarryOverProcess,
   AaiCalibratePolynomialProcess,
   AaiSetupPrinterProcess,
   AaiSetupOutputProcess,
   AaiSetupTemperatureProcess,
   AaiSetupHeaderProcess,
   AaiSetupFooterProcess,
   AaiSetup1stSerialPortProcess,
   AaiSetup2ndSerialPortProcess,
   AaiSetupBarcodeReaderProcess,
   AaiSetupCyclesProcess,
   AaiSetupPressureLimitProcess,
   AaiSetupChopperSpeedProcess,
   AaiHelpIndexProcess,
   AaiHelpAboutProcess,
   AaiHelpPrintProcess,
   AaiHelpTopicProcess,
   AaiYesNoMenuProcess,
   AaiSubMenuProcess,
   AaiMainMenuProcess,
   AaiFunctionKeyMenuProcess

} AaiProcessTypes;

typedef enum _AaiDisplayTypes {

   AaiColor,
   AaiMonochrome,
   AaiLcd

} AaiDisplayTypes;

typedef enum _AaiMenuTypes {

   AaiFunctionKeyMenu,
   AaiMainMenu,
   AaiFileMenu,
   AaiMeasureMenu,
   AaiProductMenu,
   AaiCalibrateMenu,
   AaiSetupMenu,
   AaiHelpMenu,
   AaiYesNoMenu

} AaiMenuTypes;

typedef enum _AaiHelpIndexKeyListValues {

   AaiHelpMainM,
   AaiHelpFileM,
   AaiHelpMeasM,
   AaiHelpProdM,
   AaiHelpCaliM,
   AaiHelpSetuM,
   AaiHelpHelpM,
   AaiHelpFlLoa,
   AaiHelpFlNew,
   AaiHelpFlSav,
   AaiHelpFlSvA,
   AaiHelpFlDel,
   AaiHelpFlRen,
   AaiHelpFlQui,
   AaiHelpMeMea,
   AaiHelpMePur,
   AaiHelpMeZer,
   AaiHelpMeSam,
   AaiHelpMeBat,
   AaiHelpMeLab,
   AaiHelpCaEdi,
   AaiHelpCaZer,
   AaiHelpCaCro,
   AaiHelpCaPil,
   AaiHelpCaBia,
   AaiHelpCaVie,
   AaiHelpCaMin,
   AaiHelpCaSta,
   AaiHelpCaGra,
   AaiHelpCaCar,
   AaiHelpCaPol,
   AaiHelpSePri,
   AaiHelpSeOut,
   AaiHelpSeTem,
   AaiHelpSeHea,
   AaiHelpSeFoo,
   AaiHelpSe1SP,
   AaiHelpSe2SP,
   AaiHelpSeBar,
   AaiHelpSeCyc,
   AaiHelpSePre,
   AaiHelpSeCho,
   AaiHelpHeInd,
   AaiHelpHeAbo,
   AaiHelpHePri,
   AaiHelpNoHlp

} AaiHelpIndexKeyListValues;

typedef struct _AaiMenuCharacteristics {

   CARDINAL_16 startingRow;
   CARDINAL_16 startingColumn;
   CARDINAL_16 height;
   CARDINAL_16 width;
   CARDINAL_16 option;
   CARDINAL_16 totalOptions;

} AaiMenuCharacteristics;

typedef struct _AaiColors {

   CARDINAL_16 primaryColor;
   CARDINAL_16 secondaryColor;
   CARDINAL_16 primaryHighlightColor;
   CARDINAL_16 secondaryHighlightColor;

} AaiColors;

typedef struct _AaiInputDescriptor {

   TEXT *          text;
   CARDINAL_16     editLength;
   CARDINAL_16     displayLength;
   CARDINAL_16     decimal;
   DATA_TYPES      type;
   AaiColors       colors;
   CARDINAL_16     currentRow;
   CARDINAL_16     currentColumn;
   BOOLEAN         markedFlag;
   BOOLEAN         refreshFlag;
   BOOLEAN         displayCursorFlag;
   BOOLEAN         colorIndicatorFlag;
   BOOLEAN         firstPassFlag;
   char            value[25];
   INTEGER_16      integerValue;
   INTEGER_16      minimumValue;
   INTEGER_16      maximumEditableValue;
   INTEGER_16      maximumLoadableValue;
   CARDINAL_16     currentOffset;
   CARDINAL_16     previousOffset;

} AaiInputDescriptor;

typedef struct _AaiDefaultParameters {

   char              id[50];

   AaiDisplayTypes displayType;

   AaiColors       functionKeyMenuColors;
   AaiColors       mainMenuColors;
   AaiColors       subMenuColors;
   AaiColors       yesNoMenuColors;
   AaiColors       editColors;

   CARDINAL_16     portA;
   CARDINAL_16     portB;
   CARDINAL_16     portC;
   CARDINAL_16     statusWord;
   CARDINAL_16     adcUpper;
   CARDINAL_16     adcLower;

} AaiDefaultParameters;

typedef struct _AaiProcess {

   int (* process)(void ** processParameters, CARDINAL_16 * key);

} AaiProcess;

typedef struct _AaiProcessDescriptor {

   CARDINAL_16 processNumber;
   BOOLEAN     processActiveFlag;
   void *      processParameters;
   AaiProcess  process;

} AaiProcessDescriptor;

typedef struct _AaiParametersList {

   AaiDisplayTypes        displayType;
   BOOLEAN                displayTypeSpecified;
   AaiDefaultParameters   defaultParameters;

   TEXT                   text;

   AaiMenuCharacteristics menuCharacteristicsList[AAI_TOTAL_MENUS];
   char *                 menuTextList[AAI_TOTAL_MENUS];
   char *                 menuKeysList[AAI_TOTAL_MENUS];
   char *                 mainScreenText;
   char *                 mainScreenCharacters;
   BYTE *                 mainScreenCharacterColors;

   AaiProcessDescriptor   processDescriptor[AAI_TOTAL_PROCESSES];
   CARDINAL_16            totalProcesses;

} AaiParametersList;

/*

   Process parameter list definitions.

*/

typedef struct _AaiSetupLoadSetupParameters {

   char                 configFileName[13];
   AaiDefaultParameters defaultParameters;
   BOOLEAN              bypassInterfaceFlag;

} AaiSetupLoadSetupParameters, AaiSetupSaveSetupParameters;

typedef struct _AaiYesNoMenuParameters {

   AaiParametersList * parametersList;
   PORT                port;
   TEXT                text;
   AaiColors           colors;
   MENU                menu;
   char *              menuText;
   char *              menuKeysList;
   CARDINAL_16         startingRow;
   CARDINAL_16         startingColumn;
   char *              displayMessage;
   CARDINAL_16         option;
   AaiProcessTypes     invokingProcess;
   BOOLEAN *           yesSelectedFlag;

} AaiYesNoMenuParameters;

typedef struct _AaiDisplayTimeParameters {

   TEXT        text;
   AaiColors   colors;
   CARDINAL_16 row;
   CARDINAL_16 column;
   int         minutesValue;
   int         secondsValue;
   char        separatorCharacter;

} AaiDisplayTimeParameters;

typedef struct _AaiFileLoadParameters {

   AaiParametersList *      parametersList;
   PORT                     port;
   TEXT                     text;
   AaiColors                colors;
   CARDINAL_16              startingRow;
   CARDINAL_16              startingColumn;
   CARDINAL_16              height;
   CARDINAL_16              width;
   LIST                     fileList;
   char                     fileName[MAXFILE];
   CARDINAL_32              currentFileNumber;
   CARDINAL_32              previousFileNumber;
   CARDINAL_32              firstFileNumber;
   CARDINAL_16              currentRow;

} AaiFileLoadParameters;

typedef struct _AaiFileNewParameters {

   AaiParametersList *     parametersList;
   AaiFileLoadParameters * loadParameters;
   BOOLEAN                 clearMemoryFlag;
   BOOLEAN                 processInProgressFlag;

} AaiFileNewParameters;

typedef struct _AaiFileSaveParameters {

   AaiParametersList *     parametersList;
   AaiFileLoadParameters * loadParameters;
   TEXT                    text;
   PORT                    port;
   AaiColors               colors;
   CARDINAL_16             startingRow;
   CARDINAL_16             startingColumn;
   CARDINAL_16             height;
   CARDINAL_16             width;
   AaiInputDescriptor      fileName;

} AaiFileSaveParameters;

typedef struct _AaiFileSaveAsParameters {

   AaiParametersList *     parametersList;
   AaiFileLoadParameters * loadParameters;

} AaiFileSaveAsParameters;

typedef struct _AaiFileDeleteParameters {

   AaiParametersList * parametersList;
   PORT                port;
   TEXT                text;
   AaiColors           colors;
   CARDINAL_16         startingRow;
   CARDINAL_16         startingColumn;
   CARDINAL_16         height;
   CARDINAL_16         width;
   LIST                fileList;
   char                fileName[MAXFILE];
   CARDINAL_32         currentFileNumber;
   CARDINAL_32         previousFileNumber;
   CARDINAL_32         firstFileNumber;
   CARDINAL_16         currentRow;
   BOOLEAN             deleteFileFlag;
   BOOLEAN             processInProgressFlag;

} AaiFileDeleteParameters;

typedef struct _AaiFileRenameParameters {

   AaiParametersList * parametersList;
   PORT                port;
   TEXT                text;
   AaiColors           colors;
   CARDINAL_16         startingRow;
   CARDINAL_16         startingColumn;
   CARDINAL_16         height;
   CARDINAL_16         width;
   PORT                newFilePort;
   CARDINAL_16         newFileStartingRow;
   CARDINAL_16         newFileStartingColumn;
   CARDINAL_16         newFileHeight;
   CARDINAL_16         newFileWidth;
   LIST                fileList;
   char                currentFileName[MAXFILE];
   AaiInputDescriptor  newFileName;
   CARDINAL_32         currentFileNumber;
   CARDINAL_32         previousFileNumber;
   CARDINAL_32         firstFileNumber;
   CARDINAL_16         currentRow;

} AaiFileRenameParameters;

typedef struct _AaiFileQuitParameters {

   AaiParametersList * parametersList;

} AaiFileQuitParameters;

typedef struct _AaiMeasureMeasureParameters {

   AaiParametersList * parametersList;

} AaiMeasureMeasureParameters;

typedef struct _AaiMeasurePurgeParameters {

   AaiParametersList * parametersList;

} AaiMeasurePurgeParameters;

typedef struct _AaiMeasureZeroSetParameters {

   AaiParametersList * parametersList;

} AaiMeasureZeroSetParameters;

typedef struct _AaiMeasureSampleNrParameters {

   AaiParametersList * parametersList;

} AaiMeasureSampleNrParameters;

typedef struct _AaiMeasureBatchParameters {

   AaiParametersList *  parametersList;
   PORT                 port;
   TEXT                 text;
   AaiColors            colors;
   CARDINAL_16          startingRow;
   CARDINAL_16          startingColumn;
   CARDINAL_16          height;
   CARDINAL_16          width;

   CARDINAL_16          field;
   AaiInputDescriptor * currentFieldDescriptor;
   AaiInputDescriptor   laboratory;
   AaiInputDescriptor   operator;
   AaiInputDescriptor   dateAndTime;
   AaiInputDescriptor   program;
   AaiInputDescriptor   typeOfSample;
   AaiInputDescriptor   batchCode;

} AaiMeasureBatchParameters;

typedef struct _AaiMeasureLabelParameters {

   AaiParametersList * parametersList;

} AaiMeasureLabelParameters;

typedef struct _AaiProductParameters {

   AaiParametersList * parametersList;

} AaiProductParameters;

typedef struct _AaiCalibrateEditMeasureParameters {

   AaiParametersList * parametersList;

} AaiCalibrateEditMeasureParameters;

typedef struct _AaiCalibrateZeroSetParameters {

   AaiParametersList * parametersList;

} AaiCalibrateZeroSetParameters;

typedef struct _AaiCalibrateCrossCalibrationParameters {

   AaiParametersList * parametersList;

} AaiCalibrateCrossCalibrationParameters;

typedef struct _AaiCalibratePilotSamplesParameters {

   AaiParametersList * parametersList;

} AaiCalibratePilotSamplesParameters;

typedef struct _AaiCalibrateBiasAndSlopeParameters {

   AaiParametersList * parametersList;

} AaiCalibrateBiasAndSlopeParameters;

typedef struct _AaiCalibrateViewCalibrationParameters {

   AaiParametersList * parametersList;

} AaiCalibrateViewCalibrationParameters;

typedef struct _AaiCalibrateMineralBiasParameters {

   AaiParametersList * parametersList;

} AaiCalibrateMineralBiasParameters;

typedef struct _AaiCalibrateStatisticsParameters {

   AaiParametersList * parametersList;

} AaiCalibrateStatisticsParameters;

typedef struct _AaiCalibrateGraphicsParameters {

   AaiParametersList * parametersList;

} AaiCalibrateGraphicsParameters;

typedef struct _AaiCalibrateCarryOverParameters {

   AaiParametersList * parametersList;

} AaiCalibrateCarryOverParameters;

typedef struct _AaiCalibratePolynomialParameters {

   AaiParametersList * parametersList;

} AaiCalibratePolynomialParameters;

typedef struct _AaiSetupPrinterParameters {

   AaiParametersList * parametersList;

} AaiSetupPrinterParameters;

typedef struct _AaiSetupOutputParameters {

   AaiParametersList * parametersList;

} AaiSetupOutputParameters;

typedef struct _AaiSetupTemperatureParameters {

   AaiParametersList * parametersList;

} AaiSetupTemperatureParameters;

typedef struct _AaiSetupHeaderParameters {

   AaiParametersList * parametersList;

} AaiSetupHeaderParameters;

typedef struct _AaiSetupFooterParameters {

   AaiParametersList * parametersList;

} AaiSetupFooterParameters;

typedef struct _AaiSetup1stSerialPortParameters {

   AaiParametersList * parametersList;

} AaiSetup1stSerialPortParameters;

typedef struct _AaiSetup2ndSerialPortParameters {

   AaiParametersList * parametersList;

} AaiSetup2ndSerialPortParameters;

typedef struct _AaiSetupBarcodeReaderParameters {

   AaiParametersList * parametersList;

} AaiSetupBarcodeReaderParameters;

typedef struct _AaiSetupCyclesParameters {

   AaiParametersList * parametersList;

} AaiSetupCyclesParameters;

typedef struct _AaiSetupPressureLimitParameters {

   AaiParametersList * parametersList;

} AaiSetupPressureLimitParameters;

typedef struct _AaiSetupChopperSpeedParameters {

   AaiParametersList * parametersList;

} AaiSetupChopperSpeedParameters;

typedef struct _AaiHelpTextList {

   CARDINAL_8 length;
   char       helpText[60];

} AaiHelpTextList;

typedef struct _AaiHelpIndexList {

   char indexKey[5];
   char indexDescription[60];
   LIST helpTextList;

} AaiHelpIndexList;

typedef struct _AaiHelpIndexParameters {

   AaiParametersList * parametersList;
   PORT                port;
   TEXT                text;
   AaiColors           colors;
   CARDINAL_16         startingRow;
   CARDINAL_16         startingColumn;
   CARDINAL_16         height;
   CARDINAL_16         width;
   FILE *              helpFile;
   BOOLEAN             endOfFile;
   AaiHelpIndexList    helpIndex;
   BOOLEAN             helpAvailableFlag;
   BOOLEAN             helpLoadedFlag;

   LIST                helpList;

   CARDINAL_32         firstRowLine;
   CARDINAL_16         currentRow;
   CARDINAL_16         previousRow;
   BOOLEAN             redrawScreenFlag;
   BOOLEAN             exitFlag;

} AaiHelpIndexParameters;

typedef struct _AaiHelpAboutParameters {

   AaiParametersList * parametersList;
   PORT                port;
   TEXT                text;
   AaiColors           colors;
   CARDINAL_16         startingRow;
   CARDINAL_16         startingColumn;
   CARDINAL_16         height;
   CARDINAL_16         width;

} AaiHelpAboutParameters;

typedef struct _AaiHelpPrintParameters {

   AaiParametersList *      parametersList;
   AaiHelpIndexParameters * indexParameters;
   AaiHelpIndexList *       helpIndex;
   AaiHelpTextList *        helpText;
   BOOLEAN                  exitFlag;
   FILE *                   reportFile;
   BOOLEAN                  printReportFlag;
   CARDINAL_16              pageNumber;
   CARDINAL_16              lineNumber;
   BOOLEAN                  newPageFlag;
   BOOLEAN                  processInProgressFlag;
   BOOLEAN                  firstIndexNodeFlag;
   BOOLEAN                  firstTextNodeFlag;

} AaiHelpPrintParameters;

typedef struct _AaiHelpTopicParameters {

   AaiParametersList *      parametersList;
   AaiHelpIndexParameters * indexParameters;
   AaiHelpIndexList *       helpIndex;
   AaiHelpTextList *        helpText;
   PORT                     port;
   TEXT                     text;
   AaiColors                colors;
   CARDINAL_16              startingRow;
   CARDINAL_16              startingColumn;
   CARDINAL_16              height;
   CARDINAL_16              width;
   char *                   key;
   CARDINAL_32              firstRowLine;
   BOOLEAN                  redrawScreenFlag;
   BOOLEAN                  exitFlag;

} AaiHelpTopicParameters;

typedef struct _AaiSubMenuParameters {

   AaiParametersList * parametersList;
   PORT                port;
   TEXT                text;
   AaiColors           colors;
   MENU                menu;
   char *              menuText;
   char *              menuKeysList;
   CARDINAL_16         startingRow;
   CARDINAL_16         startingColumn;
   CARDINAL_16         height;
   CARDINAL_16         width;
   CARDINAL_16         option;
   CARDINAL_16         totalOptions;
   BOOLEAN             refreshFlag;

} AaiSubMenuParameters;

typedef struct _AaiMainMenuParameters {

   AaiParametersList * parametersList;
   TEXT                text;
   AaiColors           colors;
   MENU                menu;
   char *              menuText;
   char *              menuKeysList;
   CARDINAL_16         startingRow;
   CARDINAL_16         startingColumn;
   CARDINAL_16         option;
   CARDINAL_16         totalOptions;
   BOOLEAN             exitFlag;

} AaiMainMenuParameters;

typedef struct _AaiFunctionKeyMenuParameters {

   AaiParametersList * parametersList;
   TEXT                text;
   AaiColors           colors;
   MENU                menu;
   char *              menuText;
   CARDINAL_16         startingRow;
   CARDINAL_16         startingColumn;

   BOOLEAN             hideFunctionKeysFlag;

} AaiFunctionKeyMenuParameters;

/*

   Global Variable Definitions.

*/

/*

   AAI0.C

*/

extern char                   AaiMainScreenUniqueCharacters[];
extern BYTE                   AaiMainScreenUniqueColors[];
extern char                   AaiMainScreenText[];
extern char                   AaiMainMenuText[];
extern char                   AaiMainMenuDescriptionsText[];
extern char                   AaiFunctionkeyListText[];
extern char                   AaiFileMenuText[];
extern char                   AaiMeasureMenuText[];
extern char                   AaiProductMenuText[];
extern char                   AaiCalibrationMenuText[];
extern char                   AaiSetupMenuText[];
extern char                   AaiHelpMenuText[];
extern char *                 AaiMenuTextList[];
extern AaiMenuCharacteristics AaiMenuCharacteristicsList[];
extern char *                 AaiMenuKeysList[];
extern AaiProcess             AaiProcessList[];
extern char *                 AaiHelpIndexKeyList[];

/*

   Procedure and Function Prototypes.

*/

/*

   AAI1.C

*/

int  aaiSubMenu(void ** processParameters, CARDINAL_16 * key);
int  aaiMainMenu(void ** processParameters, CARDINAL_16 * key);
int  aaiFunctionKeyMenu(void ** processParameters, CARDINAL_16 * key);

/*

   AAI2.C

*/

int  aaiFileLoad(void ** processParameters, CARDINAL_16 * key);
int  aaiFileNew(void ** processParameters, CARDINAL_16 * key);
int  aaiFileSave(void ** processParameters, CARDINAL_16 * key);
int  aaiFileSaveAs(void ** processParameters, CARDINAL_16 * key);
int  aaiFileDelete(void ** processParameters, CARDINAL_16 * key);
int  aaiFileRename(void ** processParameters, CARDINAL_16 * key);
int  aaiFileQuit(void ** processParameters, CARDINAL_16 * key);

int  aaiMeasureMeasure(void ** processParameters, CARDINAL_16 * key);
int  aaiMeasurePurge(void ** processParameters, CARDINAL_16 * key);
int  aaiMeasureZeroSet(void ** processParameters, CARDINAL_16 * key);
int  aaiMeasureSampleNr(void ** processParameters, CARDINAL_16 * key);
int  aaiMeasureBatch(void ** processParameters, CARDINAL_16 * key);
int  aaiMeasureLabel(void ** processParameters, CARDINAL_16 * key);

int  aaiProduct(void ** processParameters, CARDINAL_16 * key);

int  aaiCalibrateEditMeasure(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibrateZeroSet(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibrateCrossCalibration(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibratePilotSamples(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibrateBiasAndSlope(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibrateViewCalibration(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibrateMineralBias(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibrateStatistics(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibrateGraphics(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibrateCarryOver(void ** processParameters, CARDINAL_16 * key);
int  aaiCalibratePolynomial(void ** processParameters, CARDINAL_16 * key);

int  aaiSetupPrinter(void ** processParameters, CARDINAL_16 * key);
int  aaiSetupOutput(void ** processParameters, CARDINAL_16 * key);
int  aaiSetupTemperature(void ** processParameters, CARDINAL_16 * key);
int  aaiSetupHeader(void ** processParameters, CARDINAL_16 * key);
int  aaiSetupFooter(void ** processParameters, CARDINAL_16 * key);
int  aaiSetup1stSerialPort(void ** processParameters, CARDINAL_16 * key);
int  aaiSetup2ndSerialPort(void ** processParameters, CARDINAL_16 * key);
int  aaiSetupBarcodeReader(void ** processParameters, CARDINAL_16 * key);
int  aaiSetupCycles(void ** processParameters, CARDINAL_16 * key);
int  aaiSetupPressureLimit(void ** processParameters, CARDINAL_16 * key);
int  aaiSetupChopperSpeed(void ** processParameters, CARDINAL_16 * key);

int  aaiHelpIndex(void ** processParameters, CARDINAL_16 * key);
int  aaiHelpAbout(void ** processParameters, CARDINAL_16 * key);
int  aaiHelpPrint(void ** processParameters, CARDINAL_16 * key);
int  aaiHelpTopic(void ** processParameters, CARDINAL_16 * key);

/*

   AAI3.C

*/

void         aaiActivateProcess(AaiParametersList * parametersList, AaiProcessTypes process);
void         aaiHaltProcess(AaiParametersList * parametersList, AaiProcessTypes process);
int          aaiValidateParameters(void ** processParameters, CARDINAL_16 * key);
int          aaiAllocateParametersList(CARDINAL_16 processParametersSize, void ** processParameters);
int          aaiDisplayTime(void ** processParameters, CARDINAL_16 * key);
int          aaiLoadConfiguration(char * configFileName, AaiDefaultParameters * defaultParameters);
int          aaiSaveConfiguration(char * configFileName, AaiDefaultParameters * defaultParameters);
int          aaiYesNoMenu(void ** processParameters, CARDINAL_16 * key);
int          aaiInput(AaiInputDescriptor * input, CARDINAL_16 * key);
void         aaiSetHelpScreen(AaiParametersList * processParameters, char * key);
void         aaiInitialize8255(AaiParametersList * processParameters);
void         selectAdcChannel(AaiParametersList * processParameters, unsigned int channel);
void         aaiStartAdcConversion(AaiParametersList * processParameters);
void         aaiPollAdcUntilConversionIsFinished(AaiParametersList * processParameters);
unsigned int aaiReadAdcValue(AaiParametersList * processParameters);
