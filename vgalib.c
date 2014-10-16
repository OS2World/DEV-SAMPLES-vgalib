/* test of VioGetPhysBuf()  */

#define INCL_DOS
#define INCL_SUB
#include <os2.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

#define HANDLE 0
#define WAIT 1
#define BUFSIZE 12
#define XRES 320
#define YRES 200


void cls(ptr0,color)
PCH ptr0;
char color;
{
memset((PCH) ptr0,(color*256 + color),64000);
}

void putpixel(ptr0,x,y,color)
PCH ptr0;
unsigned int x;
unsigned int y;
char color;
{
if ((x<XRES) && (y<YRES)) { 
*(PCH) (ptr0+x+(XRES*y))=color;
}
}

char getpixel(ptr0,x,y)
PCH ptr0;
unsigned int x,y;
{
if ((x<XRES) && (y<YRES)) {
return (*(PCH) (ptr0+x+(XRES*y)));
}

}

 
void line(ptr0,x1,y1,x2,y2,color)
PCH ptr0;
unsigned int x1,y1,x2,y2;
char color;
{
unsigned int x,y;
         int d,dx,dy,incrE,incrNE;

if (x1>x2) {
   x=x2;
   x2=x1;
   x1=x;
   y=y2;
   y2=y1;
   y1=y;
}
else {
   x=x1;
   y=y1;
}

dx=x2-x1;
dy=y2-y1;
if (abs(dx)>=abs(dy)) {

  if (dy>=0) {
	*(PCH) (ptr0+x+(XRES*y))=color;
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
	*(PCH) (ptr0+x+(XRES*y))=color;
	}
  }
  else {
	*(PCH) (ptr0+x+(XRES*y))=color;
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
		  x++;  
		  y--; 
	        }
	*(PCH) (ptr0+x+(XRES*y))=color;
	} 
} 

} /* end of if (dx>dy) */
else {  /* if (dx<dy) */

  if (dy>=0) {
	*(PCH) (ptr0+x+(XRES*y))=color;
	d=(2*dx) - dy;
	incrE=2*dx;
	incrNE=2*(dx-dy);
	while (y<y2)
	{
		if (d<=0)
	        {  d+=incrE;
		   y++; }
		else
		{
		   d+=incrNE;
		   y++;
		   x++;
		}
	*(PCH) (ptr0+x+(XRES*y))=color;
	}
  }
  else {
	*(PCH) (ptr0+x+(XRES*y))=color;
	d=(2*dx)+dy;
	incrE=2*dx;
	incrNE=2*(dy+dx);
	while (y>y2)
	{
		if (d<=0)
		{ d+=incrE;
		  y--;
		   }
		else
		{ d+=incrNE;
		  y--; 
	          x++;}
	*(PCH) (ptr0+x+(XRES*y))=color;
	} 
  }
}
} /* end of midline */

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

  for (y=ly*XRES; y<=uy*XRES; y+=XRES) {
    for (x=lx;x<=ux;x++) {
      *(PCH) (ptr0+y+x)=color;
    }
  }
}

void circlepoints(ptr0,x,y,xc,yc,color)
PCH ptr0;
int x,y;
unsigned int xc,yc;
char color;
{
*(PCH) (ptr0+x+xc+(y+yc)*XRES)=color;
*(PCH) (ptr0+y+xc+(x+yc)*XRES)=color;
*(PCH) (ptr0+y+xc+(-x+yc)*XRES)=color;
*(PCH) (ptr0+x+xc+(-y+yc)*XRES)=color;
*(PCH) (ptr0-x+xc+(-y+yc)*XRES)=color;
*(PCH) (ptr0-y+xc+(-x+yc)*XRES)=color;
*(PCH) (ptr0-y+xc+(x+yc)*XRES)=color;
*(PCH) (ptr0-x+xc+(y+yc)*XRES)=color;
}

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


