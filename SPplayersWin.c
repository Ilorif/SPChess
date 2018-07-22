/*
 * SPplayersWin.c
 *
 *  Created on: 12 בספט 2017
 *      Author: Admin
 */

#include <stdio.h>
#include "SPplayersWin.h"
#include <SDL_video.h>

int isClickOnOnePlayer(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 200 && y <= 260)) {
		return 1;
	}
	return 0;
}

int isClickOnTwoPlayers(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 300 && y <= 360)) {
		return 1;
	}
	return 0;
}

int isClickOnBack2(int x, int y) {
	if ((x >= 810 && x <= 990) && (y >= 570 && y <= 620)) {
		return 1;
	}
	return 0;
}
int isClickOnStartNext(int x, int y) {
	if ((x >= 10 && x <= 190) && (y >= 570 && y <= 620)) {
		return 1;
	}
	return 0;
}

SPPlayer* spPlayersWinCreate() {
	SPPlayer* res = (SPPlayer*) calloc(sizeof(SPPlayer), sizeof(char));
	SDL_Surface* loadingSurface = NULL;
	if (res == NULL ) {
		printf("Couldn't create SPPlayersWin struct\n");
		return NULL ;
	}
	res->click = 0;
	res->nextStart = 0;
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
		spPlayersWinDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		// In the case that the window could not be made...
		spPlayersWinDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}

	//BG
	loadingSurface = SDL_LoadBMP("./graphics/images/BGMode.bmp");
	if (loadingSurface == NULL ) {
		spPlayersWinDestroy(res);
		printf("couldn't create BGMode.bmp surface\n");
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spPlayersWinDestroy(res);
		printf("couldn't create BGMode.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//ONEPLAYER BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/onePlayer_1.bmp");
	if (loadingSurface == NULL ) {
		spPlayersWinDestroy(res);
		printf("couldn't create onePlayer_1.bmp surface\n");
		return NULL ;
	}
	res->onePlayerTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->onePlayerTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spPlayersWinDestroy(res);
		printf("couldn't create onePlayer_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//ONEPLAYERBOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/onePlayer.bmp");
	if (loadingSurface == NULL ) {
		spPlayersWinDestroy(res);
		printf("couldn't create onePlayer.bmp surface\n");
		return NULL ;
	}
	res->onePlayerBoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->onePlayerBoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spPlayersWinDestroy(res);
		printf("couldn't create onePlayer.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//TWOPLAYERS BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/twoPlayers_1.bmp");
	if (loadingSurface == NULL ) {
		spPlayersWinDestroy(res);
		printf("couldn't create twoPlayers_1.bmp surface\n");
		return NULL ;
	}
	res->twoPlayerTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->twoPlayerTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spPlayersWinDestroy(res);
		printf("couldn't create twoPlayer_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//TWOPLAYERSBOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/twoPlayers.bmp");
	if (loadingSurface == NULL ) {
		spPlayersWinDestroy(res);
		printf("couldn't create twoPlayers.bmp surface\n");
		return NULL ;
	}
	res->twoPlayerBoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->twoPlayerBoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spPlayersWinDestroy(res);
		printf("couldn't create twoPlayer.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//BACK BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/back.bmp");
	if (loadingSurface == NULL ) {
		spPlayersWinDestroy(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spPlayersWinDestroy(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//START BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/start.bmp");
	if (loadingSurface == NULL ) {
		spPlayersWinDestroy(res);
		printf("couldn't create start.bmp surface\n");
		return NULL ;
	}
	res->startTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->startTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spPlayersWinDestroy(res);
		printf("couldn't create start.bmp texture\n");
		return NULL ;
	}

	//NEXT BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/next.bmp");
	if (loadingSurface == NULL ) {
		spPlayersWinDestroy(res);
		printf("couldn't create next.bmp surface\n");
		return NULL ;
	}
	res->nextTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->nextTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spPlayersWinDestroy(res);
		printf("couldn't create next.bmp texture\n");
		return NULL ;
	}

	SDL_FreeSurface(loadingSurface);
	return res;
}

void spPlayersWinDestroy(SPPlayer* src) {
	if (!src) {
		return;
	}
	if (src->onePlayerTexture != NULL ) {
		SDL_DestroyTexture(src->onePlayerTexture);
	}
	if (src->onePlayerBoldTexture != NULL ) {
		SDL_DestroyTexture(src->onePlayerBoldTexture);
	}
	if (src->twoPlayerTexture != NULL ) {
		SDL_DestroyTexture(src->twoPlayerTexture);
	}
	if (src->twoPlayerBoldTexture != NULL ) {
		SDL_DestroyTexture(src->twoPlayerBoldTexture);
	}
	if (src->backTexture != NULL ) {
		SDL_DestroyTexture(src->backTexture);
	}
	if (src->startTexture != NULL ) {
		SDL_DestroyTexture(src->startTexture);
	}
	if (src->nextTexture != NULL ) {
		SDL_DestroyTexture(src->nextTexture);
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


void spPlayersWinDraw(SPPlayer* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect bgR = { .x = 0, .y = 0, .h = 650, .w = 1000};
	SDL_Rect onePlayerR = { .x = 360, .y = 200, .h = 60, .w = 250 };
	SDL_Rect twoPlayerR = { .x = 360, .y = 300, .h = 60, .w = 250 };
	SDL_Rect nextstartR = { .x = 10, .y = 570, .h = 50, .w = 180 };
	SDL_Rect backR = { .x = 810, .y = 570, .h = 50, .w = 180 };
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &bgR);
	SDL_RenderCopy(src->renderer, src->backTexture, NULL, &backR);
	if(src->click == 0){
		SDL_RenderCopy(src->renderer, src->onePlayerTexture, NULL, &onePlayerR);
		SDL_RenderCopy(src->renderer, src->twoPlayerTexture, NULL, &twoPlayerR);
	}
	else if(src->click == 1){
		SDL_RenderCopy(src->renderer, src->onePlayerBoldTexture, NULL, &onePlayerR);
		SDL_RenderCopy(src->renderer, src->twoPlayerTexture, NULL, &twoPlayerR);
		SDL_RenderCopy(src->renderer, src->nextTexture, NULL, &nextstartR);
	}
	else if(src->click == 2){
		SDL_RenderCopy(src->renderer, src->onePlayerTexture, NULL, &onePlayerR);
		SDL_RenderCopy(src->renderer, src->twoPlayerBoldTexture, NULL, &twoPlayerR);
		SDL_RenderCopy(src->renderer, src->startTexture, NULL, &nextstartR);
	}
	SDL_RenderPresent(src->renderer);
}

SP_PLAYER_EVENT spPlayersWinHandleEvent(SPPlayer* src, SDL_Event* event) {
	if (!event) {
		return SP_PLAYERS_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnOnePlayer(event->button.x, event->button.y)) {
			return SP_PLAYERS_ONEPLAYER;
		} else if (isClickOnTwoPlayers(event->button.x, event->button.y)) {
			return SP_PLAYERS_TWOPLAYER;
		} else if (isClickOnBack2(event->button.x, event->button.y)) {
			return SP_PLAYERS_BACK;
		} else if (isClickOnStartNext(event->button.x, event->button.y) && src->nextStart == 1 && src->click != 0) {
			return SP_PLAYERS_NEXT;
		} else if (isClickOnStartNext(event->button.x, event->button.y) && src->nextStart == 0 && src->click != 0) {
			return SP_PLAYERS_START;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_PLAYERS_EXIT;
		}
		break;
	default:
		return SP_PLAYERS_NONE;
	}
	return SP_PLAYERS_NONE;
}

void spPlayersWinHide(SPPlayer* src) {
	SDL_HideWindow(src->window);
}

void spPlayersWinShow(SPPlayer* src) {
	SDL_ShowWindow(src->window);
}
