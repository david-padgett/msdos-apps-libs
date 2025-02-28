# File        : TEXT.MAK
# Module      : TEXT
# System      : None
# Description : The makefile for the TEXT module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = text.lib
OBJ1 = text1.obj text1a.obj text2.obj text2a.obj text2b.obj text2c.obj \
       text2d.obj text2e.obj text3.obj text3a.obj text3b.obj text3c.obj \
       text3d.obj text4.obj text4a.obj text4b.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
