# File        : STRING.MAK
# Module      : STRING
# System      : None
# Description : The makefile for the STRING module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = string.lib
OBJ1 = string1.obj string1a.obj string1b.obj string1c.obj string1d.obj \
       string2.obj string3.obj string4.obj string5.obj string5a.obj \
       string6.obj string6a.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
