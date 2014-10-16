#include<stdlib.h>
#include<stdio.h>
#include<conio.h>
#define INCL_BASE
#include<os2.h>
#include<string.h>
#include"vgalib.h"

#define HANDLE 0
#define BUFSIZE 12
#define HRES 320 
#define VRES 200
#define COLORSET 32

#define xs 319 
#define ys 199
#define xc 320 
#define yc 200 

PCH ptr0;
struct _VIOPHYSBUF phys;
struct _VIOMODEINFO orig,moda;
char status;
char st;
char temp;
unsigned int temp2;
unsigned long numchange;
unsigned short VWAIT;

int i,j,k,l,x,y;
unsigned char oz[HRES][VRES],nz[HRES][VRES];
int nx[5]={1,-1,0,0};
int ny[5]={0,0,1,-1};

main() {
printf("Cells - A Cellular Automata Demo for OS/2 2.0  \n");
printf("        By John E. Stone                       \n");
printf("For comments send E-Mail to: johns@cs.umr.edu  \n");
printf("\n\n\n\n\n");
printf("The number of states is how many different colors\n");
printf("a pixel can take on.  The larger the number of states\n");
printf("the longer it takes to complete, and it may even become\n");
printf("stagnant with more than 20 states.\n\n");
printf("\nProcess ID=%d\n",getpid());
printf("Would you like cells to continue processing when it\n");
printf("isn't visible on the screen? (1=no, 0=yes)                 \n");
scanf("%u",&VWAIT);
if ((VWAIT<0) || (VWAIT>1)) VWAIT=0;

printf("\n\nEnter the number of states in the system: (5-25) \n");
scanf("%d",&temp2);
st=10;
srand(getpid());

if ((temp2>4) || (temp2<26)) { st=temp2; }


/* setup for graphics mode */
phys.pBuf=(unsigned char *) 0xA0000;
phys.cb=65536;

moda.cb=12;
moda.fbType=3;
moda.color=8;
moda.row=25;
moda.col=40;
moda.hres=320;
moda.vres=200;

VioGetMode(&orig, HANDLE);
VioSetMode(&moda, HANDLE);
VioGetPhysBuf(&phys, 0);
ptr0=MAKEP(phys.asel[0], 0);
VioScrLock(1, &status, HANDLE); /* Wait for exclusive screenlock */

cls(ptr0,0);

for (i=0; i<=xs; i++) {
  for (j=0; j<=ys; j++) {
         nz[i][j]=(char) rand() % st;
         oz[i][j]=nz[i][j];
  }
}
numchange=1;

while ((kbhit()==0) && (numchange>0)) {
numchange=0;
for (i=0; i<=xs; i++) {
  for (j=0; j<=ys; j++) {
    for (x=0; x<=3; x++)  {
             k=(i+nx[x]+xc) % xc;
             l=(j+ny[x]+yc) % yc;
             if (oz[k][l]==((oz[i][j]+1) % st)) {
                 nz[i][j]=(oz[k][l] % st);
		 numchange++;
	     }
    }
  }
}

memcpy(oz,nz,sizeof(nz));
VioScrLock(VWAIT,&status,HANDLE);
if (!status) {
for (i=0; i<VRES; i++) {
  for (j=0; j<HRES; j++) {
    temp=COLORSET+nz[j][i];
    putpixel(ptr0,j,i,temp);
  }
}
}

VioScrUnLock(HANDLE);
}

VioScrLock(WAIT,&status,HANDLE);
cls(ptr0,0);

VioScrUnLock(HANDLE);

} /* end of cells.c */
