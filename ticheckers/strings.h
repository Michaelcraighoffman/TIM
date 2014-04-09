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

// C Header File
// Created 6/17/2001; 2:22:55 AM

#ifndef _STRINGS_H
#define _STRINGS_H

const char *title = "Checkers 68k v1.1";

const char *vstr[] = {
	"Red Turn",
	"Black Turn",
	"Must Jump!",
	"Multi Jump",
	"          ",
	"Loaded",
	"Saved",
	"Load Fail",
	"Save Fail",
	"Illegal!"
};

const char *intro[] = {
	"Press [ENTER] to play",
	"Press [ESC] to exit",
	"Copyright (C) 2001,2006 Techno-Plaza",
	"http://www.technoplaza.net",
	"F1 Mode:",
	"2 Player On-Calc",
	"vs. Computer",
	"Link Play [Red]",
	"Link Play [Black]",
};

const char *errors[] = {
	"Unable to setup grayscale!",
	"Unable to create link!"
};

#endif
