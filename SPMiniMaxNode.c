#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

/**
 * Given a game state, this function gives a score tag according to the
 * disks of each player.
 *
 * @param src - The current game state
 * @param player1 - player 1's symbol
 * @param player2 - player 2's symbol
 * @return
 * The function returns the total score of the given board.
 */
int calcBoardScore(SPFiarGame* src,  char player1, char player2){
	return calcBoadRows(src) +\
		calcBoadCols(src) +\
		calcBoadDiagonals(src)
}

/**
 * Given a score, this function returns the actual
 * value to add according to a weight vector: {−5, −2, −1,1,2,5}
 *
 * @param score - the calculated score of a foursome.
 * @return
 * The matching value according to the weigh vector.
 */
int singleScore(int score){
	//If score is 0 return 0
	if (score == 0) {
		return 0;
	}

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

/**
 * Given a game state, this function gives a score tag according to the
 * disks of each player by lines.
 *
 * @param src - The current game state
 * @param player1 - player 1's symbol
 * @param player2 - player 2's symbol
 * @return
 * The function returns the lines score of the given board.
 */
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
			row_score = 0;
		}
	}
	return total_score;
}

/**
 * Given a game state, this function gives a score tag according to the
 * disks of each player by columns.
 *
 * @param src - The current game state
 * @param player1 - player 1's symbol
 * @param player2 - player 2's symbol
 * @return
 * The function returns the columns score of the given board.
 */
int calcBoadCols(SPFiarGame* src, char player1, char player2){
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
			col_score = 0;
		}
	}
	return total_score;

}

/**
 * Given a game state, this function gives a score tag according to the
 * disks of each player by diagonals.
 *
 * @param src - The current game state
 * @param player1 - player 1's symbol
 * @param player2 - player 2's symbol
 * @return
 * The function returns the columns score of the given board.
 */
int calcBoadDiagonals(SPFiarGame* src, char player1, char player2){
	int diag_score=0;
	int total_score;
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS-4; r++) {
		for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS-4; c++) {
			for (unsigned int f = 0; f<4; f++) {
				if (src -> gameBoard[r+f][c+f] == player2) {
					diag_score += 1;
				} else if (src -> gameBoard[r][c+f] == player1) {
					diag_score -= 1;
				}
			}
			total_score += singleScore(diag_score);
			diag_score = 0;
		}
	}
	return total_score;

}


#endif
