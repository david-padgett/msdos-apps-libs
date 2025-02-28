/* File        : PRINTER.H
   Module      : PRINTER
   System      : None
   Description : The C interface header file for the PRINTER module.
   Modified    : 08/01/90 DWP Created.
   Notes       :
*/

#ifndef _PRINTER_MODULE
#define _PRINTER_MODULE

#define PRINTER_NOT_BUSY      0x80
#define PRINTER_ACKNOWLEDGE   0x40
#define PRINTER_OUT_OF_PAPER  0x20
#define PRINTER_SELECTED      0x10
#define PRINTER_IO_ERROR      0x08
#define PRINTER_TIME_OUT      0x01
#define PRINTER_OK            ((PRINTER_NOT_BUSY | PRINTER_SELECTED) & ~PRINTER_OUT_OF_PAPER & ~PRINTER_IO_ERROR)
#define PRINTER_ERROR         (PRINTER_OUT_OF_PAPER | PRINTER_IO_ERROR)

/* Procedures and Functions. */

unsigned int pascal PRINTER_Status(unsigned int Printer_Number);

#endif
