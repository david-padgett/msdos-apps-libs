# File        : ICENOOUT.MAK
# Module      : ICENOOUT
# System      : ICENOOUT
# Description : The makefile for the ICENOOUT program.  Disables output on
#               self-extracting ICE files.
# Modified    : 03/05/91 DWP Created.

TRANSLATOR=bcc
TRANSLATOR_SWITCHES=-c -ml -d -C -w -k -O -Z
LINKER=tlink
LINKER_SWITCHES=/c /x
LIBRARIAN=tlib
LIBRARIAN_SWITCHES=/c

OUTPUT=icenoout.exe
OBJ1=icenoout.obj
OBJ2=c:\borlandc\lib\c0l.obj
LIB1=
LIB2=c:\borlandc\lib\emu.lib c:\borlandc\lib\mathl.lib \
     c:\borlandc\lib\cl.lib

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LINKER) $(LINKER_SWITCHES) @icenoout.lnk

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
