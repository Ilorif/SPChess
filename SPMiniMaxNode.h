/*
 * SPMiniMaxNode.h
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */


#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

#include "SPPiece.h"


typedef struct node{
	SPGame* game;
	int move[4];
}Node;

/**
 * Creates a new node with a specified game. This is an extension of a game.
 * move - an array that will contain the best move.
 *
 * @game - game.
 * @return
 * NULL if either a memory allocation failure occurs.
 * Otherwise, a new node instant is returned.
 */
Node * createNode(SPGame * game);

/**
 * Frees all memory allocation associated with a given node.
 * If node==NULL the function does nothing.
 *
 * @param node - the source node
 */
void destroyNode(Node * node);

/**
 * This is a alpha beta pruning algorithm to build the minimax tree.
 *
 * @param alpha - for the alpha beta pruning
 * @param beta - for the alpha beta pruning
 * @param depthleft - The maximum depth of the miniMax algorithm
 * @param node - which include the current game state
 * @param maximizingPlayer - true if it is.
 * @param flag - in order to save the first best move.
 */
int recAlphaBeta(int alpha, int beta, int depthleft, Node * node, bool maximizingPlayer, int flag);

/**
 * Given a node which include a game state, this function calculates the score
 * according to the specified criteria at the PDF file.
 *
 * @param game - The current game state
 * @return
 * The score calculated by the scoring function.
 */
int scoringFunction(SPGame * game);

#endif /* SPMINIMAXNODE_H_ */
