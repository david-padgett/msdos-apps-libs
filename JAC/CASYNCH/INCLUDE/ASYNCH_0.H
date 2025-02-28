/**
*
*  ASYNCH_0.H	Header file for Access to Level 0 Functions
*
*		This header file defines macros, data types, and
*		declares functions needed by the Level 1 functions
*		to access the Level 0 functions.
*
*  Version 2.00 (C)Copyright Blaise Computing Inc.  1984, 1987
*
**/

#ifndef  DEF_ASYNCH_0		       /* Avoid duplicate definition   */

#include <dos.h>
#include <conio.h>

#define COM1_ADS    0x3f8
#define COM2_ADS    0x2f8

#define utinp(port) (inp (port))       /* Return a byte from a port    */
				       /* Put a byte in a port.        */
#define utoutp(port,bval) ((void) outp ((port), (int) (bval)))

#define uthiword(a)   (((a)>>16)&0xffffL)   /* High word of long a.    */
#define utloword(a)   ((a)&0xffffL)	    /* Low  word of long a.    */

				/* Combine high word a,low word b.     */
#define utwdlong(a,b) ((((0xffffL&(long)(a)))<<16)|		     \
		       (0xffffL&(long)(b)))

#define uthibyte(a)   (((a)>>8)&0x00ff) /* High byte of word a.        */
#define utlobyte(a)   ((a)&0x00ff)	/* Low	byte of word a.        */

				/* Combine high byte a, low byte b.    */
#define utbyword(a,b) ((((a)&0x00ff)<<8)|((b)&0x00ff))

#define uthinyb(a)    (((a)>>4)&0x000f) /* High nybble of byte a.      */
#define utlonyb(a)    ((a)&0x000f)	/* Low nybble  of byte a.      */

				/* Combine high nybble a, low	       */
				/* nybble b.			       */
#define utnybbyt(a,b) ((((a)&0x000f)<<4)|((b)&0x000f))


				/* Construct far void pointer.	       */
#define uttofaru(seg,off) ((void far *) 			     \
			   ((((unsigned long) (unsigned int)	     \
			     (seg)) << 16L) |			     \
			   ((unsigned long) (unsigned int) (off))))

				/* Compute offset of referenced memory */
#define utoff(p) ((unsigned int) (p))

				/* Compute segment of referenced memory*/
#define utseg(p) ((unsigned int)				     \
		  (((unsigned long) (void far *) (p)) >> 16L))

				/* Make a far pointer to a type.       */
#define uttofar(seg,off,type) ((type far *) uttofaru((seg),(off)))

				/* Return 1 if a is outside the range  */
				/* defined by l and h, 0 if not.       */
#define utrange(a,l,h)	(((a) < (l)) || ((a) > (h)))


typedef struct			       /* Structure for Level Zero gate*/
{
   unsigned ax,bx,cx,dx,si,di,ds,es;
} COMREG;

int cdecl comgate(COMREG *);	       /* General Level Zero gate      */

#define  DEF_ASYNCH_0	1	       /* Prevent a second reading of  */
#endif				       /* these definitions.	       */
