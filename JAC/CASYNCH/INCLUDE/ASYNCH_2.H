/**
*
*  ASYNCH_2.H	Header file for ASYNCH MANAGER Level 2 Functions
*
*		This header file defines the standard error, status codes,
*		data types, and the functions which comprise Level Two.
*
*  Version 2.00 (C)Copyright Blaise Computing Inc.  1984, 1985, 1987
*
**/

#ifndef  DEF_ASYNCH_2		       /* Avoid duplicate definition   */

#include <asynch_1.h>		       /* "_a1" function definitions   */

#define MEM_ALLOC_ERR	    11
#define INV_IN_Q_SIZE	   114	       /* Parameter setting errors re- */
#define INV_OUT_Q_SIZE	   124	       /* turned by OPEN_A2	       */
#define INV_INT_VALUE	   134
#define INV_BAUD_RATE	    14	       /* Parameter setting errors re- */
#define INV_PARITY	    24	       /* turned by SETOP_A2	       */
#define INV_DATA_BITS	    34
#define INV_STOP_BITS	    44
#define INV_REMOTE_FLOW     54
#define INV_LOCAL_FLOW	    64
#define INV_TRIMMING	    74
#define INV_FORCING	    84
#define INV_REQ_CTS	    94
#define INV_BREAK_TIME	   104

#define TRUE		   -1	       /* Constants used by Level Two	*/
#define FALSE		    0
#define ON		    1
#define OFF		    0
#define NONE		    0
#define ODD		    1
#define EVEN		    2

/* For the Level One functions which do not change at Level Two, just  */
/* equate names.						       */

#define wrtbk_a2    wrtbk_a1	       /* Write a block 	       */
#define wrtst_a2    wrtst_a1	       /* Write a string	       */
#define wrtch_a2    wrtch_a1	       /* Write a character	       */
#define rdbk_a2     rdbk_a1	       /* Read a block		       */
#define rdst_a2     rdst_a1	       /* Read a string 	       */
#define rdch_a2     rdch_a1	       /* Read a character	       */
#define qsize_a2    qsize_a1	       /* Return input queue size      */
#define oqsiz_a2    oqsiz_a1	       /* Return output queue size     */
#define oflsh_a2    oflsh_a1	       /* Flush the output queue       */
#define iflsh_a2    iflsh_a1	       /* Flush the input queue        */
#define break_a2    break_a1	       /* Send a break signal	       */
#define wait_a2     wait_a1	       /* Suspend processing	       */
#define bflag_a2    bflag_a1	       /* Return critical section flag */
#define init_a2     init_a1	       /* BIOS initialization of a port*/
#define stat_a2     stat_a1	       /* BIOS return of COM status    */
#define rcvch_a2    rcvch_a1	       /* BIOS read a character        */
#define sndch_a2    sndch_a1	       /* BIOS send a character        */

typedef struct			       /* Data transmission options    */
{
   int baud_rate;
   int parity;
   int data_bits;
   int stop_bits;
   int remote_flow_ctrl;
   int local_flow_ctrl;
   int bit_trimming;
   int bit_forcing;
   int require_cts;
   int break_time;
} POPT;

/* Level Two function declarations				       */

int cdecl open_a2(int,int,int,int,int);/* Open a COM port	       */
int cdecl close_a2(int);	       /* Close a COM port	       */
int cdecl setop_a2(int,POPT *);        /* Set transmission options     */
int cdecl retop_a2(int,POPT *);        /* Return transmission options  */
				       /* BIOS send a string	       */
int cdecl sndst_a2(int,char *,int,int *);

#define  DEF_ASYNCH_2	1	       /* Prevent a second reading of  */
#endif				       /* these definitions.	       */
