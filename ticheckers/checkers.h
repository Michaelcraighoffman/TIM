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
// Created 6/9/2001; 1:52:22 AM

#ifndef _CHECKERS_H
#define _CHECKERS_H

typedef struct {
	short int x, y;
} POSITION;

typedef struct {
	short int type;
	POSITION pos;
} PIECE;

typedef struct {
	short int pos, moves;
} MOVE;

#define LOGO		4
#define HEIGHT		10
#define FIRSTRED	20
#define LINKWAIT	200	// 20 * 10 = 10 second wait
#define	TIMER		10	// 10 * (1/20 Hz) = 1/2 second

enum Checkers	{RED, BLACK = 2, REDKING = 4, BLACKKING = 6, EMPTY};
enum Backdrops	{LIGHT, DARK = 2};
enum Moves	{JUMPED, ILLEGAL = 32, LEGAL = 33};
enum Board	{YMIN = 20, YMAX = 90, YSTEP = 10, XMIN = 16, XMAX = 128, XSTEP = 16};
enum Squares	{FIRST, LAST = 31, PIECES = 3};
enum Logo	{LHEIGHT = 18, LWIDTH = 32};
enum VStrings	{REDTURN,BLACKTURN,MUSTJUMP,MULTIJUMP,NOSTR,LOAD,SAVE,LOADERROR,SAVEERROR,ILLEGALMOVE};
enum VPos	{VMIN = 20, VTOTAL = 80, VCHAR = 8, VHALF = 2, VMAX = 10, LEFT = 2, RIGHT = 150};
enum Modes	{EXIT,ONCALC,VSCOMPUTER,LINKRED,LINKBLACK};
enum ModeXY	{MODEX = 55, MODEY = 60};
enum Options	{PLAY,QUIT,COPYRIGHT,URL,MODE};
enum KeyWait	{NOWAIT,WAIT};
enum LinkModes	{NOTRANSLATE,TRANSLATE};
enum LinkCodes	{LINKOK,LINKUNKNOWN,LINKABORT,LINKTIMEOUT};
enum Errors	{GRAYERROR,LINKERROR};
enum Directions	{UPLEFT = 1, UPRIGHT = 2, DOWNLEFT = 4, DOWNRIGHT = 8, JUMPMOVE = 16};
enum Moveable	{MOVEUP = 3, MOVEDOWN = 28};
enum AIWeights	{WJUMP = 10, WMULTIJUMP = 10, WKING = 15, WJUMPBACK = -8, WMOVE = 3, WJUMPBACKMULTI = -25};
enum KingPos	{REDKINGPOS = 3, BLACKKINGPOS = 28, KINGPROMOTE = 4};
enum Borders	{X1 = 0, X2 = 0, X3 = 0, X4 = 159, X5 = 0, X6 = 159, X7 = 159, X8 = 159,
		 Y1 = 0, Y2 = 99, Y3 = 0, Y4 = 0, Y5 = 99, Y6 = 99, Y7 = 0, Y8 = 99};

/* external variable declarations */

extern short int linkmode;

// strings
extern const char *title;
extern const char *vstr[];
extern const char *intro[];
extern const char *errors[];

extern const char *savefile;

// sprites
extern unsigned long int banners[6][90];
extern unsigned short int background[4][10];
extern unsigned short int checkers[8][10];

// the checkerboard
extern PIECE board[32];

/* function prototypes */

/* checkers.c */

inline void fatal(const char *);
short int doIntro(void);
void newGame(short int);
void _main(void);

/* util.c */

short int getKey(short int);
short int translateKey(short int);
short int setupLink(short int);
short int recvCalc(short int);

/* gfx.c */

void cls(void);
void drawVString(const char *str, short int align);
void vString(const char *, short int);
void printGS(short int, short int, const char *);
void drawChecker(short int, POSITION);
void drawBackground(short int, POSITION);
void flash(POSITION);
void drawBorder(void);
void drawMenu(void);
void drawCopyright(void);
void drawBoard(PIECE *);
void drawBanner(short int);
void drawTurn(short int);

/* gameplay.c */

void resetBoard(PIECE *);
void setupGame(PIECE *, short int, short int);
void move(PIECE *, short int, short int);
void removeJumped(PIECE *, short int);
void crownKing(PIECE *, short int);
short int isSelectable(PIECE, short int);
short int isOpponent(short int, short int);
inline short int type1(short int);
short int isCorner(PIECE);
short int findPos(PIECE *, short int, short int);
short int canJump(PIECE *, short int);
short int mustJump(PIECE *, short int);
short int canMove(PIECE *, short int);
short int findDirection(PIECE *, short int, short int);
short int findJumpDirection(PIECE *, short int, short int);
short int isValidMove(PIECE *, short int, short int);
short int haveWinner(PIECE *);
short int noMoves(PIECE *, short int);

/* state.c */

short int loadGame(PIECE *, short int *, short int *, short int *);
short int saveGame(PIECE *, short int, short int, short int);

/* ai.c */

short int findMoves(PIECE *, MOVE *);
inline short int becomesKing(short int);
short int oneJump(short int);
inline short int findJumpPos(PIECE *, short int, short int);
short int canMultiJump(PIECE *, short int, short int *);
short int jumpBack(PIECE *, short int, short int);
short int weightMoves(PIECE *, MOVE *, short int);
void aiPlay(PIECE *);

#endif
