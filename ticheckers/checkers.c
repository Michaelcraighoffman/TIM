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
// Created 6/9/2001; 1:51:48 AM

#include "checkers.h"
#include "strings.h"

#include <graph.h>
#include <gray.h>
#include <compat.h>
#include <link.h>
#include <kbd.h>
#include <system.h>
#include <dialogs.h>

// handler for error messages
inline void fatal(const char *msg) {
	DlgMessage((char *)title,(char *)msg,BT_OK,BT_NONE);
}

// draws the intro screen and provides game-options menu
short int doIntro(void) {
	short int key, mode = ONCALC;

	// clear the screen
	cls();

	// draw the logo
	drawBanner(LOGO);

	// to draw strings in black, must draw in both planes
	for (key = LIGHT_PLANE; key <= DARK_PLANE; key++) {
		SetPlane(key);

		// draw the borders
		drawBorder();

		// display the menu
		drawMenu();

		// display copyright
		drawCopyright();
	}

	// wait until we have received the go-ahead signal (ESC or ENTER)
	do {
		// grab the keypress
		key = getKey(WAIT);

		// F1 toggles the game mode (on-calc/vs.computer/link play)
		if (key == KEY_F1) {
			printGS(MODEX,MODEY,intro[MODE + mode]);

			if (mode < LINKBLACK) {
				mode++;
			} else {
				mode = ONCALC;
			}

			printGS(MODEX,MODEY,intro[MODE + mode]);
		}
	} while (key != KEY_ESC && key != KEY_ENTER);

	// return the mode if we're playing, else, EXIT signal
	return (key == KEY_ENTER) ? mode : EXIT;
}

// starts and plays a new game
void newGame(short int mode) {
	PIECE board[32];
	short int pos = FIRSTRED, done = FALSE, moving = FALSE, savepos = 0, jumpmove = FALSE, direction;
	short int winner = -1, type = DARK, turn = RED, mustjump = -1, jump;
	short int jumppos, newpos;
	unsigned short int key = 0;

	// setup the game board
	resetBoard(board);
	setupGame(board,type,pos);
	vString(vstr[REDTURN],LEFT);

	// wait until there's a winner, or an exit request
	while (!done) {
		// delete old keypresses
		key = 0;

		if (mode == ONCALC || (mode == VSCOMPUTER && !turn)) {
			// wait for keypress
			key = getKey(WAIT);
		} else if ((mode == LINKRED && !turn) || (mode == LINKBLACK && turn)) {
			// wait for keypress
			key = getKey(WAIT);

			// transmit keypress
			LIO_SendData(&key,2);
		} else if ((mode == LINKBLACK && !turn) || (mode == LINKRED && turn)) {
			// wait for link keypress
			if (LIO_RecvData(&key,2,LINKWAIT) == LINKABORT) {
				// if user aborts the link option
				return;
			} else {
				// translate keycode from different calc-type (89/92+ play)
				if (linkmode == TRANSLATE) {
					key = translateKey(key);
				}
			}
		} else if (mode == VSCOMPUTER && turn) {
			// remove selector
			drawBackground(type,board[pos].pos);

			// play the AI side
			aiPlay(board);

			// switch the turn
			turn = !turn;
			drawTurn(turn);
			mustjump = mustJump(board,turn);

			// restore selector
			drawBackground(type,board[pos].pos);
		}

		if (key == KEY_LEFT) {
			// move left
			drawBackground(type,board[pos].pos);

			if (pos == FIRST) {
				pos = LAST;
			} else {
				pos--;
			}

			drawBackground(type,board[pos].pos);
		} else if (key == KEY_RIGHT) {
			// move right
			drawBackground(type,board[pos].pos);

			if (pos == LAST) {
				pos = FIRST;
			} else {
				pos++;
			}

			drawBackground(type,board[pos].pos);
		} else if (key == KEY_UP) {
			// move up
			drawBackground(type,board[pos].pos);

			if ((pos / 4) == 0) {
				pos = LAST - (PIECES - pos);
			} else {
				pos -= 4;
			}

			drawBackground(type,board[pos].pos);
		} else if (key == KEY_DOWN) {
			// move down
			drawBackground(type,board[pos].pos);

			if ((pos / 4) == 7) {
				pos = PIECES - (LAST - pos);
			} else {
				pos += 4;
			}

			drawBackground(type,board[pos].pos);
		} else if (key == KEY_ESC) {
			// quit the game
			done = TRUE;
		} else if (key == KEY_F1) {
			// save-game only permitted when not moving and not in link-play
			if (!moving && mode < LINKRED) {
				// save the game
				if (saveGame(board,turn,pos,mustjump)) {
					vString((char *)vstr[SAVE],RIGHT);
				} else {
					vString((char *)vstr[SAVEERROR],RIGHT);
				}
			} else {
				vString((char *)vstr[SAVEERROR],RIGHT);
			}
		} else if (key == KEY_F2) {
			// load only permissible when not moving and not in link-play
			if (!moving && mode < LINKRED) {
				// load the game
				if (loadGame(board,&turn,&pos,&mustjump)) {
					// draw the new board
					type = DARK;
					moving = FALSE;

					// setup the loaded board
					setupGame(board,type,pos);

					// draw the correct turn information
					vString((char *)vstr[turn],LEFT);

					// draw the load string
					vString((char *)vstr[LOAD],RIGHT);
				} else {
					vString((char *)vstr[LOADERROR],RIGHT);
				}
			}
		} else if (key == KEY_ENTER) {
			// select the piece if not currently moving
			if (!moving) {
				if (isSelectable(board[pos],turn)) {
					moving = TRUE;
					savepos = pos;
					type = LIGHT;

					drawBackground(type,board[pos].pos);
				}
			} else {
				if (isSelectable(board[pos],turn)) {
					// select a different piece

					type = DARK;
					drawBackground(type,board[savepos].pos);
					savepos = pos;
					drawBackground(type,board[pos].pos);
					type = LIGHT;
				} else if (isValidMove(board,savepos,pos)) {
					// otherwise, we must be moving...
					moving = FALSE;

					// delete previous jumpmoves
					jumpmove = FALSE;

					// test for jump
					if ((jump = canJump(board,savepos)) != FALSE) {
						// find the direction of the move
						direction = findJumpDirection(board,savepos,pos);

						// find the jump-to position
						jumppos = findPos(board,savepos,direction);
						newpos = findPos(board,jumppos,direction);

						if ((jump & direction) && (pos == newpos)) {
							jumpmove = TRUE;
							removeJumped(board,jumppos);
						}
					}

					// force jump if jump-move is a must, else allow non-jumps
					if ((mustjump == -1) || jumpmove) {
						// deselect the piece
						drawBackground(type,board[pos].pos);
						type = DARK;
						drawBackground(type,board[pos].pos);
						drawBackground(type,board[savepos].pos);

						// move the checker
						move(board,savepos,pos);

						// test for multijumps
						if (jumpmove && canJump(board,pos)) {
							vString(vstr[MULTIJUMP],RIGHT);

							// reselect the piece for multijump
							moving = TRUE;
							savepos = pos;
							type = LIGHT;

							drawBackground(type,board[pos].pos);
						} else {
							// erase the right side string
							drawVString(vstr[NOSTR],RIGHT);

							// switch the turn
							turn = !turn;
							drawTurn(turn);
						}

						// promote kings where possible...
						crownKing(board,pos);

						// setup jump enforcement
						mustjump = mustJump(board,turn);
					} else {
						// inform them of the jump-move
						vString(vstr[MUSTJUMP],RIGHT);

						// flash the square that must jump
						flash(board[mustjump].pos);

						// reinstate the selector
						moving = TRUE;
					}
				} else {
					// if player attempts an illegal move, inform them
					vString((char *)vstr[ILLEGALMOVE],RIGHT);
				}
			}
		}

		// test for a winner
		if ((winner = haveWinner(board)) != -1) {
			done = TRUE;
		}

		// if the side has no moves available, then the opposing side wins by default
		if (noMoves(board,turn)) {
			// determine who was the winner
			if (turn) {
				winner = RED;
			} else {
				winner = BLACK;
			}

			// end the game-loop
			done = TRUE;
		}
	}

	// winner will be -1 if we quit, rather than a clear win
	// winner includes stalemate, but not voluntary termination
	if (winner != -1) {
		// erase the logo
		drawBanner(LOGO);

		// display the winner's banner
		drawBanner(winner);

		// wait for key before exiting
		getKey(WAIT);
	}
}

int main(void) {
	short int font = FontGetSys(), mode, setupgood;

	// reset to the medium size font
	FontSetSys(F_6x8);

	// setup the 1/2 second timer for piece flashing
	OSFreeTimer(USER_TIMER);
	OSRegisterTimer(USER_TIMER,TIMER);

	// enable grayscale mode
	if (!GrayOn()) {
		fatal(errors[GRAYERROR]);
		return 1;
	}

	// loop until the user exits from the intro
	while ((mode = doIntro()) != EXIT) {
		// if link play selected, make sure its setup properly
		if (mode == LINKRED || mode == LINKBLACK) {
			setupgood = setupLink(mode);
		} else {
			setupgood = TRUE;
		}

		if (setupgood) {
			// start the game
			newGame(mode);
		} else {
			// display error message if link setup fails
			fatal(errors[LINKERROR]);
		}
	}

	// deactivate grayscale mode
	GrayOff();

	// restore the original font before exiting... (necessary??)
	FontSetSys(font);
	return 0;
}
