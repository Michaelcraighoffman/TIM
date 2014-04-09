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

#include "__timsystem.h"
#include "alloc.h"
#include "gray.h"
#include "graph.h"
#include "system.h"
#include <cstring>

void TIMSetup() {
    DefaultScreen=malloc(LCD_SIZE);
    LCD_MEM=DefaultScreen;	
    ScreenState.XMax=160;
    ScreenState.YMax=100;
    LightPlane=malloc(LCD_SIZE);
    DarkPlane=malloc(LCD_SIZE);
    memset(LightPlane,0,LCD_SIZE);
    memset(DarkPlane,0,LCD_SIZE);
    PortRestore();
    ClrScr();
    SCR_RECT SCREENRECT;
	MakeScrRect(0,0,159,99, &SCREENRECT);
    SetCurClip(&SCREENRECT);
    /*  The first element in the MemoryBlock vector is defined as NULL.
        Grab it so applications don't get confused*/
    HANDLE Holder=HeapAlloc(1);
    /* Setup the keyboard queue */
    DEF_QUEUE *kbq = (DEF_QUEUE *)kbd_queue();
    OSqclear(kbq);
    kbq->Size=100;
}
