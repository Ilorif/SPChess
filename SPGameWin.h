/*
 * SPGameWin.h
 *
 *  Created on: 9 בספט 2017
 *      Author: Admin
 */
#ifndef SPGAMEWIN_H_
#define SPGAMEWIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
#include "SPGame.h"
#include "SPPiece.h"
#include "SPMainAux.h"

typedef enum {
	SP_GAME_EVENT_BLACK_WON,
	SP_GAME_EVENT_BLACK_CHECK,
	SP_GAME_EVENT_WHITE_WON,
	SP_GAME_EVENT_WHITE_CHECK,
	SP_GAME_EVENT_TIE,
	SP_GAME_EVENT_QUIT,
	SP_GAME_EVENT_INVALID_ARGUMENT,
	SP_GAME_EVENT_NONE,
	SP_GAME_EVENT_RESTART,
	SP_GAME_EVENT_SAVE,
	SP_GAME_EVENT_LOAD,
	SP_GAME_EVENT_UNDO,
	SP_GAME_EVENT_MAINMENU,
	SP_GAME_EVENT_EXIT,
} SP_GAME_EVENT;

typedef struct{
	int mouseDownX;
	int mouseDownY;
	int mouseUpX;
	int mouseUpY;
	int motionX;
	int motionY;
	int motion;
} Move;

typedef struct{
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* boardTexture;
	SDL_Texture* bishopWTexture;
	SDL_Texture* bishopBTexture;
	SDL_Texture* kingWTexture;
	SDL_Texture* kingBTexture;
	SDL_Texture* knightWTexture;
	SDL_Texture* knightBTexture;
	SDL_Texture* pawnWTexture;
	SDL_Texture* pawnBTexture;
	SDL_Texture* queenWTexture;
	SDL_Texture* queenBTexture;
	SDL_Texture* rookWTexture;
	SDL_Texture* rookBTexture;
	SDL_Texture* restartTexture;
	SDL_Texture* saveTexture;
	SDL_Texture* loadTexture;
	SDL_Texture* undoTexture;
	SDL_Texture* mainmenuTexture;
	SDL_Texture* exitTexture;
	int undoactive;
	SPGame* game;
	Move* moveRelevant;
	int numofsaved;
} SPGameWin;

/**
 * Checks if the undo move is possible.
 * @param SPGameWin - game window.
 * @return
 * 1 - is possible
 * 0 - otherwise
 */
int spGameValidUndo(SPGame * game);

/**
 * Checks if there are tie, checkmate or check.
 * @param SPGameWin - game window.
 * @return
 * 0 - Checkmate - game over
 * 1 - Checkmate - game over
 * 2 - tie
 * 3 - check
 * 4 - check
 * -1 - otherwise
 */
int spGameIsOver(SPGame * game);

/**
 * Checks if the range click is according to the chess board size.
 * This is the destination pixel for 'drag and drop'
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnDes(int x, int y);

/**
 * Checks if the range click is according to the chess board size.
 * This is the source pixel for 'drag and drop'
 * @param  pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnSource(int x, int y);

/**
 * Checks if the range click is according to the 'Restart' button.
 * This is the destination pixel for 'drag and drop'
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnRestart(int x, int y);

/**
 * Checks if the range click is according to the 'Save' button.
 * This is the destination pixel for 'drag and drop'
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnSave(int x, int y);

/**
 * Checks if the range click is according to the 'Load' button.
 * This is the destination pixel for 'drag and drop'
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnLoad3(int x, int y);

/**
 * Checks if the range click is according to the 'Undo' button.
 * This is the destination pixel for 'drag and drop'
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnUndo(int x, int y);

/**
 * Checks if the range click is according to the 'MainMenu' button.
 * This is the destination pixel for 'drag and drop'
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnMainMenu(int x, int y);

/**
 * Checks if the range click is according to the 'Exit' button.
 * This is the destination pixel for 'drag and drop'
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnExit2(int x, int y);

/**
 * Create new move. (move of the user)
 * @return
 * Move - the Loading window.
 */
Move* spGameCreateMove();

/**
 * Frees all memory allocation associated with a given move. If Move==NULL
 * the function does nothing.
 * @param
 * Move - the move.
 */
void spGamedestroyMove(Move* move);

/**
 * Create new game window.
 * @param game - the source game.
 * @return
 * SPGameWin - the game window.
 */
SPGameWin* spGameWindowCreate(SPGame* game);

/**
 * Frees all memory allocation associated with a given game window. If SPGameWin==NULL
 * the function does nothing.
 * @param
 * SPGameWin - game window.
 */
void spGameWindowDestroy(SPGameWin* src);

/**
 * draw the game window according to the defined textures.
 * If the mode is one players the computer move is done.
 * @param
 * SPGameWin - game window.
 */
void spGameWindowDraw(SPGameWin* src);

/**
 * Initialize the fields of move to -1.
 * @param
 * SPGameWin - game window.
 */
void initialize(SPGameWin* src);

/**
 * the function checks the pixel range and returns a click event accordingly.
 * @param
 * SPGameWin - game window.
 * SDL_Event* event - the event according the user chosen.
 * @return
 * SP_GAME_EVENT - event of game window.
 */
SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event);

/**
 * Hide the game window.
 * @param
 * SGameWin - game window.
 */
void spGameWindowHide(SPGameWin* src);

/**
 * Show the game window.
 * @param
 * SGameWin - game window.
 */
void spGameWindowShow(SPGameWin* src);

#endif
