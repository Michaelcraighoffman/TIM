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

/* __custom.h
   This header file is intended to provide all the constants and variables
   which are available on TIGCC, but not implemented by GCC
*/

#ifndef __CUSTOM_H
#define __CUSTOM_H

#include "asmtypes.h"

#define CALLBACK

typedef struct  {
    char bit0: 1;
    char bit1: 1;
    char bit2: 1;
    char bit3: 1;
    char bit4: 1;
    char bit5: 1;
    char bit6: 1;
    char bit7: 1;
} Byte;
typedef struct {
    unsigned long StartTime;
    unsigned long TimeLeft;
    Bool Expired;
    Bool InUse;
} TIMTimer;
extern TIMTimer Timers[9];
void SetBit(Byte * In, int Bit);
void ClearBit(Byte * In, int Bit);
int GetBit(Byte In, int Bit);
#endif
