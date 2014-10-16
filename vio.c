/* test of VioGetPhysBuf()  */
/* By John E. Stone  08/15/92   */
/* E-mail Johns@cs.umr.edu      */
/* Make sure that program type is set to NOTWINDOWCOMPAT before */
/*  use... Otherwise VioSetMode will fail... */




#define INCL_BASE
#include <os2.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define HANDLE 0
#define WAIT 1
#define BUFSIZE 12


/******** CLS *******/
void cls(ptr0,color)
PCH ptr0;
char color;
{
memset((PCH) ptr0,(color*256 + color),64000);
}

/********* Putpixel ********/
void putpixel(ptr0,x,y,color)
PCH ptr0;
unsigned int x;
unsigned int y;
char color;
{
*(PCH) (ptr0+(320*y)+x)=color;
}

unsigned char getpixel(ptr0,x,y)
PCH ptr0;
unsigned int x,y;
{
return(*(PCH) (ptr0+x+(320*y))); 
}



/******* midline ****************/
void midline(ptr0,x1,y1,x2,y2,color)
PCH ptr0;
unsigned int x1,y1,x2,y2;
char color;
{
unsigned int x,y;
         int d,dx,dy,incrE,incrNE;

x=x1;
y=y1;
dx=x2-x1;
dy=y2-y1;
*(PCH) (ptr0+(320*y)+x)=color;

if (dy>=0) {
	d=(2*dy) - dx;
	incrE=2*dy;
	incrNE=2*(dy-dx);

while (x<x2)
{
	if (d<=0)
        {  d+=incrE;
	   x++; }
	else
	{
	   d+=incrNE;
	   x++;
	   y++;
	}
	*(PCH) (ptr0+(320*y)+x)=color;
}
}
else {
	d=(2*dy)+dx;
	incrE=2*dy;
	incrNE=2*(dy+dx);
while (x<x2)
{
	if (d>=0)
	{ d+=incrE;
	  x++; }
	else
	{ d+=incrNE;
	  x++;  y--; 
        }
	*(PCH) (ptr0+(320*y)+x)=color;
} 
}

} /* end of midline */

/****** line ******/

void line(ptr0,x1,y1,x2,y2,color)
PCH ptr0;
unsigned int x1,y1,x2,y2;
char color;
{

if (x1<=x2)
   {
   midline(ptr0,x1,y1,x2,y2,color);
   }
else
   {
   midline(ptr0,x2,y2,x1,y1,color); 
   }
} /* end of line */


/******** Box **********/
box(ptr0,x1,y1,x2,y2,color)
PCH ptr0;
unsigned int x1,y1,x2,y2;
char color;
{
unsigned int y,lx,ly,ux,uy;
register unsigned int x;

  lx=min(x1,x2);
  ux=max(x1,x2);
  ly=min(y1,y2);
  uy=max(y1,y2);

  for (y=ly*320; y<=uy*320; y+=320) {
    for (x=lx;x<=ux;x++) {
      *(PCH) (ptr0+y+x)=color;
    }
  }
}

circlepoints(ptr0,x,y,xc,yc,color)
PCH ptr0;
int x,y;
unsigned int xc,yc;
char color;
{
*(PCH) (ptr0+x+xc+(y+yc)*320)=color;
*(PCH) (ptr0+y+xc+(x+yc)*320)=color;
*(PCH) (ptr0+y+xc+(-x+yc)*320)=color;
*(PCH) (ptr0+x+xc+(-y+yc)*320)=color;
*(PCH) (ptr0-x+xc+(-y+yc)*320)=color;
*(PCH) (ptr0-y+xc+(-x+yc)*320)=color;
*(PCH) (ptr0-y+xc+(x+yc)*320)=color;
*(PCH) (ptr0-x+xc+(y+yc)*320)=color;
}

/***** Circle ******/
void circle(ptr0,xc,yc,radius,color)
PCH ptr0;
unsigned int xc,yc,radius;
char color;
{
int x,y,d;

x=0;
y=radius;
d=1-radius;
circlepoints(ptr0,x,y,xc,yc,color);

while (y>x) {
	if (d<0) {
		d+=2*x+3;
		x++;
	}
	else {
		d+=2*(x-y)+5;
		x++;
		y--;
	}
     circlepoints(ptr0,x,y,xc,yc,color);
}
}



 
main()
{
	struct _VIOPHYSBUF phys;
	struct _VIOMODEINFO orig,moda;
	char status;
	unsigned int index;
	unsigned rc;
	unsigned short color;
	PCH ptr0;
	unsigned int x,y;
	char * pal[1000];
	char testcolor;

phys.pBuf=(unsigned char *) 0xA0000;
phys.cb=65536;

moda.cb=BUFSIZE;
moda.fbType=3;
moda.color=8;
moda.col=40;
moda.row=25;
moda.hres=320;
moda.vres=200;

VioGetMode(&orig, HANDLE);

if (rc=VioSetMode(&moda, HANDLE) )
   { printf("VioSetMode error=%u",rc);  exit(1); }

if (rc=VioGetPhysBuf(&phys, 0) )
   { printf("VioGetPhysBuf error=%u",rc); exit(1); }

ptr0=MAKEP(phys.asel[0],0);

VioScrLock(WAIT, &status, HANDLE);

for (color=0; color<256; color++) {
cls(ptr0,color);
}

cls(ptr0,0);

for (x=0; x<320; x++) {
  for (y=0; y<200; y++) {
    putpixel(ptr0,x,y,(char) y);
  }
}

cls(ptr0,0);

VioScrUnLock(HANDLE);
VioScrLock(WAIT,&status,HANDLE);
for( x=0; x<750000; x++)
{
   *(PCH) (ptr0+ (unsigned int) (rand() % 32000) + (unsigned int) rand() % 32000)=(char) rand() % 256; 
}
cls(ptr0,0);

VioScrUnLock(HANDLE);
VioScrLock(WAIT,&status,HANDLE);

for (x=0; x<100000; x++)
{ 
 line(ptr0,(unsigned int) rand() % 320, (unsigned int) rand() % 200,
           (unsigned int) rand() % 320, (unsigned int) rand() % 200, 
	   (char) rand() % 256);
}

cls(ptr0,0);

for (x=0; x<1000; x++) {
box(ptr0,(unsigned int) rand() % 320, (unsigned int) rand() % 200,
	  (unsigned int) rand() % 320, (unsigned int) rand() % 200,
	  (char) rand() % 256);
}


cls(ptr0,0);

for (x=0; x<50000; x++) {
circle(ptr0,(unsigned int) (20 + rand() % 280),
	    (unsigned int) (20 + rand() % 160),
	    15,(char) rand() % 256 );
}

cls(ptr0,0);
VioScrUnLock(HANDLE);
VioScrLock(WAIT,&status,HANDLE);
for (x=0; x<256; x++) {
  for (y=0; y<200; y++) {
      putpixel(ptr0,x,y,(char) x);
  }
}




for (x=0; x<100; x++) {
testcolor=rand() % 256;
putpixel(ptr0,x,x,testcolor);
if (getpixel(ptr0,x,x)!=testcolor) { DosBeep(5000,500); }
}

DosSleep(5000L);


VioSetMode(&orig,HANDLE);

cls(ptr0,0);

VioScrUnLock(HANDLE);
exit(0);
}

