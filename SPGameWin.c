/*
 * SPGameWin.c
 *
 *  Created on: 9 בספט 2017
 *      Author: Admin
 */

#include "SPGameWin.h"
#include <assert.h>
#include <stdio.h>

// 0=BLACK 1=WHITE 2=TIE
int spGameValidUndo(SPGame * game){
	if (game->mode==2) {
		return 0;
	}
	if (spArrayListIsEmpty(game->undoList) || (spGameGetColor(game)==SP_GAME_BLACK_PLAYER && spArrayListSize(game->undoList)==1)) {
		return 0;
	}
	return 1;
}


int spGameIsOver(SPGame * game){
	if (spGameCheck(game)) {
		if (spGameNoLegalMoves(game)) {
			if (game->currentPlayer==SP_GAME_WHITE_PLAYER) return 1; //black win Checkmate
			else return 0; //white win Checkmate
		}
		else {
			if (game->currentPlayer==SP_GAME_WHITE_PLAYER) return 3; //white Check
			else return 4; //black Check
		}
	}
	else {
		if (spGameNoLegalMoves(game))
			return 2;
	}
	return -1;
}

void convertPixel(int pixel []){
	for(int i = 0; i <= 7; i++){
		if(pixel[0] > (i*75) && pixel[0] < (i*75+75))
			pixel[0] = i;
	}
	for(int i=0; i <= 7; i++){
		if(pixel[1] > (i*75+40) && pixel[1] < (i*75+115))
			pixel[1] = i;
	}
	return;
}

int isClickOnDes(int x, int y) {
	if ((x >= 0 && x <= 600) && (y >= 40 && y <= 640)) {
		return 1;
	}
	return 0;
}

int isClickOnSource(int x, int y) {
	if ((x >= 0 && x <= 600) && (y >= 40 && y <= 640)) {
		return 1;
	}
	return 0;
}

int isClickOnRestart(int x, int y) {
	if ((x >= 690 && x <= 890) && (y >= 65 && y <= 115)) {
		return 1;
	}
	return 0;
}

int isClickOnSave(int x, int y) {
	if ((x >= 690 && x <= 890) && (y >= 165 && y <= 215)) {
		return 1;
	}
	return 0;
}

int isClickOnLoad3(int x, int y) {
	if ((x >= 690 && x <= 890) && (y >= 265 && y <= 315)) {
		return 1;
	}
	return 0;
}

int isClickOnUndo(int x, int y) {
	if ((x >= 690 && x <= 890) && (y >= 365 && y <= 415)) {
		return 1;
	}
	return 0;
}

int isClickOnMainMenu(int x, int y) {
	if ((x >= 690 && x <= 890) && (y >= 460 && y <= 510)) {
		return 1;
	}
	return 0;
}

int isClickOnExit2(int x, int y) {
	if ((x >= 690 && x <= 890) && (y >= 560 && y <= 610)) {
			return 1;
		}
		return 0;
}

Move* spGameCreateMove(){
	Move* move = (Move*)calloc(sizeof(Move),sizeof(char));
	move->mouseDownX = -1;
	move->mouseDownY = -1;
	move->mouseUpX = -1;
	move->mouseUpY = -1;
	move->motion = -1;
	move->motionX = -1;
	move->motionY = -1;
	return move;
}

void spGamedestroyMove(Move* move){
	free(move);
}

SPGameWin* spGameWindowCreate(SPGame* game) {
	SPGameWin* res = (SPGameWin*) calloc(sizeof(SPGameWin), sizeof(char));
	SDL_Surface* loadingSurface = NULL; //Used as temp surface
	if (res == NULL ) {
		printf("Couldn't create SPGameWin struct\n");
		return NULL;
	}
	res->game = game;
	if (res->game == NULL ) {
		printf("Couldn't create game\n");
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->undoactive = 0;
	// Create an application window with the following settings:
	res->window = SDL_CreateWindow("Chess", // window title
			SDL_WINDOWPOS_CENTERED,           // initial x position
			SDL_WINDOWPOS_CENTERED,           // initial y position
			1000,                               // width, in pixels
			650,                               // height, in pixels
			SDL_WINDOW_OPENGL                  // flags - see below
			);
	res->moveRelevant = spGameCreateMove();
	// Check that the window was successfully created
	if (res->window == NULL ) {
		// In the case that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->renderer = SDL_CreateRenderer(res->window, -1,
			SDL_RENDERER_ACCELERATED);
	if (res->renderer == NULL ) {
		printf("Could not create a renderer: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}

	//BG
	loadingSurface = SDL_LoadBMP("./graphics/images/BG.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a BG.bmp: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->bgTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->bgTexture == NULL ) {
		printf("Could not create a BG.bmp %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//BOARD
	loadingSurface = SDL_LoadBMP("./graphics/images/grid3.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a grid3.bmp: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	res->boardTexture = SDL_CreateTextureFromSurface(res->renderer,
			loadingSurface);
	if (res->boardTexture == NULL ) {
		printf("Could not create a grid3.bmp %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface); //We finished with the surface -> delete it

	//BishopW
	loadingSurface = SDL_LoadBMP("./graphics/images/BishopWhite.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->bishopWTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->bishopWTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//BishopB
	loadingSurface = SDL_LoadBMP("./graphics/images/BishopBlack.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->bishopBTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->bishopBTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//KingW
	loadingSurface = SDL_LoadBMP("./graphics/images/kingWhite.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->kingWTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->kingWTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//kingB
	loadingSurface = SDL_LoadBMP("./graphics/images/kingBlack.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->kingBTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->kingBTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//knightW
	loadingSurface = SDL_LoadBMP("./graphics/images/knightWhite.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->knightWTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->knightWTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//knightB
	loadingSurface = SDL_LoadBMP("./graphics/images/knightBlack.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->knightBTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->knightBTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//pawnW
	loadingSurface = SDL_LoadBMP("./graphics/images/pawnWhite.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->pawnWTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->pawnWTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//pawnB
	loadingSurface = SDL_LoadBMP("./graphics/images/pawnBlack.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->pawnBTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->pawnBTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//queenW
	loadingSurface = SDL_LoadBMP("./graphics/images/queenWhite.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->queenWTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->queenWTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//queenB
	loadingSurface = SDL_LoadBMP("./graphics/images/queenBlack.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->queenBTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->queenBTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//rookW
	loadingSurface = SDL_LoadBMP("./graphics/images/rookWhite.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->rookWTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->rookWTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//rookB
	loadingSurface = SDL_LoadBMP("./graphics/images/rookBlack.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a surface: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 255, 255));
	res->rookBTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->rookBTexture == NULL ) {
		printf("Could not create a texture: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//RESTART
	loadingSurface = SDL_LoadBMP("./graphics/images/restart.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a restart.bmp %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->restartTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->restartTexture == NULL ) {
		printf("Could not create a restart.bmp %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//SAVE
	loadingSurface = SDL_LoadBMP("./graphics/images/save.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a save: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->saveTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->saveTexture == NULL ) {
		printf("Could not create a texture save: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//LOAD
	loadingSurface = SDL_LoadBMP("./graphics/images/load.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a load: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->loadTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->loadTexture == NULL ) {
		printf("Could not create a load: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//UNDO
	loadingSurface = SDL_LoadBMP("./graphics/images/undo.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a undo: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->undoTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->undoTexture == NULL ) {
		printf("Could not create a undo: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//MAINMENU
	loadingSurface = SDL_LoadBMP("./graphics/images/mainmenu.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a mainmenu: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->mainmenuTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->mainmenuTexture == NULL ) {
		printf("Could not create a mainmenu: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);

	//EXIT
	loadingSurface = SDL_LoadBMP("./graphics/images/exit.bmp");
	if (loadingSurface == NULL ) {
		printf("Could not create a exit: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_SetColorKey(loadingSurface, SDL_TRUE,
			SDL_MapRGB(loadingSurface->format, 255, 0, 255));
	res->exitTexture = SDL_CreateTextureFromSurface(res->renderer, loadingSurface);
	if (res->exitTexture == NULL ) {
		printf("Could not create a exit: %s\n", SDL_GetError());
		spGameWindowDestroy(res);
		return NULL ;
	}
	SDL_FreeSurface(loadingSurface);
	return res;
}

void spGameWindowDestroy(SPGameWin* src) {
	if (!src) {
		return;
	}
	spGameDestroy(src->game);
	spGamedestroyMove(src->moveRelevant);
	if (src->bishopWTexture != NULL ) {
		SDL_DestroyTexture(src->bishopWTexture);
	}
	if (src->bishopBTexture != NULL ) {
		SDL_DestroyTexture(src->bishopBTexture);
	}
	if (src->kingWTexture != NULL ) {
		SDL_DestroyTexture(src->kingWTexture);
	}
	if (src->kingBTexture != NULL ) {
		SDL_DestroyTexture(src->kingBTexture);
	}
	if (src->knightWTexture != NULL ) {
		SDL_DestroyTexture(src->knightWTexture);
	}
	if (src->knightBTexture != NULL ) {
		SDL_DestroyTexture(src->knightBTexture);
	}
	if (src->pawnWTexture != NULL ) {
		SDL_DestroyTexture(src->pawnWTexture);
	}
	if (src->pawnBTexture != NULL ) {
		SDL_DestroyTexture(src->pawnBTexture);
	}
	if (src->queenWTexture != NULL ) {
		SDL_DestroyTexture(src->queenWTexture);
	}
	if (src->queenBTexture != NULL ) {
		SDL_DestroyTexture(src->queenBTexture);
	}
	if (src->rookWTexture != NULL ) {
		SDL_DestroyTexture(src->rookWTexture);
	}
	if (src->rookBTexture != NULL ) {
		SDL_DestroyTexture(src->rookBTexture);
	}
	if (src->boardTexture != NULL ) {
		SDL_DestroyTexture(src->boardTexture);
	}
	if (src->restartTexture != NULL ) {
		SDL_DestroyTexture(src->restartTexture);
	}
	if (src->saveTexture != NULL ) {
		SDL_DestroyTexture(src->saveTexture);
	}
	if (src->loadTexture != NULL ) {
		SDL_DestroyTexture(src->loadTexture);
	}
	if (src->undoTexture != NULL ) {
		SDL_DestroyTexture(src->undoTexture);
	}
	if (src->mainmenuTexture != NULL ) {
		SDL_DestroyTexture(src->mainmenuTexture);
	}
	if (src->exitTexture != NULL ) {
		SDL_DestroyTexture(src->exitTexture);
	}
	if (src->renderer != NULL ) {
		SDL_DestroyRenderer(src->renderer);
	}
	if (src->window != NULL ) {
		SDL_DestroyWindow(src->window);
	}
	free(src);
}

void spGameWindowDraw(SPGameWin* src) {
	int in = 0;
	if(src == NULL){
		return;
	}
	if(src->game->mode == 1 && spGameGetColor(src->game) != spGameGetCurrentPlayer(src->game)){
		int move[4] = {-1,-1,-1,-1};
		spMinimaxSuggestMove(src->game, move);
		spPieceSetMove(src->game, move[0], move[1], move[2], move[3]);
		in = 1;
	}
	if(spGameValidUndo(src->game)){
		src->undoactive = 1;
	} else{
		src->undoactive = 0;
	}
	SDL_Rect BGR = { .x = 0, .y = 0, .h = 650, .w = 1000 };
	SDL_Rect restartR = { .x = 690, .y = 65, .h = 50, .w = 200 };
	SDL_Rect saveR = { .x = 690, .y = 165, .h = 50, .w = 200 };
	SDL_Rect loadR = { .x = 690, .y = 265, .h = 50, .w = 200 };
	SDL_Rect undoR = { .x = 690, .y = 365, .h = 50, .w = 200 };
	SDL_Rect mainmenuR = { .x = 690, .y =460 , .h = 50, .w = 200 };
	SDL_Rect exitR = { .x = 690, .y = 560, .h = 50, .w = 200 };
	SDL_Rect rec = { .x = 0, .y = 40, .w = 600, .h = 600 };
	SDL_Rect temp = { .x = src->moveRelevant->motionX-(75/2), .y = src->moveRelevant->motionY-(75/2), .w = 75, .h = 75 };
	SDL_SetRenderDrawColor(src->renderer, 255, 255, 255, 255);
	SDL_RenderClear(src->renderer);
	SDL_RenderCopy(src->renderer, src->bgTexture, NULL, &BGR);
	SDL_RenderCopy(src->renderer, src->boardTexture, NULL, &rec);
	if(src->undoactive == 1){
		SDL_RenderCopy(src->renderer, src->restartTexture, NULL, &restartR);
		SDL_RenderCopy(src->renderer, src->saveTexture, NULL, &saveR);
		SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
		SDL_RenderCopy(src->renderer, src->undoTexture, NULL, &undoR);
		SDL_RenderCopy(src->renderer, src->mainmenuTexture, NULL, &mainmenuR);
		SDL_RenderCopy(src->renderer, src->exitTexture, NULL, &exitR);
	}
	if(src->undoactive == 0){
		SDL_RenderCopy(src->renderer, src->restartTexture, NULL, &restartR);
		SDL_RenderCopy(src->renderer, src->saveTexture, NULL, &saveR);
		SDL_RenderCopy(src->renderer, src->loadTexture, NULL, &loadR);
		SDL_RenderCopy(src->renderer, src->mainmenuTexture, NULL, &mainmenuR);
		SDL_RenderCopy(src->renderer, src->exitTexture, NULL, &exitR);
	}
	int pixel[2] = {src->moveRelevant->mouseDownX, src->moveRelevant->mouseDownY};
	convertPixel(pixel);
	int i = 0, j = 0;
	for (i = 0; i < SP_GAME_N_ROWS; i++) {
		for (j = 0; j < SP_GAME_N_COLUMNS; j++) {
			rec.x = j * 75;
			rec.y = i * 75 + 40;
			rec.h = 75;
			rec.w = 75;
			if (src->game->gameBoard[i][j] == SP_GAME_WHITE_BISHOP) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->bishopWTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->bishopWTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_BLACK_BISHOP) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->bishopBTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->bishopBTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_WHITE_KING) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->kingWTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->kingWTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_BLACK_KING) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->kingBTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->kingBTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_WHITE_KNIGHT) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->knightWTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->knightWTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_BLACK_KNIGHT) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->knightBTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->knightBTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_WHITE_PAWN) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->pawnWTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->pawnWTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_BLACK_PAWN) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->pawnBTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->pawnBTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_WHITE_QUEEN) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->queenWTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->queenWTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_BLACK_QUEEN) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->queenBTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->queenBTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_WHITE_ROOK) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->rookWTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->rookWTexture, NULL, &rec);
			} else if (src->game->gameBoard[i][j] == SP_GAME_BLACK_ROOK) {
				if(src->moveRelevant->motion == 1 && i == pixel[1] && j == pixel[0])
					SDL_RenderCopy(src->renderer, src->rookBTexture, NULL, &temp);
				else
					SDL_RenderCopy(src->renderer, src->rookBTexture, NULL, &rec);
			}
		}
	}
	SDL_RenderPresent(src->renderer);
	if(in == 1){
		int winner = spGameIsOver(src->game);
		if (winner == 0) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "The white player wins", NULL );
		else if (winner == 1) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "The black player wins", NULL );
		else if (winner == 2) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "It's a tie", NULL );
		else if (winner == 3) SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check: white King is threatened!", NULL );
		else if (winner == 4)SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check: black King is threatened!", NULL );
	}
}

void initialize(SPGameWin* src){
	src->moveRelevant->motionX = -1;
	src->moveRelevant->motionY = -1;
	src->moveRelevant->mouseDownX = -1;
	src->moveRelevant->mouseDownY = -1;
	src->moveRelevant->mouseUpX = -1;
	src->moveRelevant->mouseUpY = -1;
	src->moveRelevant->motion = -1;
}

SP_GAME_EVENT spGameWindowHandleEvent(SPGameWin* src, SDL_Event* event) {
	if (event == NULL || src == NULL ) {
		return SP_GAME_EVENT_INVALID_ARGUMENT;
	}
	switch (event->type) {
	case SDL_MOUSEBUTTONDOWN:
		if(isClickOnSource(event->button.x, event->button.y)){
			src->moveRelevant->motion = 0;
			src->moveRelevant->mouseDownX = event->button.x;
			src->moveRelevant->mouseDownY = event->button.y;
		}
		break;
	case SDL_MOUSEMOTION:
		src->moveRelevant->motion = 1;
		src->moveRelevant->motionX = event->motion.x;
		src->moveRelevant->motionY = event->motion.y;
		break;
	case SDL_MOUSEBUTTONUP:
		src->moveRelevant->motion = 0;
		if (isClickOnRestart(event->button.x, event->button.y)) {
			initialize(src);
			return SP_GAME_EVENT_RESTART;
		} else if (isClickOnSave(event->button.x, event->button.y)) {
			initialize(src);
			return SP_GAME_EVENT_SAVE;
		} else if (isClickOnLoad3(event->button.x, event->button.y)) {
			initialize(src);
			return SP_GAME_EVENT_LOAD;
		} else if (isClickOnUndo(event->button.x, event->button.y)) {
			initialize(src);
			return SP_GAME_EVENT_UNDO;
		} else if (isClickOnMainMenu(event->button.x, event->button.y)) {
			return SP_GAME_EVENT_MAINMENU;
		} else if (isClickOnExit2(event->button.x, event->button.y)) {
			return SP_GAME_EVENT_EXIT;
		} else if(isClickOnDes(event->button.x, event->button.y)){
			src->moveRelevant->mouseUpX = event->button.x;
			src->moveRelevant->mouseUpY = event->button.y;
			int des[2] = {src->moveRelevant->mouseUpX,src->moveRelevant->mouseUpY};
			int sor[2] = {src->moveRelevant->mouseDownX, src->moveRelevant->mouseDownY};
			convertPixel(des);
			convertPixel(sor);
			SPCommand cmd;
			cmd.cmd = SP_MOVE_TO;
			cmd.arg1 =  8 - sor[1];
			cmd.arg2 = sor[0] + 'A';
			cmd.arg3=  8 - des[1];
			cmd.arg4 = des[0] + 'A';
			cmd.validArg = true;
			if(spGameSetMove(src->game, cmd) == SP_INVALID_LINE){
				initialize(src);
				return SP_GAME_EVENT_INVALID_ARGUMENT;
			}
		}
		int winner = spGameIsOver(src->game);
		if (winner == 0) {
			initialize(src);
			return SP_GAME_EVENT_WHITE_WON;
		} else if (winner == 1) {
			initialize(src);
			return SP_GAME_EVENT_BLACK_WON;
		} else if (winner == 2) {
			initialize(src);
			return SP_GAME_EVENT_TIE;
		} else if (winner == 3) {
			initialize(src);
			return SP_GAME_EVENT_WHITE_CHECK;
		} else if (winner == 4) {
			initialize(src);
			return SP_GAME_EVENT_BLACK_CHECK;
		}
		initialize(src);
		break;
	case SDL_WINDOWEVENT:
		if (event->window.event == SDL_WINDOWEVENT_CLOSE) {
			return SP_GAME_EVENT_QUIT;
		}
		break;
	default:
		return SP_GAME_EVENT_NONE;
	}
	return SP_GAME_EVENT_NONE;
}

void spGameWindowHide(SPGameWin* src) {
	SDL_HideWindow(src->window);
}

void spGameWindowShow(SPGameWin* src) {
	SDL_ShowWindow(src->window);
}
