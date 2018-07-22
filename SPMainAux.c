
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "SPMainAux.h"

SPCommand spSettingState(SPGame * game) {
	SPCommand cmd;
	char str[SP_MAX_LINE_LENGTH];
	printf("Specify game setting or type 'start' to begin a game with the current setting:\n");
	while(1) {
		fgets(str,SP_MAX_LINE_LENGTH, stdin);
		cmd = spParserPraseLine(&str[0]);
		switch (cmd.cmd) {
			case SP_GAME_MODE:
				spGameMode(game, cmd);
				break;
			case SP_DIFFICULTY:
				spGameDifficulty(game, cmd);
				break;
			case SP_USER_COLOR:
				spGameUserColor(game, cmd);
				break;
			case SP_LOAD:
				spGameLoad(game, cmd.path);
				break;
			case SP_DEFAULT:
				spGameDefault(game);
				break;
			case SP_PRINT_SETTING:
				spGamePrintSetting(game);
				break;
			case SP_QUIT:
				return cmd;
			case SP_START:
				return cmd;
			default:
				break;
		}
	}
	return cmd;
}

SPCommand spGameApplyCmd(SPGame * game) {
	SPCommand cmd;
	char str[SP_MAX_LINE_LENGTH]; /* User command string */
	if (game->currentPlayer==SP_GAME_WHITE_PLAYER) printf("white player - enter your move:\n");
	else printf("black player - enter your move:\n");
	fgets(str,SP_MAX_LINE_LENGTH, stdin);
	cmd = spParserPraseLine(str);
	switch (cmd.cmd) {
		case SP_MOVE_TO:
			cmd.cmd = spGameSetMove(game, cmd);
			return cmd;
		case SP_SAVE:
			spGameSave(game, cmd.path);
			return cmd;
		case SP_UNDO:
			spGameUndo(game);
			return cmd;
		case SP_RESET:
			spGameReset(game);
			return cmd;
		case SP_QUIT:
			return cmd;
		case SP_GET_MOVES:
			spGameGetMoves(game, cmd);
			return cmd;
		default:
			return cmd;
		}
}

SPCommand spGameState1Mode(SPGame * game) {
	SPCommand cmd;
	bool prtbrd = true;
	int move[4] = {-1,-1,-1,-1};
	char * piece;
	while (1) {
		/*User turn*/
		if (spGameGetColor(game)==spGameGetCurrentPlayer(game)) {
			if (prtbrd) spGamePrintBoard(game);
			cmd = spGameApplyCmd(game);
			if (cmd.cmd==SP_QUIT || cmd.cmd==SP_RESET || cmd.cmd==SP_EXIT) return cmd;
			if (cmd.cmd==SP_INVALID_LINE || cmd.cmd==SP_SAVE) prtbrd = false;
			else prtbrd = true;
		}
		/*AI turn*/
		else {
			int res = spMinimaxSuggestMove(game, move);
			if (res==-1) {
				cmd.cmd = SP_EXIT;
				return cmd;
			}
			piece = convertPiece(game->gameBoard[move[0]][move[1]]);
			printf("Computer: move %s at <%d,%c> to <%d,%c>\n", piece, 8-move[0], move[1]+'A', 8-move[2], move[3]+'A');
			spPieceSetMove(game, move[0], move[1], move[2], move[3]);
			if (spGameCheck(game)) {
				if (spGameNoLegalMoves(game)) {
					if (game->currentPlayer==SP_GAME_WHITE_PLAYER) printf("Checkmate! black player wins the game\n");
					else printf("Checkmate! white player wins the game\n");
					cmd.cmd = SP_EXIT;
					return cmd;
				}
				printf("Check!\n");
			}
			else {
				if (spGameNoLegalMoves(game)) {
					printf("The game ends in a tie\n");
					cmd.cmd = SP_EXIT;
					return cmd;
				}
			}
		}
	}
	return cmd;
}

SPCommand spGameState2Mode(SPGame * game) {
	SPCommand cmd;
	bool prtbrd = true;
	while (1) {
		if (prtbrd) spGamePrintBoard(game);
		cmd = spGameApplyCmd(game);
		if (cmd.cmd==SP_QUIT || cmd.cmd==SP_RESET || cmd.cmd==SP_EXIT) return cmd;
		if (cmd.cmd==SP_INVALID_LINE || cmd.cmd==SP_SAVE) prtbrd = false;
		else prtbrd = true;
	}
	return cmd;
}

char * convertPiece(char piece) {
	switch(piece) {
	case SP_GAME_WHITE_PAWN:
	case SP_GAME_BLACK_PAWN:
		return "pawn";
	case SP_GAME_WHITE_BISHOP:
	case SP_GAME_BLACK_BISHOP:
		return "bishop";
	case SP_GAME_WHITE_ROOK:
	case SP_GAME_BLACK_ROOK:
		return "rook";
	case SP_GAME_WHITE_KNIGHT:
	case SP_GAME_BLACK_KNIGHT:
		return "knight";
	case SP_GAME_WHITE_KING:
	case SP_GAME_BLACK_KING:
		return "king";
	case SP_GAME_WHITE_QUEEN:
	case SP_GAME_BLACK_QUEEN:
		return "queen";
	default:
		return "";
	}
}
