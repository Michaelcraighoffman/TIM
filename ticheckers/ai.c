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
// Created 6/17/01; 9:59:06 PM

#include "checkers.h"

#include <stdlib.h>
#include <math.h>
#include <mem.h>
#include <system.h>

// find all available moves for the computer
short int findMoves(PIECE *board, MOVE *moves) {
	short int loop, pos = 0, move, mustjump = mustJump(board,1);

	// loop through the board and add possible moves to the move array
	for (loop = FIRST; loop <= LAST; loop++) {
		if (board[loop].type == BLACK || board[loop].type == BLACKKING) {
			if ((move = canMove(board,loop)) != 0) {
				if (mustjump == -1 || (move & JUMPMOVE)) {
					moves[pos].pos = loop;
					moves[pos].moves = move;
					pos++;
				}
			}
		}
	}

	// return the number of moves found
	return pos;
}

// determine if king promotion is in line
inline short int becomesKing(short int pos) {
	return (pos >= BLACKKINGPOS) ? TRUE : FALSE;
}

short int oneJump(short int jump) {
	short int direction = UPLEFT;
	
	if (!jump) {
		return 0;
	}
	
	do {
		if (jump & direction) {
			return direction;
		}
	} while ((direction <<= 1) <= DOWNRIGHT);
	
	return 0;
}

// returns the landing position of a jump
inline short int findJumpPos(PIECE *board, short int pos, short int direction) {
	return (findPos(board,findPos(board,pos,direction),direction));
}

// determines if a piece has the ability to complete multiple jumps
short int canMultiJump(PIECE *board, short int pos, short int *newpos) {
	short int weight = 0, done = FALSE, cpos = pos, jump;

	// find all jumps
	while (!done) {
		jump = findJumpPos(board,cpos,oneJump(canJump(board,cpos)));
		
		if (jump != -1) {
			weight += WMULTIJUMP;
			cpos = jump;
		} else {
			done = TRUE;
		}
	}

	if (weight > 0) {
		// assign the final position
		*newpos = cpos;
		
		// don't count the first jump
		weight -= WMULTIJUMP;
	}
	
	return weight;
}

// determines if a piece can be jumped back from its new position, if we complete a move into newpos
short int jumpBack(PIECE *board, short int oldpos, short int newpos) {
	short int weight = 0, jumper, final = 0, direction = UPLEFT, jump;
	PIECE tempboard[32];
	
	// create new temporary board...
	memcpy(tempboard,board,32*sizeof(PIECE));
	
	// make the move on our fake board
	tempboard[newpos].type = tempboard[oldpos].type;
	tempboard[oldpos].type = EMPTY;
	
	// check all possible jump-backs
	do {
		// ignore fake jump-back positions
		if ((jumper = findPos(tempboard,newpos,direction)) == -1) {
			continue;
		}
		
		// ignore fake jump-back positions
		if ((jump = findJumpPos(tempboard,jumper,oneJump(canJump(tempboard,jumper)))) == -1) {
			continue;
		}

		if (jump != -1) {
			weight = WJUMPBACK;
		} else if (canMultiJump(tempboard,jumper,&final) != 0) {
			weight = WJUMPBACKMULTI;
		}
	} while (((direction <<= 1) <= DOWNRIGHT) && weight == 0);
	
	return weight;
}

// assign weights to each potential moves -- the highest weight is in theory the best move
short int weightMoves(PIECE *board, MOVE *moves, short int number) {
	short int loop, multipos = 0, jumpweight, bestmove = 0, tweight = -50, jumpback;
	short int direction, mweight, randNum, jump;

	// loop through all the moves we found
	for (loop = 0; loop < number; loop++) {
		// reset the move weight
		mweight = 0;
	
		// test for jump-move
		if (moves[loop].moves & JUMPMOVE) {
			jump = findJumpPos(board,moves[loop].pos,oneJump(canJump(board,moves[loop].pos)));
		
			// add jump weight
			mweight += WJUMP;

			// test for multiple jumps			
			if ((jumpweight = canMultiJump(board,moves[loop].pos,&multipos)) != 0) {
				mweight += jumpweight;
			} else {
				multipos = jump;
			}
			
			// test for king promotion
			if (becomesKing(multipos)) {
				mweight += WKING;
			}
				
			// beware of jump-backs
			if ((jumpback = jumpBack(board,moves[loop].pos,multipos)) != 0) {
				mweight += jumpback;
			}
			
			// ignore all other moves of this piece
			moves[loop].moves = JUMPMOVE;
		} else {
			// set weight as move-weight
			mweight = WMOVE;
			direction = UPLEFT;
			
			// test for all moves
			do {
				if (moves[loop].moves & direction) {
					multipos = findPos(board,moves[loop].pos,direction);
			
					// determine jump-back potential
					if (jumpBack(board,moves[loop].pos,multipos) != FALSE) {
						// ignore jump-back move if others are available
						if (moves[loop].moves & ~direction) {
							moves[loop].moves &= ~direction;
						} else {
							mweight = WJUMPBACK;
						}
					} else if (becomesKing(multipos)) {
						// consider king-promotion
						mweight += WKING;
					}
				}
			} while ((direction <<= 1) <= DOWNRIGHT);
		}
		
		// add high weight, or random factor for equal weightings
		randNum = rand() % 6;
		if (mweight > tweight || ((randNum == 0 || randNum == 3) && mweight == tweight)) {
			tweight = mweight;
			bestmove = loop;
		}
	}
	
	return bestmove;
}

// play the AI side (Computer is always Black)
void aiPlay(PIECE *board) {
	short int total, which, found = 0, newpos, jump, jumped;
	MOVE moves[32], bestmove;

	// find all the moves, then the 'best move' of those available	
	total = findMoves(board,moves);
	which = weightMoves(board,moves,total);
	bestmove = moves[which];
	
	// setup the initial position
	newpos = bestmove.pos;

	// if we have a jump-move, we must take it	
	if (bestmove.moves == JUMPMOVE) {
		total = -1;
	
		// do multiple jumps, when possible...
		while ((jump = oneJump(canJump(board,newpos))) != FALSE) {
			bestmove.pos = newpos;
			jumped = findPos(board,bestmove.pos,jump);
			newpos = findJumpPos(board,bestmove.pos,jump);
			removeJumped(board,jumped);
			move(board,bestmove.pos,newpos);
			
			// flash the new jump positions
			flash(board[newpos].pos);
		}
	} else {
		// move piece
		while (!found) {
			which = (short int)pow(2,(rand() % 4));
			if (which & bestmove.moves) {
				found = 1;
			}
		}
		
		// move the piece
		newpos = findPos(board,bestmove.pos,which);
		move(board,bestmove.pos,newpos);
	}
	
	// crown the kings
	crownKing(board,newpos);
}
