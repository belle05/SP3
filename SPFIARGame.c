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
//TODO - add history var

	char board[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS];
	int tops[SP_FIAR_GAME_N_COLUMNS];

	SPFiarGame *game = (SPFiarGame *)malloc(sizeof(SPFiarGame));
	sp_

	if ((historySize<=0) || (SPFiarGame == NULL)) {
		return NULL;
	}

	SPFiarGame -> historySize = historySize;
	SPFiarGame -> currentPlayer =  SP_FIAR_GAME_PLAYER_1_SYMBOL;

	//Setting all GameBoard values to NULL
	for (unsigned int r=0; r< SP_FIAR_GAME_N_ROWS; r++){
		for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
			board[r][c] = '\0';
		}
	}
	SPFiarGame -> gameBoard = board;
	//Setting all collumns' sizes to 0
	for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
		tops[c] = 0;
	}
	SPFiarGame -> tops = tops;
	return SPFiarGame;
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
//TODO - add history var

	if (src == NULL) {
		return NULL;
	}
	sp_fiar_game_t *SPFiarGame = (sp_fiar_game_t *)malloc(sizeof(sp_fiar_game_t));
	//Set game status to be like src
	SPFiarGame -> gameBoard = src -> gameBoard;
	SPFiarGame -> tops = src -> tops;
	SPFiarGame -> currentPlayer = src -> currentPlayer;
	SPFiarGame -> historySize = src -> historySize;
	return SPFiarGame;
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
//TODO - update history

	if ((src == NULL) or (col < 0) or (col >= SP_FIAR_GAME_N_COLUMNS)) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}
	if (spFiarGameIsValidMove(src, col)) {
		return SP_FIAR_GAME_INVALID_MOVE;
	}
	src -> tops[col] = sizeOfCol + 1;
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
//TODO
	if (src == NULL) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}
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
		printf('|');
		for (unsigned int c=0; c< SP_FIAR_GAME_N_COLUMNS; c++) {
			printf(" %c", src -> gameBoard[r][c]);
		}
		printf(" |\n");
	}
	printf("-----------------\n ")
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
}

/**
* Checks if player has won the game.
* @param src - the source game, the player's simbole as char.
* @return
* true - if the specified player has won.
* false - otherwise.
*/
bool spFiarIsWinner(SPFiarGame* src, char player){
}

/**
* Checks if the game board is full.
* @param src - the source game.
* @return
* true - if the specified game board is full.
* false - otherwise.
*/
bool spFiarIsTableFull(SPFiarGame* src){
	int fullTableSize = SP_FIAR_GAME_N_COLUMNS * SP_FIAR_GAME_N_ROWS;
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
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_COLUMNS; r++) {
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
}

bool spFiarIsRow(SPFiarGame* src, char player){
	int counter=0;
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
		for (unsigned int r = 0; r<SP_FIAR_GAME_N_COLUMNS; r++) {
			if (src -> gameBoard[r][c] == player){
				counter += 1;
				if (counter == 4){
					return true;
				}
			}
		}
		counter = 0;
	}
}

bool spFiarIsDiag(SPFiarGame* src, char player){
}

