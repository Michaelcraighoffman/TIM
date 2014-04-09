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
#include "asmtypes.h"

#define   DEFINE_INT_HANDLER(HandlerName)   void HandlerName() 
#define FIRST_AUTO_INT 1
#define FIRST_TRAP 0
#define LAST_AUTO_INT 7
#define LAST_TRAP 15
#define TRAP_COUNT (LAST_TRAP - FIRST_TRAP + 1)
#define AUTO_INT_COUNT (LAST_AUTO_INT - FIRST_AUTO_INT + 1)
struct INT_HANDLER {
     void (*intptr)(void);
};
extern INT_HANDLER DUMMY_HANDLER;
enum IntVecs {AUTO_INT_1 = 0x64, AUTO_INT_2 = 0x68, AUTO_INT_3 = 0x6C, AUTO_INT_4 = 0x70, AUTO_INT_5 = 0x74, AUTO_INT_6 = 0x78, AUTO_INT_7 = 0x7C, TRAP_0 = 0x80, TRAP_1 = 0x84, TRAP_2 = 0x88, TRAP_3 = 0x8C, TRAP_4 = 0x90, TRAP_5 = 0x94, TRAP_6 = 0x98, TRAP_7 = 0x9C, TRAP_8 = 0xA0, TRAP_9 = 0xA4, TRAP_10 = 0xA8, TRAP_11 = 0xAC, TRAP_12 = 0xB0, TRAP_13 = 0xB4, TRAP_14 = 0xB8, TRAP_15 = 0xBC, INT_VEC_RESET = 0x04, INT_VEC_BUS_ERROR = 0x08, INT_VEC_ADDRESS_ERROR = 0x0C, INT_VEC_ILLEGAL_INSTRUCTION = 0x10, INT_VEC_ZERO_DIVIDE = 0x14, INT_VEC_CHK_INS = 0x18, INT_VEC_TRAPV_INS = 0x1C, INT_VEC_PRIVILEGE_VIOLATION = 0x20, INT_VEC_TRACE = 0x24, INT_VEC_LINE_1010 = 0x28, INT_VEC_LINE_1111 = 0x2C, INT_VEC_UNINITIALIZED_INT = 0x3C, INT_VEC_SPURIOUS_INT = 0x60, INT_VEC_KEY_PRESS = 0x68, INT_VEC_LINK = 0x70, INT_VEC_ON_KEY_PRESS = 0x78, INT_VEC_STACK_OVERFLOW = 0x7C, INT_VEC_INT_MASK = 0x84, INT_VEC_MANUAL_RESET = 0x88, INT_VEC_OFF = 0x90, INT_VEC_SELF_TEST = 0xA8, INT_VEC_ARCHIVE = 0xAC, INT_VEC_ER_THROW = 0xBC};


void DisablePRG (void);
void EnablePRG (void);
void ExecuteHandler (INT_HANDLER Handler);
INT_HANDLER GetIntVec (long IntVec);
short IsPRGEnabled (void);
short PRG_getRate (void);
unsigned char PRG_getStart (void);
unsigned char PRG_getValue (void);
void PRG_setRate (short rate);
void PRG_setStart (unsigned char val);
void SetIntVec (long IntVec, INT_HANDLER Handler);
