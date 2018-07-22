/*
 * SPGame.h
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */

#ifndef SPGAME_H_
#define SPGAME_H_

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "SPParser.h"
#include "SPArrayList.h"


#define SP_GAME_N_ROWS 8
#define SP_GAME_N_COLUMNS 8
#define SP_GAME_BLACK_PAWN 'M'
#define SP_GAME_WHITE_PAWN 'm'
#define SP_GAME_BLACK_BISHOP 'B'
#define SP_GAME_WHITE_BISHOP 'b'
#define SP_GAME_BLACK_ROOK 'R'
#define SP_GAME_WHITE_ROOK 'r'
#define SP_GAME_BLACK_KNIGHT 'N'
#define SP_GAME_WHITE_KNIGHT 'n'
#define SP_GAME_BLACK_KING 'K'
#define SP_GAME_WHITE_KING 'k'
#define SP_GAME_BLACK_QUEEN 'Q'
#define SP_GAME_WHITE_QUEEN 'q'
#define SP_GAME_EMPTY_ENTRY '_'
#define SP_GAME_BLACK_PLAYER 0
#define SP_GAME_WHITE_PLAYER 1

typedef struct sp_game_t {
	int mode;
	int difficulty;
	int color;
	int currentPlayer;
	int blackKing[2];
	int whiteKing[2];
	char gameBoard[SP_GAME_N_ROWS][SP_GAME_N_COLUMNS];
	SPArrayList* undoList;
} SPGame;

typedef enum sp_game_message_t {
	SP_GAME_INVALID_MOVE,
	SP_GAME_INVALID_ARGUMENT,
	SP_GAME_NO_HISTORY,
	SP_GAME_SUCCESS,
	SP_GAME_CHECKMATE,
	SP_GAME_TIE
} SP_GAME_MESSAGE;


/**
 * Creates a new checkmate game.
 *
 * @return
 * NULL if a memory allocation failure occurs.
 * Otherwise, a new game instant is returned.
 */
SPGame* spGameCreate();

/**
 *	Creates a copy of a given game.
 *	The new copy has the same status as the game given.
 *
 *	@param game - the source game which will be copied
 *	@return
 *	NULL if either game is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source game is returned.
 */
SPGame* spGameCopy(SPGame* game);

/**
 * Frees all memory allocation associated with a given game. If game==NULL
 * the function does nothing.
 *
 * @param game - the source game
 */
void spGameDestroy(SPGame* game);

/**
 * starts a new game with default settings.
 *
 * @param game - the source game
 */
void spGameReset(SPGame * game);

/**
 * starts a new game with the current settings.
 *
 * @param game - the source game
 */
void spGameRestart(SPGame * game);

/**
 * Returns the color of the player.
 * @param game - the source game
 * @return
 * SP_GAME_BLACK_PLAYER - if itws color is black
 * SP_GAME_WHITE_PLAYER - if it's color is white
 * 2    - otherwise
 */
int spGameGetColor(SPGame * game);

/**
 * Returns the color of the player.
 * @param game - the source game
 * @return
 * "black" - if itws color is black
 * "white" - if it's color is white
 */
char * spGameGetColorString(SPGame * game);

/**
 * Returns the current player of the specified game.
 * @param game - the source game
 * @return
 * SP_GAME_BLACK_PLAYER - if it's black player turn
 * SP_GAME_WHITE_PLAYER - if it's white player turn
 * 2    - otherwise
 */
int spGameGetCurrentPlayer(SPGame * game);

/**
 * changes the current player.
 *
 * @param game - the source game
 */
void spGameChangePlayer(SPGame* game);

/**
 * On success, the function prints the settings of the game.
 * If an error occurs, then the function does nothing.
 *
 * @param game - the target game
 */
void spGamePrintSetting(SPGame * game);

/**
 * On success, the function prints the board game. If an error occurs, then the
 * function does nothing.
 *
 * @param game - the target game
 */
void spGamePrintBoard(SPGame * game);

/**
 * updates the game mode according to the command typed by the user.
 *
 * @param game - the source game
 * @param cmd - game_mode command and its parameters.
 */
void spGameMode(SPGame * game, SPCommand cmd);

/**
 * updates the game difficulty according to the command typed by the user.
 *
 * @param game - the source game
 * @param cmd - difficulty command and its parameters.
 */
void spGameDifficulty(SPGame * game, SPCommand cmd);

/**
 * updates the player color according to the command typed by the user.
 *
 * @param game - the source game
 * @param cmd - game_color command and its parameters.
 */
void spGameUserColor(SPGame * game, SPCommand cmd);

/**
 * updates the game settings according to the default settings.
 *
 * @param game - the source game
 */
void spGameDefault(SPGame * game);

/**
 * loads a saved game according to the path typed by the user.
 *
 * @param game - the source game
 * @param path - the path which the game will be loaded from.
 */
void spGameLoad(SPGame * game, char* path);

/**
 * extract the needed value and parses it to int.
 *
 * @param buff - char*.
 * @return
 * int value.
 */
int spGameParseXMLData(char* buff);

/**
 * extract the needed value.
 *
 * @param buff - char*.
 * @return
 * char*.
 */
char* spGameParseXMLBoard(char* buff);

/**
 * saves the current game according to the path typed by the user.
 *
 * @param game - the source game
 * @param path - the path which the game will be saved to.
 */
void spGameSave(SPGame * game, char* path);

/**
 * undo the last move and changes the current player's turn.
 * If the user invoked this command more than 3 times
 * in a row then the command is no longer available.
 *
 * @param game - The source game
 * @return
 * SP_FIAR_GAME_INVALID_ARGUMENT - if game == NULL
 * SP_FIAR_GAME_NO_HISTORY       - if the user invoked this function more then
 *                                 3 times in a row.
 * SP_FIAR_GAME_SUCCESS          - on success.
 */
SP_GAME_MESSAGE spGameUndoPrevMove(SPGame * game);

/**
 * undo the last move made by the user and undo the last move made by the computer.
 * using the function SP_GAME_MESSAGE spGameUndoPrevMove(SPGame* game).
 *
 * @param game - The source game
 */
void spGameUndo(SPGame * game);

#endif /* SPGAME_H_ */
