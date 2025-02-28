# File        : MSDOS.MAK
# Module      : MSDOS
# System      : None
# Description : The makefile for the MSDOS module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..\..\C;..\..\C\MSDos
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

msdos1.obj: ..\..\C\MSDos\msdos1.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) ..\..\C\MSDos\msdos1.c

msdos3a.obj: ..\..\C\MSDos\msdos3a.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) ..\..\C\MSDos\msdos3a.c

msdos3b.obj: ..\..\C\MSDos\msdos3b.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) ..\..\C\MSDos\msdos3b.c

msdos4.obj: ..\..\C\MSDos\msdos4.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) ..\..\C\MSDos\msdos4.c

msdos4a.obj: ..\..\C\MSDos\msdos4a.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) ..\..\C\MSDos\msdos4a.c

msdos4b.obj: ..\..\C\MSDos\msdos4b.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) ..\..\C\MSDos\msdos4b.c

msdos4c.obj: ..\..\C\MSDos\msdos4c.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) ..\..\C\MSDos\msdos4c.c

msdos4d.obj: ..\..\C\MSDos\msdos4d.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) ..\..\C\MSDos\msdos4d.c

msdos6a.obj: ..\..\C\MSDos\msdos6a.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) ..\..\C\MSDos\msdos6a.c
