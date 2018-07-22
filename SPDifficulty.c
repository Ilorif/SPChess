/*
 * SPDifficulty.c
 *
 *  Created on: 12 בספט 2017
 *      Author: Admin
 */
#include "SPDifficulty.h"
#include <SDL_video.h>
#include <stdio.h>

int isClickOnNoob(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 150 && y <= 210)) {
		return 1;
	}
	return 0;
}

int isClickOnEasy(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 250 && y <= 310)) {
		return 1;
	}
	return 0;
}

int isClickOnModerate(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 350 && y <= 410)) {
		return 1;
	}
	return 0;
}

int isClickOnHard(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 450 && y <= 510)) {
		return 1;
	}
	return 0;
}

int isClickOnExpert(int x, int y) {
	if ((x >= 360 && x <= 610) && (y >= 550 && y <= 610)) {
		return 1;
	}
	return 0;
}

int isClickOnBack3(int x, int y) {
	if ((x >= 810 && x <= 990) && (y >= 570 && y <= 620)) {
		return 1;
	}
	return 0;
}

int isClickOnNext(int x, int y) {
	if ((x >= 10 && x <= 190) && (y >= 570 && y <= 620)) {
		return 1;
	}
	return 0;
}

SPDifficulty* spDifficultyWinCreate() {
	SDL_Surface* loadingSurface = NULL;
	SPDifficulty* res = (SPDifficulty*) calloc(sizeof(SPDifficulty), sizeof(char));
	if (res == NULL ) {
		return NULL ;
	}
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
		spDifficultyWinDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		// In the case that the window could not be made...
		spDifficultyWinDestroy(res);
		printf("Could not create window: %s\n", SDL_GetError());
		return NULL ;
	}
	res->click = 0;

	//BG BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/BGDifficulty.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create BGDifficulty.bmp surface\n");
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create BGDifficulty.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Noob BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/noob_1.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create noob_1.bmp surface\n");
		return NULL ;
	}
	res->noobTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->noobTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create noob_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//NOOBBOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/noob.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create noob.bmp surface\n");
		return NULL ;
	}
	res->noobBoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->noobBoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create noob.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//EASY BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/easy_1.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create easy_1.bmp surface\n");
		return NULL ;
	}
	res->easyTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->easyTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create easy_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//EASYBOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/easy.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create easy.bmp surface\n");
		return NULL ;
	}
	res->easyBoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->easyBoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create easy.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//MODERATE BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/moderate_1.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create moderate_1.bmp surface\n");
		return NULL ;
	}
	res->moderateTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->moderateTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create moderate_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//MODERATEBOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/moderate.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create moderate.bmp surface\n");
		return NULL ;
	}
	res->moderateBoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->moderateBoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create moderate.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//Hard BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/hard_1.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create hard_1.bmp surface\n");
		return NULL ;
	}
	res->hardTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->hardTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create hard_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//HardBOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/hard.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create hard.bmp surface\n");
		return NULL ;
	}
	res->hardBoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->hardBoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create hard.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//EXPERT BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/expert_1.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create expert_1.bmp surface\n");
		return NULL ;
	}
	res->expertTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->expertTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create expert_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//EXPERTBOLD BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/expert.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create expert.bmp surface\n");
		return NULL ;
	}
	res->expertBoldTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->expertBoldTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create expert_1.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//BACK BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/back.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create back.bmp surface\n");
		return NULL ;
	}
	res->backTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->backTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create back.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//NEXT BUTTON
	loadingSurface = SDL_LoadBMP("./graphics/images/next.bmp");
	if (loadingSurface == NULL ) {
		spDifficultyWinDestroy(res);
		printf("couldn't create next.bmp surface\n");
		return NULL ;
	}
	res->nextTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->nextTexture == NULL ) {
		SDL_FreeSurface(loadingSurface);
		spDifficultyWinDestroy(res);
		printf("couldn't create next.bmp texture\n");
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spDifficultyWinDestroy(SPDifficulty* src) {
	if (!src) {
		return;
	}
	if (src->noobTexture != NULL ) {
		SDL_DestroyTexture(src->noobTexture);
	}
	if (src->noobBoldTexture != NULL ) {
		SDL_DestroyTexture(src->noobTexture);
	}
	if (src->easyTexture != NULL ) {
		SDL_DestroyTexture(src->easyTexture);
	}
	if (src->easyBoldTexture != NULL ) {
		SDL_DestroyTexture(src->noobTexture);
	}
	if (src->moderateTexture != NULL ) {
		SDL_DestroyTexture(src->moderateTexture);
	}
	if (src->moderateBoldTexture != NULL ) {
		SDL_DestroyTexture(src->noobTexture);
	}
	if (src->hardTexture != NULL ) {
		SDL_DestroyTexture(src->hardTexture);
	}
	if (src->hardBoldTexture != NULL ) {
		SDL_DestroyTexture(src->noobTexture);
	}
	if (src->expertTexture != NULL ) {
		SDL_DestroyTexture(src->noobTexture);
	}
	if (src->expertBoldTexture != NULL ) {
		SDL_DestroyTexture(src->noobTexture);
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


void spDifficultyWinDraw(SPDifficulty* src) {
	if(src==NULL){
		return;
	}
	SDL_Rect bgR = { .x = 0, .y = 0, .h = 650, .w = 1000 };
	SDL_Rect noobR = { .x = 360, .y = 150, .h = 60, .w = 250 };
	SDL_Rect easyR = { .x = 360, .y = 250, .h = 60, .w = 250 };
	SDL_Rect moderateR = { .x = 360, .y = 350, .h = 60, .w = 250 };
	SDL_Rect hardR = { .x = 360, .y = 450, .h = 60, .w = 250 };
	SDL_Rect expertR = { .x = 360, .y = 550, .h = 60, .w = 250 };
	SDL_Rect backR = { .x = 810, .y = 570, .h = 50, .w = 180 };
	SDL_Rect nextR = { .x = 10, .y = 570, .h = 50, .w = 180 };
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &bgR);
	SDL_RenderCopy(src->renderer, src->backTexture, NULL, &backR);
	if(src->click == 0){
		SDL_RenderCopy(src->renderer, src->noobTexture, NULL, &noobR);
		SDL_RenderCopy(src->renderer, src->easyTexture, NULL, &easyR);
		SDL_RenderCopy(src->renderer, src->moderateTexture, NULL, &moderateR);
		SDL_RenderCopy(src->renderer, src->hardTexture, NULL, &hardR);
		SDL_RenderCopy(src->renderer, src->expertTexture, NULL, &expertR);
	} else if(src->click == 1){
		SDL_RenderCopy(src->renderer, src->noobBoldTexture, NULL, &noobR);
		SDL_RenderCopy(src->renderer, src->easyTexture, NULL, &easyR);
		SDL_RenderCopy(src->renderer, src->moderateTexture, NULL, &moderateR);
		SDL_RenderCopy(src->renderer, src->hardTexture, NULL, &hardR);
		SDL_RenderCopy(src->renderer, src->expertTexture, NULL, &expertR);
		SDL_RenderCopy(src->renderer, src->nextTexture, NULL, &nextR);
	} else if(src->click == 2){
		SDL_RenderCopy(src->renderer, src->noobTexture, NULL, &noobR);
		SDL_RenderCopy(src->renderer, src->easyBoldTexture, NULL, &easyR);
		SDL_RenderCopy(src->renderer, src->moderateTexture, NULL, &moderateR);
		SDL_RenderCopy(src->renderer, src->hardTexture, NULL, &hardR);
		SDL_RenderCopy(src->renderer, src->expertTexture, NULL, &expertR);
		SDL_RenderCopy(src->renderer, src->nextTexture, NULL, &nextR);
	} else if(src->click == 3){
		SDL_RenderCopy(src->renderer, src->noobTexture, NULL, &noobR);
		SDL_RenderCopy(src->renderer, src->easyTexture, NULL, &easyR);
		SDL_RenderCopy(src->renderer, src->moderateBoldTexture, NULL, &moderateR);
		SDL_RenderCopy(src->renderer, src->hardTexture, NULL, &hardR);
		SDL_RenderCopy(src->renderer, src->expertTexture, NULL, &expertR);
		SDL_RenderCopy(src->renderer, src->nextTexture, NULL, &nextR);
	} else if(src->click == 4){
		SDL_RenderCopy(src->renderer, src->noobTexture, NULL, &noobR);
		SDL_RenderCopy(src->renderer, src->easyTexture, NULL, &easyR);
		SDL_RenderCopy(src->renderer, src->moderateTexture, NULL, &moderateR);
		SDL_RenderCopy(src->renderer, src->hardBoldTexture, NULL, &hardR);
		SDL_RenderCopy(src->renderer, src->expertTexture, NULL, &expertR);
		SDL_RenderCopy(src->renderer, src->nextTexture, NULL, &nextR);
	} else if(src->click == 5){
		SDL_RenderCopy(src->renderer, src->noobTexture, NULL, &noobR);
		SDL_RenderCopy(src->renderer, src->easyTexture, NULL, &easyR);
		SDL_RenderCopy(src->renderer, src->moderateTexture, NULL, &moderateR);
		SDL_RenderCopy(src->renderer, src->hardTexture, NULL, &hardR);
		SDL_RenderCopy(src->renderer, src->expertBoldTexture, NULL, &expertR);
		SDL_RenderCopy(src->renderer, src->nextTexture, NULL, &nextR);
	}

	SDL_RenderPresent(src->renderer);
}

SP_DIFFICULTY_EVENT spDifficultyWinHandleEvent(SPDifficulty* src, SDL_Event* event) {
	if (!event) {
		return SP_DIFFICULTY_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONUP:
		if (isClickOnNoob(event->button.x, event->button.y)) {
			return SP_DIFFICULTY_NOOB;
		} else if (isClickOnEasy(event->button.x, event->button.y)) {
			return SP_DIFFICULTY_EASY;
		} else if (isClickOnModerate(event->button.x, event->button.y)) {
			return SP_DIFFICULTY_MODERATE;
		} else if (isClickOnHard(event->button.x, event->button.y)) {
			return SP_DIFFICULTY_HARD;
		} else if (isClickOnExpert(event->button.x, event->button.y)) {
			return SP_DIFFICULTY_EXPERT;
		} else if (isClickOnBack3(event->button.x, event->button.y)) {
			return SP_DIFFICULTY_BACK;
		} else if (isClickOnNext(event->button.x, event->button.y) && src->click!=0) {
			return SP_DIFFICULTY_NEXT;
		}
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_DIFFICULTY_EXIT;
		}
		break;
	default:
		return SP_DIFFICULTY_NONE;
	}
	return SP_DIFFICULTY_NONE;
}

void spDifficultyWinHide(SPDifficulty* src) {
	SDL_HideWindow(src->window);
}

void spDifficultyWinShow(SPDifficulty* src) {
	SDL_ShowWindow(src->window);
}
