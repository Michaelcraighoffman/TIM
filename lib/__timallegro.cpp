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

#include <allegro.h>
#include "asmtypes.h"
#include "gray.h"
#include "stub.h"
#include "system.h"

#include "__timsystem.h"
#include "__custom.h"

extern void * DefaultScreen;

/*   Useful Allegro Passthroughs */

void TimedWait(int i) {
    rest(i);
}
void TIMRenderScreen() {
    if(GrayCheckRunning()) {
        TIMRenderGray();
    }
    else TIMRenderNormal();
}

void TIMRenderNormal() {
    BITMAP * Buffer=create_bitmap(160,100); 
    Byte * BitMap=(Byte *)DefaultScreen;
    int ByteNum;
    for(int y=0; y<100; y++) {
        for(int x=0; x<160; x++) {
            ByteNum=(y*160)+x;
            if(GetBit(BitMap[ByteNum/8], ByteNum%8)!=0) {
                putpixel(Buffer, x, y, makecol(0,0,0));
            }
        }
    }
    blit(Buffer, screen, 0,0,0,0,160,100);
    destroy_bitmap(Buffer);
}

void TIMRenderGray() {
    BITMAP * Buffer=create_bitmap(160,100); 
    clear_to_color(Buffer, makecol(255,255,255));
    Byte * LPlane=(Byte *)GrayGetPlane(LIGHT_PLANE);
    Byte * DPlane=(Byte *)GrayGetPlane(DARK_PLANE);
    int ByteNum;
    int StartCol;
    for(int y=0; y<100; y++) {
        for(int x=0; x<160; x++) {
            ByteNum=(y*160)+x;
            StartCol=255;
            if(GetBit(LPlane[ByteNum/8], ByteNum%8)!=0)
                StartCol-=85;
            if(GetBit(DPlane[ByteNum/8], ByteNum%8)!=0)
                StartCol-=170;
            if(StartCol!=255)
                putpixel(Buffer, x,y, makecol(StartCol, StartCol, StartCol));
        }
    }
    blit(Buffer, screen, 0,0,0,0,160,100);
    destroy_bitmap(Buffer);
}

void TIMGetKeys() {
    TRACK("TIMGetKeys");
    while(keypressed()) {
        void * kbq=kbd_queue();
        int val=readkey();
        if ((val >> 8) == KEY_UP)
            OSenqueue(337, kbq);
        else if ((val >> 8) == KEY_RIGHT)
            OSenqueue(344, kbq);
        else if ((val >> 8) == KEY_DOWN)
            OSenqueue(340, kbq);
        else if ((val >> 8) == KEY_LEFT)
            OSenqueue(338, kbq);
        else if ((val >> 8) == KEY_ENTER)
            OSenqueue(13, kbq);        
        else if ((val >> 8) == KEY_ESC)
            OSenqueue(264, kbq);
        else if ((val >> 8) == KEY_F1)
            OSenqueue(268, kbq);
        else
            OSenqueue((val & 0xff), kbq);
    }
}

void TIMTimerTick() {
    for(int i=0; i<9; i++) {
        if(Timers[i].InUse==TRUE) {
            if(Timers[i].TimeLeft>0)
                Timers[i].TimeLeft--;
            if(Timers[i].TimeLeft==0)
                Timers[i].Expired=TRUE;
        }
    }
}


