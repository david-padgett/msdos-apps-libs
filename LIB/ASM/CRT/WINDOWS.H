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

#define WN_BDR_SINGLE "�Ŀ� ����" /* Single line border                     */
#define WN_BDR_DOUBLE "�ͻ� ��ͼ" /* Double line border                     */
#define WN_BDR_DRSC   "�͸� ��;" /* Double row, single column              */
#define WN_BDR_SRDC   "�ķ� ��Ľ" /* Single row, double column              */
#define WN_BDR_DTOP   "�͸� ����" /* Double top row, rest is single         */
#define WN_BDR_DBOT   "�Ŀ� ��;" /* Double bottom row, rest is single      */
#define WN_BDR_DLEFT  "�Ŀ� ����" /* Double left column, rest is single     */
#define WN_BDR_DRIGHT "�ķ� ��Ľ" /* Double right column, rest is single    */
#define WN_BDR_STOP   "�ķ� ��ͼ" /* Single top row, rest is double         */
#define WN_BDR_SBOT   "�ͻ� ��Ľ" /* Single bottom row, rest is double      */
#define WN_BDR_SLEFT  "�ͻ� ��ͼ" /* Single left column, rest is double     */
#define WN_BDR_SRIGHT "�͸� ��;" /* Single right column, rest is double    */

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