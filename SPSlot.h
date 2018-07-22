/*
 * SPSlot.h
 *
 *  Created on: 11 בספט 2017
 *      Author: Admin
 */
#ifndef SPSLOT_H_
#define SPSLOT_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>

typedef enum {
	SP_SLOT_EXIT, SP_SLOT_GAMESLOT1, SP_SLOT_GAMESLOT2, SP_SLOT_GAMESLOT3, SP_SLOT_GAMESLOT4, SP_SLOT_GAMESLOT5,
	SP_SLOT_BACK, SP_SLOT_LOAD, SP_SLOT_MAINWIN, SP_SLOT_INVALID_ARGUMENT, SP_SLOT_NONE
} SP_SLOT_EVENT;

typedef struct {
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* bgTexture;
	SDL_Texture* slot1Texture;
	SDL_Texture* slot1BoldTexture;
	SDL_Texture* slot2Texture;
	SDL_Texture* slot2BoldTexture;
	SDL_Texture* slot3Texture;
	SDL_Texture* slot3BoldTexture;
	SDL_Texture* slot4Texture;
	SDL_Texture* slot4BoldTexture;
	SDL_Texture* slot5Texture;
	SDL_Texture* slot5BoldTexture;
	SDL_Texture* backTexture;
	SDL_Texture* loadTexture;
	int click; // 0=noting 1=slot1 2=slot2 3=slot3 4=slot4 5=slot5
	int numslots;// 1=Slot1 2=Slot2 3=Slot3 4=Slot4 5=Slot5
} SPSlot;

/**
 * Checks if the range click is according to the 'Slot1' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnSlot1(int x, int y);

/**
 * Checks if the range click is according to the 'Slot2' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnSlot2(int x, int y);

/**
 * Checks if the range click is according to the 'Slot3' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnSlot3(int x, int y);

/**
 * Checks if the range click is according to the 'Slot4' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnSlot4(int x, int y);

/**
 * Checks if the range click is according to the 'Slot5' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnSlot5(int x, int y);

/**
 * Checks if the range click is according to the 'Back' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnBack(int x, int y);

/**
 * Checks if the range click is according to the 'Load' button.
 * @param pixel coordinates x , y
 * @return
 * 1 - if it's in the range.
 * 0 - otherwise
 */
int isClickOnLoad2(int x, int y);

/**
 * Create new loading window.
 * @return
 * SPSlot - the loading window.
 */
SPSlot* spSlotCreate();

/**
 * Frees all memory allocation associated with a given loading window. If SPSlot==NULL
 * the function does nothing.
 * @param
 * SPSlot - loading window.
 */
void spSlotDestroy(SPSlot* src);

/**
 * draw the loading window according to the defined textures.
 * @param
 * SPSlot - loading window.
 */
void spSlotDraw(SPSlot* src);

/**
 * the function checks the pixel range and returns a click event accordingly.
 * @param
 * SPSlot - loading window.
 * SDL_Event* event - the event according the user chosen.
 * @return
 * SP_SLOT_EVENT - event of loading window.
 */
SP_SLOT_EVENT spSlotHandleEvent(SPSlot* src, SDL_Event* event);

/**
 * Hide the loading window.
 * @param
 * SPSlot - loading window.
 */
void spSlotHide(SPSlot* src);

/**
 * Show the loading window.
 * @param
 * SPSlot - loading window.
 */
void spSlotShow(SPSlot* src);

#endif
