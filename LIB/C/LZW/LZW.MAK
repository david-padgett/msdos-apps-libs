# File        : LZW.MAK
# Module      : LZW
# System      : None
# Description : The makefile for the LZW module.
# Modified    : 03/06/91 DWP Created.

.AUTODEPEND

TRANSLATOR=bcc
TRANSLATOR_SWITCHES=-c -ml -d -C -w -k -O -Z -I..
LINKER=tlink
LINKER_SWITCHES=/c /x
LIBRARIAN=tlib
LIBRARIAN_SWITCHES=/c

OUTPUT=lzw.lib
OBJ1=lzw0.obj lzw1.obj lzw2.obj lzw3.obj lzw4.obj
OBJ2=
LIB1=
LIB2=

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
