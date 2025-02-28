# File        : XBASE.MAK
# Module      : XBASE
# System      : None
# Description : The makefile for the XBASE module.
# Modified    : 01/10/2025 DWP Created.
# Notes       :

.AUTODEPEND

TRANSLATOR = bcc
TRANSLATOR_SWITCHES = -c -ml -d -C -w -k -O -Z -I..
LINKER = tlink
LINKER_SWITCHES = /c /x
LIBRARIAN = tlib
LIBRARIAN_SWITCHES = /c

OUTPUT = xbase.lib
OBJ1 = xbase0.obj xbase1.obj xbase2.obj xbase2a.obj xbase2b.obj xbase2c.obj \
       xbase2d.obj xbase3.obj xbase3a.obj xbase3b.obj xbase3c.obj xbase4.obj \
       xbase4a.obj xbase4b.obj xbase4c.obj xbase4d.obj xbase4e.obj xbase4f.obj \
	   xbase4g.obj xbase4h.obj xbase4i.obj xbase4j.obj  xbase4k.obj \
	   xbase4l.obj xbase4m.obj xbase4n.obj xbase4o.obj xbase4p.obj \
	   xbase4q.obj xbase4r.obj xbase4s.obj xbase4t.obj xbase4u.obj xbase4v.obj \
	   xbase4w.obj xbase4x.obj xbase5.obj xbase5a.obj xbase5b.obj
OBJ2 =
LIB1 =
LIB2 =

$(OUTPUT) : $(OBJ1) $(OBJ2) $(LIB1) $(LIB2)
     $(LIBRARIAN) $(LIBRARIAN_SWITCHES) $(OUTPUT) @lib.mak

.c.obj:
     $(TRANSLATOR) $(TRANSLATOR_SWITCHES) {$< }
