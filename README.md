
All of the code contained in the lib directory is licensed under the BSD license.  The Checkers example project is from Ticalc.org and was apparently orginally written by someone at technoplaza.net.  I did not write it, and short of a single change to checkers.c, did not modifiy it from its original form either. 

Pretty much just run your typical make -> make install to compile and install the library.  TIM requires the Allegro4 library. 
To make the checkers example, run 'make checkers' and look for checkers in the bin directory.

Porting to TIM 
----------------------------------------------

The header names correspond directly to those in the standard TIGCC distribution (some may be missing if they're not implemented).  TIGCC uses void _main() as it's entry point, but PC compilation requires an int main().  This can be as simple as putting:
int main() { _main(); return 0; } 
just below your _main definition.  


Information about TIM's structure
----------------------------------------------------------

The include files seek to emulate the TIGCC library, listed at http://tigcc.ticalc.org/doc/hdrindex.html
Source files which begin with two underscores ( __ ) are TIM internals.  

__custom provides a convenient way to access the bits of a byte, so that the code is easier to read (ie no bitshifts)
__font and __fontimages provides the fonts for TIM
__timsystem is the interface to allegro
__once is the library constructor and destructor to set up the library for use
