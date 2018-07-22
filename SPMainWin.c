/*
 * SPMainWin.c
 *
 *  Created on: 9 בספט 2017
 *      Author: Admin
 */

#include <stdio.h>
#include <SDL_video.h>
#include "SPMainWin.h"


//Inner functions
int isClickOnNewGame(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 200 && y <= 260)) {
		return 1;
	}
	return 0;
}

int isClickOnLoad(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 300 && y <= 360)) {
		return 1;
	}
	return 0;
}

int isClickOnExit(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 500 && y <= 560)) {
		return 1;
	}
	return 0;
}

SPMainWin* spMainWindowCreate() {
	SPMainWin* res = NULL;
	SDL_Surface* loadingSurface = NULL;
	res = (SPMainWin*) calloc(sizeof(SPMainWin), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}

	// Create an application window with the following settings:
	res->mainWindow = SDL_CreateWindow("chess", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			1000,                               // width, in pixels
			650,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);

	// Check that the window was successfully created
	if (res->mainWindow == NULL ) {
		spMainWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->mainRenderer = SDL_CreateRenderer(res->mainWindow, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->mainRenderer == NULL ) {
		// In the case that the window could not be made...
		spMainWindowDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	//BG
	loadingSurface = SDL_LoadBMP("./graphics/images/BGMain.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a BGMain.bmp: %s\n", SDL_GetError());
		spMainWindowDestroy(res);
		return NULL ;
	}
	res->bg = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->bg == NULL ) {
		printf("Could not create a BGMain.bmp %s\n", SDL_GetError());
		spMainWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//NEWGAME BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/newgame_1.bmp");
	if (loadingSurface == NULL ) {
		spMainWindowDestroy(res);
		printf("couldn't create newgame_1.bmp surface\n");
		return NULL ;
	}
	res->newgameTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->newgameTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create newgame_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//LOAD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/load_1.bmp");
	if (loadingSurface == NULL ) {
		spMainWindowDestroy(res);
		printf("couldn't create load_1.bmp surface\n");
		return NULL ;
	}
	res->loadTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->loadTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create load_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//EXIT BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/exit_1.bmp");
	if (loadingSurface == NULL ) {
		spMainWindowDestroy(res);
		printf("couldn't create exit_1.bmp surface\n");
		return NULL ;
	}
	res->exitTexture = SDL_CreateTextureFromSurface(res->mainRenderer,
			loadingSurface);
	if (res->exitTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spMainWindowDestroy(res);
		printf("couldn't create exit_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	return res;
}

void spMainWindowDestroy(SPMainWin* src) {
	if (!src) {
		return;
	}
	if (src->newgameTexture != NULL ) {
		SDL_DestroyTexture(src->newgameTexture);
	}
	if (src->exitTexture != NULL ) {
		SDL_DestroyTexture(src->exitTexture);
	}
	if (src->loadTexture != NULL ) {
		SDL_DestroyTexture(src->loadTexture);
	}
	if (src->mainRenderer != NULL ) {
		SDL_DestroyRenderer(src->mainRenderer);
	}
	if (src->mainWindow != NULL ) {
		SDL_DestroyWindow(src->mainWindow);
	}
	free(src);
}

void spMainWindowDraw(SPMainWin* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect bgR = { .x = 0, .y = 0, .h = 650, .w = 1000 };
	SDL_Rect newgameR = { .x = 360, .y = 200, .h = 60, .w = 250 };
	SDL_Rect loadR = { .x = 360, .y = 300, .h = 60, .w = 250 };
	SDL_Rect exitR = { .x = 360, .y = 500, .h = 60, .w = 250 };
	SDL_SetRenderDrawColor(src->mainRenderer, 255, 255, 255, 255);
	SDL_RenderClear(src->mainRenderer);
	SDL_RenderCopy(src->mainRenderer, src->bg, NULL, &bgR);
	SDL_RenderCopy(src->mainRenderer, src->newgameTexture, NULL, &newgameR);
	SDL_RenderCopy(src->mainRenderer, src->loadTexture, NULL, &loadR);
	SDL_RenderCopy(src->mainRenderer, src->exitTexture, NULL, &exitR);
	SDL_RenderPresent(src->mainRenderer);
}

SP_MAIN_EVENT spMainWindowHandleEvent(SDL_Event* event) {
	if (!event) {
		return SP_MAIN_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnNewGame(event->button.x, event->button.y)) {
			return SP_MAIN_NEWGAME;
		} else if (isClickOnExit(event->button.x, event->button.y)) {
			return SP_MAIN_EXIT;
		} else if (isClickOnLoad(event->button.x, event->button.y)) {
			return SP_MAIN_LOAD;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_MAIN_EXIT;
		}
		break;
	default:
		return SP_MAIN_NONE;
	}
	return SP_MAIN_NONE;
}

void spMainWindowHide(SPMainWin* src) {
	SDL_HideWindow(src->mainWindow);
}

void spMainWindowShow(SPMainWin* src) {
	SDL_ShowWindow(src->mainWindow);
}
