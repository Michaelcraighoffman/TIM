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

#include "gray.h"
#include "stub.h"
#include "__timsystem.h"
#include <allegro.h>

void TIMSetupAllegro() {
    allegro_init();
    install_keyboard();
    install_timer();
    set_color_depth(24);
    if(set_gfx_mode(GFX_AUTODETECT_WINDOWED, 160,100, 0,0)!=0) {
        FIXME("Could not create display");
        exit(EXIT_FAILURE);
    }
    clear_to_color(screen, makecol(255,255,255));
    LOCK_FUNCTION(TIMRenderScreen);
    LOCK_VARIABLE(GrayIsRunning);
    install_int_ex(TIMRenderScreen, BPS_TO_TIMER(30));
    LOCK_FUNCTION(TIMGetKeys);
    install_int_ex(TIMGetKeys, BPS_TO_TIMER(20));
    LOCK_FUNCTION(TIMTimerTick);
    install_int_ex(TIMTimerTick, BPS_TO_TIMER(20));
}
void __attribute__ ((destructor)) TIMShutdown() {
     remove_int(TIMRenderScreen);
}

void __attribute__ ((constructor)) TIMStartup() {
    /* Initialize Tim Pieces */
    TIMSetup();
    /* Initialize Allegro */
    TIMSetupAllegro();
    TRACK("Finished TIMStartup");
}

