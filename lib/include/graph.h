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

/* graph.h */

#ifndef   graph_h
#define   graph_h

#include "wingraph.h"


#define BITMAP_HDR_SIZE 4
extern void * LCD_MEM;
#define LCD_SIZE 3840

enum Attrs {A_REVERSE, A_NORMAL, A_XOR, A_SHADED, A_REPLACE, A_OR, A_AND, A_THICK1, A_SHADE_V, A_SHADE_H, A_SHADE_NS, A_SHADE_PS};
enum Fonts {F_4x6, F_6x8, F_8x10};

typedef union {
     struct {
	    unsigned char x0, y0, x1, y1;
     } xy;
     unsigned int l;
} SCR_RECT;

typedef struct {
	unsigned short i[16];
} ICON;

typedef struct {
	unsigned char Count;
     struct {
	    signed char Attr, x0, y0, x1, y1;
     } Data[];
} MULTI_LINE;

typedef struct {
	void *ScrAddr;
unsigned char XMax, YMax;
short CurFont, CurAttr, CurX, CurY;
SCR_RECT CurClip;
} SCR_STATE;

typedef struct {
	unsigned short NumRows, NumCols;
unsigned char Data[];
} BITMAP;

typedef char LCD_BUFFER[LCD_SIZE];

extern void * DefaultScreen;
extern SCR_STATE ScreenState;


void BitmapGet (const SCR_RECT *rect, void *BitMap);
void BitmapInit (const SCR_RECT *rect, void *BitMap);
void BitmapPut (short x, short y, const void *BitMap, const SCR_RECT *clip, short Attr);
unsigned short BitmapSize (const SCR_RECT *rect);
unsigned short CalcBitmapSize (BITMAP *b);
void ClientToScr (const SCR_RECT *WindowRect, const SCR_RECT *Rect, SCR_RECT *Result);
void ClrScr (void);
void DisplayOff (void);
void DisplayOn (void);
void DrawChar (short x, short y, char c, short Attr);
void DrawClipChar (short x, short y, short c, const SCR_RECT *clip, short Attr);
void DrawClipEllipse (short x, short y, short a, short b, const SCR_RECT *clip, short Attr);
void DrawClipLine (const WIN_RECT *Line, const SCR_RECT *clip, short Attr);
void DrawClipPix (short x, short y);
void DrawClipRect (const WIN_RECT *rect, const SCR_RECT *clip, short Attr);
void DrawFkey (short x, short y, short fkey_no, short Attr);
void DrawIcon (short x, short y, const void *Icon, short Attr);
void DrawLine (short x0, short y0, short x1, short y1, short Attr);
void DrawMultiLines (short x, short y, const void *multi_lines);
void DrawPix (short x, short y, short Attr);
void DrawStr (short x, short y, const char *str, short Attr);
short DrawStrWidth (const char *str, short Font);
unsigned short DrawStrWidthP (const char *str, short len, short Font);
void FillLines2 (const WIN_RECT *lower_line, const WIN_RECT *upper_line, const SCR_RECT *clip, short Attr);
void FillTriangle (short x0, short y0, short x1, short y1, short x2, short y2, const SCR_RECT *clip, short Attr);
short FontCharWidth (short c);
unsigned char FontGetSys(void);
unsigned char FontSetSys (short Font);
short GetPix (short x, short y);
void LCD_restore (const void *buffer);
void LCD_save (void *buffer);
void LineTo (short x, short y);
SCR_RECT *MakeScrRect (short x0, short y0, short x1, short y1, SCR_RECT *s);
void MoveTo (short x, short y);
void PortRestore (void);
void PortSet (void *vm_addr, short x_max, short y_max);
short QScrRectOverlap (const SCR_RECT *r1, const SCR_RECT *r2);
void RestoreScrState (const void *buffer);
void SaveScrState (void *buffer);
void ScrRectFill (const SCR_RECT *rect, const SCR_RECT *clip, short Attr);
short ScrRectOverlap (const SCR_RECT *r1, const SCR_RECT *r2, SCR_RECT *r);
void ScrRectScroll (const SCR_RECT *rect, const SCR_RECT *clip, short NumRows, short Attr);
void ScrRectShift (const SCR_RECT *rect, const SCR_RECT *clip, short NumCols, short Attr);
SCR_RECT *ScrToHome (SCR_RECT *rect);
WIN_RECT *ScrToWin (const SCR_RECT *rect);
short SetCurAttr (short Attr);
void SetCurClip (const SCR_RECT *clip);

/*  Deprecated Aliases */

void  SetPlane(short plane);
void *GetPlane(short plane);

#endif
