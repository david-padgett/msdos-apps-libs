#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <bios.h>
#include <dos.h>

int main(void)
{             
 unsigned char stat,stat2;
 unsigned int lower,upper,total;
 int total1;
 int portad  = 0x308; /* a/d address */
 int portpia  = 0x300; /* pia   "     */
 int portpiac  = 0x303; /* pia control word address */
 int A=1,B=1;
char ch;

 /* setup pia port a and b output, c input | output 0x00 to port a & b */
 outportb(portpiac,0x89);
 outportb(portpia,0x06);
 outportb(portpia+1,0x01);
 while(A){
	outportb(portad,0x00);
	while(B){
		stat = inportb(portpia + 2) ;
		stat2 = stat & 0x10;
		if( stat2 == 0x00)
			B=0;
	}
	lower = inportb(portad+1);
	upper = inportb(portad);
	total = _rotl(upper,4) + _rotr(lower,4);
	total1 = total - 0x8000;
		printf("Total = %+05d      ",total1);
	if(kbhit()) {
		ch = getch();
		if( ch == 'q')
		A=0;
	}
	
	B=1;
	}
 return 0;
}
