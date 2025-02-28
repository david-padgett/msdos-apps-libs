	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
$comm	macro	name,dist,size,count
	comm	dist name:BYTE:count*size
	endm
	else
$comm	macro	name,dist,size,count
	comm	dist name[size]:BYTE:count
	endm
	endif
	?debug	V 300h
	?debug	S "dir2.c"
	?debug	C E960A9611706646972322E63
	?debug	C E9B0782F5A19433A5C424F524C414E44435C494E434C5544455C64+
	?debug	C 69722E68
	?debug	C E9B1782F5A1B433A5C424F524C414E44435C494E434C5544455C5F+
	?debug	C 646566732E68
	?debug	C E923812F5A056469722E68
	?debug	C E9B0782F5A19433A5C424F524C414E44435C494E434C5544455C64+
	?debug	C 69722E68
	?debug	C E9736DDD16162E2E5C5374616E646172645C7374616E646172642E+
	?debug	C 68
DIR2_TEXT	segment byte public 'CODE'
DIR2_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:DIR2_TEXT,ds:DGROUP
_DATA	segment word public 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
DIR2_TEXT	segment byte public 'CODE'
   ;	
   ;	BOOLEAN DIR_FindFirst(char far * Path, int Attribute, struct ffblk far * FFBLK) {
   ;	
	assume	cs:DIR2_TEXT
_DIR_FindFirst	proc	far
	push	bp
	mov	bp,sp
	sub	sp,4
	push	si
   ;	
   ;	
   ;	   struct ffblk * current_dta;
   ;	   BOOLEAN        result = FALSE;
   ;	
	xor	si,si
   ;	
   ;	
   ;	   /* Save registers. */
   ;	
   ;	   asm {
   ;	
   ;	      push  es
   ;	
	push	  es
   ;	
   ;	      push  ds
   ;	
	push	  ds
   ;	
   ;	      push  dx
   ;	
	push	  dx
   ;	
   ;	      push  cx
   ;	
	push	  cx
   ;	
   ;	      push  bx
   ;	
	push	  bx
   ;	
   ;	
   ;	   }
   ;	
   ;	   /* Save old DTA. */
   ;	
   ;	   asm {
   ;	
   ;	      mov   ah, 2fh
   ;	
	mov	   ah, 2fh
   ;	
   ;	      int   21h
   ;	
	int	   21h
   ;	
   ;	      mov   current_dta + 2, es
   ;	
	mov	   [bp-4] + 2, es
   ;	
   ;	      mov   current_dta, bx
   ;	
	mov	   [bp-4], bx
   ;	
   ;	
   ;	   }
   ;	
   ;	   /* Establish the new disk transfer address. */
   ;	
   ;	   asm {
   ;	
   ;	      mov   ax, FFBLK + 2
   ;	
	mov	   ax, [bp+12] + 2
   ;	
   ;	      mov   ds, ax
   ;	
	mov	   ds, ax
   ;	
   ;	      mov   dx, FFBLK
   ;	
	mov	   dx, [bp+12]
   ;	
   ;	      mov   ah, 1ah
   ;	
	mov	   ah, 1ah
   ;	
   ;	      int   21h
   ;	
	int	   21h
   ;	
   ;	
   ;	   }
   ;	
   ;	   /* Find the first file whose attribute matches exactly the specified attribute using DOS INT 21h subfunction 4Eh. */
   ;	
   ;	   asm {
   ;	
   ;	      mov   ax, Path + 2
   ;	
	mov	   ax, [bp+6] + 2
   ;	
   ;	      mov   ds, ax
   ;	
	mov	   ds, ax
   ;	
   ;	      mov   dx, Path
   ;	
	mov	   dx, [bp+6]
   ;	
   ;	      mov   cx, Attribute
   ;	
	mov	   cx, [bp+10]
   ;	
   ;	      mov   ah, 4eh
   ;	
	mov	   ah, 4eh
   ;	
   ;	      int   21h
   ;	
	int	   21h
   ;	
   ;	
   ;	      jc    near label_0
   ;	
	jc	short @1@926
@1@646:
   ;	
   ;	
   ;	   }
   ;	
   ;	   while (TRUE) {
   ;	
   ;	      /* If the attribute of the found file and the specified attribute are identical, exit. */
   ;	
   ;	      if (FFBLK->ff_attrib == Attribute) {
   ;	
	les	bx,dword ptr [bp+12]
	mov	al,byte ptr es:[bx+21]
	cbw	
	cmp	ax,word ptr [bp+10]
	jne	short @1@702
   ;	
   ;	
   ;		 result = TRUE;
   ;	
	mov	si,1
   ;	
   ;	         break;
   ;	
	jmp	short @1@926
@1@702:
   ;	
   ;	
   ;	      }
   ;	
   ;	      /* Find the next file. */
   ;	
   ;	      asm {
   ;	
   ;	         mov   ax, Path + 2
   ;	
	mov	   ax, [bp+6] + 2
   ;	
   ;	         mov   ds, ax
   ;	
	mov	   ds, ax
   ;	
   ;	         mov   dx, Path
   ;	
	mov	   dx, [bp+6]
   ;	
   ;	         mov   cx, Attribute
   ;	
	mov	   cx, [bp+10]
   ;	
   ;	         mov   ah, 4fh
   ;	
	mov	   ah, 4fh
   ;	
   ;	         int   21h
   ;	
	int	   21h
   ;	
   ;	
   ;	         jc    near label_0
   ;	
	jc	short @1@926
	jmp	short @1@646
@1@926:
   ;	
   ;	
   ;	      }
   ;	
   ;	   }
   ;	
   ;	   label_0:;
   ;	
   ;	   /* Restore original DTA. */
   ;	
   ;	   asm {
   ;	
   ;	      mov   ax, current_dta + 2
   ;	
	mov	   ax, [bp-4] + 2
   ;	
   ;	      mov   ds, ax
   ;	
	mov	   ds, ax
   ;	
   ;	      mov   dx, current_dta
   ;	
	mov	   dx, [bp-4]
   ;	
   ;	      mov   ah, 1ah
   ;	
	mov	   ah, 1ah
   ;	
   ;	      int   21h
   ;	
	int	   21h
   ;	
   ;	
   ;	   }
   ;	
   ;	   /* Restore registers. */
   ;	
   ;	   asm {
   ;	
   ;	      pop   bx
   ;	
	pop	   bx
   ;	
   ;	      pop   cx
   ;	
	pop	   cx
   ;	
   ;	      pop   dx
   ;	
	pop	   dx
   ;	
   ;	      pop   ds
   ;	
	pop	   ds
   ;	
   ;	      pop   es
   ;	
	pop	   es
   ;	
   ;	
   ;	   }
   ;	
   ;	   return (result);
   ;	
	mov	ax,si
   ;	
   ;	
   ;	}
   ;	
	pop	si
	mov	sp,bp
	pop	bp
	ret	
_DIR_FindFirst	endp
	?debug	C E9
	?debug	C FA00000000
DIR2_TEXT	ends
_DATA	segment word public 'DATA'
s@	label	byte
_DATA	ends
DIR2_TEXT	segment byte public 'CODE'
DIR2_TEXT	ends
	public	_DIR_FindFirst
_s@	equ	s@
	end
