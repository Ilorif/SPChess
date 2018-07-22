/*
 * SPMainAux.h
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */

#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

#include "SPGame.h"
#include "SPMiniMax.h"
#include "SPPiece.h"
#include "SPParser.h"

/**
 * the setting state of the game.
 * called when game is started and when game is restarted.
 * operates the relevant function according to the command that
 * was typed by the user.
 *
 * @param game - The source game
 * @return
 * SPCommand - SP_QUIT to quit the game,
 * or SP_START to start the game.
 */
SPCommand spSettingState(SPGame * game);

/**
 *
 * operates the relevant function according to the command that
 * was typed by the user during the game.
 *
 * @param game - The source game
 * @return
 * SPCommand that was typed.
 */
SPCommand spGameApplyCmd(SPGame * game);

/**
 * 1 mode state.
 *
 * @param game - The source game
 * @return
 * SPCommand - SP_QUIT to quit the game,
 * or SP_EXIT when there was a tie or checkmate
 * or SP_RESET to reset the game.
 */
SPCommand spGameState1Mode(SPGame * game);

/**
 * 2 mode state.
 *
 * @param game - The source game
 * @return
 * SPCommand - SP_QUIT to quit the game,
 * or SP_EXIT when there was a tie or checkmate
 * or SP_RESET to reset the game.
 */
SPCommand spGameState2Mode(SPGame * game);

/**
 * 2 mode state.
 *
 * @param char
 * @return
 * the string represented by the given char.
 */
char * convertPiece(char piece);

#endif /* SPMAINAUX_H_ */
