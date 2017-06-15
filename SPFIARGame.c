#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SPArrayList.h"
#include "SPFIARGame.h"

/**
 * Creates a new game with a specified history size. The history size is a
 * parameter which specifies the number of previous moves to store. If the number
 * of moves played so far exceeds this parameter, then first moves stored will
 * be discarded in order for new moves to be stored.
 *
 * @historySize - The total number of moves to undo,
 *                a player can undo at most historySizeMoves turns.
 * @return
 * NULL if either a memory allocation failure occurs or historySize <= 0.
 * Otherwise, a new game instant is returned.
 */
SPFiarGame* spFiarGameCreate(int historySize){
	SPFiarGame *game;
	game = (SPFiarGame *)malloc(sizeof(SPFiarGame));
	if ((historySize <= 0) || (game == NULL)) {
		return NULL;
	}

	game -> history = spArrayListCreate(historySize);
	game -> historySize = historySize;
	game -> currentPlayer =  SP_FIAR_GAME_PLAYER_1_SYMBOL;

	//Setting all GameBoard values to NULL
	for (unsigned int r=0; r< SP_FIAR_GAME_N_ROWS; r++){
		for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
			game -> gameBoard[r][c] = '\0';
		}
	}
	//Setting all collumns' sizes to 0
	for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
		game -> tops[c] = 0;
	}
	return game;
}

/**
 *	Creates a copy of a given game.
 *	The new copy has the same status as the src game.
 *
 *	@param src - the source game which will be copied
 *	@return
 *	NULL if either src is NULL or a memory allocation failure occurred.
 *	Otherwise, an new copy of the source game is returned.
 *
 */
SPFiarGame* spFiarGameCopy(SPFiarGame* src){
	if (src == NULL) {
		return NULL;
	}
	SPFiarGame *game = (SPFiarGame *)malloc(sizeof(SPFiarGame));
	//Set game status to be like src
	for (unsigned int r=0; r< SP_FIAR_GAME_N_ROWS; r++){
		for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
			game -> gameBoard[r][c] = src -> gameBoard[r][c];
		}
	}
	for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
		game -> tops[c] = src -> tops[c];
	}
	game -> currentPlayer = src -> currentPlayer;
	game -> historySize = src -> historySize;
	game -> history = spArrayListCopy(src -> history);
	return game;
}

/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void spFiarGameDestroy(SPFiarGame* src){
	if (src != NULL) {
		free(src);
	}
}

/**
 * Sets the next move in a given game by specifying column index. The
 * columns are 0-based and in the range [0,SP_FIAR_GAME_N_COLUMNS -1].
 *
 * @param src - The target game
 * @param col - The target column, the columns are 0-based
 * @return
 * SP_FIAR_GAME_INVALID_ARGUMENT - if src is NULL or col is out-of-range
 * SP_FIAR_GAME_INVALID_MOVE - if the given column is full.
 */
SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col){
	if ((src == NULL) || (col < 0) || (col >= SP_FIAR_GAME_N_COLUMNS)) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}
	if (!spFiarGameIsValidMove(src, col)) {
		return SP_FIAR_GAME_INVALID_MOVE;
	}
	src -> tops[col] = src -> tops[col] + 1;
	src -> gameBoard[src -> tops[col]][col] = src -> currentPlayer;
	spArrayListAddFirst(src -> history, col);
	return SP_FIAR_GAME_SUCCESS;
}

/**
 * Checks if a disk can be put in the specified column.
 *
 * @param src - The source game
 * @param col - The specified column
 * @return
 * true  - if the a disc can be put in the target column
 * false - otherwise.
 */
bool spFiarGameIsValidMove(SPFiarGame* src, int col){
	int sizeOfCol = src -> tops[col];
	if (sizeOfCol == SP_FIAR_GAME_N_COLUMNS-1) {
		return false;
	}
	return true;
}

/**
 * Removes a disc that was put in the previous move and changes the current
 * player's turn. If the user invoked this command more than historySize times
 * in a row then an error occurs.
 *
 * @param src - The source game
 * @return
 * SP_FIAR_GAME_INVALID_ARGUMENT - if src == NULL
 * SP_FIAR_GAME_NO_HISTORY       - if the user invoked this function more then
 *                                 historySize in a row.
 * SP_FIAR_GAME_SUCCESS          - on success. The last disc that was put on the
 *                                 board is removed and the current player is changed
 */
SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src){
	bool success = false;
	if (src == NULL) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	} else if (src -> history -> actualSize == 0) {
		return SP_FIAR_GAME_NO_HISTORY;
	}
	success = spFiarGameRemoveDisc(src, spArrayListGetAt(src -> history, 0));
	if (success) {
		spArrayListRemoveAt(src -> history, 0);
	}
	return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameRemoveDisc(SPFiarGame* src, int col){
	if (src -> gameBoard[col] == 0) {
		return false;
	}
	src -> gameBoard[src -> tops[col]][col] = '\0';
	src -> tops[col] = src -> tops[col] - 1;
	return true;
}

/**
 * On success, the function prints the board game. If an error occurs, then the
 * function does nothing. The characters 'X' and 'O' are used to represent
 * the discs of player 1 and player 2, respectively.
 *
 * @param src - the target game
 * @return
 * SP_FIAR_GAME_INVALID_ARGUMENT - if src==NULL
 * SP_FIAR_GAME_SUCCESS - otherwise
 *
 */
SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src){
	if (src == NULL) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
		printf("|");
		for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
			printf(" %c", src -> gameBoard[r][c]);
		}
		printf(" |\n");
	}
	printf("-----------------\n ");
	for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
		printf(" %d", c);
	}
	return SP_FIAR_GAME_SUCCESS;
}

/**
 * Returns the current player of the specified game.
 * @param src - the source game
 * @return
 * SP_FIAR_GAME_PLAYER_1_SYMBOL - if it's player one's turn
 * SP_FIAR_GAME_PLAYER_2_SYMBOL - if it's player two's turn
 * SP_FIAR_GAME_EMPTY_ENTRY     - otherwise
 */
char spFiarGameGetCurrentPlayer(SPFiarGame* src){
	return src -> currentPlayer;
}
/**
* Checks if there's a winner in the specified game status. The function returns either
* SP_FIAR_GAME_PLAYER_1_SYMBOL or SP_FIAR_GAME_PLAYER_2_SYMBOL in case there's a winner, where
* the value returned is the symbol of the winner. If the game is over and there's a tie
* then the value SP_FIAR_GAME_TIE_SYMBOL is returned. in any other case the null characters
* is returned.
* @param src - the source game
* @return
* SP_FIAR_GAME_PLAYER_1_SYMBOL - if player 1 won
* SP_FIAR_GAME_PLAYER_2_SYMBOL - if player 2 won
* SP_FIAR_GAME_TIE_SYMBOL - If the game is over and there's a tie
* null character - otherwise
*/
char spFiarCheckWinner(SPFiarGame* src){
	bool playerOneWon = spFiarIsWinner(src,SP_FIAR_GAME_PLAYER_1_SYMBOL);
	bool playerTwoWon = spFiarIsWinner(src,SP_FIAR_GAME_PLAYER_2_SYMBOL);
	if ( (playerOneWon == true) && (playerTwoWon == false) ) {
		return SP_FIAR_GAME_PLAYER_1_SYMBOL;
	}
	else if ( (playerOneWon == false) && (playerTwoWon == true) ) {
		return SP_FIAR_GAME_PLAYER_2_SYMBOL;
	}
	else if ((spFiarIsTableFull(src)) && (playerOneWon == false) && (playerTwoWon == false) ) {
		return SP_FIAR_GAME_TIE_SYMBOL;
	}
	else {
		return '\0';
	}
}
		 

/**
* Checks if player has won the game.
* @param src - the source game, the player's simbole as char.
* @return
* true - if the specified player has won.
* false - otherwise.
*/
bool spFiarIsWinner(SPFiarGame* src, char player){
	if (spFiarIsCol(src,player) || spFiarIsRow(src,player) || spFiarIsDiag(src,player)) {
		return true;
	}
	return false;
}

/**
* Checks if the game board is full.
* @param src - the source game.
* @return
* true - if the specified game board is full.
* false - otherwise.
*/
bool spFiarIsTableFull(SPFiarGame* src){
	int takenSpots = SP_FIAR_GAME_N_COLUMNS * SP_FIAR_GAME_N_ROWS;
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
		for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
			if (src -> gameBoard[r][c] == '\0') {
				takenSpots = takenSpots - 1;
			}
		}
	}
	if (takenSpots == 0) {
		return true;
	}
	return false;
}

bool spFiarIsCol(SPFiarGame* src, char player){
	int counter=0;
	for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS; c++) {
		for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
			if (src -> gameBoard[r][c] == player){
				counter += 1;
				if (counter == 4){
					return true;
				}
			}
		}
		counter = 0;
	}
	return false;
}

bool spFiarIsRow(SPFiarGame* src, char player){
	int counter=0;
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
		for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS; c++) {
			if (src -> gameBoard[r][c] == player){
				counter += 1;
				if (counter == 4){
					return true;
				}
			}
		}
		counter = 0;
	}
	return false;
}

bool spFiarIsDiag(SPFiarGame* src, char player){
	int counter = 0;
	for (unsigned int s = 0; s<SP_FIAR_GAME_N_COLUMNS+SP_FIAR_GAME_N_ROWS-1; s++) {
		for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS; c++) {
			for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
				if (c+r == s) {
					if (src -> gameBoard[r][c] == player){
						counter+=1;
						if (counter == 4) {
							return true;
						}
					}
				}
			}
		}
		counter = 0;
	}
	counter = 0;
	int max = 0;
	if (SP_FIAR_GAME_N_COLUMNS >= SP_FIAR_GAME_N_ROWS) {
		max = SP_FIAR_GAME_N_COLUMNS;
	}
	else {
		max = SP_FIAR_GAME_N_ROWS;
	}
	for (int s = 0; s<max; s++) {
                for (int c = 0; c<SP_FIAR_GAME_N_COLUMNS; c++) {
                        for (int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
                                if (c-r == s) {
                                        if (src -> gameBoard[r][c] == player){
                                                counter+=1;
                                                if (counter == 4) {
                                                        return true;
                                                }
                                        }
                                }
                        }
                }
                counter = 0;
        }
	for (int s = 0; s<max; s++) {
                for (int c = 0; c<SP_FIAR_GAME_N_COLUMNS; c++) {
                        for (int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
                                if (r-c == s) {
                                        if (src -> gameBoard[r][c] == player){
                                                counter+=1;
                                                if (counter == 4) {
                                                        return true;
                                                }
                                        }
                                }
                        }
                }
                counter = 0;
        }
	return false;
}

