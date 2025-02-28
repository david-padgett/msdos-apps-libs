# File        : DATE.MAK
# Module      : DATE
# System      : None
# Description : The makefile for the DATE module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = date.lib
OBJ1 = date0.obj date0a.obj date1.obj date2.obj date3.obj date4.obj \
       date5.obj date6.obj date6a.obj date7.obj date8.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
