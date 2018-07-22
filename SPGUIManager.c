/*
 * SPGUIManager.c
 *
 *  Created on: 9 בספט 2017
 *      Author: Admin
 */

#include <stdio.h>
#include <stdlib.h>
#include "SPGUIManager.h"

SPGuiManager* spManagerCreate() {
	SPGuiManager* res = (SPGuiManager*) malloc(sizeof(SPGuiManager));
	if (res == NULL) {
		return NULL;
	}
	res->mainWin = spMainWindowCreate();
	if (res->mainWin == NULL ) {
		free(res);
		return NULL;
	}
	res->game = NULL;
	res->gameWin = NULL;
	res->slotWin = NULL;
	res->playerWin = NULL;
	res->difficultyWin = NULL;
	res->colorWin = NULL;
	res->loadFrom = 0;
	res->activeWin = SP_MAIN_WINDOW_ACTIVE;
	return res;
}

void spManagerDestroy(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == SP_GAME_WINDOW_ACTIVE) {
		spGameWindowDestroy(src->gameWin);
	}
	if(src->activeWin == SP_SLOT_WINDOW_ACTIVE){
		spSlotDestroy(src->slotWin);
	}
	if(src->activeWin == SP_PLAYERS_WINDOW_ACTIVE){
		spPlayersWinDestroy(src->playerWin);
	}
	if(src->activeWin == SP_DIFFICULTY_WINDOW_ACTIVE){
		spDifficultyWinDestroy(src->difficultyWin);
	}
	if(src->activeWin == SP_COLOR_WINDOW_ACTIVE){
		spColorWinDestroy(src->colorWin);
	}
	spMainWindowDestroy(src->mainWin);
	free(src);
}

void spManagerDraw(SPGuiManager* src) {
	if (!src) {
		return;
	}
	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
		spMainWindowDraw(src->mainWin);
	} else if (src->activeWin == SP_GAME_WINDOW_ACTIVE) {
		spGameWindowDraw(src->gameWin);
	} else if(src->activeWin == SP_PLAYERS_WINDOW_ACTIVE){
		spPlayersWinDraw(src->playerWin);
	} else if(src->activeWin == SP_DIFFICULTY_WINDOW_ACTIVE){
		spDifficultyWinDraw(src->difficultyWin);
	} else if(src->activeWin == SP_COLOR_WINDOW_ACTIVE){
		spColorWinDraw(src->colorWin);
	} else{
		spSlotDraw(src->slotWin);
	}
}

SP_MANAGER_EVENET handleManagerDueToMainEvent(SPGuiManager* src, SP_MAIN_EVENT event) {
	if (src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_MAIN_NEWGAME) {
		spMainWindowHide(src->mainWin);
		src->game = spGameCreate();
		if(src->game == NULL){
			printf("couldn't create game");
			return SP_MANAGER_QUTT;
		}
		if(src->slotWin == NULL){
			src->slotWin = spSlotCreate();
			if(src->slotWin == NULL){
				printf("Couldn't create slot window\n");
				return SP_MANAGER_QUTT;
			}
			spSlotHide(src->slotWin);
		}
		src->playerWin = spPlayersWinCreate();
		if(src->playerWin == NULL){
			printf("Couldn't create players window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_PLAYERS_WINDOW_ACTIVE;
	}
	if (event == SP_MAIN_EXIT) {
		return SP_MANAGER_QUTT;
	}
	if (event == SP_MAIN_LOAD) {
		src->loadFrom = 1;
		spMainWindowHide(src->mainWin);
		if(src->slotWin == NULL){
			src->slotWin = spSlotCreate();
			if(src->slotWin == NULL){
				printf("Couldn't create slot window\n");
				return SP_MANAGER_QUTT;
			}
		}
		else{
			spSlotShow(src->slotWin);
		}
		src->activeWin = SP_SLOT_WINDOW_ACTIVE;
	}
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToPlayersEvent(SPGuiManager* src,
		SP_PLAYER_EVENT event){
	if (event == SP_PLAYERS_NONE || src == NULL ) {
		return SP_MANAGER_NONE;
	} else if(event == SP_PLAYERS_ONEPLAYER){
		src->game->mode = 1; //Computer
		src->playerWin->click = 1;
		src->playerWin->nextStart = 1;
	} else if(event == SP_PLAYERS_TWOPLAYER){
		src->game->mode = 2; //Twice
		src->playerWin->click = 2;
		src->playerWin->nextStart = 0;
	} else if(event == SP_PLAYERS_BACK){
		src->playerWin->click = 0;
		spPlayersWinHide(src->playerWin);
		spMainWindowShow(src->mainWin);
		src->activeWin = SP_MAIN_WINDOW_ACTIVE;
	} else if(event == SP_PLAYERS_NEXT){
		src->playerWin->click = 0;
		spPlayersWinHide(src->playerWin);
		src->difficultyWin = spDifficultyWinCreate();
		if(src->difficultyWin == NULL){
			printf("Couldn't create difficulty window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_DIFFICULTY_WINDOW_ACTIVE;
	} else if(event == SP_PLAYERS_START){
		src->playerWin->click = 0;
		spPlayersWinHide(src->playerWin);
		src->gameWin = spGameWindowCreate(src->game);
		if(src->gameWin == NULL){
			printf("Couldn't create game window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_GAME_WINDOW_ACTIVE;
	}
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToColorEvent(SPGuiManager* src,
		SP_COLOR_EVENT event){
	if (event == SP_COLOR_NONE || src == NULL ) {
		return SP_MANAGER_NONE;
	} else if(event == SP_COLOR_WHITE){
		src->game->color = 1;
		src->colorWin->click = 1;
	} else if(event == SP_COLOR_BLACK){
		src->game->color = 0;
		src->colorWin->click = 2;
	} else if(event == SP_COLOR_BACK){
		src->colorWin->click = 0;
		spColorWinHide(src->colorWin);
		spDifficultyWinShow(src->difficultyWin);
		src->activeWin = SP_DIFFICULTY_WINDOW_ACTIVE;
	} else if(event == SP_COLOR_START){
		src->colorWin->click = 0;
		spColorWinHide(src->colorWin);
		src->gameWin = spGameWindowCreate(src->game);
		if(src->gameWin == NULL){
			printf("Couldn't create game window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_GAME_WINDOW_ACTIVE;
	}
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToDifficultyEvent(SPGuiManager* src,
		SP_DIFFICULTY_EVENT event){
	if (event == SP_DIFFICULTY_NONE || src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if(event == SP_DIFFICULTY_NOOB){
		src->game->difficulty = 1;
		src->difficultyWin->click = 1;
	} else if(event == SP_DIFFICULTY_EASY){
		src->game->difficulty = 2;
		src->difficultyWin->click = 2;
	} else if(event == SP_DIFFICULTY_MODERATE){
		src->game->difficulty = 3;
		src->difficultyWin->click = 3;
	} else if(event == SP_DIFFICULTY_HARD){
		src->game->difficulty = 4;
		src->difficultyWin->click = 4;
	} else if(event == SP_DIFFICULTY_EXPERT){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Bonus", "This part isn't implemented", NULL );
		//src->game->difficulty = 5;
		//src->difficultyWin->click = 5;
	} else if(event == SP_DIFFICULTY_BACK){
		src->difficultyWin->click = 0;
		spDifficultyWinHide(src->difficultyWin);
		spPlayersWinShow(src->playerWin);
		src->activeWin = SP_PLAYERS_WINDOW_ACTIVE;
	} else if(event == SP_DIFFICULTY_NEXT){
		src->difficultyWin->click = 0;
		spDifficultyWinHide(src->difficultyWin);
		src->colorWin = spColorWinCreate();
		if(src->colorWin == NULL){
			printf("Couldn't create color window\n");
			return SP_MANAGER_QUTT;
		}
		src->activeWin = SP_COLOR_WINDOW_ACTIVE;
	}
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET handleManagerDueToSlotEvent(SPGuiManager* src, SP_SLOT_EVENT event){
	if (event == SP_SLOT_NONE || src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if(event == SP_SLOT_GAMESLOT1){
		if(src->slotWin->numslots < 1)
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save", "No saved games in slot1",NULL);
		else
			src->slotWin->click = 1;
	} else if(event == SP_SLOT_GAMESLOT2){
		if(src->slotWin->numslots < 2)
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save", "No saved games in slot2",NULL);
		else
			src->slotWin->click = 2;
	} else if(event == SP_SLOT_GAMESLOT3){
		if(src->slotWin->numslots < 3)
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save", "No saved games in slot3",NULL);
		else
			src->slotWin->click = 3;
	} else if(event == SP_SLOT_GAMESLOT4){
		if(src->slotWin->numslots < 4)
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save", "No saved games in slot4",NULL);
		else
			src->slotWin->click = 4;
	} else if(event == SP_SLOT_GAMESLOT5){
		if(src->slotWin->numslots < 5)
			SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save", "No saved games in slot5",NULL);
		else
			src->slotWin->click = 5;
	} else if(event == SP_SLOT_BACK){
		src->slotWin->click = 0;
		spSlotHide(src->slotWin);
		if(src->loadFrom == 1){
			spMainWindowShow(src->mainWin);
			src->activeWin = SP_MAIN_WINDOW_ACTIVE;
		}
		if(src->loadFrom == 2){
			spGameWindowShow(src->gameWin);
			src->activeWin = SP_GAME_WINDOW_ACTIVE;
		}
	} else if(event == SP_SLOT_LOAD){
		spSlotHide(src->slotWin);
		printf("%d", src->slotWin->click);
		if(src->gameWin != NULL){
			if(src->slotWin->click == 1) spGameLoad(src->game, "./savedGames/gameSlot1");
			if(src->slotWin->click == 2) spGameLoad(src->game, "./savedGames/gameSlot2");
			if(src->slotWin->click == 3) spGameLoad(src->game, "./savedGames/gameSlot3");
			if(src->slotWin->click == 4) spGameLoad(src->game, "./savedGames/gameSlot4");
			if(src->slotWin->click == 5) spGameLoad(src->game, "./savedGames/gameSlot5");
			spGameWindowShow(src->gameWin);
			spGameWindowDraw(src->gameWin);
		}
		src->activeWin = SP_GAME_WINDOW_ACTIVE;
		src->slotWin->click = 0;
	}
	return SP_MANAGER_NONE;
}

int spExit (){
	const SDL_MessageBoxButtonData buttons[] = {
		{ /* .flags, .buttonid, .text */        0, 0, "no" },
		{ SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "yes" },
		{ SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "cancel" },
	};
	const SDL_MessageBoxColorScheme colorScheme = {
		{ /* .colors (.r, .g, .b) */
			/* [SDL_MESSAGEBOX_COLOR_BACKGROUND] */
			{ 255,   0,   0 },
			/* [SDL_MESSAGEBOX_COLOR_TEXT] */
			{   0, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BORDER] */
			{ 255, 255,   0 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_BACKGROUND] */
			{   0,   0, 255 },
			/* [SDL_MESSAGEBOX_COLOR_BUTTON_SELECTED] */
			{ 255,   0, 255 }
		}
	};
	const SDL_MessageBoxData messageboxdata = {
		SDL_MESSAGEBOX_INFORMATION, /* .flags */
		NULL, /* .window */
		"Exit", /* .title */
		"Would you like to save the game?", /* .message */
		SDL_arraysize(buttons), /* .numbuttons */
		buttons, /* .buttons */
		&colorScheme /* .colorScheme */
	};
	int buttonid = -1;
	if (SDL_ShowMessageBox(&messageboxdata, &buttonid) < 0) {
		SDL_Log("error displaying message box");
	}
	return buttonid;
}


SP_MANAGER_EVENET handleManagerDueToGameEvent(SPGuiManager* src,
		SP_GAME_EVENT event) {
	if (event == SP_GAME_EVENT_NONE || src == NULL ) {
		return SP_MANAGER_NONE;
	} else if(event == SP_GAME_EVENT_RESTART){
		src->gameWin->undoactive = 0;
		spGameRestart(src->gameWin->game);
	} else if(event == SP_GAME_EVENT_SAVE){
		SPGame* game = spGameCreate();
		if(game == NULL){

		}
		if(src->slotWin->numslots == 0){
			spGameSave(src->gameWin->game, "./savedGames/gameSlot1");
		} else if(src->slotWin->numslots == 1){
			spGameLoad(game, "./savedGames/gameSlot1");
			spGameSave(game, "./savedGames/gameSlot2");
			spGameSave(src->gameWin->game, "./savedGames/gameSlot1");
		} else if(src->slotWin->numslots == 2){
			spGameLoad(game, "./savedGames/gameSlot2");
			spGameSave(game, "./savedGames/gameSlot3");
			spGameLoad(game, "./savedGames/gameSlot1");
			spGameSave(game, "./savedGames/gameSlot2");
			spGameSave(src->gameWin->game, "./savedGames/gameSlot1");
		} else if(src->slotWin->numslots == 3){
			spGameLoad(game, "./savedGames/gameSlot3");
			spGameSave(game, "./savedGames/gameSlot4");
			spGameLoad(game, "./savedGames/gameSlot2");
			spGameSave(game, "./savedGames/gameSlot3");
			spGameLoad(game, "./savedGames/gameSlot1");
			spGameSave(game, "./savedGames/gameSlot2");
			spGameSave(src->gameWin->game, "./savedGames/gameSlot1");
		} else {
			spGameLoad(game, "./savedGames/gameSlot4");
			spGameSave(game, "./savedGames/gameSlot5");
			spGameLoad(game, "./savedGames/gameSlot3");
			spGameSave(game, "./savedGames/gameSlot4");
			spGameLoad(game, "./savedGames/gameSlot2");
			spGameSave(game, "./savedGames/gameSlot3");
			spGameLoad(game, "./savedGames/gameSlot1");
			spGameSave(game, "./savedGames/gameSlot2");
			spGameSave(src->gameWin->game, "./savedGames/gameSlot1");
		}
		spGameDestroy(game);
		if(src->slotWin->numslots < 5) src->slotWin->numslots++;
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Save", "You have saved the current game",NULL);
	} else if(event == SP_GAME_EVENT_LOAD){
		src->loadFrom = 2;
		spGameWindowHide(src->gameWin);
		spSlotShow(src->slotWin);
		src->activeWin = SP_SLOT_WINDOW_ACTIVE;
	} else if(event == SP_GAME_EVENT_UNDO){
		 spGameUndo(src->gameWin->game);
	} else if(event == SP_GAME_EVENT_MAINMENU){
		int buttonid = spExit();
		if(buttonid == 0){
			spGameWindowHide(src->gameWin);
			spMainWindowShow(src->mainWin);
			src->activeWin = SP_MAIN_WINDOW_ACTIVE;
		}
		return SP_MANAGER_NONE;
	} else if(event == SP_GAME_EVENT_EXIT){
		int buttonid = spExit();
		if(buttonid == 0) return SP_MANAGER_QUTT;
		return SP_MANAGER_NONE;
	}
	if (event == SP_GAME_EVENT_NONE || src == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (event == SP_GAME_EVENT_BLACK_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "The black player wins", NULL );
	} else if (event == SP_GAME_EVENT_WHITE_WON) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "The white player wins", NULL );
	} else if (event == SP_GAME_EVENT_TIE) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Game over", "It's a tie", NULL );
	} else if(event == SP_GAME_EVENT_BLACK_CHECK){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check: black King is threatened!", NULL );
	} else if(event == SP_GAME_EVENT_WHITE_CHECK){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Check", "Check: white King is threatened!", NULL );
	} else if(event == SP_GAME_EVENT_INVALID_ARGUMENT){
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", "Invalid move", NULL );
	}
	return SP_MANAGER_NONE;
}

SP_MANAGER_EVENET spManagerHandleEvent(SPGuiManager* src, SDL_Event* event) {
	if (src == NULL || event == NULL ) {
		return SP_MANAGER_NONE;
	}
	if (src->activeWin == SP_MAIN_WINDOW_ACTIVE) {
		SP_MAIN_EVENT mainEvent = spMainWindowHandleEvent(event);
		return handleManagerDueToMainEvent(src, mainEvent);
	} else if(src->activeWin == SP_SLOT_WINDOW_ACTIVE){
		SP_SLOT_EVENT modeEvent = spSlotHandleEvent(src->slotWin, event);
		return handleManagerDueToSlotEvent(src, modeEvent);
	}else if(src->activeWin == SP_PLAYERS_WINDOW_ACTIVE){
		SP_PLAYER_EVENT playerEvent = spPlayersWinHandleEvent(src->playerWin, event);
		return handleManagerDueToPlayersEvent(src, playerEvent);
	} else if(src->activeWin == SP_DIFFICULTY_WINDOW_ACTIVE){
		SP_DIFFICULTY_EVENT difficultyEvent = spDifficultyWinHandleEvent(src->difficultyWin, event);
		return handleManagerDueToDifficultyEvent(src, difficultyEvent);
	} else if(src->activeWin == SP_COLOR_WINDOW_ACTIVE){
		SP_COLOR_EVENT colorEvent = spColorWinHandleEvent(src->colorWin, event);
		return handleManagerDueToColorEvent(src, colorEvent);
	}else {
		SP_GAME_EVENT gameEvent = spGameWindowHandleEvent(src->gameWin, event);
		spManagerDraw(src);
		return handleManagerDueToGameEvent(src, gameEvent);
	}
	return SP_MANAGER_NONE;
}
