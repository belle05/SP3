#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "SPArrayList.h"
#include "SPFIARGame.h"

SPFiarGame* spFiarGameCreate(int historySize){
	SPFiarGame *game;
	game = calloc(1, sizeof(SPFiarGame));
	if ((historySize <= 0) || (game == NULL)) {
		printf("Error: spFiarGameCreate has failed\n");
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

SPFiarGame* spFiarGameCopy(SPFiarGame* src){
	if (src == NULL) {
		return NULL;
	}
	SPFiarGame *game;
	game = calloc(1, sizeof(SPFiarGame));
	if (game == NULL) {
		printf("Error: spFiarGameCopy has failed\n");
		return NULL;
	}
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

void spFiarGameDestroy(SPFiarGame* src){
	if (src != NULL) {
		free(src);
	}
}

SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col){
	if ((src == NULL) || (col < 0) || (col >= SP_FIAR_GAME_N_COLUMNS)) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	}
	if (!spFiarGameIsValidMove(src, col)) {
		return SP_FIAR_GAME_INVALID_MOVE;
	}
	src -> gameBoard[src -> tops[col]][col] = src -> currentPlayer;
	src -> tops[col] = src -> tops[col] + 1;
	spArrayListAddFirst(src -> history, col);
	return SP_FIAR_GAME_SUCCESS;
}

bool spFiarGameIsValidMove(SPFiarGame* src, int col){
	int sizeOfCol = src -> tops[col];
	if (sizeOfCol == SP_FIAR_GAME_N_COLUMNS-1) {
		return false;
	}
	return true;
}

SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src){
	bool success = false;
	int discToRemove;
	bool userTurn = spArrayListSize(src -> history) % 2;
	if (src == NULL) {
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	} else if (spArrayListSize(src -> history) == 0) {
		return SP_FIAR_GAME_NO_HISTORY;
	} //undoing Computer's last move
	discToRemove = spArrayListGetAt(src -> history, 0);
	success = spFiarGameRemoveDisc(src, discToRemove);
	if (success) {
		if (userTurn) {
			printf("Remove disc: remove user's disc at column %d\n",discToRemove+1);
		} else {
			printf("Remove disc: remove computer's disc at column %d\n",discToRemove+1);
		}
		spArrayListRemoveFirst(src -> history);
		return SP_FIAR_GAME_SUCCESS;
	} //undoing user's last move
//	discToRemove = spArrayListGetAt(src -> history, 0);
//	success = spFiarGameRemoveDisc(src, discToRemove);
//	if (success) {
//		printf("Remove disc: remove user's disc at column %d\n",discToRemove+1);
//		spArrayListRemoveFirst(src -> history);
//		return SP_FIAR_GAME_SUCCESS;
//	}
	return SP_FIAR_GAME_INVALID_ARGUMENT;
}

bool spFiarGameRemoveDisc(SPFiarGame* src, int col){
	int colSize;
	if (src -> tops[col] == 0) {
		return false;
	}
	colSize = src -> tops[col];
	src -> gameBoard[colSize-1][col] = '\0';
	src -> tops[col] = colSize - 1;
	return true;
}

SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src){
	if(src == NULL)
		return SP_FIAR_GAME_INVALID_ARGUMENT;
	for (int r=SP_FIAR_GAME_N_ROWS-1; r>=0; r--){
		printf("|");
		for(int c=0; c<SP_FIAR_GAME_N_COLUMNS; c++){
			if (src -> gameBoard[r][c] == '\0') {
				printf("  ");
			}
			else {
				printf(" %c", src->gameBoard[r][c]);
			}
		}
		printf(" |\n");
	}
	printf("-----------------\n");
	printf("  1 2 3 4 5 6 7  \n");
	return SP_FIAR_GAME_SUCCESS;
}

char spFiarGameGetCurrentPlayer(SPFiarGame* src){
	return src -> currentPlayer;
}

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

bool spFiarIsWinner(SPFiarGame* src, char player){
	if (spFiarIsCol(src,player) || spFiarIsRow(src,player) || spFiarIsDiag(src,player)) {
		return true;
	}
	return false;
}

bool spFiarIsTableFull(SPFiarGame* src){
	for (int r = 0; r < SP_FIAR_GAME_N_ROWS; r++) {
		for (int c=0; c < SP_FIAR_GAME_N_COLUMNS; c++) {
			if (src -> gameBoard[r][c] == '\0') {
				return false;
			}
		}
	}
	return true;
}

bool spFiarIsCol(SPFiarGame* src, char player){
	for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS; c++) {
		for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS-4; r++) {
			if (src -> gameBoard[r][c] == player && src -> gameBoard[r+1][c] == player && src -> gameBoard[r+2][c] == player && src -> gameBoard[r+3][c] == player){
					return true;
			}
		}
	}
	return false;
}

bool spFiarIsRow(SPFiarGame* src, char player){
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
		for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS-4; c++) {
			if (src -> gameBoard[r][c] == player && src -> gameBoard[r][c+1] == player && src -> gameBoard[r][c+2] == player && src -> gameBoard[r][c+3] == player){
				return true;
			}
		}
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
