/* File        : ARCHIVE.H
   Description : Header file for archive.asm/archive.obj.
   Modified    : 01/23/90 DWP Created
*/

#ifndef ARCHIVE_MODULE
#define ARCHIVE_MODULE

/* Function    : lzw_compress
   Description : Compresses a contiguous block of memory  using the
                 Lempel-Ziv-Welch data compression algorithm discussed in
                 Dr. Dobbs Journal, October, 1989, starting on page 29.  There
                 are 3 different code lengths used in the compression, 9, 10,
                 and 12.  This algorithm tries each of the code lengths,
                 the code length with the best compression results is the one
                 actually used.
   Expects     : far ptr SOURCE = far addr of buffer for input data
                                  byte 0  = size of SOURCE, low byte
                                  byte 1  = size of SOURCE, high byte
                                  byte 2+ = actual data buffer
                 far ptr DEST   = far addr of buffer for output data
                                  byte 0  = size of DEST, low byte (undefined)
                                  byte 1  = size of DEST, hight byte (undefined)
                                  byte 2  = compression code used (undefined)
                                  byte 3+ = actual data buffer (undefined)
                                  DEST should be the same size as SOURCE.
   Returns     : DEST byte 0  = size of DEST, low byte
                      byte 1  = size of DEST, high byte
                      byte 2  = compression code used, now defined (0, 1, 2, or 4)
                      byte 3+ = image of SOURCE compressed using code type DEST.byte 2
                                with length (DEST.byte 1)*256 + DEST.byte 2
                 AX           = Error Code (0 = no errors)
   Modified    : 12/21/89 DWP Initial coding completed
                 01/25/90 DWP Completed recoding for use with buffers, no I/O required
   Notes       : 1) Uses PASCAL calling conventions
                 2) Requires that 25106 bytes be available from DOS
*/

int far pascal lzw_compress(char far *source, char far *dest);

/* Function  : lzw_expand
   Description : Expands a contiguous block of memory previously compressed
                 with LZW_COMPRESS.
   Expects     : far ptr SOURCE = far addr of buffer for input data
                                  byte 0  = size of SOURCE, low byte
                                  byte 1  = size of SOURCE, high byte
                                  byte 2  = compression code length (assigned
                                            in LZW_COMPRESS (0, 1, 2, or 4)
                                  byte 3+ = actual data buffer
                 far ptr DEST   = far addr of buffer for output data
                                  byte 0  = size of DEST, low byte (undefined)
                                  byte 1  = size of DEST, high byte (undefined)
                                  byte 2+ = actual data buffer (undefined)
                                  DEST should be the size as SOURCE
   Returns     : DEST byte 0  = size of DEST, low byte
                      byte 1  = size of DEST, high byte
                      byte 2+ = uncompressed image of SOURCE with length
                                (DEST.byte 1)*256 + DEST.byte 0
                 AX = Error Code (0=successful, no errors)
   Modified    : 12/21/89 DWP Initial coding completed
                 01/25/90 DWP Completed update for use with memory buffers
   Notes       : 1) Uses PASCAL calling conventions
                 2) Requires that 29,202 bytes be available from DOS
*/

int far pascal lzw_expand(char far *source, char far *dest);

#endif
