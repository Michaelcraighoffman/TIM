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

#ifndef   TIGCC_GRAY_H
#define   TIGCC_GRAY_H

#define GRAYDBUFFER_SIZE 7688

extern void * LightPlane;
extern void * DarkPlane;
extern volatile short GrayIsRunning;

enum GrayPlanes {LIGHT_PLANE = 0, DARK_PLANE = 1};

void GrayAdjust (short adjustment);
short GrayCheckRunning (void);
void GrayDBufCleanup (void);
short GrayDBufGetActiveIdx (void);
void *GrayDBufGetActivePlane (short plane);
short GrayDBufGetHiddenIdx (void);
void *GrayDBufGetHiddenPlane (short plane);
void *GrayDBufGetPlane (short idx, short plane);
void GrayDBufInit (void *buf);
void GrayDBufSetActiveAMSPlane (short plane);
void GrayDBufSetActiveIdx (short idx);
void GrayDBufSetActiveIdxSync (short idx);
void GrayDBufSetAMSPlane (short idx, short plane);
void GrayDBufSetHiddenAMSPlane (short plane);
void GrayDBufToggle (void);
void GrayDBufToggleSync (void);
//INT_HANDLER GrayGetInt1Handler (void);
void *GrayGetPlane (short plane);
unsigned long GrayGetSwitchCount (void);
const char *GrayGetVersionString (void);
void GrayOff (void);
short GrayOn (void);
void GrayOnThrow (void);
void GraySetAMSPlane (short plane);
//void GraySetInt1Handler (INT_HANDLER handler);
void GraySetSwitchCount (unsigned long val);
void GrayWaitNSwitches (short wait);


#endif
