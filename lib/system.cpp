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

#include "system.h"
#include "stub.h"

const unsigned char *CTypeTable;
signed short CU_cursorState;
volatile unsigned long FiftyMsecTick;
unsigned char OSContrastValue;
unsigned char OSOnBreak;
const char * ReleaseDate;
const char * ReleaseVersion;
QUEUE(200) KeyboardQueue;


unsigned long AB_getGateArrayVersion (void);
void AB_prodid (char *buffer);
void AB_prodname (char *buffer);
short AB_serno (char *buffer);
void ASM_call (void *base_addr);
void ASM_fastcall (void *base_addr);
short CB_fetchTEXT (HANDLE *hText, unsigned long *len);
short CB_replaceTEXT (char *text, unsigned long len, short strip_CR);
void CU_restore (short State);
short CU_start (void);
short CU_stop (void);
void enter_ghost_space (void) {
    TRACK("enter_ghost_space");
}
const void *EX_getBasecodeParmBlock (void);
void EX_patch (void *base_addr, void *tag_ptr);
void HelpKeys (void) {
    TRACK("HelpKeys");
}
void idle (void) {
    TRACK("idle");
}
void *kbd_queue (void) {
    TRACK("kbd_queue");
    return &KeyboardQueue;
}
void LOC_formatDate (const char *format, short y, short m, short d, char *date);
const char *LOC_getLocalDateFormat (void);
char *LOC_localVersionDate (char datebuf[]);
void NeedStack (short Size) {
    TRACK("NeedStack");
}
void off (void) {
    TRACK("off");
}
short OSCheckBreak (void);
void OSClearBreak (void);
unsigned char *OSContrastAddress(void);
void OSContrastDn (void);
void OSContrastUp (void);
short OSdequeue (unsigned short *dest, void *Queue) {
     TRACK("OSdequeue");
     DEF_QUEUE * QueueObj=(DEF_QUEUE *)Queue;

     if(QueueObj->Used>QueueObj->Head) {
          *dest=QueueObj->Buffer[QueueObj->Head];
          QueueObj->Head++;
          return FALSE;
     }
     return TRUE;
}
void OSDisableBreak (void) {
    TRACK("OSDisableBreak");
}
void OSEnableBreak (void) {
    TRACK("OSEnableBreak");
}
short OSenqueue (unsigned short data, void *Queue) {
     TRACK("OSenqueue");
     DEF_QUEUE * QueueObj=(DEF_QUEUE *)Queue;
     if(QueueObj->Used < QueueObj->Size) {
          QueueObj->Buffer[QueueObj->Used]=data;
          QueueObj->Used++;
          return TRUE;
     }
     return FALSE;
}
short OSFreeTimer (short timer_no) {
     TRACK("OSFreeTimer");
     Timers[timer_no].StartTime=0;
     Timers[timer_no].TimeLeft=0;
     Timers[timer_no].InUse=false;
     Timers[timer_no].Expired=false;
     return TRUE;
}
void OSqclear (void *Queue) {
     TRACK("OSqclear");
     DEF_QUEUE * QueueObj=(DEF_QUEUE *)Queue;
     QueueObj->Head=0;
     QueueObj->Used=0;
     TRACK("OSqclear-end");
}

unsigned short OSqhead (unsigned short *dummy, void *Queue);
short OSqinquire (unsigned short *dest, void *Queue);
short OSRegisterTimer (short timer_no, unsigned long T) {
    TRACK("OSRegisterTimer");
    if(Timers[timer_no].InUse==TRUE) {
        return FALSE;
    }
    Timers[timer_no].StartTime=T;
    Timers[timer_no].TimeLeft=T;
    Timers[timer_no].InUse=TRUE;
    Timers[timer_no].Expired=FALSE;
    return TRUE;
}
void OSReset (void);
short OSSetSR (short SR);
unsigned long OSTimerCurVal (short timer_no) {
    TRACK("OSTimerCurVal");
    return Timers[timer_no].TimeLeft;
}
short OSTimerExpired (short timer_no) {
    TRACK("OSTimerExpired");
    if(Timers[timer_no].InUse==FALSE) {
        return FALSE;
    }
    return Timers[timer_no].Expired;
}
unsigned long OSTimerRestart (short timer_no) {
     TRACK("OSTimerRestart");
     int OldTime=Timers[timer_no].TimeLeft;
     Timers[timer_no].TimeLeft=Timers[timer_no].StartTime;
     Timers[timer_no].Expired=FALSE;
     return OldTime;
}
short OSVFreeTimer (short timer_no);
short OSVRegisterTimer (short timer_no, unsigned long T, Timer_Callback_t Action);
short QModeKey (short code);
short QSysKey (short code);
short SumStoChkMem (void);
short WordInList (unsigned short Word, unsigned short *List);
const char *XR_stringPtr (long XR_string_no);
