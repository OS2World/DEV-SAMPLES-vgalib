/* Vgalib.h     (C)1992 By John E. Stone                       */
/* This file contains protos for the vgalib functions.         */
/* 08/19/92                                                    */

extern void cls(PCH, char);

extern void putpixel(PCH, unsigned int, unsigned int, char);

extern char getpixel(PCH, unsigned int, unsigned int );

extern void line(PCH, unsigned int, unsigned int, unsigned int,
		      unsigned int, char);

extern void box(PCH, unsigned int, unsigned int, 
			unsigned int, unsigned int, char);

extern void circlepoints(PCH, int, int, unsigned int, unsigned int, 
		  char);

extern void circle(PCH, unsigned int, unsigned int, unsigned int,
	    char);

