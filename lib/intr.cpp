/* Copyright 2010 Michael Hoffman. All rights reserved.

Redistribution and use in source and binary forms, with or without modification, are
permitted provided that the following conditions are met:

   1. Redistributions of source code must retain the above copyright notice, this list of
      conditions and the following disclaimer.

   2. Redistributions in binary form must reproduce the above copyright notice, this list
      of conditions and the following disclaimer in the documentation and/or other materials
      provided with the distribution.

THIS SOFTWARE IS PROVIDED BY MICHAEL HOFFMAN ``AS IS'' AND ANY EXPRESS OR IMPLIED
WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

The views and conclusions contained in the software and documentation are those of the
authors and should not be interpreted as representing official policies, either expressed
or implied, of the copyright holder.

*/

#include "intr.h"

INT_HANDLER DUMMY_HANDLER;

void DisablePRG (void) {
     STUB("DisablePRG");
}
void EnablePRG (void) {
     STUB("EnablePRG");
}
void ExecuteHandler (INT_HANDLER Handler) {
     if(Handler.intptr != DUMMY_HANDLER.intptr) {
          Handler.intptr();
     }
}
INT_HANDLER GetIntVec (long IntVec) {
     STUB("GetIntVec");
	 return *(new INT_HANDLER);
}
short IsPRGEnabled (void) {
     STUB("IsPRGEnabled");
     return TRUE;
}
short PRG_getRate (void) {
     STUB("PRG_getRate");
     return 0;
}
unsigned char PRG_getStart (void) {
     STUB("PRG_getStart");
     return 0;
}
unsigned char PRG_getValue (void) {
     STUB("PRG_getValue");
     return 0;
}
void PRG_setRate (short rate) {
     STUB("PRG_setRate");
}
void PRG_setStart (unsigned char val) {
     STUB("PRG_setStart");
}
void SetIntVec (long IntVec, INT_HANDLER Handler) {
     STUB("SetIntVec");
}
