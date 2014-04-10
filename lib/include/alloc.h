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

#ifndef   alloc_h
#define   alloc_h

#include <stdlib.h>
#include "asmtypes.h"

#define H_NULL 0
#define MAX_HANDLES 200  /* The maximum number of handles to allow */


enum HeapWalkCmds {H_WALK_VERIFY = 0, H_WALK_STATUS = 1, H_WALK_DUMP = 2, H_WALK_SYM = 3};

typedef unsigned short HANDLE;
typedef struct {
     void * Data;
     Bool Allocated;
     Bool Locked;
} MemoryBlock ;
extern MemoryBlock AllHandles[MAX_HANDLES];


void *calloc_throw (unsigned short NoOfItems, unsigned short SizeOfItems);
short FreeHandles (void);
HANDLE HeapAlloc (unsigned long Size);
HANDLE HeapAllocESTACK (unsigned long Size);
HANDLE HeapAllocHigh (unsigned long Size) ;
HANDLE HeapAllocHighThrow (unsigned long Size);
void *HeapAllocPtr (unsigned long Size);
void *HeapAllocPtrThrow (unsigned long Size);
HANDLE HeapAllocThrow (unsigned long Size);
unsigned long HeapAvail (void);
void HeapCompress (void);
void *HeapDeref (HANDLE Handle);
void *HeapEnd (void);
void HeapFree (HANDLE Handle);
void HeapFreeIndir (HANDLE *HandlePtr);
void HeapFreePtr (void *Ptr);
HANDLE HeapGetHandle (void);
short HeapGetLock (HANDLE Handle);
HANDLE HeapLock (HANDLE Handle);
unsigned long HeapMax (void);
HANDLE HeapPtrToHandle (void *Ptr);
HANDLE HeapRealloc (HANDLE Handle, unsigned long NewSize);
HANDLE HeapReallocThrow (HANDLE Handle, unsigned long NewSize);
void HeapShuffle();
unsigned long HeapSize (HANDLE Handle);
HANDLE HeapUnlock (HANDLE Handle);
short HeapWalk (short function);
void *HLock (HANDLE Handle);
void *malloc_throw (unsigned long Size);
void *realloc_throw (void *Ptr, unsigned long NewSize);

#endif    /* alloc_h */
