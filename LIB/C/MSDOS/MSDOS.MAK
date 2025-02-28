# File        : DOS.MAK
# Module      : DOS
# System      : None
# Description : The makefile for the DOS module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = msdos.lib
OBJ1 = msdos1.obj msdos2.obj msdos3.obj msdos3a.obj msdos3b.obj msdos4.obj \
       msdos4a.obj msdos4b.obj msdos4c.obj msdos4d.obj msdos5.obj \
       msdos5a.obj msdos6.obj msdos6a.obj msdos7.obj msdos8.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.asm.obj:
     tasm /ml $<

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
