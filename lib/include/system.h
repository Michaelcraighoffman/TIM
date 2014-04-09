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

#ifndef   SYSTEM_H
#define   SYSTEM_H

#include "asmtypes.h"
#include "./alloc.h"
#include "__custom.h"

#define QUEUE(n) struct TIMqueue {unsigned short Head, Tail, Size, Used, Buffer[n/2];} 

enum Timers {USER1_TIMER = 1, BATT_TIMER = 1, APD_TIMER = 2, LIO_TIMER = 3, CURSOR_TIMER = 4, MISC_TIMER = 5, USER_TIMER = 6, BATTERY_TIMER = 7, BP_TIMER = 8};
extern const unsigned char *CTypeTable;
extern signed short CU_cursorState;
extern volatile unsigned long FiftyMsecTick;
extern unsigned char OSContrastValue;
extern unsigned char OSOnBreak;
extern const char * ReleaseDate;
extern const char * ReleaseVersion;
typedef struct {
	unsigned short len; /* length of parameter block */
     unsigned char releaseVersionMajor; /* Major AMS version */
     unsigned char releaseVersionMinor; /* Minor AMS version */
     unsigned short releaseDateYear;
     unsigned char releaseDateMonth;
     unsigned char releaseDateDay;
} BASECODE_PARM_BLOCK;
typedef struct {
	unsigned short Head; /* Offset to the head of the queue */
     unsigned short Tail; /* Offset to the tail of the queue */
     unsigned short Size; /* Max number of entries in the queue */
     unsigned short Used; /* Actual number of entries in the queue */
     unsigned short Buffer[];
} DEF_QUEUE;

typedef CALLBACK void (*Timer_Callback_t) (void);


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
void enter_ghost_space (void);
const void *EX_getBasecodeParmBlock (void);
void EX_patch (void *base_addr, void *tag_ptr);
void HelpKeys (void);
void idle (void);
void *kbd_queue (void);
void LOC_formatDate (const char *format, short y, short m, short d, char *date);
const char *LOC_getLocalDateFormat (void);
char *LOC_localVersionDate (char datebuf[]);
void NeedStack (short Size);
void off (void);
short OSCheckBreak(void);
void OSClearBreak (void);
unsigned char *OSContrastAddress(void);
void OSContrastDn (void);
void OSContrastUp (void);
short OSdequeue (unsigned short *dest, void *Queue);
void OSDisableBreak (void);
void OSEnableBreak (void);
short OSenqueue (unsigned short data, void *Queue);
short OSFreeTimer (short timer_no);
void OSqclear (void *Queue);
unsigned short OSqhead (unsigned short *dummy, void *Queue);
short OSqinquire (unsigned short *dest, void *Queue);
short OSRegisterTimer (short timer_no, unsigned long T);
void OSReset (void);
short OSSetSR (short SR);
unsigned long OSTimerCurVal (short timer_no);
short OSTimerExpired (short timer_no);
unsigned long OSTimerRestart (short timer_no);
short OSVFreeTimer (short timer_no);
short OSVRegisterTimer (short timer_no, unsigned long T, Timer_Callback_t Action);
short QModeKey (short code);
short QSysKey (short code);
short SumStoChkMem (void);
short WordInList (unsigned short Word, unsigned short *List);
const char *XR_stringPtr (long XR_string_no);


#endif
