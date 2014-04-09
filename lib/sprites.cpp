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


#include "__custom.h"
#include "asmtypes.h"
#include "graph.h"
#include "stub.h"
#include "sprites.h"

void Sprite8  (short x, short y, short height, const unsigned char *sprite, void *vm_addr, short mode) {
     TRACK("Sprite8");
     Byte * Dest=(Byte *)vm_addr;
     Byte * SpriteData=(Byte *)(void *)sprite;
     int SpriteByteNum, ByteNum;
     for(int sy=0; sy<height; sy++) {
         for(int sx=0; sx<8; sx++) {
            SpriteByteNum=((sy)*8)+(7-sx);
            ByteNum=((sy+y)*ScreenState.XMax)+sx+x;
            if(GetBit(SpriteData[SpriteByteNum/8], SpriteByteNum%8)!=0) {
                if(mode==SPRT_XOR) {
                    if(GetBit(Dest[ByteNum/8], ByteNum%8)!=0) {
                         ClearBit(&Dest[ByteNum/8], ByteNum%8);
                    }
                    else
                         SetBit(&Dest[ByteNum/8], ByteNum%8);
                }
                if(mode==SPRT_OR || mode==SPRT_COPY) {
                    SetBit(&Dest[ByteNum/8], ByteNum%8);
                }
             }
             else {
                 if(mode==SPRT_AND) {
                     SetBit(&Dest[ByteNum/8], ByteNum%8);
                 }
                 else if(mode==SPRT_COPY) {
                     ClearBit(&Dest[ByteNum/8], ByteNum%8);
                 }
             }
         }
     }
}
void Sprite16 (short x, short y, short height, const unsigned short *sprite, void *vm_addr, short mode) {
     TRACK("Sprite16");
     Byte * Dest=(Byte *)vm_addr;
     Byte * SpriteData=(Byte *)(void *)sprite;
     int SpriteByteNum, ByteNum;
     for(int sy=0; sy<height; sy++) {
         for(int sx=0; sx<16; sx++) {
            SpriteByteNum=((sy)*16)+(15-sx);
            ByteNum=((sy+y)*ScreenState.XMax)+sx+x;
            if(GetBit(SpriteData[SpriteByteNum/8], SpriteByteNum%8)!=0) {
                if(mode==SPRT_XOR) {
                    if(GetBit(Dest[ByteNum/8], ByteNum%8)!=0) {
                         ClearBit(&Dest[ByteNum/8], ByteNum%8);
                    }
                    else
                         SetBit(&Dest[ByteNum/8], ByteNum%8);
                }
                if(mode==SPRT_OR || mode==SPRT_COPY) {
                    SetBit(&Dest[ByteNum/8], ByteNum%8);
                }
             }
             else {
                 if(mode==SPRT_AND) {
                     SetBit(&Dest[ByteNum/8], ByteNum%8);
                 }
                 else if(mode==SPRT_COPY) {
                     ClearBit(&Dest[ByteNum/8], ByteNum%8);
                 }
             }
         }
     }
}
void Sprite32 (short x, short y, short height, const unsigned long *sprite, void *vm_addr, short mode) {
     TRACK("Sprite32");
     Byte * Dest=(Byte *)vm_addr;
     Byte * SpriteData=(Byte *)(void *)sprite;
     int SpriteByteNum, ByteNum;
     for(int sy=0; sy<height; sy++) {
         for(int sx=0; sx<32; sx++) {
               if(sizeof(long) == 4)
                    SpriteByteNum=((sy)*32)+(31-sx);
               else /* 8byte long on 64-bit*/
                    SpriteByteNum=((sy)*64)+(31-sx);
               ByteNum=((sy+y)*ScreenState.XMax)+sx+x;
               if(GetBit(SpriteData[SpriteByteNum/8], SpriteByteNum%8)!=0) {
                    if(mode==SPRT_XOR) {
                         SetBit(&Dest[ByteNum/8], ByteNum%8);
                    }
                    if(mode==SPRT_OR) {
                         SetBit(&Dest[ByteNum/8], ByteNum%8);
                    }
               }
               else {
                    if(mode==SPRT_AND) {
                         SetBit(&Dest[ByteNum/8], ByteNum%8);
                    }
               }
          }
     }
}

