/*

   File        : Values.C
   Module      : Test
   System      : AAI
   Description : This program polls the adc used by ATI's milk analyzer.
   Modified    : 12/17/94 DWP Created.
   Notes       :

*/

#include <dos.h>
#include <stdio.h>
#include <stdlib.h>

#include "kb\kb.h"

/*

   Global variables.

*/

unsigned int portA = 0x300;
unsigned int portB = 0x301;
unsigned int portC = 0x302;
unsigned int statusWord = 0x0303;
unsigned int adcUpper = 0x308;
unsigned int adcLower = 0x309;

/*

   Procedures and Functions.

*/

/*

   Procedure   : initialize8255
   Description : Initializes the Intel 8255 located on ATI's milk analyzer i/o card.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 12/17/94 DWP Initial coding.
   Notes       :

*/

void initialize8255(void) {

   /*

      Initializes the 8255 and the i/o card.  This might need to be changed.

   */

   outportb(statusWord, 0x89);
   outportb(portA, 0x06);
   outportb(portB, 0x01);

}

/*

   Procedure   : selectAdcChannel
   Description : Selects one of the 8 channels located on ATI's milk analyzer i/o card.
   Inputs      : channel = The channel to select.  See notes.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 12/17/94 DWP Initial coding.
   Notes       : 1)  Selects the adc channel to monitor.  Values are as follows:

                    0 - Lactose Reference
                    1 - Lactose
                    2 - Protein
                    3 - Fat
                    4 - Not Used
                    5 - Cuvette Temperature
                    6 - H Valve Temperature
                    7 - Pump Pressure

*/

void selectAdcChannel(unsigned int channel) {

   /*

      Selects the adc channel to monitor.

   */

   outportb(portB, (channel << 3) | 0x01);

}

/*

   Procedure   : startAdcConversion
   Description : Tells the adc located on ATI's milk analyzer i/o card to start the conversion.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 12/17/94 DWP Initial coding.
   Notes       :

*/

void startAdcConversion(void) {

   /*

      Tell the adc to start its conversion.

   */

   outport(adcUpper, 0x00);

}

/*

   Procedure   : pollAdcUntilConversionIsFinished
   Description : Polls the adc in ATI's milk analzyer i/o card until the conversion process has finished.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Nothing.
   Modified    : 12/17/94 DWP Initial coding.
   Notes       :

*/

void pollAdcUntilConversionIsFinished(void) {

   unsigned int status = 0;
   BOOLEAN      adcBusyFlag = TRUE;

   /*

      Tell the adc to start its conversion.

   */

   outport(adcUpper, 0x00);

   /*

      Loop until the conversion has been completed.

   */

   while (adcBusyFlag) {

      status = inportb(portC) & 0x10;

      if (status == 0) {

         adcBusyFlag = FALSE;

      }

   }

}

/*

   Function    : readAdcValue
   Description : Gets the value that was most recently converted by the adc from ATI's milk analyzer i/o card.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : The most recently converted value.
   Modified    : 12/17/94 DWP Initial coding.
   Notes       :

*/

unsigned int readAdcValue(void) {

   /*

      Read the adc value.  The lower value is read first, then the lower 4
      bits are exchanged with the upper 4 bits.

      Comment not finished.

   */

   return ((_rotr(inportb(adcLower), 4) + _rotl(inportb(adcUpper), 4)) & 0x7fff);

}

/*

   Function    : main
   Description : The main entry point to the Values program.  Continuously polls ATI's milk analyzer i/o card for data.
   Inputs      : Nothing.
   Updates     : Nothing.
   Outputs     : Nothing.
   Returns     : Always returns 0.
   Modified    : 12/17/94 DWP Initial coding.
   Notes       : 1)  Press ESC to stop the program.
                 2)  Press the space bar to pause/resume polling.

*/

int main(void) {

   unsigned int lactoseReference = 0;
   unsigned int lactose = 0;
   unsigned int protein = 0;
   unsigned int fat = 0;
   unsigned int cuvetteTemperature = 0;
   unsigned int hValveTemperature = 0;
   unsigned int pumpPressure = 0;
   BOOLEAN      exitFlag = FALSE;
   BOOLEAN      paused = FALSE;

   initialize8255();

   while (!exitFlag) {

      /*

         Do nothing if the program has been paused by pressing the space bar.

      */

      if (!paused) {

         /*

            Get the lactose reference.

         */

         selectAdcChannel(0);
         startAdcConversion();
         pollAdcUntilConversionIsFinished();
         lactoseReference = readAdcValue();

         /*

            Get the lactose.

         */

         selectAdcChannel(1);
         startAdcConversion();
         pollAdcUntilConversionIsFinished();
         lactose = readAdcValue();

         /*

            Get the protein.

         */

         selectAdcChannel(2);
         startAdcConversion();
         pollAdcUntilConversionIsFinished();
         protein = readAdcValue();

         /*

            Get the fat.

         */

         selectAdcChannel(3);
         startAdcConversion();
         pollAdcUntilConversionIsFinished();
         fat = readAdcValue();

         /*

            Get the cuvette temperature.

         */

         selectAdcChannel(5);
         startAdcConversion();
         pollAdcUntilConversionIsFinished();
         cuvetteTemperature = readAdcValue();

         /*

            Get the h valve temperature.

         */

         selectAdcChannel(6);
         startAdcConversion();
         pollAdcUntilConversionIsFinished();
         hValveTemperature = readAdcValue();

         /*

            Get the pump pressure.

         */

         selectAdcChannel(7);
         startAdcConversion();
         pollAdcUntilConversionIsFinished();
         pumpPressure = readAdcValue();

         /*

            Display the results.

         */

         printf("LR %5.5u LA %5.5u PR %5.5u FA %5.5u CT %5.5u HV %5.5u PP %5.5u\n", lactoseReference, lactose, protein, fat, cuvetteTemperature, hValveTemperature, pumpPressure);

      }

      /*

         Exit the loop if ESC has been pressed.

      */

      if (KB_Preview()) {

         switch (KB_Read()) {

            case KB_SPACE :

               paused = !paused;
               break;

            case KB_ESC :

               exitFlag = TRUE;
               break;

            default :

               break;

         }

      }

   }
selectAdcChannel(7);
   return (0);

}
