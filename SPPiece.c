/*
 * SPPiece.c
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */


#include "SPPiece.h"


bool spPieceIsValidPosition(int x, int y, int i, int j) {
	if(x<0 || x>7 || y<0 || y>7 || i<0 || i>7 || j<0 || j>7)
		return false;
	return true;
}

bool spPieceIsNotEmptytPosition(SPGame * game, int x, int y) {
	if (game->gameBoard[x][y]==SP_GAME_EMPTY_ENTRY)
		return false;
	return true;
}

bool spPiecePositionContainsPlayerPiece(SPGame * game, int x, int y) {
	char piece = game->gameBoard[x][y];
	if ((game->currentPlayer==SP_GAME_BLACK_PLAYER && isupper(piece))
		|| (game->currentPlayer==SP_GAME_WHITE_PLAYER && islower(piece)))
		return true;
	return false;
}

bool spPiecePositionContainsOpponentPiece(SPGame * game, int x, int y) {
	char piece = game->gameBoard[x][y];
	if ((game->currentPlayer==SP_GAME_BLACK_PLAYER && islower(piece))
		|| (game->currentPlayer==SP_GAME_WHITE_PLAYER && isupper(piece)))
		return true;
	return false;
}

bool spPieceBlackPawnIsValidMove(SPGame * game, int x, int y, int i, int j) {
	if (y==j && (i==x+1 || (i==x+2 && x==1)) && !spPieceIsNotEmptytPosition(game, i, j)) return true;
	if (i==x+1 && (j==y-1 || j==y+1) && islower(game->gameBoard[i][j])) return true;
	return false;
}

bool spPieceWhitePawnIsValidMove(SPGame * game, int x, int y, int i, int j) {
	if (y==j && (i==x-1 || (i==x-2 && x==6)) && !spPieceIsNotEmptytPosition(game, i, j)) return true;
	if (i==x-1 && (j==y-1 || j==y+1) && isupper(game->gameBoard[i][j])) return true;
	return false;
}

bool spPieceBishopIsValidMove(SPGame * game, int x, int y, int i, int j) {
	if (abs(x-i)!=abs(y-j)) return false;
	if (j>y) {
		if (i>x) {
			for (int k=1; k<(j-y); k++) {
				if (spPieceIsNotEmptytPosition(game, x+k, y+k)) return false;
			}
		}
		else {
			for (int k=1; k<(j-y); k++) {
				if (spPieceIsNotEmptytPosition(game, x-k, y+k)) return false;
			}
		}
	}
	else {
		if (i>x) {
			for (int k=1; k<(y-j); k++) {
				if (spPieceIsNotEmptytPosition(game, x+k, y-k)) return false;
			}
		}
		else {
			for (int k=1; k<(y-j); k++) {
				if (spPieceIsNotEmptytPosition(game, x-k, y-k)) return false;
			}
		}
	}
	return true;
}

bool spPieceRookIsValidMove(SPGame * game, int x, int y, int i, int j) {
	if (x==i) {
		if (j>y) {
			for (int k=1; k<(j-y); k++) {
				if (spPieceIsNotEmptytPosition(game, x, y+k)) return false;
			}
		}
		else {
			for (int k=1; k<(y-j); k++) {
				if (spPieceIsNotEmptytPosition(game, x, y-k)) return false;
			}
		}
		return true;
	}
	else {
		if (y==j) {
			if (i>x) {
				for (int k=1; k<(i-x); k++) {
					if (spPieceIsNotEmptytPosition(game, x+k, y)) return false;
				}
			}
			else {
				for (int k=1; k<(x-i); k++) {
					if (spPieceIsNotEmptytPosition(game, x-k, y)) return false;
				}
			}
			return true;
		}
	}
	return false;
}

bool spPieceKnightIsValidMove(int x, int y, int i, int j) {
	if ((x==i+1 && y==j-2) || (x==i+1 && y==j+2) || (x==i-1 && y==j-2) || (x==i-1 && y==j+2)
			|| (x==i-2 && y==j-1) || (x==i-2 && y==j+1) || (x==i+2 && y==j-1) || (x==i+2 && y==j+1))
		return true;
	return false;
}

bool spPieceQueenIsValidMove(SPGame * game, int x, int y, int i, int j) {
	if (spPieceRookIsValidMove(game, x, y, i, j) || spPieceBishopIsValidMove(game, x, y, i, j))
		return true;
	return false;
}

bool spPieceKingIsValidMove(int x, int y, int i, int j) {
	if ((x==i && y==j-1) || (x==i && y==j+1) || (x==i-1 && y==j-1) || (x==i+1 && y==j-1)
			|| (x==i-1 && y==j) || (x==i+1 && y==j) || (x==i-1 && y==j+1) || (x==i+1 && y==j+1))
		return true;
	return false;
}

bool spPieceIsValidMove(int player, SPGame * game, int x, int y, int i, int j) {
	char piece = game->gameBoard[x][y];
	char target = game->gameBoard[i][j];
	if ((player==SP_GAME_BLACK_PLAYER && islower(piece)) || (player==SP_GAME_WHITE_PLAYER && isupper(piece)))
		return false;
	if ((player==SP_GAME_BLACK_PLAYER && isupper(target)) || (player==SP_GAME_WHITE_PLAYER && islower(target)))
		return false;
	switch(piece) {
		case SP_GAME_WHITE_PAWN:
			return spPieceWhitePawnIsValidMove(game, x, y, i, j);
		case SP_GAME_BLACK_PAWN:
			return spPieceBlackPawnIsValidMove(game, x, y, i, j);
		case SP_GAME_WHITE_BISHOP:
		case SP_GAME_BLACK_BISHOP:
			return spPieceBishopIsValidMove(game, x, y, i, j);
		case SP_GAME_WHITE_ROOK:
		case SP_GAME_BLACK_ROOK:
			return spPieceRookIsValidMove(game, x, y, i, j);
		case SP_GAME_WHITE_KNIGHT:
		case SP_GAME_BLACK_KNIGHT:
			return spPieceKnightIsValidMove(x, y, i, j);
		case SP_GAME_WHITE_KING:
		case SP_GAME_BLACK_KING:
			return spPieceKingIsValidMove(x, y, i, j);
		case SP_GAME_WHITE_QUEEN:
		case SP_GAME_BLACK_QUEEN:
			return spPieceQueenIsValidMove(game, x, y, i, j);
		default:
			return false;
	}
	return false;
}

bool spGameCheck(SPGame * game) {
	for (int i=0; i<SP_GAME_N_ROWS; i++) {
		for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
			if (game->currentPlayer==SP_GAME_WHITE_PLAYER) {
				if(spPieceIsValidMove(SP_GAME_BLACK_PLAYER, game, i, j, game->whiteKing[0], game->whiteKing[1])) {
					return true;
				}
			}
			else {
				if(spPieceIsValidMove(SP_GAME_WHITE_PLAYER, game, i, j, game->blackKing[0], game->blackKing[1])) {
					return true;
				}
			}
		}
	}
	return false;
}

bool spGameCheckOnPlayer(SPGame * game, int x, int y, int i, int j) {
	SPGame * copy = spGameCopy(game);
	bool ans = false;
	spPieceSetMove(copy, x, y, i, j);
	spGameChangePlayer(copy);
	if (spGameCheck(copy)) ans = true;
	spGameDestroy(copy);
	return ans;
}

bool spGameNoLegalMoves(SPGame * game) {
	for (int x=0; x<SP_GAME_N_ROWS; x++) {
		for (int y=0; y<SP_GAME_N_COLUMNS; y++) {
			for (int i=0; i<SP_GAME_N_ROWS; i++) {
				for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
					if (spPieceIsNotEmptytPosition(game, x, y)) {
						if (spGameIsValidMove(game->currentPlayer, game, x, y, i, j)) {
								return false;
						}
					}
				}
			}
		}
	}
	return true;
}

bool spGameIsValidMove(int player, SPGame * game, int x, int y, int i, int j) {
	if (!spPieceIsValidMove(player, game, x, y , i, j) || spGameCheckOnPlayer(game, x, y , i, j))
		return false;
	return true;
}

void spPieceSetMove(SPGame * game, int x, int y, int i, int j) {
	if (spArrayListIsFull(game->undoList)) {
		spArrayListRemoveFirst(game->undoList);
	}
	spArrayListAddLast(game->undoList, game->gameBoard[i][j], x, y, i, j);
	game->gameBoard[i][j]=game->gameBoard[x][y];
	game->gameBoard[x][y]=SP_GAME_EMPTY_ENTRY;
	if (game->gameBoard[i][j]==SP_GAME_BLACK_KING) {
		game->blackKing[0]=i;
		game->blackKing[1]=j;
	}
	else if (game->gameBoard[i][j]==SP_GAME_WHITE_KING) {
		game->whiteKing[0]=i;
		game->whiteKing[1]=j;
	}
	spGameChangePlayer(game);
}

SP_COMMAND spGameSetMove(SPGame * game, SPCommand cmd) {
	int x = 8 - cmd.arg1;
	int y = (int)cmd.arg2 - 65;
	int i = 8 - cmd.arg3;
	int j = (int)cmd.arg4 - 65;
	if (!spPieceIsValidPosition(x, y, i, j) || !(cmd.validArg)) {
		printf("Invalid position on the board\n");
		return SP_INVALID_LINE;
	}
	if (!spPiecePositionContainsPlayerPiece(game, x, y)) {
		printf("The specified position does not contain your piece\n");
		return SP_INVALID_LINE;
	}
	if (!spGameIsValidMove(game->currentPlayer, game, x, y , i, j)) {
		printf("Illegal move\n");
		return SP_INVALID_LINE;
	}
	spPieceSetMove(game, x, y, i, j);
	if (spGameCheck(game)) {
		if (spGameNoLegalMoves(game)) {
			if (game->currentPlayer==SP_GAME_WHITE_PLAYER) printf("Checkmate! black player wins the game\n");
			else printf("Checkmate! white player wins the game\n");
			return SP_EXIT;
		}
		if (game->currentPlayer==SP_GAME_WHITE_PLAYER) printf("Check: white King is threatened!\n");
		else printf("Check: black King is threatened!\n");
	}
	else {
		if (spGameNoLegalMoves(game)) {
			printf("The game is tied\n");
			return SP_EXIT;
		}
	}
	return SP_MOVE_TO;
}

void spGameGetMoves(SPGame * game, SPCommand cmd) {
	bool opp;
	bool check;
	if (game->mode==1 && (game->difficulty==1 || game->difficulty==2)) {
		int x = 8 - cmd.arg1;
		int y = (int)cmd.arg2 - 65;
		if (x<0 || x>7 || y<0 || y>7) {
			printf("Invalid position on the board\n");
			return;
		}
		if (!spPiecePositionContainsPlayerPiece(game, x, y)) {
			printf("The specified position does not contain %s player piece\n", spGameGetColorString(game));
			return;
		}
		for (int i=SP_GAME_N_ROWS-1; i>=0; i--) {
			for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
				if (spPieceIsValidMove(game->currentPlayer, game, x, y, i, j)) {
					opp = spPiecePositionContainsOpponentPiece(game, i, j);
					check = spGameCheckOnPlayer(game, x, y, i, j);
					if (check && !opp) {
						printf("<%d,%c>*\n", 8-i, j+'A');
					}
					else if (!check && opp) {
						printf("<%d,%c>^\n", 8-i, j+'A');
					}
					else if (check && opp) {
						printf("<%d,%c>*^\n", 8-i, j+'A');
					}
					else printf("<%d,%c>\n", 8-i, j+'A');
				}
			}
		}
	}
	else printf("\n");
}

