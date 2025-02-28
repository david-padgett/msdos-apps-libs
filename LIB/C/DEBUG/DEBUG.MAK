# File        : DEBUG.MAK
# Module      : DEBUG
# System      : None
# Description : The makefile for the DEBUG module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = debug.lib
OBJ1 = debug0.obj debug1.obj debug2.obj debug2a.obj debug2b.obj debug2c.obj \
       debug3.obj debug3a.obj debug3b.obj debug4.obj debug4a.obj debug4b.obj \
       debug4c.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
