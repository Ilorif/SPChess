/*
 * SPDifficulty.h
 *
 *  Created on: 12 בספט 2017
 *      Author: Admin
 */

#ifndef SPDIFFICULTY_H_
#define SPDIFFICULTY_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>

typedef enum {
	SP_DIFFICULTY_EXIT, SP_DIFFICULTY_NOOB, SP_DIFFICULTY_NOOBBOLD, SP_DIFFICULTY_EASY, SP_DIFFICULTY_EASYBOLD,
	SP_DIFFICULTY_MODERATE, SP_DIFFICULTY_MODERATEBOLD, SP_DIFFICULTY_HARD, SP_DIFFICULTY_HARDBOLD,
	SP_DIFFICULTY_EXPERT, SP_DIFFICULTY_EXPERTBOLD,	SP_DIFFICULTY_BACK,
	SP_DIFFICULTY_NEXT, SP_DIFFICULTY_MAINWIN, SP_DIFFICULTY_INVALID_ARGUMENT,
	SP_DIFFICULTY_NONE
} SP_DIFFICULTY_EVENT;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* noobTexture;
	SDL_Texture* noobBoldTexture;
	SDL_Texture* easyTexture;
	SDL_Texture* easyBoldTexture;
	SDL_Texture* moderateTexture;
	SDL_Texture* moderateBoldTexture;
	SDL_Texture* hardTexture;
	SDL_Texture* hardBoldTexture;
	SDL_Texture* expertTexture;
	SDL_Texture* expertBoldTexture;
	SDL_Texture* backTexture;
	SDL_Texture* nextTexture;
	int click; //0=nothing 1=noob 2=easy 3=moderate 4=hard 5=expert
} SPDifficulty;

/**
 * Checks if the range click is according to the 'Noob' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnNoob(int x, int y);

/**
 * Checks if the range click is according to the 'Easy' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnEasy(int x, int y);

/**
 * Checks if the range click is according to the 'Moderate' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnModerate(int x, int y);

/**
 * Checks if the range click is according to the 'Hard' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnHard(int x, int y);

/**
 * Checks if the range click is according to the 'Expert' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnExpert(int x, int y);

/**
 * Checks if the range click is according to the 'Back' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnBack3(int x, int y);

/**
 * Checks if the range click is according to the 'Next' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnNext(int x, int y);

/**
 * Create new difficulty window.
 * @return
 * SPDifficulty - the difficulty window.
 */
SPDifficulty* spDifficultyWinCreate();

/**
 * Frees all memory allocation associated with a given difficulty window. If SPDifficulty==NULL
 * the function does nothing.
 * @param
 * SPDifficulty - difficulty window.
 */
void spDifficultyWinDestroy(SPDifficulty* src);

/**
 * draw the difficulty window according to the defined textures.
 * @param
 * SPDifficulty - difficulty window.
 */
void spDifficultyWinDraw(SPDifficulty* src);

/**
 * the function checks the pixel range and returns a click event accordingly.
 * @param
 * SPDifficulty - difficulty window.
 * SDL_Event* event - the event according the user chosen.
 * @return
 * SP_DIFFICULTY_EVENT - event of difficulty window.
 */
SP_DIFFICULTY_EVENT spDifficultyWinHandleEvent(SPDifficulty* src, SDL_Event* event);

/**
 * Hide the difficulty window.
 * @param
 * SPDifficulty - difficulty window.
 */
void spDifficultyWinHide(SPDifficulty* src);

/**
 * Show the difficulty window.
 * @param
 * SPDifficulty - difficulty window.
 */
void spDifficultyWinShow(SPDifficulty* src);

#endif /* SPDIFFICULTY_H_ */
