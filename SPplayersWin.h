/*
 * SPplayersWin.h
 *
 *  Created on: 12 בספט 2017
 *      Author: Admin
 */

#ifndef PLAYERSWIN_H_
#define PLAYERSWIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>

typedef enum {
	SP_PLAYERS_EXIT, SP_PLAYERS_ONEPLAYER, SP_PLAYERS_TWOPLAYER, SP_PLAYERS_BACK, SP_PLAYERS_START,
	SP_PLAYERS_MAINWIN, SP_PLAYERS_INVALID_ARGUMENT, SP_PLAYERS_NONE, SP_PLAYERS_NEXT,
	SP_PLAYERS_ONEPLAYERBOLD, SP_PLAYERS_TWOPLAYERBOLD
} SP_PLAYER_EVENT;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* onePlayerTexture;
	SDL_Texture* twoPlayerTexture;
	SDL_Texture* onePlayerBoldTexture;
	SDL_Texture* twoPlayerBoldTexture;
	SDL_Texture* backTexture;
	SDL_Texture* startTexture;
	SDL_Texture* nextTexture;
	int click;// 0=nothing 1=oneplayer 2=twoplayer
	int nextStart; // 1=NEXT 0=START
} SPPlayer;

/**
 * Checks if the range click is according to the 'Oneplayer' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnOnePlayer(int x, int y);

/**
 * Checks if the range click is according to the 'Twoplayers' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnTwoPlayers(int x, int y);

/**
 * Checks if the range click is according to the 'Back' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnBack2(int x, int y);

/**
 * Checks if the range click is according to the 'Start' or 'Next' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnStartNext(int x, int y);

/**
 * Create new mode window.
 * @return
 * SPPlayer - the mode window.
 */
SPPlayer* spPlayersWinCreate();

/**
 * Frees all memory allocation associated with a given mode window. If SPPlayer==NULL
 * the function does nothing.
 * @param
 * SPPlayer - mode window.
 */
void spPlayersWinDestroy(SPPlayer* src);

/**
 * draw the mode window according to the defined textures.
 * @param
 * SPPlayer - mode window.
 */
void spPlayersWinDraw(SPPlayer* src);

/**
 * the function checks the pixel range and returns a click event accordingly.
 * @param
 * SPPlayer - mode window.
 * SDL_Event* event - the event according the user chosen.
 * @return
 * SP_PLAYER_EVENT - event of mode window.
 */
SP_PLAYER_EVENT spPlayersWinHandleEvent(SPPlayer* src, SDL_Event* event);

/**
 * Hide the mode window.
 * @param
 * SPPlayer - mode window.
 */
void spPlayersWinHide(SPPlayer* src);

/**
 * Show the mode window.
 * @param
 * SPPlayer - mode window.
 */
void spPlayersWinShow(SPPlayer* src);

#endif /* PLAYERSWIN_H_ */
