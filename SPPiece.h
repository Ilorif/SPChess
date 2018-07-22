/*
 * SPPiece.h
 *
 *  Created on: 7 баев 2017
 *      Author: Admin
 */



#ifndef SPPIECE_H_
#define SPPIECE_H_

#include <stdbool.h>
#include <ctype.h>

#include "SPGame.h"

/**
 * checks if the given parameters are valid positions on the game board.
 * @param x, y, i, j - the position coordinates.
 * @return
 * false if not, true otherwise.
 */
bool spPieceIsValidPosition(int x, int y, int i, int j);

/**
 * checks if a given position is not empty.
 * @param game - current game.
 * @param x, y - the position coordinates.
 * @return
 * false if empty, true otherwise.
 */
bool spPieceIsNotEmptytPosition(SPGame * game, int x, int y);

/**
 * checks if a given position contains player piece.
 * @param game - current game.
 * @param x, y - the position coordinates.
 * @return
 * true if it is, false otherwise.
 */
bool spPiecePositionContainsPlayerPiece(SPGame * game, int x, int y);

/**
 * checks if a given position contains opponent piece.
 * @param game - current game.
 * @param x, y - the position coordinates.
 * @return
 * true if it is, false otherwise.
 */
bool spPiecePositionContainsOpponentPiece(SPGame * game, int x, int y);

/**
 * checks if a given move is valid for black pawn piece.
 * @param game - current game.
 * @param x, y, i, j - the positions coordinates.
 * @return
 * true if it is valid, false otherwise.
 */
bool spPieceBlackPawnIsValidMove(SPGame * game, int x, int y, int i, int j);

/**
 * checks if a given move is valid for white pawn piece.
 * @param game - current game.
 * @param x, y, i, j - the positions coordinates.
 * @return
 * true if it is valid, false otherwise.
 */
bool spPieceWhitePawnIsValidMove(SPGame * game, int x, int y, int i, int j);

/**
 * checks if a given move is valid for bishop piece.
 * @param game - current game.
 * @param x, y, i, j - the positions coordinates.
 * @return
 * true if it is valid, false otherwise.
 */
bool spPieceBishopIsValidMove(SPGame * game, int x, int y, int i, int j);

/**
 * checks if a given move is valid for rook piece.
 * @param game - current game.
 * @param x, y, i, j - the positions coordinates.
 * @return
 * true if it is valid, false otherwise.
 */
bool spPieceRookIsValidMove(SPGame * game, int x, int y, int i, int j);

/**
 * checks if a given move is valid for knight piece.
 * @param x, y, i, j - the positions coordinates.
 * @return
 * true if it is valid, false otherwise.
 */
bool spPieceKnightIsValidMove(int x, int y, int i, int j);

/**
 * checks if a given move is valid for queen piece.
 * @param game - current game.
 * @param x, y, i, j - the positions coordinates.
 * @return
 * true if it is valid, false otherwise.
 */
bool spPieceQueenIsValidMove(SPGame * game, int x, int y, int i, int j);

/**
 * checks if a given move is valid for king piece.
 * @param x, y, i, j - the positions coordinates.
 * @return
 * true if it is valid, false otherwise.
 */
bool spPieceKingIsValidMove(int x, int y, int i, int j);

/**
 * checks if a given move from square [x,y] to square [i,j] is valid
 * for the piece that is in [x,y] square, in terms valid piece move.
 * @param player - the player we assume is now playing.
 * @param game - current game.
 * @param x, y, i, j - the positions coordinates.
 * @return
 * true if it is valid, false otherwise.
 */
bool spPieceIsValidMove(int player, SPGame * game, int x, int y, int i, int j);

/**
 * checks if there is a check on the current player in the game.
 * @param game - current game.
 * @return
 * true if there is, false otherwise.
 */
bool spGameCheck(SPGame * game);

/**
 * checks if a given move causes a check on the current player in the game.
 * @param game - current game.
 * @return
 * true if it is, false otherwise.
 */
bool spGameCheckOnPlayer(SPGame * game, int x, int y, int i, int j);

/**
 * checks if there are not legal moves for the current player in the game.
 * @param game - current game.
 * @return
 * true if it is, false otherwise.
 */
bool spGameNoLegalMoves(SPGame * game);

/**
 * checks if a given move from square [x,y] to square [i,j] is valid
 * for the piece that is in [x,y] square, and doesn't causes a check for
 * this player.
 * @param player - the player we assume is now playing.
 * @param game - current game.
 * @param x, y, i, j - the positions coordinates.
 * @return
 * true if it is valid, false otherwise.
 */
bool spGameIsValidMove(int player, SPGame * game, int x, int y, int i, int j);

/**
 * apply the move for the player, changes the board, kings positions, etc.
 * this player.
 * @param game - current game.
 * @param x, y, i, j - the positions coordinates.
 */
void spPieceSetMove(SPGame * game, int x, int y, int i, int j);

/**
 * apply the move for the player, if valid.
 * this player.
 * @param game - current game.
 * @param cmd - the set_move command.
 * @return
 * SP_INVALID_LINE - if the move is not valid.
 * SP_EXIT - if there was a checkmate or a tie.
 * SP_GET_MOVE - otherwise.
 */
SP_COMMAND spGameSetMove(SPGame * game, SPCommand cmd);

/**
 * apply the move for the player, changes the board, kings positions, etc.
 * this player.
 * @param game - current game.
 * @param cmd - the get_moves command.
 */
void spGameGetMoves(SPGame * game, SPCommand cmd);


#endif /* SPPIECE_H_ */
