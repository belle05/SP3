#include <stdio.h>
#include <stdlib.h>
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"

MiniMaxNode* nodeCreate(SPFiarGame *game) {
	MiniMaxNode *myNode;
	myNode = (MiniMaxNode*)malloc(sizeof(myNode));
	if (myNode == NULL) {
			return NULL;
		}
	myNode -> myGame = game;
	for (unsigned i=0; i<SP_FIAR_GAME_N_COLUMNS; i++) {
		myNode -> childs[i] = NULL;
	}
	myNode -> score = calcBoardScore(game);
	myNode -> minChildIndex = -2;
	myNode -> maxChildIndex = -2;
	myNode -> minChildScore = myNode -> score;
	myNode -> maxChildScore = myNode -> score;
	return myNode;
}

MiniMaxNode* copyNode(MiniMaxNode *myNode) {
	MiniMaxNode *newNode;
	newNode = (MiniMaxNode*)malloc(sizeof(newNode));
	if (newNode == NULL) {
		return NULL;
	}
	SPFiarGame *copyGame;
	copyGame = spFiarGameCopy((myNode -> myGame));
	newNode -> myGame = copyGame;
	for (unsigned i=0; i<SP_FIAR_GAME_N_COLUMNS; i++) {
		newNode -> childs[i] = myNode -> childs[i];
	}
	newNode -> score = myNode -> score;
	newNode -> minChildIndex = myNode -> minChildIndex;
	newNode -> maxChildIndex = myNode -> maxChildIndex;
	newNode -> minChildScore = myNode -> minChildScore;
	newNode -> maxChildScore = myNode -> maxChildScore;
	return newNode;
}

void MiniMaxDelete(MiniMaxNode *myNode) {
	if (myNode == NULL) {
		return;
	}
	if (ifLeaf(myNode)) {
		spFiarGameDestroy(myNode -> myGame);
		free(myNode);
		return;
	}
	for (unsigned i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
		MiniMaxDelete(myNode -> childs[i]);
	}
	free(myNode);
}


bool ifLeaf(MiniMaxNode *myNode) {
	if (myNode == NULL) {
		return false;
	}
	bool allNULL = true;
	for (unsigned i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
		if (myNode -> childs[i] != NULL){
			allNULL = false;
		}
	}
	if (allNULL == true) {
		 return true;
	}
	else {
		return false;
	}
}



bool updateMiniMaxNode(MiniMaxNode *myNode) {
	if (myNode == NULL) {
		return false;
	}
	for (int i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
		if (myNode -> childs[i] == NULL){
			continue;
		}
		else if ((myNode -> childs[i] -> score) > (myNode -> maxChildScore)) {
			myNode -> maxChildScore = myNode -> childs[i] -> score;
			myNode -> maxChildIndex = i;
		}
		else if (((myNode -> childs[i]) -> score == (myNode -> maxChildScore)) && (i < (myNode -> maxChildIndex))) {
			myNode -> maxChildIndex = i;
		}
		else if ((myNode -> childs[i] -> score) < (myNode -> minChildScore)) {
			myNode -> minChildScore = myNode -> childs[i] -> score;
			myNode -> minChildIndex = i;
		}
		else if (((myNode -> childs[i]) -> score == (myNode -> minChildScore)) && (i < (myNode -> minChildIndex))) {
			myNode -> minChildIndex = i;
		}
	}
	return true;
}

bool createNewTreeFromNode(MiniMaxNode *myNode, int level) {
	bool success = false;

	if (level <0) {
		return false;
	}
	else if (level == 0) {
		return true;
	}
	if (myNode == NULL) {
		 return false;
	}
	else if (ifLeaf(myNode)) {
		success = createNodesForChilds(myNode);
		for (int i = 0; i<=level; i++) {
			if (success) {
				success = createNewTreeFromNode(myNode -> childs[i], level-1);
			}
		}
		updateMiniMaxNode(myNode);
		return success;
	}
	return 1;
}

bool createNodesForChilds(MiniMaxNode *myNode) {
	if (myNode == NULL) {
		return false;
	}
	else if (ifLeaf(myNode)){
		for (unsigned int i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
				SPFiarGame *copyGame;
				copyGame = spFiarGameCopy(myNode -> myGame);
				myNode -> childs[i] = nodeCreate(copyGame);
		}
		return true;
	}
	else {
		return false;
	}
}
MiniMaxNode* moveForward(MiniMaxNode *myNode, int index) {
	MiniMaxNode *newNode;
	if (index < 0 || index >= SP_FIAR_GAME_N_COLUMNS) {
		return NULL;
	}
	if (myNode == NULL) {
		 return NULL;
	}
	newNode =  myNode -> childs[index];
	if (newNode == NULL) {
		 return NULL;
	}
	myNode -> childs[index] = NULL;
	createNewTreeFromNode(newNode,newNode -> myGame -> level);
	MiniMaxDelete(myNode);
	return newNode;
}

/**
*bool updateMiniMaxRecursivlly(MiniMaxNode *myNode, int level) {
*	if (level <0) {
*		return false;
*	}
*	else if (level == 0) {
*		return true;
*	}
*	else if (isLeaf(myNode)) {
*		for (unsigned i = 0; i<=level; i++) {
*			updateMiniMaxRecursivlly(myNode -> childs[i], level-1);
*		}
*		updateMiniMaxNode(myNode);
*		return true;
*		}
*}
*/

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
int calcBoardScore(SPFiarGame* src){
	return calcBoardRows(src) + calcBoardCols(src) + calcBoardDiagonals(src);
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
	return scores[score+3];
/** If the static cont won't work:
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
**/
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
int calcBoardRows(SPFiarGame* src){
	int row_score=0;
	int total_score;
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
		for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS-4; c++) {
			for (unsigned int f = 0; f<4; f++) {
				if (src -> gameBoard[r][c+f] == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
					row_score += 1;
				} else if (src -> gameBoard[r][c+f] == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
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
int calcBoardCols(SPFiarGame* src){
	int col_score=0;
	int total_score=0;
	for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS; c++) {
		for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS-4; r++) {
			for (unsigned int f = 0; f<4; f++) {
				if (src -> gameBoard[r+f][c] == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
					col_score += 1;
				} else if (src -> gameBoard[r+f][c] == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
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
int calcBoardDiagonals(SPFiarGame* src){
	int diag_score=0;
	int total_score;
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS-4; r++) {
		for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS-4; c++) {
			for (unsigned int f = 0; f<4; f++) {
				if (src -> gameBoard[r+f][c+f] == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
					diag_score += 1;
				} else if (src -> gameBoard[r][c+f] == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
					diag_score -= 1;
				}
			}
			total_score += singleScore(diag_score);
			diag_score = 0;
		}
	}
	return total_score;

}

