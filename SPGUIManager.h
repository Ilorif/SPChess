/*
 * SPGUIManager.h
 *
 *  Created on: 9 בספט 2017
 *      Author: Admin
 */
#ifndef SPGUIMANAGER_H_
#define SPGUIMANAGER_H_

#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_video.h>
#include "SPGameWin.h"
#include "SPMainWin.h"
#include "SPSlot.h"
#include "SPplayersWin.h"
#include "SPColorWin.h"
#include "SPDifficulty.h"
#include "SPGame.h"

typedef enum{
	SP_MAIN_WINDOW_ACTIVE,
	SP_GAME_WINDOW_ACTIVE,
	SP_SLOT_WINDOW_ACTIVE,
	SP_PLAYERS_WINDOW_ACTIVE,
	SP_DIFFICULTY_WINDOW_ACTIVE,
	SP_COLOR_WINDOW_ACTIVE
}ACTIVE_WINDOW;

typedef enum{
	SP_MANAGER_QUTT,
	SP_MANAGER_NONE,
}SP_MANAGER_EVENET;

typedef struct {
	SPGameWin* gameWin;
	SPMainWin* mainWin;
	SPSlot* slotWin;
	SPPlayer* playerWin;
	SPDifficulty* difficultyWin;
	SPColor* colorWin;
	ACTIVE_WINDOW activeWin;
	SPGame* game;
	int loadFrom; //1=MAIN 2=GAME
} SPGuiManager;

/**
 * Create new manager. the manager connects the various windows.
 * @return
 * SPGuiManager - the manager.
 */
SPGuiManager* spManagerCreate();

/**
 * Frees all memory allocation associated with a given manager. If SPGuiManager==NULL
 * the function does nothing.
 * @param
 * SPGuiManager - manager for the windows.
 */
void spManagerDestroy(SPGuiManager* src);

/**
 * draw the appropriate window according to the field 'ActiveWindow'.
 * @param
 * SPGuiManager - manager for the windows.
 */
void spManagerDraw(SPGuiManager* src);

/**
 * function check how to respond to an event in the main window.
 * @param
 * SPGuiManager - the manager.
 * SP_MAIN_EVENT - event in the main window.
 * @return
 * SP_MANAGER_EVENET - event in the manager.
 */
SP_MANAGER_EVENET handleManagerDueToMainEvent(SPGuiManager* src, SP_MAIN_EVENT event);

/**
 * function check how to respond to an event in the mode window.
 * @param
 * SPGuiManager - the manager.
 * SP_PLAYER_EVENT - event in the mode window.
 * @return
 * SP_MANAGER_EVENET - event in the manager.
 */
SP_MANAGER_EVENET handleManagerDueToPlayersEvent(SPGuiManager* src, SP_PLAYER_EVENT event);

/**
 * function check how to respond to an event in the color window.
 * @param
 * SPGuiManager - the manager.
 * SP_COLOR_EVENT - event in the main window.
 * @return
 * SP_MANAGER_EVENET - event in the manager.
 */
SP_MANAGER_EVENET handleManagerDueToColorEvent(SPGuiManager* src, SP_COLOR_EVENT event);

/**
 * function check how to respond to an event in the diffiuclty window.
 * @param
 * SPGuiManager - the manager.
 * SP_DIFFIUCLTY_EVENT - event in the difficulty window.
 * @return
 * SP_MANAGER_EVENET - event in the manager.
 */
SP_MANAGER_EVENET handleManagerDueToDifficultyEvent(SPGuiManager* src, SP_DIFFICULTY_EVENT event);

/**
 * function check how to respond to an event in the loading window.
 * @param
 * SPGuiManager - the manager.
 * SP_SLOT_EVENT - event in the loading window.
 * @return
 * SP_MANAGER_EVENET - event in the manager.
 */
SP_MANAGER_EVENET handleManagerDueToSlotEvent(SPGuiManager* src, SP_SLOT_EVENT event);

/**
 * function check how to respond to an event in the game window.
 * @param
 * SPGuiManager - the manager.
 * SP_GAME_EVENT - event in the game window.
 * @return
 * SP_MANAGER_EVENET - event in the manager.
 */
SP_MANAGER_EVENET handleManagerDueToGameEvent(SPGuiManager* src, SP_GAME_EVENT event);

/**
 * function check who is the active window and respond accordingly.
 * @param
 * SPGuiManager - the manager.
 * SDL_Event* event - the event according the user chosen.
 * @return
 * SP_MANAGER_EVENET - event in the manager.
 */
SP_MANAGER_EVENET spManagerHandleEvent(SPGuiManager* src, SDL_Event* event);

/**
 * function create Exit window that ask the user if he want to save his game.
 * @return
 * 0 - the user chosen is NO.
 * 1 - the user chosen is Yes.
 * 2 - the user chosen is Cancel.
 */
int spExit ();

#endif /* SPGUIMANAGER_H_ */
