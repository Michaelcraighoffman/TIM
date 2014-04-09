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

#include "gray.h"
#include "graph.h"
#include "asmtypes.h"
#include "stub.h"
#include <cstdlib>
#include <cstring>

void * LightPlane;
void * DarkPlane;
volatile short GrayIsRunning;

void GrayAdjust (short adjustment) {
     STUB("GrayAdjust");
}
short GrayCheckRunning (void) {
     return GrayIsRunning;
}
void GrayDBufCleanup (void){
     STUB("GrayDBufCleanup");
}
short GrayDBufGetActiveIdx (void){
     STUB("GrayDBufGetActiveIdx");
     return 0;
}
void *GrayDBufGetActivePlane (short plane){
     STUB("GrayDBufGetActivePlane");
	 return NULL;
}
short GrayDBufGetHiddenIdx (void){
     STUB("GrayDBufGetHiddenIdx");
	 return 0;
}
void *GrayDBufGetHiddenPlane (short plane){
     STUB("GrayDBufGetHiddenPlane");
	 return NULL;
}
void *GrayDBufGetPlane (short idx, short plane){
     STUB("GrayDBufGetPlane");
	 return NULL;
}
void GrayDBufInit (void *buf){
     STUB("GrayDBufInit");
}
void GrayDBufSetActiveAMSPlane (short plane){
     STUB("GrayDBufSetActiveAMSPlane");
}
void GrayDBufSetActiveIdx (short idx);
void GrayDBufSetActiveIdxSync (short idx);
void GrayDBufSetAMSPlane (short idx, short plane);
void GrayDBufSetHiddenAMSPlane (short plane);
void GrayDBufToggle (void);
void GrayDBufToggleSync (void);
//INT_HANDLER GrayGetInt1Handler (void);
void *GrayGetPlane (short plane) {
     TRACK("GrayGetPlane");
     if(plane==LIGHT_PLANE) {
          return LightPlane;
     }
     else if(plane==DARK_PLANE) {
          return DarkPlane;
     }
     else {
          FIXME("GrayGetPlane gave bad value");
          return NULL;
     }
}

unsigned long GrayGetSwitchCount (void);
const char *GrayGetVersionString (void);
void GrayOff (void) {
     TRACK("GrayOff");
     GrayIsRunning=FALSE;
}
short GrayOn (void) {
     TRACK("GrayOn");
     GrayIsRunning=TRUE;
     return TRUE;
}
void GrayOnThrow (void) {
    GrayOn();
}
void GraySetAMSPlane (short plane) {
     TRACK("GraySetAMSPlane");
     PortSet(GrayGetPlane(plane), 159, 99);
}
//void GraySetInt1Handler (INT_HANDLER handler);
void GraySetSwitchCount (unsigned long val);
void GrayWaitNSwitches (short wait);

/*  Deprecated Aliases */

void  SetPlane(short plane) { GraySetAMSPlane(plane); }
void *GetPlane(short plane) { return GrayGetPlane(plane); }
