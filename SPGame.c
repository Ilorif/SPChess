/*
 * SPGame.c
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */

#include "SPGame.h"

SPGame* spGameCreate() {
	SPGame* game = (SPGame*) malloc(sizeof(SPGame));
	if (game == NULL) {
		printf(ERROR_FUNC,"malloc");
		return NULL;
	}
	game->undoList = spArrayListCreate();
	if (game->undoList == NULL) {
		free(game);
		return NULL;
	}
	spGameReset(game);
	return game;
}

SPGame* spGameCopy(SPGame* game) {
	if (game!=NULL) {
		SPGame* copy = (SPGame*) malloc(sizeof(SPGame));
		if (copy == NULL) {
			printf(ERROR_FUNC,"malloc");
			return NULL;
		}
		copy->mode=game->mode;
		copy->difficulty=game->difficulty;
		copy->color=game->color;
		copy->currentPlayer = game->currentPlayer;
		copy->blackKing[0] = game->blackKing[0];
		copy->blackKing[1] = game->blackKing[1];
		copy->whiteKing[0] = game->whiteKing[0];
		copy->whiteKing[1] = game->whiteKing[1];
		for (int i=0; i<SP_GAME_N_ROWS; i++) {
			for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
				copy->gameBoard[i][j] = game->gameBoard[i][j];
			}
		}
		copy->undoList = spArrayListCopy(game->undoList);
		if (copy->undoList == NULL) {
			return NULL;
		}
		return copy;
	}
	return NULL;
}

void spGameDestroy(SPGame* game) {
	if (game == NULL) return;
	spArrayListDestroy(game->undoList);
	free(game);
	return;
}

void spGameReset(SPGame * game) {
	spGameDefault(game);
	spGameRestart(game);
}

void spGameRestart(SPGame * game) {
	game->blackKing[0] = 0;
	game->blackKing[1] = 4;
	game->whiteKing[0] = 7;
	game->whiteKing[1] = 4;
	for (int i=2; i<SP_GAME_N_ROWS-2; i++) {
		for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
			game->gameBoard[i][j] = SP_GAME_EMPTY_ENTRY;
		}
	}
	for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
		game->gameBoard[1][j] = SP_GAME_BLACK_PAWN;
		game->gameBoard[6][j] = SP_GAME_WHITE_PAWN;
	}
	game->gameBoard[0][0] = SP_GAME_BLACK_ROOK;
	game->gameBoard[0][1] = SP_GAME_BLACK_KNIGHT;
	game->gameBoard[0][2] = SP_GAME_BLACK_BISHOP;
	game->gameBoard[0][3] = SP_GAME_BLACK_QUEEN;
	game->gameBoard[0][4] = SP_GAME_BLACK_KING;
	game->gameBoard[0][5] = SP_GAME_BLACK_BISHOP;
	game->gameBoard[0][6] = SP_GAME_BLACK_KNIGHT;
	game->gameBoard[0][7] = SP_GAME_BLACK_ROOK;
	game->gameBoard[7][0] = SP_GAME_WHITE_ROOK;
	game->gameBoard[7][1] = SP_GAME_WHITE_KNIGHT;
	game->gameBoard[7][2] = SP_GAME_WHITE_BISHOP;
	game->gameBoard[7][3] = SP_GAME_WHITE_QUEEN;
	game->gameBoard[7][4] = SP_GAME_WHITE_KING;
	game->gameBoard[7][5] = SP_GAME_WHITE_BISHOP;
	game->gameBoard[7][6] = SP_GAME_WHITE_KNIGHT;
	game->gameBoard[7][7] = SP_GAME_WHITE_ROOK;

	spArrayListClear(game->undoList);
	game->currentPlayer = SP_GAME_WHITE_PLAYER;
}

int spGameGetColor(SPGame * game) {
	if (game == NULL) return 2;
	if (game->color == SP_GAME_WHITE_PLAYER) return SP_GAME_WHITE_PLAYER;
	else if (game->color == SP_GAME_BLACK_PLAYER) return SP_GAME_BLACK_PLAYER;
		else return 2;
}

char * spGameGetColorString(SPGame * game) {
	if (spGameGetColor(game)) return "white";
	else return "black";
}

int spGameGetCurrentPlayer(SPGame * game) {
	if (game == NULL) return 2;
	if (game->currentPlayer == SP_GAME_WHITE_PLAYER) return SP_GAME_WHITE_PLAYER;
	else if (game->currentPlayer == SP_GAME_BLACK_PLAYER) return SP_GAME_BLACK_PLAYER;
		else return 2;
}

void spGameChangePlayer(SPGame* game) {
	if (game == NULL) return;
	if (game->currentPlayer == SP_GAME_WHITE_PLAYER)
		game->currentPlayer = SP_GAME_BLACK_PLAYER;
	else game->currentPlayer = SP_GAME_WHITE_PLAYER;
}

void spGamePrintSetting(SPGame * game) {
	printf("SETTINGS:\n");
	if (game->mode==2) printf("GAME_MODE: 2\n");
	else {
		printf("GAME_MODE: 1\n");
		printf("DIFFICULTY_LVL: %d\n",game->difficulty);
		if(game->color==0) printf("USER_CLR: BLACK\n");
		else printf("USER_CLR: WHITE\n");
	}
}

void spGamePrintBoard(SPGame * game) {
	if (game==NULL) return;
	for (int i=0; i<SP_GAME_N_ROWS; i++) {
		printf("%d",8-i);
		printf("| ");
			for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
				printf("%c ",game->gameBoard[i][j]);
		}
		printf("|\n");
	}
	printf("  -----------------\n");
	printf("   A B C D E F G H\n");
}

void spGameMode(SPGame * game, SPCommand cmd) {
	if (cmd.validArg && cmd.arg1==1) {
		game->mode = 1;
		printf("Game mode is set to 1 player\n");
	}
	else {
		if (cmd.validArg && cmd.arg1==2) {
			game->mode = 2;
			printf("Game mode is set to 2 players\n");
		}
		else printf("Wrong game mode\n");
	}
}

void spGameDifficulty(SPGame * game, SPCommand cmd) {
	if (game->mode==1) {
		if (cmd.validArg && (cmd.arg1>0 && cmd.arg1<5)) {
			game->difficulty = cmd.arg1;
			return;
		}
		if (cmd.validArg && cmd.arg1==5) printf("Expert level not supported, please choose a value between 1 to 4:\n");
		else printf("Wrong difficulty level. The value should be between 1 to 5\n");
	}
}

void spGameUserColor(SPGame * game, SPCommand cmd) {
	if (game->mode==1 && (cmd.arg1==0 || cmd.arg1==1)) {
		game->color = cmd.arg1;
	}
}

void spGameDefault(SPGame * game) {
	if (game==NULL) return;
	game->mode=1;
	game->difficulty=2;
	game->color=1;
	return;
}

void spGameLoad(SPGame * game, char* path) {
	FILE * fp;
	char buff[1024];
	char* line;
	fp=fopen(path, "r");
	if(fp) {
		fgets(buff, 1024, (FILE*)fp);
		fgets(buff, 1024, (FILE*)fp);
		fgets(buff, 1024, (FILE*)fp);
		game->currentPlayer = spGameParseXMLData(buff);
		fgets(buff, 1024, (FILE*)fp);
		game->mode = spGameParseXMLData(buff);
		if (game->mode==1) {
			fgets(buff, 1024, (FILE*)fp);
			game->difficulty = spGameParseXMLData(buff);
			fgets(buff, 1024, (FILE*)fp);
			game->color = spGameParseXMLData(buff);
		}
		fgets(buff, 1024, (FILE*)fp);
		for (int j=0; j<8; j++) {
			fgets(buff, 1024, (FILE*)fp);
			line = spGameParseXMLBoard(buff);
			for (int i=0; i<8; i++) {
				game->gameBoard[j][i] = line[i];
				if (game->gameBoard[j][i]==SP_GAME_WHITE_KING) {
					game->whiteKing[0] = j;
					game->whiteKing[1] = i;
				}
				if (game->gameBoard[j][i]==SP_GAME_BLACK_KING) {
					game->blackKing[0] = j;
					game->blackKing[1] = i;
				}
			}
		}
		spArrayListClear(game->undoList);
	}
	else {
		printf("Error: File doesn't exist or cannot be opened\n");
	}
}

int spGameParseXMLData(char* buff) {
	char* tok;
	char* token[2] = {"",""};
	int i=0;
	tok = strtok(buff, " <>\t\r\n");
	while (tok != NULL && i<2) {
		token[i] = tok;
		tok = strtok(NULL, " <>\t\r\n");
		i++;
	}
	if (spParserIsInt(token[1])) {
		return atoi(token[1]);
	}
	return 0;
}

char* spGameParseXMLBoard(char* buff) {
	char* tok;
	char* token[2] = {"",""};
	int i=0;
	tok = strtok(buff, " <>\t\r\n");
	while (tok != NULL && i<2) {
		token[i] = tok;
		tok = strtok(NULL, " <>\t\r\n");
		i++;
	}
	return token[1];
}

void spGameSave(SPGame * game, char* path) {
	FILE * fp;
	char* string;
	fp=fopen(path,"w");
	if(fp) {
		string = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
		fprintf(fp,"%s\n",string);
		string = "<game>";
		fprintf(fp,"%s\n",string);
		fprintf(fp,"\t<current_turn>%d</current_turn>\n",game->currentPlayer);
		fprintf(fp,"\t<game_mode>%d</game_ mode>\n",game->mode);
		if (game->mode==1) {
			fprintf(fp,"\t<difficulty>%d</difficulty>\n",game->difficulty);
			fprintf(fp,"\t<user_color>%d</user_color>\n",game->color);
		}
		string = "\t<board>";
		fprintf(fp,"%s\n",string);
		for (int i=0; i<SP_GAME_N_ROWS; i++) {
			fprintf(fp,"\t\t<row_%d>",8-i);
				for (int j=0; j<SP_GAME_N_COLUMNS; j++) {
					fprintf(fp,"%c",game->gameBoard[i][j]);
			}
			fprintf(fp,"</row_%d>\n",8-i);
		}
		string = "\t</board>\n";
		fprintf(fp,"%s\n",string);
		string = "</game>";
		fprintf(fp,"%s\n",string);
		fclose(fp);
	}
	else {
		printf("File cannot be created or modified\n");
	}
}

SP_GAME_MESSAGE spGameUndoPrevMove(SPGame * game) {
	if (game==NULL)
		return SP_GAME_INVALID_ARGUMENT;
	if (spArrayListIsEmpty(game->undoList))
		return SP_GAME_NO_HISTORY;
	int x = game->undoList->positions[0][game->undoList->actualSize-1];
	int y = game->undoList->positions[1][game->undoList->actualSize-1];
	int z = game->undoList->positions[2][game->undoList->actualSize-1];
	int w = game->undoList->positions[3][game->undoList->actualSize-1];
	char oldPiece = game->undoList->element[game->undoList->actualSize-1];
	char newPiece = game->gameBoard[z][w];
	game->gameBoard[x][y] = newPiece;
	game->gameBoard[z][w] = oldPiece;
	if (oldPiece==SP_GAME_BLACK_KING) {
		game->blackKing[0]=z;
		game->blackKing[1]=w;
	}
	if (newPiece==SP_GAME_BLACK_KING) {
		game->blackKing[0]=x;
		game->blackKing[1]=y;
	}
	if (oldPiece==SP_GAME_WHITE_KING) {
		game->whiteKing[0]=z;
		game->whiteKing[1]=w;
	}
	if (newPiece==SP_GAME_WHITE_KING) {
		game->whiteKing[0]=x;
		game->whiteKing[1]=y;
	}
	spArrayListRemoveLast(game->undoList);
	spGameChangePlayer(game);
	if (islower(newPiece)) {
		printf("Undo move for player white : <%d,%c> -> <%d,%c>\n",8-z,(char)w+65,8-x,(char)y+65);
	}
	else printf("Undo move for player black : <%d,%c> -> <%d,%c>\n",8-z,(char)w+65,8-x,(char)y+65);

	return SP_GAME_SUCCESS;
}

void spGameUndo(SPGame * game) {
	if (game->mode==2) {
		printf("Undo command not available in 2 players mode\n");
		return;
	}
	if (spArrayListIsEmpty(game->undoList) || (spGameGetColor(game)==SP_GAME_BLACK_PLAYER && spArrayListSize(game->undoList)==1)) {
		printf("Empty history, move cannot be undone\n");
		return;
	}
	spGameUndoPrevMove(game);
	spGameUndoPrevMove(game);
}



