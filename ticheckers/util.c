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
// Created 6/17/2001; 1:08:39 AM

#include "checkers.h"

#include <kbd.h>
#include <system.h>
#include <compat.h>
#include <../include/link.h>

// link translation variable
short int linkmode = NOTRANSLATE;

// returns keypress from the keyboard using fast kbd reading
short int getKey(short int wait) {
	unsigned short int key = 0, done = 0;
	void *kbq = kbd_queue();
	
	// if we are told to wait, then wait until we have a key, else return anything we have
	while (!done) {
		if (!wait || !OSdequeue(&key,kbq)) {
			done = 1;
		}
	}
	
	// cast to signed for easier comparison
	return (signed short int)key;
}

// interprets keycodes that differ on the TI-89 from the TI-92+
// only changes arrow-keys currently...
short int translateKey(short int keycode) {
	short int newkey;
	
	// translate the arrow keys
	switch (keycode) {
		case 337: newkey = 338; break;
		case 340: newkey = 344; break;
		case 338: newkey = 337; break;
		case 344: newkey = 340; break;
		
		// if we have some other key, it should not require translation
		default: newkey = keycode; break;
	}
	
	// return the translated keycode
	return newkey;
}

// setup link acknowledgement on both sides
short int setupLink(short int side) {
	short int setupgood = 1, mycalc = CALCULATOR;

	if (side == LINKBLACK) {
		// black recives then sends
		
		if (!recvCalc(mycalc)) {
			setupgood = 0;
		}
		
		LIO_SendData(&mycalc,2);
	} else if (side == LINKRED) {
		// red sends then receives
		
		LIO_SendData(&mycalc,2);
		
		if (!recvCalc(mycalc)) {
			setupgood = 0;
		}
	}
	
	// if we have any problems, this will return 0 (FALSE)
	return setupgood;
}

// for key translations, we must know what the other calculator is
short int recvCalc(short int mycalc) {
	short int calc = -1;

	// give the link 20 seconds to send the requested data before auto-abort
	if (LIO_RecvData(&calc,2,LINKWAIT * 2) != LINKOK) {
		// return FALSE on error
		return 0;
	} else {
		// if our calcs are the same, no translation is needed
		if (calc == mycalc) {
			linkmode = NOTRANSLATE;
		} else {
			// otherwise, make sure and translate those keys
			linkmode = TRANSLATE;
		}
	}

	// on error, we will not reach this TRUE return statement
	return 1;
}
