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

#ifndef dialogs_h
#define dialogs_h

#include "alloc.h"
#include "kbd.h"

#define CENTER (-1)
enum DialogMessages { DB_CONTINUE =1, DB_MEMFULL = -1, DB_QACTIVE = -2, DB_REDRAW = -3, DB_REDRAW_AND_CONTINUE = -4, DB_UNKNOWN = -5,DB_GET_EDIT_HANDLE = -6, DB_GET_TITLE = -7, DB_EXIT = -8 };
enum Buttons { BT_NONE = 0, BT_OK = 1, BT_SAVE = 2, BT_YES = 3, BT_CANCEL = 4, BT_NO = 5, BT_GOTO = 6};
enum DialogFlags { DF_TAB_ELLIPSES = 0x01, DF_MAX_MENU_WIDTH = 0x01, DF_SCROLLABLE = 0x02, DF_CLR_ON_REDRAW = 0x04, DF_TAB_SPACES = 0x04, DF_OWNER_DRAW = 0x08, DF_POPUP_RADIO = 0x20, DF_SCREEN_SAVE = 0x40, DF_SKIP = 0x80};
enum DialogTypes { D_END = 0, D_MENU = 1, D_EDIT_FIELD = 2, D_SCROLL_REGION = 3, D_OPTION = 4, D_RADIO = 5, D_BUTTON = 6, D_TEXT = 7, D_HEADER = 8, D_POPUP = 10, D_DYNPOPUP = 11, D_HEDIT = 12, D_DYNHEADER = 13, D_HPOPUP = 14, D_XFLAGS = 15};
enum DialogXFlags { XF_ALLOW_VARLINK = 0x0001, XF_TE_REPAINT = 0x0002, XF_NO_ALPHA_LOCK = 0x0004, XF_VARLINK_SELECT_ONLY = 0x8001 };

/*
typedef struct {
	unsigned char Type;
     unsigned char Flags;
     unsigned char x0, y0;
     union {
          struct {
               void *Menu;
               unsigned char MaxMenuWidth;
          } dMenu;
          struct {
	          short oText;
               void *PopUp;
               unsigned short oIndex;
          } dPopUp;
          struct {
               short oText;
               HANDLE (*GetPopUp)(unsigned short);
               unsigned short oIndex;
          } dDynPopUp;
          struct {
               short oText;
               HANDLE hPopUp;
               unsigned short dummy;
               unsigned short oIndex;
          } dHPopUp;
          struct DEditType {
               short oText;
               unsigned short bOffset;
               unsigned short Flen;
               unsigned char Dlen;
          } dEdit;
          struct {
               short oText;
          } dText;
          struct {
               short oText;
               unsigned char lButton, rButton;
          } dHeader;
          struct {
               short oIcon;
          } dIcon;
          struct {
               unsigned char x1, y1;
               unsigned char Index0, Index1;
               unsigned char NumDspFields, TotNumFields;
               unsigned char FieldHeight;
          } dScrollR;
          struct {
               unsigned short xFlags[4];
          } dFlags;
     } f;
} DIALOG_ITEM;

typedef struct {
	unsigned short TextOffset;
     unsigned short NumItems;
     unsigned char Width, Height;
     Dialog_Callback_t CallBack;
     DIALOG_ITEM Fields[];
} DIALOG;

typedef struct {
	DIALOG_ITEM *Item;
     WINDOW *pW;
} OWNER_DRAW_STRUCT;
*/
short DlgMessage (const char *title, const char *message, short left_button, short right_button);

#endif
