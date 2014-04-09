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

#include "stub.h"

#include "alloc.h"
#include "asmtypes.h"
#include "graph.h"
#include "gray.h"
#include "sprites.h"
#include "__custom.h"
#include "__font.h"
#include "__timsystem.h"

#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>

void * DefaultScreen;
SCR_STATE ScreenState;
unsigned char CurrentFont;
void * LCD_MEM;

void BitmapGet (const SCR_RECT *rect, void *BitMap) {
    STUB("BitmapGet");
}
void BitmapInit (const SCR_RECT *rect, void *BitMap) {
    STUB("BitmapInit");
}
void BitmapPut (short x, short y, const void *BitMap, const SCR_RECT *clip, short Attr) {
    STUB("BitmapPut");
}
unsigned short BitmapSize (const SCR_RECT *rect) {
    STUB("BitmapSize");
	return 0;
}
unsigned short CalcBitmapSize (BITMAP *b) {
    TRACK("CalcBitmapSize");
    return ((((b->NumCols + 7) >> 3) * b->NumRows) + BITMAP_HDR_SIZE);
}

void ClientToScr (const SCR_RECT *WindowRect, const SCR_RECT *Rect, SCR_RECT *Result) {
    STUB("ClientToScr");
}
void ClrScr (void) {
    TRACK("ClrScr");
    memset(ScreenState.ScrAddr,0,LCD_SIZE);
}

void DisplayOff (void) {
    TRACK("DisplayOff");
    void * Virtual=malloc (LCD_SIZE);
    PortSet (Virtual, 159, 99);
}
void DisplayOn (void) {
    TRACK("DisplayOn");
    free(ScreenState.ScrAddr);
    PortRestore();
}
void DrawChar (short x, short y, char c, short Attr) {
     TRACK("DrawChar");
     char ActiveFont=FontGetSys();
     int Character=c-32;
     int SpriteAttr=SPRT_OR;
     if(Attr==A_REPLACE) {
          SpriteAttr=SPRT_COPY;
     }
     else if(Attr==A_XOR) {
          SpriteAttr=SPRT_XOR;
     }
     if(Character>-1) {
        if(ActiveFont==F_4x6) {
            Sprite8(x,y,6,Font4X6[Character], ScreenState.ScrAddr, SpriteAttr);
        }
        else if(ActiveFont==F_6x8) {
            Sprite8(x,y,8, Font6X8[Character], ScreenState.ScrAddr, SpriteAttr);
        }
        else if(ActiveFont==F_8x10) {
            FIXME("DrawChar - 8x10 Font");
        }
        else {
            FIXME("DrawChar - Unknown Font");
        }
     }
}
void DrawClipChar (short x, short y, short c, const SCR_RECT *clip, short Attr) {
    PARTIAL("DrawClipChar - Forward to DrawChar");
    DrawChar(x,y,c,Attr);
}
void DrawClipEllipse (short x, short y, short a, short b, const SCR_RECT *clip, short Attr) {
    STUB("DrawClipEllipse");
}
void DrawClipLine (const WIN_RECT *Line, const SCR_RECT *clip, short Attr) {
    short OldAttr=ScreenState.CurAttr;
    ScreenState.CurAttr=Attr;
    int SlopeX=std::abs((float)Line->x1-Line->x0);
    int SlopeY=std::abs((float)Line->y1-Line->y0);
    if(SlopeX==0) {
        for(int y=Line->y0; y<Line->y1; y++) {
            DrawClipPix(Line->x0, y);
        }
    }
    else {
        float Slope=(float)SlopeY/SlopeX;
        for(int x=Line->x0; x<Line->x1; x++) {
            DrawClipPix(x, (Slope*(x-Line->x0))+Line->y0);
        }
    }
    ScreenState.CurAttr=OldAttr;
}
void DrawClipPix (short x, short y) {
    TRACK("DrawClipPix");
    void * HoldData=ScreenState.ScrAddr;
    Byte * BitMap=(Byte *)HoldData;
    int ByteNum;
    if( x>=ScreenState.CurClip.xy.x0 &&
        x<=ScreenState.CurClip.xy.x1 &&
        y>=ScreenState.CurClip.xy.y0 &&
        y<=ScreenState.CurClip.xy.y1) {

        if(ScreenState.CurAttr==A_NORMAL) {
            ByteNum=(y*ScreenState.XMax)+x;
            SetBit(&BitMap[ByteNum/8], ByteNum%8);
        }
        else if(ScreenState.CurAttr==A_REVERSE) {
            ByteNum=(y*ScreenState.XMax)+x;
            ClearBit(&BitMap[ByteNum/8], ByteNum%8);
        }
        else if(ScreenState.CurAttr==A_XOR) {
            ByteNum=(y*ScreenState.XMax)+x;
            if(GetBit(BitMap[ByteNum/8], ByteNum%8)==0)
                SetBit(&BitMap[ByteNum/8], ByteNum%8);
            else
                ClearBit(&BitMap[ByteNum/8], ByteNum%8);
        }
    }
}
void DrawClipRect (const WIN_RECT *rect, const SCR_RECT *clip, short Attr) {
    STUB("DrawClipRect");
}
void DrawFkey (short x, short y, short fkey_no, short Attr) {
    STUB("DrawFKey");
}
void DrawIcon (short x, short y, const void *Icon, short Attr) {
    STUB("DrawIcon");
}
void DrawLine (short x0, short y0, short x1, short y1, short Attr) {
    TRACK("DrawLine");
    WIN_RECT Out;
    Out.x0=x0;
    Out.y0=y0;
    Out.x1=x1;
    Out.y1=y1;
    DrawClipLine(&Out, &ScreenState.CurClip, Attr);
}
void DrawMultiLines (short x, short y, const void *multi_lines) {
     TRACK("DrawMultiLines");
     MULTI_LINE * LineStruct=(MULTI_LINE *)multi_lines;
     for(int i=0; i<LineStruct->Count; i++) {
          DrawLine(LineStruct->Data[i].x0+x, LineStruct->Data[i].y0+y, LineStruct->Data[i].x1+x, LineStruct->Data[i].y1+y, LineStruct->Data[i].Attr);
     }
}
void DrawPix (short x, short y, short Attr) {
    TRACK("DrawPix");
    short OldAttr=ScreenState.CurAttr;
    ScreenState.CurAttr=Attr;
    DrawClipPix(x,y);
    ScreenState.CurAttr=OldAttr;
}

void DrawStr (short x, short y, const char *str, short Attr) {
     TRACK("DrawStr");
     std::string In=str;
     int Position=x;
     for(int i=0; i<In.size(); i++) {
         DrawChar(Position, y, In[i], Attr);
         Position+=FontCharWidth(In[i]);
         /* Some glyphs in 4x6 break the rules, so put make sure we have a space */
         if(FontGetSys()==F_4x6)
             Position+=1;
     }
}
short DrawStrWidth (const char *str, short Font) {
    STUB("DrawStrWidth");
	return 0;
}
unsigned short DrawStrWidthP (const char *str, short len, short Font) {
    STUB("DrawStrWidthP");
	return 0;
}
void FillLines2 (const WIN_RECT *lower_line, const WIN_RECT *upper_line, const SCR_RECT *clip, short Attr) {
    STUB("FillLines2");
}
void FillTriangle (short x0, short y0, short x1, short y1, short x2, short y2, const SCR_RECT *clip, short Attr) {
    STUB("FillTriangle");
}
short FontCharWidth (short c) {
    TRACK("FontCharWidth");
    char ActiveFont=FontGetSys();
    if(ActiveFont==F_4x6) {
        if(c-32>-1) {
            int glyph=c-32;
            int maxwidth=1;
            for(int i=0; i<6; i++) {
                if(Font4X6[glyph][i] & 8) {
                    return 5;
                }
                else if(Font4X6[glyph][i] & 16) {
                    maxwidth=4;
                }
                else if(Font4X6[glyph][i] & 32) {
                    if(maxwidth < 3)
                        maxwidth=3;
                }
                else if(Font4X6[glyph][i] & 64) {
                    if(maxwidth <2)
                        maxwidth=2;
                }
            }
            return maxwidth;
        }
    }

    if(ActiveFont==F_6x8)
        return 6;
    if(ActiveFont==F_8x10)
        return 10;
    FIXME("Invalid Font");
    return 0;
}

unsigned char FontGetSys(void) {
     TRACK("FontGetSys");
     return CurrentFont;
}
unsigned char FontSetSys (short Font) {
     TRACK("FontSetSys");
     char old=CurrentFont;
     CurrentFont=Font;
     return old;
}
short GetPix (short x, short y) {
    TRACK("GetPix");
    void * HoldData=ScreenState.ScrAddr;
    Bool * BitMap=(Bool *)HoldData;
    return BitMap[(y*ScreenState.XMax)+x];
}
void LCD_restore (const void *buffer) {
    TRACK("LCD_restore");
    std::memcpy(DefaultScreen, buffer, LCD_SIZE);
}
void LCD_save (void *buffer) {
    TRACK("LCD_save");
    std::memcpy(buffer,DefaultScreen, LCD_SIZE);
}

void LineTo (short x, short y) {
    TRACK("LineTo");
    DrawLine(ScreenState.CurX, x, ScreenState.CurY, y, ScreenState.CurAttr);
}
SCR_RECT *MakeScrRect (short x0, short y0, short x1, short y1, SCR_RECT *s) {
    TRACK("MakeScrRect");
	s=new SCR_RECT();
	s->xy.x0=x0; s->xy.x1=x1; s->xy.y0=y0; s->xy.y1=y1;
    return s;
}
void MoveTo (short x, short y) {
    TRACK("MoveTo");
    ScreenState.CurX=x;
    ScreenState.CurY=y;
}
void PortRestore (void) {
    TRACK("PortRestore");
    PortSet(DefaultScreen, 159, 99);
}
void PortSet (void *vm_addr, short x_max, short y_max) {
    TRACK("PortSet");
    ScreenState.ScrAddr=vm_addr;
    ScreenState.XMax=x_max+1;
    ScreenState.YMax=y_max+1;
}
short QScrRectOverlap (const SCR_RECT *r1, const SCR_RECT *r2) {
    STUB("QScrRectOverlap");
	return 0;
}
void RestoreScrState (const void *buffer) {
    TRACK("RestoreScrState");
    memcpy(&ScreenState, buffer, sizeof(ScreenState));
}
void SaveScrState (void *buffer) {
    TRACK("SaveScrState");
    memcpy(buffer,&ScreenState, sizeof(ScreenState));
}
void ScrRectFill (const SCR_RECT *rect, const SCR_RECT *clip, short Attr) {
    PARTIAL("ScrRectFill is using global clipping coords");
    for(int y=0; y<(rect->xy.y1-rect->xy.y0); y++) {    
        for(int x=0; x<(rect->xy.x1-rect->xy.x0); x++) {
            DrawPix(x+rect->xy.x0, y+rect->xy.y0, Attr);
        }
    }
}
short ScrRectOverlap (const SCR_RECT *r1, const SCR_RECT *r2, SCR_RECT *r) {
    STUB("ScrRectOverlap");
	return 0;
}
void ScrRectScroll (const SCR_RECT *rect, const SCR_RECT *clip, short NumRows, short Attr) {
    STUB("ScrRectScroll");
}
void ScrRectShift (const SCR_RECT *rect, const SCR_RECT *clip, short NumCols, short Attr) {
    STUB("ScrRectShift");
}
SCR_RECT *ScrToHome (SCR_RECT *rect) {
    TRACK("ScrToHome");
    rect->xy.x1-=rect->xy.x0;
    rect->xy.y1-=rect->xy.y0;
    rect->xy.x0=0;
    rect->xy.y0=0;
    return rect;
}
WIN_RECT *ScrToWin (const SCR_RECT *rect) {
     TRACK("ScrToWin");
     WIN_RECT * Out;
     Out->x0=rect->xy.x0;
     Out->y0=rect->xy.y0;
     Out->x1=rect->xy.x1;
     Out->y1=rect->xy.y1;
     return Out;
}
short SetCurAttr (short Attr) {
    TRACK("SetCurAttr");
	short oldAttr=ScreenState.CurAttr;
    ScreenState.CurAttr=Attr;
	return oldAttr;
}
void SetCurClip (const SCR_RECT *clip) {
    TRACK("SetCurClip");
    memcpy(&ScreenState.CurClip, clip, sizeof(clip));
}
