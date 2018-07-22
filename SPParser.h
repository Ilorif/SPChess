/*
 * SPParser.h
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */

#ifndef SPPARSER_H_
#define SPPARSER_H_

#include <stdbool.h>

#define SP_MAX_LINE_LENGTH 1024

typedef enum {
	SP_GAME_MODE,
	SP_DIFFICULTY,
	SP_USER_COLOR,
	SP_LOAD,
	SP_DEFAULT,
	SP_PRINT_SETTING,
	SP_QUIT,
	SP_START,
	SP_MOVE_TO,
	SP_GET_MOVES,
	SP_SAVE,
	SP_UNDO,
	SP_RESET,
	SP_QUEEN,
	SP_ROOK,
	SP_KNIGHT,
	SP_BISHOP,
	SP_PAWN,
	SP_INVALID_LINE,
	SP_EXIT
} SP_COMMAND;

typedef struct command_t {
	SP_COMMAND cmd;
	bool validArg;
	int arg1;
	char arg2;
	int arg3;
	char arg4;
	char* path;
} SPCommand;


/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */
bool spParserIsInt(const char* str);

/**
 * Parses a specified line. If the line is a command which has
 * arguments then the arguments are parsed and saved in the fields arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg1 - the integer argument in case validArg is set to true
 *   arg2 - the char argument in case validArg is set to true
 *   arg3 - the integer argument in case validArg is set to true
 *   arg4 - the char argument in case validArg is set to true
 *   path -	the char* argument in case validArg is set to true
 */
SPCommand spParserPraseLine(const char* str);


#endif /* SPPARSER_H_ */
