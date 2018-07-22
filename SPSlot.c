/*
 * SPSlot.c
 *
 *  Created on: 11 בספט 2017
 *      Author: Admin
 */

#include "SPSlot.h"
#include <SDL_video.h>
#include <stdio.h>

int isClickOnSlot1(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 150 && y <= 210)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot2(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 250 && y <= 310)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot3(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 350 && y <= 410)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot4(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 450 && y <= 510)) {
		return 1;
	}
	return 0;
}

int isClickOnSlot5(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 550 && y <= 610)) {
		return 1;
	}
	return 0;
}

int isClickOnBack(int x, int y) {
	if ((x >= 810 && x <= 990) && (y >= 570 && y <= 620)) {
		return 1;
	}
	return 0;
}
int isClickOnLoad2(int x, int y) {
	if ((x >= 10 && x <= 190) && (y >= 570 && y <= 620)) {
		return 1;
	}
	return 0;
}

SPSlot* spSlotCreate() {
	SDL_Surface* loadingSurface = NULL;
	SPSlot* res = (SPSlot*) calloc(sizeof(SPSlot), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}
	res->click = 0;
	res->numslots = 0;
	// Create an application window with the following settings:
	res->window = SDL_CreateWindow("chess", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			1000,                               // width, in pixels
			650,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->window == NULL) {
		spSlotDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		// In the case that the window could not be made...
		spSlotDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	//BG BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/BG.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create BG.bmp surface\n");
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create BG.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOT1 BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot1_1.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot1_1.bmp surface\n");
		return NULL ;
	}
	res->slot1Texture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot1Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot1_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOT1BOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot1.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot1.bmp surface\n");
		return NULL ;
	}
	res->slot1BoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot1BoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOT2 BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot2_1.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot_1.bmp surface\n");
		return NULL ;
	}
	res->slot2Texture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot2Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot2_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOT2BOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot2.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot2.bmp surface\n");
		return NULL ;
	}
	res->slot2BoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot2BoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot2.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOT3 BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot3_1.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot3_1.bmp surface\n");
		return NULL ;
	}
	res->slot3Texture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot3Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot3_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOT3BOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot3.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot3.bmp surface\n");
		return NULL ;
	}
	res->slot3BoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot3BoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot3.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOT4 BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot4_1.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot4_1.bmp surface\n");
		return NULL ;
	}
	res->slot4Texture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot4Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot4_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOT4BOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot4.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot4.bmp surface\n");
		return NULL ;
	}
	res->slot4BoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot4BoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot4.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOT5 BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot5_1.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot5_1.bmp surface\n");
		return NULL ;
	}
	res->slot5Texture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot5Texture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot5_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SLOTBOLD5 BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/gameSlot5.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create gameSlot5.bmp surface\n");
		return NULL ;
	}
	res->slot5BoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->slot5BoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create gameSlot5_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//BACK BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/back.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//LOAD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/load.bmp");
	if (loadingSurface == NULL ) {
		spSlotDestroy(res);
		printf("couldn't create load.bmp surface\n");
		return NULL ;
	}
	res->loadTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->loadTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spSlotDestroy(res);
		printf("couldn't create load.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}


void spSlotDestroy(SPSlot* src) {
	if (!src) {
		return;
	}
	if (src->slot1Texture != NULL ) {
		SDL_DestroyTexture(src->slot1Texture);
	}
	if (src->slot1BoldTexture != NULL ) {
		SDL_DestroyTexture(src->slot1BoldTexture);
	}
	if (src->slot2Texture != NULL ) {
		SDL_DestroyTexture(src->slot2Texture);
	}
	if (src->slot2BoldTexture != NULL ) {
		SDL_DestroyTexture(src->slot2BoldTexture);
	}
	if (src->slot3Texture != NULL ) {
		SDL_DestroyTexture(src->slot3Texture);
	}
	if (src->slot3BoldTexture != NULL ) {
		SDL_DestroyTexture(src->slot3BoldTexture);
	}
	if (src->slot4Texture != NULL ) {
		SDL_DestroyTexture(src->slot4Texture);
	}
	if (src->slot4BoldTexture != NULL ) {
		SDL_DestroyTexture(src->slot4BoldTexture);
	}
	if (src->slot5Texture != NULL ) {
		SDL_DestroyTexture(src->slot5Texture);
	}
	if (src->slot5BoldTexture != NULL ) {
		SDL_DestroyTexture(src->slot5BoldTexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->loadTexture != NULL ) {
		SDL_DestroyTexture(src->loadTexture);
	}
	if (src->renderer != NULL ) {
		SDL_DestroyRenderer(src->renderer);
	}
	if (src->window != NULL ) {
		SDL_DestroyWindow(src->window);
	}
	if (src->bgTexture != NULL ) {
		SDL_DestroyTexture(src->bgTexture);
	}
	free(src);
}


void spSlotDraw(SPSlot* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect bgR = { .x = 0, .y = 0, .h = 650, .w = 1000 };
	SDL_Rect slot1R = { .x = 360, .y = 150, .h = 60, .w = 250 };
	SDL_Rect slot2R = {  .x = 360, .y = 250, .h = 60, .w = 250 };
	SDL_Rect slot3R = {  .x = 360, .y = 350, .h = 60, .w = 250 };
	SDL_Rect slot4R = { .x = 360, .y = 450, .h = 60, .w = 250 };
	SDL_Rect slot5R = {.x = 360, .y = 550, .h = 60, .w = 250 };
	SDL_Rect backR = { .x = 810, .y = 570, .h = 50, .w = 180 };
	SDL_Rect loadR = { .x = 10, .y = 570, .h = 50, .w = 180 };
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &bgR);
	SDL_RenderCopy(src->renderer, src->backTexture, NULL, &backR);
	if (src->click == 0){
		SDL_RenderCopy(src->renderer, src->slot1Texture, NULL, &slot1R);
		SDL_RenderCopy(src->renderer, src->slot2Texture, NULL, &slot2R);
		SDL_RenderCopy(src->renderer, src->slot3Texture, NULL, &slot3R);
		SDL_RenderCopy(src->renderer, src->slot4Texture, NULL, &slot4R);
		SDL_RenderCopy(src->renderer, src->slot5Texture, NULL, &slot5R);
	} else if(src->click == 1){
		SDL_RenderCopy(src->renderer, src->slot1BoldTexture, NULL, &slot1R);
		SDL_RenderCopy(src->renderer, src->slot2Texture, NULL, &slot2R);
		SDL_RenderCopy(src->renderer, src->slot3Texture, NULL, &slot3R);
		SDL_RenderCopy(src->renderer, src->slot4Texture, NULL, &slot4R);
		SDL_RenderCopy(src->renderer, src->slot5Texture, NULL, &slot5R);
		SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
	} else if(src->click == 2){
		SDL_RenderCopy(src->renderer, src->slot1Texture, NULL, &slot1R);
		SDL_RenderCopy(src->renderer, src->slot2BoldTexture, NULL, &slot2R);
		SDL_RenderCopy(src->renderer, src->slot3Texture, NULL, &slot3R);
		SDL_RenderCopy(src->renderer, src->slot4Texture, NULL, &slot4R);
		SDL_RenderCopy(src->renderer, src->slot5Texture, NULL, &slot5R);
		SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
	} else if(src->click == 3){
		SDL_RenderCopy(src->renderer, src->slot1Texture, NULL, &slot1R);
		SDL_RenderCopy(src->renderer, src->slot2Texture, NULL, &slot2R);
		SDL_RenderCopy(src->renderer, src->slot3BoldTexture, NULL, &slot3R);
		SDL_RenderCopy(src->renderer, src->slot4Texture, NULL, &slot4R);
		SDL_RenderCopy(src->renderer, src->slot5Texture, NULL, &slot5R);
		SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
	} else if(src->click == 4){
		SDL_RenderCopy(src->renderer, src->slot1Texture, NULL, &slot1R);
		SDL_RenderCopy(src->renderer, src->slot2Texture, NULL, &slot2R);
		SDL_RenderCopy(src->renderer, src->slot3Texture, NULL, &slot3R);
		SDL_RenderCopy(src->renderer, src->slot4BoldTexture, NULL, &slot4R);
		SDL_RenderCopy(src->renderer, src->slot5Texture, NULL, &slot5R);
		SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
	} else if(src->click == 5){
		SDL_RenderCopy(src->renderer, src->slot1Texture, NULL, &slot1R);
		SDL_RenderCopy(src->renderer, src->slot2Texture, NULL, &slot2R);
		SDL_RenderCopy(src->renderer, src->slot3Texture, NULL, &slot3R);
		SDL_RenderCopy(src->renderer, src->slot4Texture, NULL, &slot4R);
		SDL_RenderCopy(src->renderer, src->slot5BoldTexture, NULL, &slot5R);
		SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
	}
	SDL_RenderPresent(src->renderer);
}

SP_SLOT_EVENT spSlotHandleEvent(SPSlot* src, SDL_Event* event) {
	if (!event) {
		return SP_SLOT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnSlot1(event->button.x, event->button.y)) {
			return SP_SLOT_GAMESLOT1;
		} else if (isClickOnSlot2(event->button.x, event->button.y)) {
			return SP_SLOT_GAMESLOT2;
		} else if (isClickOnSlot3(event->button.x, event->button.y)) {
			return SP_SLOT_GAMESLOT3;
		} else if (isClickOnSlot4(event->button.x, event->button.y)) {
			return SP_SLOT_GAMESLOT4;
		} else if (isClickOnSlot5(event->button.x, event->button.y)) {
			return SP_SLOT_GAMESLOT5;
		} else if (isClickOnBack(event->button.x, event->button.y)) {
			return SP_SLOT_BACK;
		} else if (isClickOnLoad2(event->button.x, event->button.y) && src->click != 0) {
			return SP_SLOT_LOAD;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_SLOT_EXIT;
		}
		break;
	default:
		return SP_SLOT_NONE;
	}
	return SP_SLOT_NONE;
}

void spSlotHide(SPSlot* src) {
	SDL_HideWindow(src->window);
}

void spSlotShow(SPSlot* src) {
	SDL_ShowWindow(src->window);
}
