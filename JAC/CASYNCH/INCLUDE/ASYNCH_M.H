/**
*
*  ASYNCH_M.H	Header file for ASYNCH MANAGER Modem Control
*
*		This header file defines the standard error, status codes,
*		data types, and the functions which comprise the modem
*		control functions.
*
*  Version 2.00 (C)Copyright Blaise Computing Inc.  1984, 1985, 1987
*
**/

#ifndef  DEF_ASYNCH_M		       /* Avoid duplicate definition   */

#include <asynch_2.h>		       /* "_a2" function definitions   */

#define MD_NOT_INIT	   266	       /* Modem control return codes   */
#define PRE_TRAN_ERR	   267
#define CMD_TRAN_ERR	   268
#define SUF_TRAN_ERR	   269
#define MD_READ_ERR	   270
#define RSP_NOT_COMPLETE   271

typedef struct			       /* Modem control structure      */
{
   char *prefix;		       /* Modem command prefix	       */
   int	pre_len;		       /* Command prefix length        */
   int	cmd_len;		       /* Maximum command length       */
   char *suffix;		       /* Modem command suffix	       */
   int	suf_len;		       /* Command suffix length        */
   int	resp_delay;		       /* Delay before reading response*/
   int	mport_no;		       /* Communications port number   */
} MDPARM;

int parm_md(MDPARM **); 	       /* Initialize modem ctrl struc  */
int cmd_md(char *,int *);	       /* Send a command to the modem  */
int resp_md(char *,int,int *);	       /* Receive a modem command resp */

#define  DEF_ASYNCH_M	1	       /* Prevent a second reading of  */
#endif				       /* these definitions.	       */
