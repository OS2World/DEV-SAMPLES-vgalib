

Info on VIO direct graphics demos...
************************************


10/13/92  -  Test release of some of my demos and code.

This is the first release of my tiny direct graphics library
and associated demos.  The purpose of this library was to see if
it was possible to write programs that write directly to the video
hardware without PM.  This was accomplished by using the Vio subsystem
that is still supported under OS/2 2.0  The Vio subsystem has several
calls which are useful for this.  The 2 primary calls used to implement
this are VioGetPhysBuf() and VioSetMode().  I got examples of this
from Norton's book on OS/2 programming (1.3 code, but with some changes
it works under 2.0)   


I won't provide any detailed information this time around, I mainly 
want to let some people see it, and get feedback.  I'm not sure
how much farther I'm going to go, it all depends on wether or not
I have time, and get the tools to complete the job the right way.


Here is what is done:  2d lines (if either of the endpoints are outside of the
screen then the line isn't drawn, I haven't done 2d clipping yet...)
2d points.  Screenclears, solid filled boxes, circles (although I discovered
that my aspect ratio is not square in 320x200, so I'll need to fix it...)
and some other things.  

I did a VERY simple 3d demo, using points, a HUGE array of a 3d heightfield,
3d sin functions, and some rotation.  I would like to improve upon this 
dramatically after writing some more 2d primitives (ala putimage getimage etc
from turbo c...)  I also have no filled polygons or floodfill yet.

If anyone has good code that works already for 3d projection (must have
depth so I can do z-buffering, and depth sorting) or other stuff 
i.e. finished floodfill algorithms in c... Let me know!

I REALLY need to get some sort of assembler for use with OS/2 2.0
I know where there are some EXCELLENT 3d polyblit codes, but they 
are in asm, and I don't want to waste my time rewriting them in C, only
to be disappointed with the speed.



Demo info:
**********

Volcano:  This is a simple program that is supposed to simulate a volcano,
         it was my first demo with my library.  It has one command line
         parameter, which is the max number of lava points that can be in
         the air at one time.  The least is about 30, the max is 2000.
         If you enter an illegal value it will probably blow up (i.e. 
         give you a GPF or register dump :-)  But then OS/2 is great for
         that, so if you want to demonstrate a program crashing, you might
         want to purposefully use a number over 2000...
         (I'll fix this later, not real high on my priority list)


Cells:  This demo is based upon a Scientific American article from a long
       time back, I coded a version in pascal some time ago, and just
       changed it over to C, and my graphics library.  You will be prompted
       for the number of states in the system and wether or not you would like
       cells to keep crunching when it isn't in the foreground.


Wave:  Wave is my favorite, although it is also the least polished.
      Wave requires 1Mb of free ram to run, it needs this ram to generate
      a large heightfield to hold the 3d surface.  (hey, we've got the
      ram so lets use it!!!)   DO NOT RUN THIS IF YOU DO NOT HAVE A 
      MATH COPROCESSOR, IT WILL TAKE TO LONG!!!
      I saw it run on a machine without a math chip, and it never completed
      calculating the 3d surface, not sure what to do about it at the moment,
      I may use fixed point sin tables to correct the problem with speed
      during the initial setup.
      
      I plan to focus most of my work on getting some sort of 3D library
      written, based upon the results I've gotten so far with Wave and
      some other tests.  There is much to be done with this, and this is
      really an alpha as it were...  I won't go into anything else here,
      just use some reasonable values for rho, d, etc..
      The number of points on a side can be anywhere from 10 to 100.
      The shape that is rotated and scrolled is a sinewave swept around
      the Z-axis.  The points are colored by height, but are not depth
      sorted so glitches will occur when there are a large number of 
      points in a small area.  


For more info:
**************

If you have any suggestions/questions about these demos or source, 
feel free to send me email on internet at:   johns@cs.umr.edu

I also read the OS/2 programmers group    comp.os.os2.programmer 
on usenet.

Thanks,
        John E. Stone
        johns@cs.umr.edu



P.S.  If anyone is interested in developing games for OS/2 that use these
      routines, I'd be more than happy to help them get started, I'd like
      to see some stuff like that, so that OS/2 will have a jump on 
      windows NT for stuff like games/ 3d stuff...

    
 
