/**
*
*  ASYNCH_1.H	Header file for ASYNCH MANAGER Level 1 Functions
*
*		This header file defines the standard error and status
*		codes, and the functions which comprise Level 1.
*
*  Version 2.00 (C)Copyright Blaise Computing Inc.  1984, 1987
*
**/

#ifndef DEF_ASYNCH_1		       /* Avoid duplicate definition   */

#define OK		     0
#define INV_PORT	     2
#define PORT_NOT_OPEN	     3
#define INV_PARAMETER	     4
#define NO_PORT_FOUND	     6
#define OUT_Q_FULL	     7
#define PORT_OPEN_ALREADY    9
#define IN_Q_EMPTY	    10
#define INTERNAL_ERROR	   255

#define INPUT_LOST	   0x0001      /* Port status word values re-  */
#define ASYNCH_ERROR	   0x0002      /* turned by the read functions.*/
#define PARITY		   0x0010
#define OVERRUN 	   0x0020
#define FRAMING 	   0x0040
#define BREAK		   0x0080
#define REM_XOFF	   0x1000
#define REM_XON 	   0x2000
#define LOC_XOFF	   0x4000
#define LOC_XON 	   0x8000
#define STATUS_ERR	   0x00F3      /* INPUT_LOST + ASYNCH_ERROR +  */
				       /* PARITY + OVERRUN + FRAMING + */
				       /* FRAMING errors.	       */
#define COM1		   1	       /* Port numbers		       */
#define COM2		   2

#define NIL	((void *) 0)	       /* Universal nil pointer        */

/* Declaration of Level One functions				       */
				       /* Determine presence of LCOM   */
int cdecl iscom_a1(int,unsigned *,unsigned *,char far **);
				       /* Open a COM port	       */
int cdecl open_a1(int,int,int,int,int,char *);
int cdecl close_a1(int);	       /* Close a COM port	       */
				       /* Write a block 	       */
int cdecl wrtbk_a1(int,int,char,char *,int *);
				       /* Write a string	       */
int cdecl wrtst_a1(int,int,char *,int *);
int cdecl wrtch_a1(int,char);	       /* Write a character	       */
				       /* Read a character	       */
int cdecl rdch_a1(int,char *,int *,unsigned *);
				       /* Read a string 	       */
int cdecl rdst_a1(int,int,char *,int *,int *,unsigned *);
				       /* Read a block		       */
int cdecl rdbk_a1(int,int,char,char *,int *,int *,unsigned *);
				       /* Return input queue size      */
int cdecl qsize_a1(int,int *,unsigned *);
int cdecl oqsiz_a1(int,int *);	       /* Return output queue size     */
int cdecl setop_a1(int,int,int);       /* Set transmission options     */
int cdecl retop_a1(int,int,int *);     /* Return transmission options  */
int cdecl oflsh_a1(int);	       /* Flush the output queue       */
int cdecl iflsh_a1(int);	       /* Flush the input queue        */
int cdecl break_a1(int);	       /* Send a break signal	       */
				       /* BIOS initialization of a port*/
int cdecl init_a1(int,int,int,int,int,int *,int *);
int cdecl stat_a1(int,int *,int *);    /* BIOS return of COM status    */
int cdecl rcvch_a1(int,char *);        /* BIOS read a character        */
int cdecl sndch_a1(int,char);	       /* BIOS send a character        */
				       /* Return the busy flag	       */
int cdecl bflag_a1(int,int *,int far **);
unsigned cdecl wait_a1(unsigned);      /* Suspend processing	       */


#define DEF_ASYNCH_1	   1	       /* Prevent second reading of    */
#endif				       /* these definitions	       */
