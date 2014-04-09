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

#include "kbd.h"
#include "stub.h"

short AlphaStatus=0;

short _keytest_optimized (short row, short col) {
     return _keytest(row, col);
}
short _keytest (short row, short col) {
     STUB("keytest");
     return 0;
}
unsigned short _rowread (unsigned short row) {
     STUB("_rowread");
     return 0;
}
void alphaLockOff (unsigned char *Status) {
     STUB("alphaLockOff");
     Status=0;
}
void alphaLockOn (unsigned char *Status) {
     STUB("alphaLockOn");
     Status=0;
}
unsigned char GetAlphaStatus (void) {
     STUB("GetAlphaStatus");
     return 0;
}
short GKeyDown (void) {
     STUB("GKeyDown");
     return 0;
}
void GKeyFlush (void) {
     STUB("GKeyFlush");
}
short GKeyIn (SCR_RECT *cursor_shape, unsigned short Flags) {
     STUB("GKeyIn");
     return 0;
}
short kbhit (void) {
     STUB("kbhit");
     return 0;
}
short KeyYesOrNo (unsigned short key) {
     STUB("KeyYesOrNo");
     return 0;
}
short ngetchx (void) {
     STUB("ngetchx");
     return 0;
}
short OSGetStatKeys (void){
     STUB("OSGetStatKeys");
     return 0;
}
short OSInitBetweenKeyDelay (short rate){
     STUB("OSInitBetweenKeyDelay");
     return 0;
}
short OSInitKeyInitDelay (short delay){
     STUB("OSInitKeyInitDelay");
     return 0;
}
void pushkey (short code){
     void * KeyboardQueue=kbd_queue();
     OSenqueue(code, KeyboardQueue);
     TRACK("pushkey");
}
void restoreAlphaLock (unsigned char *Status){
     STUB("restoreAlphaLock");
}
void SetAlphaStatus (unsigned char Status) {
     STUB("SetAlphaStatus");
}
