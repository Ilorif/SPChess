/*
 * SPColorWin.h
 *
 *  Created on: 21 בספט 2017
 *      Author: Admin
 */

#ifndef SPCOLORWIN_H_
#define SPCOLORWIN_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>

typedef enum {
	SP_COLOR_EXIT, SP_COLOR_BLACK, SP_COLOR_WHITE, SP_COLOR_BACK, SP_COLOR_START,
	SP_COLOR_MAINWIN, SP_COLOR_INVALID_ARGUMENT, SP_COLOR_NONE,
	SP_COLOR_BLACKBOLD, SP_COLOR_WHITEBOLD
} SP_COLOR_EVENT;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* blackTexture;
	SDL_Texture* whiteTexture;
	SDL_Texture* blackBoldTexture;
	SDL_Texture* whiteBoldTexture;
	SDL_Texture* backTexture;
	SDL_Texture* startTexture;
	int click; //0=nothing 1=white 2=black
} SPColor;

/**
 * Checks if the range click is according to the 'White' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnWhite(int x, int y);

/**
 * Checks if the pixel range is according to the 'Black' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnBlack(int x, int y);

/**
 * Checks if the pixel range is according to the 'Back' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnBack4(int x, int y);

/**
 * Checks if the pixel range is according to the 'Start' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnStart(int x, int y);

/**
 * Create new color window.
 * @return
 * SPColor - the color window.
 */
SPColor* spColorWinCreate();

/**
 * Frees all memory allocation associated with a given color window. If SPColor==NULL
 * the function does nothing.
 * @param
 * SPColor - color window.
 */
void spColorWinDestroy(SPColor* src);

/**
 * draw the color window according to the defined textures.
 * @param
 * SPColor - color window.
 */
void spColorWinDraw(SPColor* src);

/**
 * the function checks the pixel range and returns a click event accordingly.
 * @param
 * SPColor - color window.
 * SDL_Event* event - the event according the user chosen.
 * @return
 * SP_COLOR_EVENT - event of color window.
 */
SP_COLOR_EVENT spColorWinHandleEvent(SPColor* src, SDL_Event* event);

/**
 * Hide the color window.
 * @param
 * SPColor - color window.
 */
void spColorWinHide(SPColor* src);

/**
 * Show the color window.
 * @param
 * SPColor - color window.
 */
void spColorWinShow(SPColor* src);

#endif /* SPCOLORWIN_H_ */
