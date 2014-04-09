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

/* kbd.h Definitions*/

#ifndef   kbd_h
#define   kbd_h

#include "graph.h"
#include "system.h"

#define   BEGIN_KEYTEST
#define   END_KEYTEST
#define   KB_AUTOREPEAT (1<<11)

extern unsigned char OSFastArrows;
#ifndef   __HAVE__KDB_ENUMS
#define   __HAVE__KDB_ENUMS
enum Arrows {ARROW_UP = 1, ARROW_LEFT = 2, ARROW_DOWN = 3, ARROW_RIGHT = 4};
enum CommonKeys {KEY_F1 = 268, KEY_F2 = 269, KEY_F3 = 270, KEY_F4 = 271, KEY_F5 = 272, KEY_F6 = 273, KEY_F7 = 274, KEY_F8 = 275, KEY_ESC = 264, KEY_QUIT = 4360, KEY_APPS = 265, KEY_SWITCH = 4361, KEY_MODE = 266, KEY_BACKSPACE = 257, KEY_INS = 4353, KEY_CLEAR = 263, KEY_VARLNK = 4141, KEY_CHAR = 4139, KEY_ENTER = 13, KEY_ENTRY = 4109, KEY_STO = 258, KEY_RCL = 4354, KEY_SIGN = 173, KEY_MATH = 4149, KEY_MEM = 4150, KEY_ON = 267, KEY_OFF = 4363};
enum GKeyFlags {GKF_NORMAL=0, GKF_MODAL=1, GKF_REPUSH_KEY=2, GKF_ACCEPT=4, GKF_SYS=8, GKF_NO_EVS=16};
#endif    /* __HAVE__KDB_ENUMS */


short _keytest_optimized (short row, short col);
short _keytest (short row, short col);
unsigned short _rowread (unsigned short row);
void alphaLockOff (unsigned char *Status);
void alphaLockOn (unsigned char *Status);
unsigned char GetAlphaStatus (void);
short GKeyDown (void);
void GKeyFlush (void);
short GKeyIn (SCR_RECT *cursor_shape, unsigned short Flags);
short kbhit (void);
short KeyYesOrNo (unsigned short key);
short ngetchx (void);
short OSGetStatKeys (void);
short OSInitBetweenKeyDelay (short rate);
short OSInitKeyInitDelay (short delay);
void pushkey (short code);
void restoreAlphaLock (unsigned char *Status);
void SetAlphaStatus (unsigned char Status);

#endif
