/*
 * SPColorWin.c
 *
 *  Created on: 21 בספט 2017
 *      Author: Admin
 */

#include <stdio.h>
#include <stdlib.h>
#include <SDL_video.h>
#include "SPColorWin.h"

int isClickOnWhite(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 200 && y <= 260)) {
		return 1;
	}
	return 0;
}

int isClickOnBlack(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 300 && y <= 360)) {
		return 1;
	}
	return 0;
}


int isClickOnBack4(int x, int y) {
	if ((x >= 810 && x <= 990) && (y >= 570 && y <= 620)) {
		return 1;
	}
	return 0;
}
int isClickOnStart(int x, int y) {
	if ((x >= 10 && x <= 190) && (y >= 570 && y <= 620)) {
		return 1;
	}
	return 0;
}

SPColor* spColorWinCreate() {
	SPColor* res = (SPColor*) calloc(sizeof(SPColor), sizeof(char));
	SDL_Surface* loadingSurface = NULL;
	if (res == NULL ) {
		printf("Couldn't create SPColorWin struct\n");
		return NULL ;
	}
	res->click = 0;
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
		spColorWinDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		// In the case that the window could not be made...
		spColorWinDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	//BG
	loadingSurface = SDL_LoadBMP("./graphics/images/BGColor.bmp");
	if (loadingSurface == NULL ) {
		spColorWinDestroy(res);
		printf("couldn't create bgcolor.bmp surface\n");
		return NULL;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spColorWinDestroy(res);
		printf("couldn't create bgcolor.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//WHITE BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/white_1.bmp");
	if (loadingSurface == NULL ) {
		spColorWinDestroy(res);
		printf("couldn't create white_1.bmp surface\n");
		return NULL;
	}
	res->whiteTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->whiteTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spColorWinDestroy(res);
		printf("couldn't create white_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//BLACK BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/black_1.bmp");
	if (loadingSurface == NULL ) {
		spColorWinDestroy(res);
		printf("couldn't create black_1.bmp surface\n");
		return NULL ;
	}
	res->blackTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->blackTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spColorWinDestroy(res);
		printf("couldn't create black_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//WHITEBOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/white.bmp");
	if (loadingSurface == NULL ) {
		spColorWinDestroy(res);
		printf("couldn't create white.bmp surface\n");
		return NULL ;
	}
	res->whiteBoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->whiteBoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spColorWinDestroy(res);
		printf("couldn't create white.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//BLACKBOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/black.bmp");
	if (loadingSurface == NULL ) {
		spColorWinDestroy(res);
		printf("couldn't create black.bmp surface\n");
		return NULL ;
	}
	res->blackBoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->blackBoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spColorWinDestroy(res);
		printf("couldn't create black.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//BACK BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/back.bmp");
	if (loadingSurface == NULL ) {
		spColorWinDestroy(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spColorWinDestroy(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//START BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/start.bmp");
	if (loadingSurface == NULL ) {
		spColorWinDestroy(res);
		printf("couldn't create start.bmp surface\n");
		return NULL ;
	}
	res->startTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->startTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spColorWinDestroy(res);
		printf("couldn't create start.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spColorWinDestroy(SPColor* src) {
	if (!src) {
		return;
	}
	if (src->blackTexture != NULL ) {
		SDL_DestroyTexture(src->blackTexture);
	}
	if (src->blackBoldTexture != NULL ) {
		SDL_DestroyTexture(src->blackBoldTexture);
	}
	if (src->whiteTexture != NULL ) {
		SDL_DestroyTexture(src->whiteTexture);
	}
	if (src->whiteBoldTexture != NULL ) {
		SDL_DestroyTexture(src->whiteBoldTexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->startTexture != NULL ) {
		SDL_DestroyTexture(src->startTexture);
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


void spColorWinDraw(SPColor* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect bgR = { .x = 0, .y = 0, .h = 650, .w = 1000 };
	SDL_Rect whiteR = { .x = 360, .y = 200, .h = 60, .w = 250 };
	SDL_Rect blackR = { .x = 360, .y = 300, .h = 60, .w = 250 };
	SDL_Rect startR = { .x = 10, .y = 570, .h = 50, .w = 180 };
	SDL_Rect backR = { .x = 810, .y = 570, .h = 50, .w = 180 };
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &bgR);
	SDL_RenderCopy(src->renderer, src->backTexture, NULL, &backR);
	if(src->click == 0){
		SDL_RenderCopy(src->renderer, src->whiteTexture, NULL, &whiteR);
		SDL_RenderCopy(src->renderer, src->blackTexture, NULL, &blackR);
	}
	else if(src->click == 1){
		SDL_RenderCopy(src->renderer, src->whiteBoldTexture, NULL, &whiteR);
		SDL_RenderCopy(src->renderer, src->blackTexture, NULL, &blackR);
		SDL_RenderCopy(src->renderer, src->startTexture, NULL, &startR);
	}
	else if(src->click==2){
		SDL_RenderCopy(src->renderer, src->whiteTexture, NULL, &whiteR);
		SDL_RenderCopy(src->renderer, src->blackBoldTexture, NULL, &blackR);
		SDL_RenderCopy(src->renderer, src->startTexture, NULL, &startR);
	}
	SDL_RenderPresent(src->renderer);
}

SP_COLOR_EVENT spColorWinHandleEvent(SPColor* src, SDL_Event* event) {
	if (!event) {
		return SP_COLOR_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnBlack(event->button.x, event->button.y)) {
			return SP_COLOR_BLACK;
		} else if (isClickOnWhite(event->button.x, event->button.y)) {
			return SP_COLOR_WHITE;
		} else if (isClickOnBack4(event->button.x, event->button.y)) {
			return SP_COLOR_BACK;
		} else if (isClickOnStart(event->button.x, event->button.y) && src->click != 0) {
			return SP_COLOR_START;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_COLOR_EXIT;
		}
		break;
	default:
		return SP_COLOR_NONE;
	}
	return SP_COLOR_NONE;
}

void spColorWinHide(SPColor* src) {
	SDL_HideWindow(src->window);
}

void spColorWinShow(SPColor* src) {
	SDL_ShowWindow(src->window);
}

