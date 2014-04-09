#include "tests.h"
#include "sprites.h"
#include <tigcclib.h>

bool TestGrayH() {
    if (!GrayOn ())
        return false;
    GraySetAMSPlane (LIGHT_PLANE);
    ClrScr ();
    ScrRectFill (&(SCR_RECT){{20,20,40,40}},&ScreenState.CurClip , A_NORMAL);
    ScrRectFill (&(SCR_RECT){{80,20,100,40}}, &ScreenState.CurClip, A_NORMAL);
    GraySetAMSPlane (DARK_PLANE);
    ClrScr ();
    ScrRectFill (&(SCR_RECT){{50,20,70,40}}, &ScreenState.CurClip, A_NORMAL);
    ScrRectFill (&(SCR_RECT){{80,20,100,40}}, &ScreenState.CurClip, A_NORMAL);
    static const unsigned char sprite[] = {0xFF,0x80,0x80,0x80,0x80,0x80,0x80,0xFF};
    Sprite8(30,10, 8, sprite ,GrayGetPlane(DARK_PLANE), SPRT_XOR);
    Sprite8(30,10, 8, sprite ,GrayGetPlane(LIGHT_PLANE), SPRT_XOR);
    return true;
}

