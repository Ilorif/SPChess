/*
 * SPMiniMaxNode.c
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */

#include "SPMiniMaxNode.h"


Node * createNode(SPGame * game) {
	if(game==NULL) return NULL;
	Node* node = (Node*)malloc(sizeof(Node));
    if(node == NULL){
    	printf(ERROR_FUNC,"malloc");
    	return NULL;
    }
    node->game = game;
    node->move[0] = -2;
    node->move[1] = -2;
    node->move[2] = -2;
    node->move[3] = -2;
    return node;
}

void destroyNode(Node* node) {
	if(node==NULL) return;
	spGameDestroy(node->game);
	free(node);
	return;
}

int recAlphaBeta(int alpha, int beta, int depthleft, Node* node, bool maximizingPlayer, int flag) {
	int score;
	int result;
	SPGame * game;
	Node * child;
	if (spGameCheck(node->game) && spGameNoLegalMoves(node->game)) {
		if (maximizingPlayer) return INT_MIN;
		else return INT_MAX;
	}
	if (spGameNoLegalMoves(node->game)) {
		return 0;
	}
	if (depthleft == 0) {
		return scoringFunction(node->game);
	}
	if (maximizingPlayer) {
		score = INT_MIN;
		for (int x=0; x<SP_GAME_N_ROWS; x++) {
			for (int y=0; y<SP_GAME_N_COLUMNS; y++) {
				for (int i=0; i<SP_GAME_N_ROWS; i++) {
					for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
						if (spPiecePositionContainsPlayerPiece(node->game, x, y)) {
							if (spGameIsValidMove(node->game->currentPlayer, node->game, x, y, i, j)) {
								if (flag==1) {
									flag=0;
									node->move[0] = x;
									node->move[1] = y;
									node->move[2] = i;
									node->move[3] = j;
								}
								game = spGameCopy(node->game);
								spPieceSetMove(game, x, y, i, j);
								child = createNode(game);
								result = recAlphaBeta(alpha, beta, depthleft-1, child, false, flag);
								if (score < result) {
									score = result;
									node->move[0] = x;
									node->move[1] = y;
									node->move[2] = i;
									node->move[3] = j;
								}
								if (score > alpha) alpha = score;
								destroyNode(child);
								if (alpha>=beta) {
									return score;
								}
							}
						}
					}
				}
			}
		}
		return score;
	}
	else {
		score = INT_MAX;
		for (int x=0; x<SP_GAME_N_ROWS; x++) {
			for (int y=0; y<SP_GAME_N_COLUMNS; y++) {
				for (int i=0; i<SP_GAME_N_ROWS; i++) {
					for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
						if (spPiecePositionContainsPlayerPiece(node->game, x, y)) {
							if (spGameIsValidMove(node->game->currentPlayer, node->game, x, y, i, j)) {
								game = spGameCopy(node->game);
								spPieceSetMove(game, x, y, i, j);
								child = createNode(game);
								result = recAlphaBeta(alpha, beta, depthleft-1, child, true, flag);
								if (score > result) {
									score = result;
									node->move[0] = x;
									node->move[1] = y;
									node->move[2] = i;
									node->move[3] = j;
								}
								if (score < beta) beta = score;
								destroyNode(child);
								if (alpha>=beta) {
									return score;
								}
							}
						}
					}
				}
			}
		}
		return score;
	}
}

int scoringFunction(SPGame * game) {
	int score = 0;
	int white = 0;
	int black = 0;
	char piece;
	for (int i=0; i<SP_GAME_N_ROWS; i++) {
		for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
			piece = game->gameBoard[i][j];
			switch(piece) {
				case SP_GAME_WHITE_PAWN:
					white+=1;
					break;
				case SP_GAME_BLACK_PAWN:
					black+=1;
					break;
				case SP_GAME_WHITE_BISHOP:
					white+=3;
					break;
				case SP_GAME_BLACK_BISHOP:
					black+=3;
					break;
				case SP_GAME_WHITE_ROOK:
					white+=5;
					break;
				case SP_GAME_BLACK_ROOK:
					black+=5;
					break;
				case SP_GAME_WHITE_KNIGHT:
					white+=3;
					break;
				case SP_GAME_BLACK_KNIGHT:
					black+=3;
					break;
				case SP_GAME_WHITE_KING:
					white+=100;
					break;
				case SP_GAME_BLACK_KING:
					black+=100;
					break;
				case SP_GAME_WHITE_QUEEN:
					white+=9;
					break;
				case SP_GAME_BLACK_QUEEN:
					black+=9;
					break;
				default:
					break;
			}
		}
	}
	if (game->color==SP_GAME_WHITE_PLAYER) score = black-white;
	else score = white-black;
	return score;
}
