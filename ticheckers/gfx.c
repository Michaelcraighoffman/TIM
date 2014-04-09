/*
 * Checkers 68k v1.1
 * Copyright (C) 2001,2006 Techno-Plaza
 * http://www.technoplaza.net/
 *
 * This file is part of Checkers 68k.
 *
 * Checkers 68k is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * Checkers 68k is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Checkers 68k; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

// C Source File
// Created 6/17/2001; 1:12:06 AM

#include "checkers.h"
#include "gfx.h"

#include <string.h>
#include <graph.h>
#include <gray.h>
#include <sprites.h>
#include <system.h>

// clearing the screen of a memory-mapped device is as easy as setting all the bits to 0
void cls(void) {
	memset(GetPlane(LIGHT_PLANE),0,LCD_SIZE);
	memset(GetPlane(DARK_PLANE),0,LCD_SIZE);
}

// draws a vertical string (align == RIGHT || align == LEFT)
void drawVString(const char *str, short int align) {
	short int len = (short int)strlen(str), loop, start;

	// VMAX characters MAX when VTOTAL pixels are available
	if (len > VMAX) {
		len = VMAX;
	}

	// find the center of the screen based on string length
	start = VMIN + (VTOTAL - (len * VCHAR)) / VHALF;

	// draw each character one atop another
	for (loop = 0; loop < len; loop++) {
		DrawChar(align,start+loop*VCHAR,(char)str[loop],A_REPLACE);
	}
}

// inlined version draws the "NOSTR" (empty string) to erase first
void vString(const char *str, short int align) {
	drawVString(vstr[NOSTR],align);
	drawVString(str,align);
}

// prints a string in both light and dark planes
void printGS(short int x, short int y, const char *str) {
	SetPlane(LIGHT_PLANE);
	DrawStr(x,y,(char *)str,A_XOR);
	SetPlane(DARK_PLANE);
	DrawStr(x,y,(char *)str,A_XOR);
}

// draws a checker sprite
void drawChecker(short int lightdark, POSITION pos) {
	Sprite16(pos.x,pos.y,HEIGHT,checkers[lightdark],GetPlane(LIGHT_PLANE),SPRT_XOR);
	Sprite16(pos.x,pos.y,HEIGHT,checkers[lightdark+1],GetPlane(DARK_PLANE),SPRT_XOR);
}

// draws a backdrop square (for backgrounds and highlights)
void drawBackground(short int lightdark, POSITION pos) {
	Sprite16(pos.x,pos.y,HEIGHT,background[lightdark],GetPlane(LIGHT_PLANE),SPRT_XOR);
	Sprite16(pos.x,pos.y,HEIGHT,background[lightdark+1],GetPlane(DARK_PLANE),SPRT_XOR);
}

// flashes a square position to bring attention to a square
void flash(POSITION pos) {
	short int loop;

	// flash for 4 * USER_TIMER seconds (default is 1/2 second - so 2 seconds)
	for (loop = 0; loop < 4; loop++) {
		// draw the highlight
		drawBackground(DARK,pos);

		// restart the timer to wait until time to continue
		OSTimerRestart(USER_TIMER);
		while (!OSTimerExpired(USER_TIMER));
	}
}

// draw the screen border
void drawBorder(void) {
	DrawLine(X1,Y1,X2,Y2,A_NORMAL);
	DrawLine(X3,Y3,X4,Y4,A_NORMAL);
	DrawLine(X5,Y5,X6,Y6,A_NORMAL);
	DrawLine(X7,Y7,X8,Y8,A_NORMAL);
}

// draw the intro menu
void drawMenu(void) {
	DrawStr(15,30,(char *)intro[PLAY],A_XOR);
	DrawStr(23,40,(char *)intro[QUIT],A_XOR);
	DrawStr(5,60,(char *)intro[MODE],A_XOR);
	DrawStr(55,60,(char *)intro[MODE + ONCALC],A_XOR);
}

// draw the copyright notice
void drawCopyright(void) {
	FontSetSys(F_4x6);
	DrawStr(15,85,(char *)intro[COPYRIGHT],A_XOR);
	DrawStr(25,92,(char *)intro[URL],A_XOR);
	FontSetSys(F_6x8);
}

// draw the checkerboard
void drawBoard(PIECE *board) {
	short int x, y, pos = 0, loop;

	// draw the checkerboard
	for (y = YMIN; y < YMAX + YSTEP; y+= YSTEP) {
		for (x = XMIN; x < XMAX + XSTEP; x+= XSTEP) {
			drawBackground((pos % 2) * 2,(POSITION){x,y});
			++pos;
		}
		++pos;
	}

	// draw the checkers atop the board
	for (loop = FIRST; loop <= LAST; loop++) {
		if (board[loop].type != EMPTY) {
			drawChecker(board[loop].type,board[loop].pos);
		}
	}
}

// draws a banner (the game logo and the winner's banners)
void drawBanner(short int banner) {
	short int loop, offset = 0;

	// TI-89 dimensions apply to both calculators (no special case graphics!)
	for (loop = 0; loop < 160; loop += LWIDTH) {
		Sprite32(loop,0,LHEIGHT,banners[banner]+offset,GetPlane(LIGHT_PLANE),SPRT_XOR);
		Sprite32(loop,0,LHEIGHT,banners[banner+1]+offset,GetPlane(DARK_PLANE),SPRT_XOR);
		offset += LHEIGHT;
	}
}

// draws the turn string (red or black)
void drawTurn(short int turn) {
	vString(vstr[REDTURN + turn],LEFT);
}
