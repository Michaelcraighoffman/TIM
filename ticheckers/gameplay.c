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
// Created 6/17/2001; 1:13:51 AM

#include "checkers.h"
#include "board.h"

#include <mem.h>

enum Boolean {FALSE,TRUE};

// setup the board
void resetBoard(PIECE *board) {
	memcpy(board,start,32 * sizeof(PIECE));
}

// setup the game screen
void setupGame(PIECE *board, short int type, short int pos) {
	// clear the screen
	cls();

	// draw the logo
	drawBanner(LOGO);

	// draw the checkerboard
	drawBoard(board);

	// invert the current piece
	drawBackground(type,board[pos].pos);
}

// move a checker from pos to newpos
void move(PIECE *board, short int pos, short int newpos) {
	// erase the old checker
	drawChecker(board[pos].type,board[pos].pos);
	board[newpos].type = board[pos].type;

	// redraw the checker in its new place
	drawChecker(board[newpos].type,board[newpos].pos);
	board[pos].type = EMPTY;
}

// remove a jumped piece
void removeJumped(PIECE *board, short int pos) {
	drawChecker(board[pos].type,board[pos].pos);
	board[pos].type = EMPTY;
}

// test for king promotion and apply when needed
void crownKing(PIECE *board, short int pos) {
	short int type;

	// separate by side
	if (pos >= BLACKKINGPOS) {
		type = BLACK;
	} else if (pos <= REDKINGPOS) {
		type = RED;
	} else {
		return;
	}

	// if we are at the 8th rank, and are the low-piece, promote to king
	if (board[pos].type == type) {
		drawChecker(board[pos].type,board[pos].pos);
		board[pos].type += KINGPROMOTE;
		drawChecker(board[pos].type,board[pos].pos);
	}
}

// determines if we can select a checker based on whose turn it is
short int isSelectable(PIECE checker, short int turn) {
	short int selectable = FALSE;

	if (!turn && (checker.type == RED || checker.type == REDKING)) {
		selectable = TRUE;
	} else if (turn && (checker.type == BLACK || checker.type == BLACKKING)) {
		selectable = TRUE;
	}

	return selectable;
}

// determines if a checker is an opponent checker
short int isOpponent(short int you, short int them) {
	short int opponent = FALSE;

	if ((you == RED || you == REDKING) && (them == BLACK || them == BLACKKING)) {
		opponent = TRUE;
	} else if ((you == BLACK || you == BLACKKING) && (them == RED || them == REDKING)) {
		opponent = TRUE;
	}

	return opponent;
}

// type1 = checker rows that start on square 1, not square 0
inline short int type1(short int x) {
	return ((x % (XSTEP * 2)) == FALSE) ? TRUE : FALSE;
}

// determines if a piece is a corner piece
short int isCorner(PIECE checker) {
	if (checker.pos.x == XMIN || checker.pos.x == XMAX) {
		return TRUE;
	}

	return FALSE;
}

// find a position on the checkerboard relative to our current position and intended direction
short int findPos(PIECE *board, short int pos, short int direction) {
	short int newpos = -1, slot1 = type1(board[pos].pos.x), corner = isCorner(board[pos]);

	if ((direction == UPLEFT) && (pos > MOVEUP)) {
		if (slot1) {
			newpos = pos - 4;
		} else {
			if (!corner) {
				newpos = pos - 5;
			}
		}
	} else if ((direction == UPRIGHT) && (pos > MOVEUP)){
		if (!slot1) {
			newpos = pos - 4;
		} else {
			if (!corner) {
				newpos = pos - 3;
			}
		}
	} else if ((direction == DOWNLEFT) && (pos < MOVEDOWN)){
		if (slot1) {
			newpos = pos + 4;
		} else {
			if (!corner) {
				newpos = pos + 3;
			}
		}
	} else if ((direction == DOWNRIGHT) && (pos < MOVEDOWN)){
		if (!slot1) {
			newpos = pos + 4;
		} else {
			if (!corner) {
				newpos = pos + 5;
			}
		}
	}

	// newpos will still equal -1 if the move is not valid
	return newpos;
}

// determines if a piece has the ability to jump
short int canJump(PIECE *board, short int pos) {
	short int direction = UPLEFT, last = DOWNRIGHT, jumped, potential, jump = 0;

	// all other pieces can jump in directions starting from UPLEFT
	if (board[pos].type == BLACK) {
		direction = DOWNLEFT;
	} else if (board[pos].type == RED) {
		last = UPRIGHT;
	}

	do {
		// we now have the direction we will test for the jump...
		// must find jumped
		jumped = findPos(board,pos,direction);

		// if the direction we are working towards is valid
		if (jumped != -1) {
			// you can only jump an opponent
			if (isOpponent(board[pos].type,board[jumped].type)) {
				// now find the potential square of re-entry
				potential = findPos(board,jumped,direction);

				if (potential != -1) {
					if (board[potential].type == EMPTY) {
						// we found a valid jump-move
						jump |= direction;
					}
				}
			}
		}
	} while ((direction <<= 1) <= last);

	return jump;
}

// determines if the current side has a jump opportunity (jumps must be taken)
short int mustJump(PIECE *board, short int turn) {
	short int loop, t1 = RED, t2 = REDKING;

	// turn == 1 == black's turn
	if (turn) {
		t1 = BLACK;
		t2 = BLACKKING;
	}

	// if any square has a jump-possibility, then that side must jump
	for (loop = FIRST; loop <= LAST; loop++) {
		if (board[loop].type == t1 || board[loop].type == t2) {
			if (canJump(board,loop)) {
				return loop;
			}
		}
	}

	// otherwise, return FALSE, but not 0, because 0 could be a valid jump-position
	return -1;
}

// determines if this piece can move
short int canMove(PIECE *board, short int pos) {
	short int moves = 0, newpos, direction = UPLEFT, last = DOWNRIGHT;

	// if they can jump, add the jumpmove to the list of potential moves
	if (canJump(board,pos)) {
		moves |= JUMPMOVE;
	}

	// setup directional abilities based on piece type
	if (board[pos].type == BLACK) {
		direction = DOWNLEFT;
	} else if (board[pos].type == RED) {
		last = UPRIGHT;
	}

	// loop through the possible directions
	do {
		// check for movement in direction
		if ((newpos = findPos(board,pos,direction)) != -1) {
			if (board[newpos].type == EMPTY) {
				// add movement to moves if movement is possible
				moves |= direction;
			}
		}
	} while ((direction <<= 1) <= last);

	return moves;
}

// determine the direction of a move based on the old and new position
short int findDirection(PIECE *board, short int oldpos, short int newpos) {
	short int direction, pos;

	// loop through the directions...
	for (direction = UPLEFT; direction <= DOWNRIGHT; direction <<= 1) {
		pos = findPos(board,oldpos,direction);

		if (pos == newpos) {
			return direction;
		}
	}

	// return FALSE if it's a bad move
	return FALSE;
}

// find the direction of a jump based on the old and new positions
short int findJumpDirection(PIECE *board, short int oldpos, short int newpos) {
	short int jumped, land, direction;

	for (direction = UPLEFT; direction <= DOWNRIGHT; direction <<= 1) {
		// find the jumped position, then the land position
		jumped = findPos(board,oldpos,direction);
		land = findPos(board,jumped,direction);

		if (land == newpos) {
			return direction;
		}
	}

	return FALSE;
}

// determines the validity of a potential move
short int isValidMove(PIECE *board, short int oldpos, short int newpos) {
	short int direction = findDirection(board,oldpos,newpos), valid = FALSE, jump;

	// we can't move into a non-empty square, return FALSE immediately
	if (board[newpos].type != EMPTY) {
		return FALSE;
	}

	// determine jump validity
	jump = canJump(board,oldpos);
	if ((jump & direction) || (jump & findJumpDirection(board,oldpos,newpos))) {
		valid = TRUE;
	}

	// determine move validity piece-wise (BLACK's can't go up, RED's can't go down)
	if (board[oldpos].type != BLACK) {
		if (direction & UPLEFT || direction & UPRIGHT) {
			valid = TRUE;
		}
	}

	if (board[oldpos].type != RED) {
		if (direction & DOWNLEFT || direction & DOWNRIGHT) {
			valid = TRUE;
		}
	}

	// return move validity
	return valid;
}

// determines if we have a winner (by opposition annihilation)
short int haveWinner(PIECE *board) {
	short int red = 0, black = 0, loop, winner = -1;

	// loop through the board and count the pieces on each side
	for (loop = FIRST; loop <= LAST; loop++) {
		if (board[loop].type == RED || board[loop].type == REDKING) {
			red++;
		} else if (board[loop].type == BLACK || board[loop].type == BLACKKING) {
			black++;
		}
	}

	// if one sides pieces are gone, the other side wins
	if (red == 0) {
		winner = BLACK;
	} else if (black == 0) {
		winner = RED;
	}

	return winner;
}

// determines if a side has no moves left (and thereby loses by default)
short int noMoves(PIECE *board, short int turn) {
	short int loop, type = (turn == RED) ? RED : BLACK;

	// loop through the board until we find a movable piece
	for (loop = FIRST; loop <= LAST; loop++) {
		if (board[loop].type != EMPTY) {
			if (!isOpponent(type,board[loop].type)) {
				if (canMove(board,loop)) {
					return FALSE;
				}
			}
		}
	}

	// if we got through the entire board without finding one, we must have no moves
	return TRUE;
}
