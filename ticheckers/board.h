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
// Created 6/17/2001; 1:28:09 AM

#ifndef _BOARD_H
#define _BOARD_H

PIECE start[32] = {
	{BLACK,{16,20}},{BLACK,{48,20}},{BLACK,{80,20}},{BLACK,{112,20}},
	{BLACK,{32,30}},{BLACK,{64,30}},{BLACK,{96,30}},{BLACK,{128,30}},
	{BLACK,{16,40}},{BLACK,{48,40}},{BLACK,{80,40}},{BLACK,{112,40}},
	{EMPTY,{32,50}},{EMPTY,{64,50}},{EMPTY,{96,50}},{EMPTY,{128,50}},
	{EMPTY,{16,60}},{EMPTY,{48,60}},{EMPTY,{80,60}},{EMPTY,{112,60}},
	{RED,{32,70}},{RED,{64,70}},{RED,{96,70}},{RED,{128,70}},
	{RED,{16,80}},{RED,{48,80}},{RED,{80,80}},{RED,{112,80}},
	{RED,{32,90}},{RED,{64,90}},{RED,{96,90}},{RED,{128,90}}
};

#endif
