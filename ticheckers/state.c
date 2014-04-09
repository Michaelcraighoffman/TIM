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
// Created 6/17/2001; 1:14:12 AM

#include "checkers.h"

#include <stdio.h>
#include <string.h>
#include <args.h>

// the save state file
const char *savefile = "chksaves";

// load game from the savefile
short int loadGame(PIECE *board, short int *turn, short int *pos, short int *mustjump) {
	short int good = TRUE, tturn = 0, tpos = 0, tmustjump = 0;
	PIECE tboard[32];
	FILE *f = fopen(savefile,"rb");

	// make sure the file was opened
	if (f != NULL) {
		if (fread(tboard,sizeof(PIECE),32,f) != 32) good = FALSE;
		if (fread(&tturn,sizeof(short int),1,f) != 1) good = FALSE;
		if (fread(&tpos,sizeof(short int),1,f) != 1) good = FALSE;
		if (fread(&tmustjump,sizeof(short int),1,f) != 1) good = FALSE;
		fclose(f);
	} else {
		good = FALSE;
	}

	if (good) {
		// setup the real board (so we don't ruin a current game over a failed load)
		memcpy(board,tboard,32 * sizeof(PIECE));
		*turn = tturn;
		*pos = tpos;
		*mustjump = tmustjump;
	}

	// let the caller know if the load was successful
	return good;
}

// save the current game to the save file
short int saveGame(PIECE *board, short int turn, short int pos, short int mustjump) {
	short int good = TRUE;
	FILE *f;

	// delete old save file (if exists)
	//unlink(savefile);

	// make sure the file was opened properly
	if ((f = fopen(savefile,"wb")) != NULL) {
		if (fwrite(board,sizeof(PIECE),32,f) != 32) good = FALSE;
		if (fwrite(&turn,sizeof(short int),1,f) != 1) good = FALSE;
		if (fwrite(&pos,sizeof(short int),1,f) != 1) good = FALSE;
		if (fwrite(&mustjump,sizeof(short int),1,f) != 1) good = FALSE;

		// append the filetype as '68K'
		fputc(0,f);
		fputs("68K",f);
		fputc(0,f);
		fputc(OTH_TAG,f);
		fclose(f);
	} else {
		good = FALSE;
	}

	return good;
}
