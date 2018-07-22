/*
 * SPMiniMax.c
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */



#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "SPMiniMax.h"

int spMinimaxSuggestMove(SPGame* game, int * move) {
	SPGame * copy = spGameCopy(game);
	Node * root;
	if (copy == NULL) return -1;
	root = createNode(copy);
	if (root!=NULL) {
		recAlphaBeta(INT_MIN, INT_MAX, game->difficulty, root, true, 1);
		move[0] = root->move[0];
		move[1] = root->move[1];
		move[2] = root->move[2];
		move[3] = root->move[3];
		destroyNode(root);
		return 0;
	}
	return -1;
}
