# File        : DIR.MAK
# Module      : DIR
# System      : None
# Description : The makefile for the DIR module.
# Modified    : 03/06/91 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = dir.lib
OBJ1 = dir1.obj dir1a.obj dir1b.obj dir1c.obj dir1d.obj dir2.obj dir2a.obj \
       dir3.obj dir3a.obj dir3b.obj dir4.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak
     del *.bak

dir2.obj : dir2.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) -S dir2.c
     tasm /ml dir2.asm

dir2a.obj : dir2a.c
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) -S dir2a.c
     tasm /ml dir2a.asm

dir3b.obj : ..\..\ASM\Dir\dir3b.asm
     tasm /ml ..\..\ASM\Dir\dir3b.asm

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
