#include "include/alloc.h"
#include "stub.h"
#include <vector>

MemoryBlock AllHandles[MAX_HANDLES];

void *calloc_throw (USHORT NoOfItems, USHORT SizeOfItems) {
    PARTIAL("calloc_throw - No Error Handling");
    return calloc(NoOfItems, SizeOfItems);
}
SSHORT FreeHandles (void) {
    TRACK("FreeHandles");
    SSHORT count=0;
    for(SSHORT i=1; i<MAX_HANDLES; i++) {
          if(AllHandles[i].Allocated==false) {
               count++;
          }
     }
     return count;
}
HANDLE HeapAlloc (ULONG Size) {
     TRACK("HeapAlloc");
     MemoryBlock Mem;
     HANDLE H=H_NULL;
     Mem.Data=malloc(Size);
     if(Mem.Data!=NULL) {
          Mem.Allocated=TRUE;
          H=HeapGetHandle();
          if(H != H_NULL) {
               AllHandles[H]=Mem;
          }
          else {
               free(Mem.Data);
          }
     }
     return H;
}
HANDLE HeapAllocESTACK (ULONG Size) {
     TRACK("HeapAllocESTACK");
     return HeapAlloc(Size);
}
HANDLE HeapAllocHigh (ULONG Size) {
     TRACK("HeapAllocHigh");
     return HeapAlloc(Size);
}
HANDLE HeapAllocHighThrow (ULONG Size) {
     PARTIAL("HeapAllocHighThrow - No Error Handling");
     return HeapAllocHigh(Size);
}
void *HeapAllocPtr (ULONG Size) {
     TRACK("HeapAllocPtr");
     MemoryBlock Mem;
     HANDLE H;
     Mem.Data=malloc(Size);
     if(Mem.Data!=NULL) {
          Mem.Allocated=TRUE;
          H=HeapGetHandle();
          if(H != H_NULL) {
               AllHandles[H]=Mem;
          }
          else {
               free(Mem.Data);
          }
     }
     return Mem.Data;
}
void *HeapAllocPtrThrow (ULONG Size){
     PARTIAL("HeapAllocPtrThrow - No Error Handling");
     return HeapAllocPtr(Size);
}
HANDLE HeapAllocThrow (ULONG Size){
     PARTIAL("HeapAllocThrow - No Error Handling");
     return HeapAlloc(Size);
}
ULONG HeapAvail (void){
     TRACK("HeapAvail");
     return 50000;
}
void HeapCompress (void) {
     TRACK("HeapCompress");
     for(SSHORT i=0; i<MAX_HANDLES; i++) {
          if(AllHandles[i].Allocated==FALSE) {
               /* Find a non-empty, unlocked block */
               SSHORT j;
               for(j=i+1; j<MAX_HANDLES; j++) {
                    if(  AllHandles[j].Locked==FALSE &&
                         AllHandles[j].Allocated==TRUE) {
                              AllHandles[i]=AllHandles[j];
                    }
               }
               /*   If we make it to the end without finding one, we can stop
                    compressing. */
               if(j==MAX_HANDLES) {
                    i=MAX_HANDLES;
               }
          }
     }
}
void *HeapDeref (HANDLE Handle){
     TRACK("HeapDeref");
     return AllHandles[Handle].Data;
}
void *HeapEnd (void) {
     STUB("HeapEnd");
     return NULL;
}
void HeapFree (HANDLE Handle) {
     TRACK("HeapFree");
     AllHandles[Handle].Allocated=FALSE;
     AllHandles[Handle].Locked=FALSE;
     free(AllHandles[Handle].Data);
}
void HeapFreeIndir (HANDLE *HandlePtr) {
     TRACK("HeapFreeIndir");
     HeapFree(*HandlePtr);
}
void HeapFreePtr (void *Ptr) {
     TRACK("HeapFreePtr");
     if(HeapPtrToHandle(Ptr) != H_NULL) {
          HeapFree(HeapPtrToHandle(Ptr));
     }
     else
          free(Ptr);
}
HANDLE HeapGetHandle (void) {
     TRACK("HeapGetHandle");
     for(SSHORT i=1; i<MAX_HANDLES; i++) {
          if(AllHandles[i].Allocated==FALSE) {
               return i;
          }
     }
     return H_NULL;
}
short HeapGetLock (HANDLE Handle) {
     TRACK("HeapGetLock");
     return AllHandles[Handle].Locked;
}
HANDLE HeapLock (HANDLE Handle) {
     TRACK("HeapLock");
     AllHandles[Handle].Locked=TRUE;
     return Handle;
}
ULONG HeapMax (void) {
     TRACK("HeapMax");
     /* TI-Calc says the function always causes compression */
     HeapCompress();
     /* Check if we have handles left */
     if(HeapGetHandle() != H_NULL) {
          /* Theres at least one handle left, return that we have space */
          return 65520;
     }
     /* No handles left, return no space */
     return 0;
}
HANDLE HeapPtrToHandle (void *Ptr) {
     TRACK("HeapPtrToHandle");
     for(SSHORT i=1; i<MAX_HANDLES; i++) {
          if(Ptr == AllHandles[i].Data) {
               return i;
          }
     }
     return H_NULL;
}
HANDLE HeapRealloc (HANDLE Handle, ULONG NewSize) {
     PARTIAL("HeapRealloc - Needs rewrite to avoid data loss on failure");
     HeapFree(Handle);
     return HeapAlloc(NewSize);
}
HANDLE HeapReallocThrow (HANDLE Handle, ULONG NewSize) {
     PARTIAL("HeapReallocThrow - No Error Handling");
     return HeapRealloc(Handle, NewSize);
}
void HeapShuffle() {
     TRACK("HeapShuffle");
     for(SSHORT i=0; i<MAX_HANDLES; i++) {
          SSHORT NewPosition=rand()%MAX_HANDLES;
          MemoryBlock Hold;
          Hold=AllHandles[i];
          AllHandles[i]=AllHandles[NewPosition];
          AllHandles[NewPosition]=Hold;
     }
}

ULONG HeapSize (HANDLE Handle) {
     TRACK("HeapSize");
     return sizeof(AllHandles[Handle].Data);
}
HANDLE HeapUnlock (HANDLE Handle) {
     TRACK("HeapUnlock");
     AllHandles[Handle].Locked=FALSE;
     return Handle;
}
SSHORT HeapWalk (SSHORT function) {
     STUB("HeapWalk");
     return 0;
}
void *HLock (HANDLE Handle) {
     TRACK("HLock");
     HeapLock(Handle);
     return HeapDeref(Handle);
}
void *malloc_throw (ULONG Size) {
     PARTIAL("malloc_throw - No error handling");
     return malloc(Size);
}
void *realloc_throw (void *Ptr, ULONG NewSize) {
     PARTIAL("realloc_throw - No error handling");
     return realloc(Ptr,NewSize);
}
