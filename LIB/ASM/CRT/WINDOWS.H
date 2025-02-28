/* File        : WINDOWS.H
   Description : The C header file for WINDOWS.ASM.
   Modified    : 05/21/90 DWP Created.
*/

#ifndef WINDOWS
#define WINDOWS

#define WN_NOPOPUP  0
#define WN_POPUP    1

#define WN_NOSHADOW 0
#define WN_SHADOW   1

/* Border definitions - Border definitions consist of 6 characters and are
                        defined as follows:  top left corner, top line, top
                        right corner, left line, right line, bottom left
                        corner, bottom line, bottom right corner.  The border
                        definition string does not need to be \0 terminated */

#define WN_BDR_SINGLE "ÚÄ¿³ ³ÀÄÙ" /* Single line border                     */
#define WN_BDR_DOUBLE "ÉÍ»º ºÈÍ¼" /* Double line border                     */
#define WN_BDR_DRSC   "ÕÍ¸³ ³ÔÍ¾" /* Double row, single column              */
#define WN_BDR_SRDC   "ÖÄ·º ºÓÄ½" /* Single row, double column              */
#define WN_BDR_DTOP   "ÕÍ¸³ ³ÀÄÙ" /* Double top row, rest is single         */
#define WN_BDR_DBOT   "ÚÄ¿³ ³ÔÍ¾" /* Double bottom row, rest is single      */
#define WN_BDR_DLEFT  "ÖÄ¿º ³ÓÄÙ" /* Double left column, rest is single     */
#define WN_BDR_DRIGHT "ÚÄ·³ ºÀÄ½" /* Double right column, rest is single    */
#define WN_BDR_STOP   "ÖÄ·º ºÈÍ¼" /* Single top row, rest is double         */
#define WN_BDR_SBOT   "ÉÍ»º ºÓÄ½" /* Single bottom row, rest is double      */
#define WN_BDR_SLEFT  "ÕÍ»³ ºÔÍ¼" /* Single left column, rest is double     */
#define WN_BDR_SRIGHT "ÉÍ¸º ³ÈÍ¾" /* Single right column, rest is double    */

typedef struct window_rec_type {
   unsigned char row;         /* top left row coord. of window (absolute)   */
   unsigned char col;         /* top left col coord. of window (absolute)   */
   unsigned char length;      /* length of window                           */
   unsigned char width;       /* width of window                            */
   int           attr;        /* foreground/background color of window      */
   char          *border;     /* border characters, NULL = no border        */
   int           border_attr; /* border attribute, not used if border = NULL*/
   unsigned char type;        /* type of window, [WN_NOPOPUP, WN_POPUP]     */
   unsigned char background;  /* type of background [WN_NOSHADOW, WN_SHADOW]*/
   char          *bufr;       /* save buffer                                */
} window_rec;

#endif
