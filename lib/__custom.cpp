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

TIMTimer Timers[9];

void SetBit(Byte * In, int Bit) {
    switch(Bit) {
        case 0:
            In->bit0=1; break;
        case 1:
            In->bit1=1; break;
        case 2:
            In->bit2=1; break;
        case 3:
            In->bit3=1; break;
        case 4:
            In->bit4=1; break;
        case 5:
            In->bit5=1; break;
        case 6:
            In->bit6=1; break;
        case 7:
            In->bit7=1; break;
    }
}
void ClearBit(Byte * In, int Bit) {
    switch(Bit) {
        case 0:
            In->bit0=0; break;
        case 1:
            In->bit1=0; break;
        case 2:
            In->bit2=0; break;
        case 3:
            In->bit3=0; break;
        case 4:
            In->bit4=0; break;
        case 5:
            In->bit5=0; break;
        case 6:
            In->bit6=0; break;
        case 7:
            In->bit7=0; break;
    }
}

int GetBit(Byte In, int Bit) {
    switch(Bit) {
        case 0:
            return In.bit0;
        case 1:
            return In.bit1;
        case 2:
            return In.bit2;
        case 3:
            return In.bit3;
        case 4:
            return In.bit4;
        case 5:
            return In.bit5;
        case 6:
            return In.bit6;
        case 7:
            return In.bit7;
    }
}
