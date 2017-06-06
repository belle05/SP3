#ifndef SPMINIMAX_H_
#define SPMINIMAX_H_

#include "SPFIARGame.h"

/**
 * Given a game state, this function evaluates the best move according to
 * the current player. The function initiates a MiniMax algorithm up to a
 * specified length given by maxDepth. The current game state doesn't change
 * by this function including the history of previous moves.
 *
 * @param currentGame - The current game state
 * @param maxDepth - The maximum depth of the miniMax algorithm
 * @return
 * -1 if either currentGame is NULL or maxDepth <= 0.
 * On success the function returns a number between [0,SP_FIAR_GAME_N_COLUMNS -1]
 * which is the best move for the current player.
 */
int spMinimaxSuggestMove(SPFiarGame* currentGame,
		unsigned int maxDepth){

}


int calcBoardScore(SPFiarGame* src){
	return calcBoadRows(src) +\
		calcBoadCols(src) +\
		calcBoadDiagonals(src)
}

int singleScore(int score){
	//If score is 0 return 0
	if (score == 0) {
		return 0;
	}

	//if score is not 0, return by the following
	//logic: {-3:−5,-2:−2,-1:−1,1:1,2:2,3:5}
	int pos;
	int sign = 1;
	if (score > 0) {
		pos = score;
	} else {
		pos = score * (-1);
		sign = -1;
	}

	if (pos < 3) {
		return sign*pos;
	} else {
		return sign*5;

}

int calcBoadRows(SPFiarGame* src, char player1, char player2){
	int row_score=0;
	int total_score;
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
		for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS-4; c++) {
			for (unsigned int f = 0; f<4; f++) {
				if (src -> gameBoard[r][c+f] == player2) {
					row_score += 1;
				} else if (src -> gameBoard[r][c+f] == player1) {
					row_score -= 1;
				}
			}
			total_score += singleScore(row_score);
		}
	}
	return total_score;
}

int calcBoadCols(SPFiarGame* src){
	int col_score=0;
	int total_score=0;
	for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS; c++) {
		for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS-4; r++) {
			for (unsigned int f = 0; f<4; f++) {
				if (src -> gameBoard[r+f][c] == player2) {
					col_score += 1;
				} else if (src -> gameBoard[r+f][c] == player1) {
					col_score -= 1;
				}
			}
			total_score += singleScore(col_score);
		}
	}
	return total_score;

}

int calcBoadDiagonals(SPFiarGame* src){

}



#endif
