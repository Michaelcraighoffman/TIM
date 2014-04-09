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

#include "__font.h"

/*  Defines for all the glyphs the calculator draws.  Those marked with (TI89)
    have been verified pixel perfect to the TI-89 glyphs
*/

/* For Glyphs that do not yet have proper sprites */
#define FONT4X6_NOTIMPLEMENTED {0xF0, 0xF0, 0xF0, 0xF0, 0xF0, 0xF0}
#define FONT6X8_NOTIMPLEMENTED {0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC, 0xFC}
#define FONT8X10_NOTIMPLEMENTED {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}

/* Proportional font.  Despite being 4x6, some glyphs are wider than 4 pixels */
unsigned char Font4X6 [95][6]= {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   /* Space (TI89)*/
    {0x80, 0x80, 0x80, 0x80, 0x00, 0x80},   /* ! */
    {0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00},   /* " */
    {0xA0, 0xF0, 0xA0, 0xF0, 0xA0, 0x00},   /* # */
    {0x40, 0xF0, 0xC0, 0x60, 0xF0, 0x40},   /* $ */
    {0xC0, 0xD0, 0x20, 0x20, 0x40, 0x30},   /* % */
    {0xF0, 0x80, 0x50, 0x20, 0x50, 0xF0},   /* & */
    {0x40, 0x00, 0x00, 0x00, 0x00, 0x00},   /* ' */
    {0x00, 0x40, 0x80, 0x80, 0x80, 0x40},   /* ( (TI89)*/
    {0x00, 0x80, 0x40, 0x40, 0x40, 0x80},   /* ) (TI89)*/
    FONT4X6_NOTIMPLEMENTED,                             /* * */
    FONT4X6_NOTIMPLEMENTED,                             /* + */
    {0x00, 0x00, 0x00, 0x40, 0x40, 0x80},   /* , (TI89)*/
    {0x00, 0x00, 0xE0, 0x00, 0x00, 0x00},   /* - (TI89)*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x80},   /* . */
    {0x10, 0x10, 0x20, 0x40, 0x80, 0x80},   /* / */
    {0x00, 0x40, 0xA0, 0xA0, 0xA0, 0x40},   /* 0 (TI89)*/
    {0x00, 0x40, 0xC0, 0x40, 0x40, 0xE0},   /* 1 (TI89)*/
    {0x00, 0xC0, 0x20, 0x40, 0x80, 0xE0},   /* 2 (TI89)*/
    FONT4X6_NOTIMPLEMENTED,                             /* 3 */
    FONT4X6_NOTIMPLEMENTED,                             /* 4 */
    FONT4X6_NOTIMPLEMENTED,                             /* 5 */
    {0x00, 0x60, 0x80, 0xE0, 0xA0, 0xE0},   /* 6 (TI89)*/
    FONT4X6_NOTIMPLEMENTED,                             /* 7 */
    FONT4X6_NOTIMPLEMENTED,                             /* 8 */
    {0xF0, 0x90, 0xF0, 0x10, 0x10, 0xF0},   /* 9 */
    {0x00, 0x00, 0x80, 0x00, 0x80, 0x00},   /* : (TI89)*/
    FONT4X6_NOTIMPLEMENTED,                             /* ; */
    FONT4X6_NOTIMPLEMENTED,                             /* < */
    FONT4X6_NOTIMPLEMENTED,                             /* = */
    FONT4X6_NOTIMPLEMENTED,                             /* > */
    FONT4X6_NOTIMPLEMENTED,                             /* ? */
    {0xF0, 0x90, 0xC0, 0x90, 0x80, 0xF0},   /* @ */
    {0x60, 0x90, 0x90, 0xF0, 0x90, 0x90},   /* A */
    {0xE0, 0x90, 0xE0, 0x90, 0x90, 0xE0},   /* B */
    {0x00, 0x60, 0x80, 0x80, 0x80, 0x60},   /* C (TI89)*/
    {0xE0, 0x90, 0x90, 0x90, 0x90, 0xE0},   /* D */
    {0xF0, 0x80, 0x80, 0xF0, 0x80, 0xF0},   /* E */
    {0xF0, 0x80, 0xF0, 0x80, 0x80, 0x80},   /* F */
    {0xF0, 0x80, 0x80, 0xB0, 0x90, 0xF0},   /* G */
    {0x90, 0x90, 0xF0, 0x90, 0x90, 0x90},   /* H */
    {0xF0, 0x60, 0x60, 0x60, 0x60, 0xF0},   /* I */
    {0xF0, 0x10, 0x10, 0x10, 0x90, 0xE0},   /* J */
    {0x90, 0x90, 0xA0, 0xC0, 0xA0, 0x90},   /* K */
    {0x80, 0x80, 0x80, 0x80, 0x80, 0xF0},   /* L */
    {0x90, 0xF0, 0xF0, 0x90, 0x90, 0x90},   /* M */
    {0x90, 0xD0, 0xD0, 0xB0, 0xB0, 0xB0},   /* N */
    {0xF0, 0x90, 0x90, 0x90, 0x90, 0xF0},   /* O */
    {0x00, 0xC0, 0xA0, 0xC0, 0x80, 0x80},   /* P (TI89)*/
    {0xF0, 0x90, 0x90, 0xB0, 0xF0, 0x10},   /* Q */
    {0xF0, 0x90, 0xF0, 0xA0, 0x90, 0x90},   /* R */
    {0xF0, 0x80, 0xF0, 0x10, 0x10, 0xF0},   /* S */
    {0x00, 0xE0, 0x40, 0x40, 0x40, 0x40},   /* T (TI89)*/
    {0x90, 0x90, 0x90, 0x90, 0x90, 0xF0},   /* U */
    {0x90, 0x90, 0x90, 0x90, 0x60, 0x60},   /* V */
    {0x90, 0x90, 0x90, 0xF0, 0xF0, 0x90},   /* W */
    {0x90, 0x90, 0x60, 0x60, 0x90, 0x90},   /* X */
    {0x90, 0x90, 0x90, 0x60, 0x60, 0x60},   /* Y */
    {0xF0, 0x10, 0x20, 0x40, 0x80, 0xF0},   /* Z */
    {0xC0, 0x80, 0x80, 0x80, 0x80, 0xC0},   /* [ */
    {0x80, 0x80, 0x40, 0x20, 0x10, 0x10},   /* \ */
    {0xC0, 0x40, 0x40, 0x40, 0x40, 0xC0},   /* ] */
    FONT4X6_NOTIMPLEMENTED,                             /* ^ */
    {0x00, 0x00, 0x00, 0x00, 0x00, 0xF0},   /* _ */
    {0x80, 0x40, 0x00, 0x00, 0x00, 0x00},   /* ` */
    {0x00, 0x00, 0x60, 0xA0, 0xA0, 0x60},   /* a (TI89)*/
    {0x80, 0x80, 0xF0, 0x90, 0x90, 0xF0},   /* b */
    {0x00, 0x00, 0x60, 0x80, 0x80, 0x60},   /* c (TI89)*/
    {0x10, 0x10, 0xF0, 0x90, 0x90, 0xF0},   /* d */
    {0x00, 0x00, 0x40, 0xA0, 0xC0, 0x60},   /* e (TI89)*/
    {0x70, 0x80, 0xF0, 0x80, 0x80, 0x80},   /* f */
    {0x00, 0x60, 0xA0, 0x60, 0x20, 0xC0},   /* g (TI89)*/
    {0x00, 0x80, 0xC0, 0xA0, 0xA0, 0xA0},   /* h (TI89)*/
    {0x00, 0x80, 0x00, 0x80, 0x80, 0x80},   /* i (TI89)*/
    {0x00, 0x40, 0x00, 0x40, 0x40, 0xC0},   /* j */
    FONT4X6_NOTIMPLEMENTED,                             /* k */
    {0x00, 0xC0, 0x40, 0x40, 0x40, 0x40},   /* l (TI89)*/
    {0x00, 0x00, 0x90, 0xF0, 0x90, 0x90},   /* m */
    {0x00, 0x00, 0xC0, 0xA0, 0xA0, 0xA0},   /* n */
    {0x00, 0x00, 0x40, 0xA0, 0xA0, 0x40},   /* o (TI89)*/
    {0x00, 0x00, 0xC0, 0xA0, 0xC0, 0x80},   /* p (TI89)*/
    {0x00, 0x00, 0xB0, 0x90, 0xB0, 0x80},   /* q */
    {0x00, 0x00, 0xA0, 0xC0, 0x80, 0x80},   /* r (TI89)*/
    {0x00, 0x00, 0x80, 0x70, 0x20, 0x70},   /* s */
    {0x00, 0x80, 0xC0, 0x80, 0x80, 0x40},   /* t (TI89)*/
    {0x00, 0x00, 0x00, 0xB0, 0xB0, 0xE0},   /* u */
    {0x00, 0x00, 0x00, 0xB0, 0xB0, 0x40},   /* v */
    {0x00, 0x00, 0x88, 0xA8, 0xA8, 0x50},   /* w (TI89)*/
    FONT4X6_NOTIMPLEMENTED,                             /* x */
    {0x00, 0x00, 0xA0, 0xA0, 0x40, 0x80},   /* y (TI89)*/
    {0x00, 0x00, 0xF0, 0x20, 0x40, 0xF0},   /* z (TI89)*/
    FONT4X6_NOTIMPLEMENTED,                             /* { */
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80},   /* | */
    FONT4X6_NOTIMPLEMENTED,                             /* } */
    FONT4X6_NOTIMPLEMENTED,                             /* ~ */
};



unsigned char Font6X8 [95][8]= {
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   /* Space (TI-89)*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},   /* ! */
    FONT6X8_NOTIMPLEMENTED,                             /* " */
    FONT6X8_NOTIMPLEMENTED,                             /* # */
    FONT6X8_NOTIMPLEMENTED,                             /* $ */
    FONT6X8_NOTIMPLEMENTED,                             /* % */
    FONT6X8_NOTIMPLEMENTED,                             /* & */
    FONT6X8_NOTIMPLEMENTED,                             /* ' */
    FONT6X8_NOTIMPLEMENTED,                             /* ( */
    FONT6X8_NOTIMPLEMENTED,                             /* ) */
    FONT6X8_NOTIMPLEMENTED,                             /* * */
    FONT6X8_NOTIMPLEMENTED,                             /* + */
    FONT6X8_NOTIMPLEMENTED,                             /* , */
    {0x00, 0x00, 0x00, 0xF8, 0x00, 0x00, 0x00, 0x00},   /* - (TI-89)*/
    {0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x60, 0x00},   /* . (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* / */
    FONT6X8_NOTIMPLEMENTED,                             /* 0 */
    {0x40, 0xC0, 0x40, 0x40, 0x40, 0x40, 0xE0, 0x00},   /* 1 (TI-89)*/
    {0x70, 0x88, 0x08, 0x10, 0x20, 0x40, 0xF8, 0x00},   /* 2 (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* 3 */
    FONT6X8_NOTIMPLEMENTED,                             /* 4 */
    FONT6X8_NOTIMPLEMENTED,                             /* 5 */
    FONT6X8_NOTIMPLEMENTED,                             /* 6 */
    FONT6X8_NOTIMPLEMENTED,                             /* 7 */
    FONT6X8_NOTIMPLEMENTED,                             /* 8 */
    FONT6X8_NOTIMPLEMENTED,                             /* 9 */
    {0x00, 0x60, 0x60, 0x00, 0x60, 0x60, 0x00, 0x00},   /* : (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* ; */
    FONT6X8_NOTIMPLEMENTED,                             /* < */
    FONT6X8_NOTIMPLEMENTED,                             /* = */
    FONT6X8_NOTIMPLEMENTED,                             /* > */
    FONT6X8_NOTIMPLEMENTED,                             /* ? */
    FONT6X8_NOTIMPLEMENTED,                             /* @ */
    FONT6X8_NOTIMPLEMENTED,                             /* A */
    {0xF0, 0x88, 0x88, 0xF0, 0x88, 0x88, 0xF0, 0x00},   /* B (TI-89)*/
    {0x70, 0x88, 0x80, 0x80, 0x80, 0x88, 0x70, 0x00},   /* C (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* D */
    {0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0xF8, 0x00},   /* E (TI-89)*/
    {0xF8, 0x80, 0x80, 0xF0, 0x80, 0x80, 0x80, 0x00},   /* F (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* G */
    FONT6X8_NOTIMPLEMENTED,                             /* H */
    {0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00},   /* I (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* J */
    FONT6X8_NOTIMPLEMENTED,                             /* K */
    {0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF8, 0x00},   /* L (TI-89)*/
    {0x88, 0xD8, 0xA8, 0xA8, 0x88, 0x88, 0x88, 0x00},   /* M (TI-89)*/
    {0x88, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x00},   /* N (TI-89)*/
    {0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00},   /* O (TI-89)*/
    {0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80, 0x80, 0x00},   /* P (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* Q */
    {0xF0, 0x88, 0x88, 0xF0, 0xA0, 0x90, 0x88, 0x00},   /* R (TI-89)*/
    {0x78, 0x80, 0x80, 0x70, 0x08, 0x08, 0xF0, 0x00},   /* S (TI-89)*/
    {0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00},   /* T (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* U */
    FONT6X8_NOTIMPLEMENTED,                             /* V */
    FONT6X8_NOTIMPLEMENTED,                             /* W */
    FONT6X8_NOTIMPLEMENTED,                             /* X */
    FONT6X8_NOTIMPLEMENTED,                             /* Y */
    FONT6X8_NOTIMPLEMENTED,                             /* Z */
    {0x30, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x00},   /* [ (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* \ */
    {0x30, 0x10, 0x10, 0x10, 0x10, 0x10, 0x30, 0x00},   /* ] (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* ^ */
    FONT6X8_NOTIMPLEMENTED,                             /* _ */
    FONT6X8_NOTIMPLEMENTED,                             /* ` */
    {0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00},   /* a (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* b */
    {0x00, 0x00, 0x70, 0x80, 0x80, 0x88, 0x70, 0x00},   /* c (TI-89)*/
    {0x08, 0x08, 0x68, 0x98, 0x88, 0x88, 0x78, 0x00},   /* d (TI-89)*/
    {0x00, 0x00, 0x70, 0x88, 0xF8, 0x80, 0x70, 0x00},   /* e (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* f */
    {0x00, 0x78, 0x88, 0x88, 0x78, 0x08, 0x70, 0x00},   /* g (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* h */
    {0x40, 0x00, 0xC0, 0x40, 0x40, 0x40, 0xE0, 0x00},   /* i */
    FONT6X8_NOTIMPLEMENTED,                             /* j */
    {0x80, 0x80, 0x90, 0xA0, 0xC0, 0xA0, 0x90, 0x00},   /* k (TI-89)*/
    {0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00},   /* l (TI-89)*/
    {0x00, 0x00, 0xD0, 0xA8, 0xA8, 0xA8, 0xA8, 0x00},   /* m (TI-89)*/
    {0x00, 0x00, 0xB0, 0xC8, 0x88, 0x88, 0x88, 0x00},   /* n (TI-89)*/
    {0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00},   /* o (TI-89)*/
    {0x00, 0x00, 0xF0, 0x88, 0x88, 0xF0, 0x80, 0x80},   /* p (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* q */
    {0x00, 0x00, 0xB0, 0xC8, 0x80, 0x80, 0x80, 0x00},   /* r (TI-89)*/
    {0x00, 0x00, 0x70, 0x80, 0x70, 0x08, 0xF0, 0x00},   /* s (TI-89)*/
    {0x40, 0x40, 0xE0, 0x40, 0x40, 0x48, 0x30, 0x00},   /* t (TI-89)*/
    {0x00, 0x00, 0x88, 0x88, 0x88, 0x98, 0x68, 0x00},   /* u (TI-89)*/
    {0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00},   /* v (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* w */
    {0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00},   /* x (TI-89)*/
    {0x00, 0x00, 0x88, 0x88, 0x88, 0x78, 0x08, 0x70},   /* y (TI-89)*/
    FONT6X8_NOTIMPLEMENTED,                             /* z */
    FONT6X8_NOTIMPLEMENTED,                             /* { */
    FONT6X8_NOTIMPLEMENTED,                             /* | */
    FONT6X8_NOTIMPLEMENTED,                             /* } */
    FONT6X8_NOTIMPLEMENTED,                             /* ~ */
};
unsigned short Font8X10[95][10]={
    FONT8X10_NOTIMPLEMENTED,                             /* Space */
    FONT8X10_NOTIMPLEMENTED,                             /* ! */
    FONT8X10_NOTIMPLEMENTED,                             /* " */
    FONT8X10_NOTIMPLEMENTED,                             /* # */
    FONT8X10_NOTIMPLEMENTED,                             /* $ */
    FONT8X10_NOTIMPLEMENTED,                             /* % */
    FONT8X10_NOTIMPLEMENTED,                             /* & */
    FONT8X10_NOTIMPLEMENTED,                             /* ' */
    FONT8X10_NOTIMPLEMENTED,                             /* ( */
    FONT8X10_NOTIMPLEMENTED,                             /* ) */
    FONT8X10_NOTIMPLEMENTED,                             /* * */
    FONT8X10_NOTIMPLEMENTED,                             /* + */
    FONT8X10_NOTIMPLEMENTED,                             /* , */
    FONT8X10_NOTIMPLEMENTED,                             /* - */
    FONT8X10_NOTIMPLEMENTED,                             /* . */
    FONT8X10_NOTIMPLEMENTED,                             /* / */
    FONT8X10_NOTIMPLEMENTED,                             /* 0 */
    FONT8X10_NOTIMPLEMENTED,                             /* 1 */
    FONT8X10_NOTIMPLEMENTED,                             /* 2 */
    FONT8X10_NOTIMPLEMENTED,                             /* 3 */
    FONT8X10_NOTIMPLEMENTED,                             /* 4 */
    FONT8X10_NOTIMPLEMENTED,                             /* 5 */
    FONT8X10_NOTIMPLEMENTED,                             /* 6 */
    FONT8X10_NOTIMPLEMENTED,                             /* 7 */
    FONT8X10_NOTIMPLEMENTED,                             /* 8 */
    FONT8X10_NOTIMPLEMENTED,                             /* 9 */
    FONT8X10_NOTIMPLEMENTED,                             /* : */
    FONT8X10_NOTIMPLEMENTED,                             /* ; */
    FONT8X10_NOTIMPLEMENTED,                             /* < */
    FONT8X10_NOTIMPLEMENTED,                             /* = */
    FONT8X10_NOTIMPLEMENTED,                             /* > */
    FONT8X10_NOTIMPLEMENTED,                             /* ? */
    FONT8X10_NOTIMPLEMENTED,                             /* @ */
    FONT8X10_NOTIMPLEMENTED,                             /* A */
    FONT8X10_NOTIMPLEMENTED,                             /* B */
    FONT8X10_NOTIMPLEMENTED,                             /* C */
    FONT8X10_NOTIMPLEMENTED,                             /* D */
    FONT8X10_NOTIMPLEMENTED,                             /* E */
    FONT8X10_NOTIMPLEMENTED,                             /* F */
    FONT8X10_NOTIMPLEMENTED,                             /* G */
    FONT8X10_NOTIMPLEMENTED,                             /* H */
    FONT8X10_NOTIMPLEMENTED,                             /* I */
    FONT8X10_NOTIMPLEMENTED,                             /* J */
    FONT8X10_NOTIMPLEMENTED,                             /* K */
    FONT8X10_NOTIMPLEMENTED,                             /* L */
    FONT8X10_NOTIMPLEMENTED,                             /* M */
    FONT8X10_NOTIMPLEMENTED,                             /* N */
    FONT8X10_NOTIMPLEMENTED,                             /* O */
    FONT8X10_NOTIMPLEMENTED,                             /* P */
    FONT8X10_NOTIMPLEMENTED,                             /* Q */
    FONT8X10_NOTIMPLEMENTED,                             /* R */
    FONT8X10_NOTIMPLEMENTED,                             /* S */
    FONT8X10_NOTIMPLEMENTED,                             /* T */
    FONT8X10_NOTIMPLEMENTED,                             /* U */
    FONT8X10_NOTIMPLEMENTED,                             /* V */
    FONT8X10_NOTIMPLEMENTED,                             /* W */
    FONT8X10_NOTIMPLEMENTED,                             /* X */
    FONT8X10_NOTIMPLEMENTED,                             /* Y */
    FONT8X10_NOTIMPLEMENTED,                             /* Z */
    FONT8X10_NOTIMPLEMENTED,                             /* [ */
    FONT8X10_NOTIMPLEMENTED,                             /* \ */
    FONT8X10_NOTIMPLEMENTED,                             /* ] */
    FONT8X10_NOTIMPLEMENTED,                             /* ^ */
    FONT8X10_NOTIMPLEMENTED,                             /* _ */
    FONT8X10_NOTIMPLEMENTED,                             /* ` */
    FONT8X10_NOTIMPLEMENTED,                             /* a */
    FONT8X10_NOTIMPLEMENTED,                             /* b */
    FONT8X10_NOTIMPLEMENTED,                             /* c */
    FONT8X10_NOTIMPLEMENTED,                             /* d */
    FONT8X10_NOTIMPLEMENTED,                             /* e */
    FONT8X10_NOTIMPLEMENTED,                             /* f */
    FONT8X10_NOTIMPLEMENTED,                             /* g */
    FONT8X10_NOTIMPLEMENTED,                             /* h */
    FONT8X10_NOTIMPLEMENTED,                             /* i */
    FONT8X10_NOTIMPLEMENTED,                             /* j */
    FONT8X10_NOTIMPLEMENTED,                             /* k */
    FONT8X10_NOTIMPLEMENTED,                             /* l */
    FONT8X10_NOTIMPLEMENTED,                             /* m */
    FONT8X10_NOTIMPLEMENTED,                             /* n */
    FONT8X10_NOTIMPLEMENTED,                             /* o */
    FONT8X10_NOTIMPLEMENTED,                             /* p */
    FONT8X10_NOTIMPLEMENTED,                             /* q */
    FONT8X10_NOTIMPLEMENTED,                             /* r */
    FONT8X10_NOTIMPLEMENTED,                             /* s */
    FONT8X10_NOTIMPLEMENTED,                             /* t */
    FONT8X10_NOTIMPLEMENTED,                             /* u */
    FONT8X10_NOTIMPLEMENTED,                             /* v */
    FONT8X10_NOTIMPLEMENTED,                             /* w */
    FONT8X10_NOTIMPLEMENTED,                             /* x */
    FONT8X10_NOTIMPLEMENTED,                             /* y */
    FONT8X10_NOTIMPLEMENTED,                             /* z */
    FONT8X10_NOTIMPLEMENTED,                             /* { */
    FONT8X10_NOTIMPLEMENTED,                             /* | */
    FONT8X10_NOTIMPLEMENTED,                             /* } */
    FONT8X10_NOTIMPLEMENTED,                             /* ~ */
};
