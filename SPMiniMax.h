/*
 * SPMiniMax.h
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */

#ifndef SPMINIMAX_H_
#define SPMINIMAX_H_

#include "SPGame.h"
#include "SPMiniMaxNode.h"

/**
 * Given a game state and int array, this function evaluates the best move according to
 * the current player. The function initiates a MiniMax algorithm up to a
 * specified length given by the game difficulty level. The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param game - The current game state
 * @param move - The int array to keep the best move
 * @return
 * -1 if either game is NULL.
 * On success the function returns 0.
 */
int spMinimaxSuggestMove(SPGame* game, int * move);

#endif /* SPMINIMAX_H_ */
