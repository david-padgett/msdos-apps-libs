/**
*
*  SUPPORT.H	Header file for Test Program Support Functions
*
*		This header file defines macros, data types, and
*		declares functions used by the ASYNCH Manager test
*		programs TESTASC, MESSAGE and FILEMOVE.
*
*  Version 2.00 (C)Copyright Blaise Computing Inc.  1987
*
**/

#ifndef min
#define min(a,b)      ((a)<=(b)?(a):(b))     /* Minimum of two values  */
#endif

#define utbell putch(0x07);

void sccurset(int,int); 	       /* Position the cursor	       */
void sccurst(int *,int *,int *,int *); /* Return cursor position & size*/
void sccursor(int,int,int);	       /* Set cursor size	       */
void scscroll(int,int,int,int,int,int);/* Scroll a specified window    */
void scclear(void);		       /* Clear the screen	       */
void scattrib(int,int,char,unsigned);  /* Display character with attr  */
void scwrite(char,unsigned);	       /* Display character	       */
void scdspmsg(int,int,int,int,char *); /* Display a message	       */
void scclrmsg(int,int,int);	       /* Clear a message	       */
int  aprdnum(char *);		       /* Return a numeric response    */
int  aprdtext(char *,char *);	       /* Return a text response       */
unsigned char utinkey(unsigned char *);/* Return key sequence	       */
void utpause(char *);		       /* Suspend processing	       */
