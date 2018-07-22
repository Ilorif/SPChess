/*
 * SPParser.c
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include "SPParser.h"

bool spParserIsInt(const char* str) {
	if (atoi(str)!=0) return true;
	return false;
}

SPCommand spParserPraseLine(const char* str) {
	char* token[5] = {"","","","",""};
	char* tok;
	int i = 0;
	SPCommand cmd;
	char string[SP_MAX_LINE_LENGTH];
	int c = 0;
	cmd.validArg = false;
	cmd.arg1 = atoi(str);
	cmd.arg2 = atoi(str);
	cmd.arg3 = atoi(str);
	cmd.arg4 = atoi(str);
	cmd.path = NULL;

	while (str[c]!='\0') {
		string[c] = str[c];
		c++;
	}
	string[c] = '\0';
	tok = strtok(string, " \t\r\n");
	while (tok != NULL && i<5) {
		token[i] = tok;
		tok = strtok(NULL, " \t\r\n");
		i++;
	}

	if (strcmp(token[4],"")) cmd.cmd = SP_INVALID_LINE;
	else if (!strcmp(token[0],"queen") && !strcmp(token[1],"")) cmd.cmd = SP_QUEEN;
	else if (!strcmp(token[0],"rook") && !strcmp(token[1],"")) cmd.cmd = SP_ROOK;
	else if (!strcmp(token[0],"knight") && !strcmp(token[1],"")) cmd.cmd = SP_KNIGHT;
	else if (!strcmp(token[0],"bishop") && !strcmp(token[1],"")) cmd.cmd = SP_BISHOP;
	else if (!strcmp(token[0],"pawn") && !strcmp(token[1],"")) cmd.cmd = SP_PAWN;
	else if (!strcmp(token[0],"quit") && !strcmp(token[1],"")) cmd.cmd = SP_QUIT;
	else if (!strcmp(token[0],"start") && !strcmp(token[1],"")) cmd.cmd = SP_START;
	else if (!strcmp(token[0],"reset") && !strcmp(token[1],"")) cmd.cmd = SP_RESET;
	else if (!strcmp(token[0],"undo") && !strcmp(token[1],"")) cmd.cmd = SP_UNDO;
	else if (!strcmp(token[0],"default") && !strcmp(token[1],"")) cmd.cmd = SP_DEFAULT;
	else if (!strcmp(token[0],"print_setting") && !strcmp(token[1],"")) cmd.cmd = SP_PRINT_SETTING;
	else if (!strcmp(token[0],"game_mode") && !strcmp(token[2],"")) {
		cmd.cmd = SP_GAME_MODE;
		if (spParserIsInt(token[1])) {
			cmd.arg1 = atoi(token[1]);
			cmd.validArg = true;
		}
		else cmd.validArg = false;
	}
	else if (!strcmp(token[0],"difficulty") && !strcmp(token[2],"")) {
		cmd.cmd = SP_DIFFICULTY;
		if (spParserIsInt(token[1])) {
			cmd.arg1 = atoi(token[1]);
			cmd.validArg = true;
		}
		else cmd.validArg = false;
	}
	else if (!strcmp(token[0],"user_color") && !strcmp(token[2],"")) {
		cmd.cmd = SP_USER_COLOR;
		if (spParserIsInt(token[1])) {
			cmd.arg1 = atoi(token[1]);
			cmd.validArg = true;
		}
		else cmd.validArg = false;
	}
	else if (!strcmp(token[0],"save") && !strcmp(token[2],"")) {
		cmd.cmd = SP_SAVE;
		cmd.path = token[1];
		cmd.validArg = true;
	}
	else if (!strcmp(token[0],"load") && !strcmp(token[2],"")) {
		cmd.cmd = SP_LOAD;
		cmd.path = token[1];
		cmd.validArg = true;
	}
	else if (!strcmp(token[0],"move") && !strcmp(token[2],"to")) {
		if (token[1][0]=='<' && token[1][2]==',' && token[1][4]=='>' && token[3][0]=='<'
				&& token[3][2]==',' && token[3][4]=='>' && isdigit(token[1][1]) && isalpha(token[1][3])
				&& isdigit(token[3][1]) && isalpha(token[3][3])) {
			cmd.cmd = SP_MOVE_TO;
			cmd.arg1 = (int) token[1][1] - 48;
			cmd.arg2 = token[1][3];
			cmd.arg3 = (int) token[3][1] - 48;
			cmd.arg4 = token[3][3];
			cmd.validArg = true;
		}
		else cmd.validArg = false;
	}
	else if (!strcmp(token[0],"get_moves") && !strcmp(token[2],"")) {
		if (token[1][0]=='<' && token[1][2]==',' && token[1][4]=='>'
				 && isdigit(token[1][1]) && isalpha(token[1][3])) {
			cmd.cmd = SP_GET_MOVES;
			cmd.arg1 = (int) token[1][1] - 48;
			cmd.arg2 = token[1][3];
			cmd.validArg = true;
		}
		else cmd.validArg = false;
	}
	else cmd.cmd = SP_INVALID_LINE;
	return cmd;
}

