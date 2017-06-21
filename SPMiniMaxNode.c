#include <stdio.h>
#include <stdlib.h>
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"

MiniMaxNode* nodeCreate(SPFiarGame *game) {
	MiniMaxNode *myNode;
	myNode = calloc(1, sizeof(MiniMaxNode));
	if (myNode == NULL) {
			return NULL;
		}
	myNode -> myGame = game;
	for (unsigned i=0; i<SP_FIAR_GAME_N_COLUMNS; i++) {
		myNode -> childs[i] = NULL;
	}
	myNode -> score = calcBoardScore2(game);
	myNode -> minChildIndex = -2;
	myNode -> maxChildIndex = -2;
	myNode -> minChildScore = 200000;
	myNode -> maxChildScore = -200000;
	return myNode;
}

int getBestMove(MiniMaxNode *myNode){
    updateScores(myNode);

    if(myNode->myGame->currentPlayer == SP_FIAR_GAME_PLAYER_2_SYMBOL){
        int max = -200000;
        int index = -1;
        for(int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++){
            printf("%d\n",myNode -> childs[i]->score);
            if(myNode -> childs[i] != NULL && myNode -> childs[i]->score > max){
                max = myNode -> childs[i]->score;
                index = i;
            }
        }
        return index;
    }else{
        int min = 200000;
        int index = -1;
        for(int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++){
            printf("%d\n",myNode -> childs[i]->score);
            if(myNode -> childs[i] != NULL && myNode -> childs[i]->score < min){
                min = myNode -> childs[i]->score;
                index = i;
            }
        }
        return index;
    }
}

void updateScores(MiniMaxNode *myNode){
    if(myNode == NULL){
        return;
    }
    for(int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++){
        updateScores(myNode->childs[i]);
    }

    if(myNode->myGame->currentPlayer == SP_FIAR_GAME_PLAYER_2_SYMBOL){
        int max = -200000;
        for(int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++){
            if(myNode -> childs[i] != NULL && myNode -> childs[i]->score > max){
                max = myNode -> childs[i]->score;
            }
        }
        if(max != -200000){
            myNode->score = max;
        }
    }else{
        int min = 200000;
        for(int i = 0; i<SP_FIAR_GAME_N_COLUMNS; i++){
            if(myNode -> childs[i] != NULL && myNode -> childs[i]->score < min){
                min = myNode -> childs[i]->score;
            }
        }
        if(min != 200000){
            myNode->score = min;
        }
    }
}

//MiniMaxNode* copyNode(MiniMaxNode *myNode) {
//	MiniMaxNode *newNode;
//	newNode = (MiniMaxNode*)malloc(sizeof(MiniMaxNode));
//	if (newNode == NULL) {
//		return NULL;
//	}
//	SPFiarGame *copyGame;
//	copyGame = spFiarGameCopy((myNode -> myGame));
//	newNode -> myGame = copyGame;
//	for (unsigned i=0; i<SP_FIAR_GAME_N_COLUMNS; i++) {
//		newNode -> childs[i] = myNode -> childs[i];
//	}
//	newNode -> score = myNode -> score;
//	newNode -> minChildIndex = myNode -> minChildIndex;
//	newNode -> maxChildIndex = myNode -> maxChildIndex;
//	newNode -> minChildScore = myNode -> minChildScore;
//	newNode -> maxChildScore = myNode -> maxChildScore;
//	return newNode;
//}

bool MiniMaxDelete(MiniMaxNode *myNode) {
	if (myNode == NULL) {
		return false;
	}
//	if (ifLeaf(myNode)) {
//		printf("This node is a leaf\n");
//		if (myNode -> myGame != NULL) {
//			spFiarGameDestroy(myNode -> myGame);
//			printf("GameDestroyed..\n");
//		}
//		free(myNode);
//		return true;
//	}else {

    for (int i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
        if (myNode->childs[i] != NULL){
        MiniMaxDelete(myNode->childs[i]);
    }
    }
	if (myNode -> myGame != NULL) {
        spFiarGameDestroy(myNode -> myGame);
	}
	free(myNode);
//	}
	return true;
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
		if ((myNode -> childs[i] -> minChildScore) > (myNode -> maxChildScore)) {
			myNode -> maxChildScore = myNode -> childs[i] -> minChildScore;
			myNode -> maxChildIndex = i;
		}
//		if (((myNode -> childs[i]) -> score == (myNode -> maxChildScore)) && (i < (myNode -> maxChildIndex))) {
//			myNode -> maxChildIndex = i;
//		}
		if ((myNode -> childs[i] -> maxChildScore) < (myNode -> minChildScore)) {
			myNode -> minChildScore = myNode -> childs[i] -> maxChildScore;
			myNode -> minChildIndex = i;
		}
//		if (((myNode -> childs[i]) -> score == (myNode -> minChildScore)) && (i < (myNode -> minChildIndex))) {
//			myNode -> minChildIndex = i;
//		}
	}
	return true;
}

bool createNewTreeFromNode(MiniMaxNode *myNode, int level) {
//	bool success = false;

	if (level <0) {
		return false;
	}
	else if (level == 0) {
		return true;
	}
	if (myNode == NULL) {
		 return false;
	}
	//if (ifLeaf(myNode)) {
//		createNodesForChilds(myNode);
	//}
    if(spFiarCheckWinner(myNode->myGame)==0){
	SPFiarGame *newGame;
	for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
	//	if (success) {
		if (spFiarGameIsValidMove(myNode -> myGame, i)) {
			newGame = spFiarGameCopy(myNode -> myGame);
			spFiarGameSetMove(newGame, i);
			myNode -> childs[i] = nodeCreate(newGame);
            if(newGame->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL){
                newGame->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
            }else {
                newGame->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
            }
            createNewTreeFromNode(myNode -> childs[i], level-1);
		}
	//	}
	}}
//	updateMiniMaxNode(myNode);
//	printf("updated minimax node at level %d\n", level);
	//return success;
	return 1;
}

//bool createNodesForChilds(MiniMaxNode *myNode) {
//	if (myNode == NULL) {
//		return false;
//	}
//	//if (ifLeaf(myNode)){
//	for (unsigned int i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
//			if (myNode -> myGame == NULL) {
//				printf("game is null");
//			}
//			myNode -> childs[i] = nodeCreate(myNode -> myGame);
//	}
//	return true;
//	//}
//	//else {
//	//	return false;
//	//}
//}
MiniMaxNode* moveForward(MiniMaxNode *myNode, int index) {
//	SPFiarGame *newGame;
//	MiniMaxNode *newNode;
	if (index < 0 || index >= SP_FIAR_GAME_N_COLUMNS) {
		return NULL;
	}
	if (myNode == NULL) {
		 return NULL;
	}
//	newNode =  myNode -> childs[index];
//	if (newNode == NULL) {
//		 return NULL;
//	}
//	myNode -> childs[index] = NULL;
//	newGame = spFiarGameCopy(myNode -> myGame);
//	printf("CopiedGame");
//	newNode = nodeCreate(newGame);
//	printf("Created new node\n");
	createNewTreeFromNode(myNode, myNode -> myGame -> level);
	printf("Created new tree\n");
//	MiniMaxDelete(myNode);
//	printf("Deleted old node\n");
	return myNode;
}
//MiniMaxNode* moveForward(MiniMaxNode *myNode, int index) {
//	MiniMaxNode *newNode;
//	if (index < 0 || index >= SP_FIAR_GAME_N_COLUMNS) {
//		return NULL;
//	}
//	if (myNode == NULL) {
//		 return NULL;
//	}
//	SPFiarGame newGame = myNode -> myGame;
//	newNode =  myNode -> childs[index];
//	newNode -> myGame -> level = (myNode -> myGame -> level);
//	myNode -> childs[index] = NULL;
//	if (newNode == NULL) {
//		 return NULL;
//	}
//	myNode -> childs[index] = NULL;
//	newGame = spFiarGameCopy(myNode -> myGame);
//	printf("CopiedGame");
//	newNode = nodeCreate(newGame);
//	printf("Created new node\n");
//	printf("before deleting myNode\n");
//	MiniMaxDelete(myNode);
//	printf("after deleting myNode\n");
//	createNewTreeFromNode(newNode, newNode -> myGame -> level );
//	printf("Created new tree\n");
//	MiniMaxDelete(myNode);
//	printf("Deleted old node\n");
//	return myNode;
//}

 
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
    if(score == -4){
        return 30000;
    }
    if(score == 4){
        return -30000;
    }
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
	int total_score = 0;
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS; r++) {
		for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS-3; c++) {
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
		for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS-3; r++) {
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
	int total_score=0;
	for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS-3; r++) {
		for (unsigned int c = 0; c<SP_FIAR_GAME_N_COLUMNS-3; c++) {
			for (unsigned int f = 0; f<4; f++) {
				if (src -> gameBoard[r+f][c+f] == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
					diag_score += 1;
				} else if (src -> gameBoard[r+f][c+f] == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
					diag_score -= 1;
				}
			}
			total_score += singleScore(diag_score);
			diag_score = 0;
		}
	}
    diag_score = 0;
    for (unsigned int r = 0; r<SP_FIAR_GAME_N_ROWS-3; r++) {
        for (unsigned int c = 3; c<SP_FIAR_GAME_N_COLUMNS; c++) {
            for (unsigned int f = 0; f<4; f++) {
                if (src -> gameBoard[r+f][c-f] == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
                    diag_score += 1;
                } else if (src -> gameBoard[r+f][c-f] == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
                    diag_score -= 1;
                }
            }
            total_score += singleScore(diag_score);
            diag_score = 0;
        }
    }
	return total_score;

}

int calcBoardScore2(SPFiarGame* src) {
    int directions[] = {1,0,0,1,1,1,-1,1};
    int score = 0;

    int total_score = 0;
    for(int j = 0; j < 8; j+=2){
        for (int r = 0; r < SP_FIAR_GAME_N_ROWS; r++) {
            for (int c = 0; c < SP_FIAR_GAME_N_COLUMNS; c++) {
                if(r+directions[j]*3<SP_FIAR_GAME_N_ROWS && r+directions[j]*3>=0 && c+directions[j+1]*3<SP_FIAR_GAME_N_COLUMNS && c+directions[j+1]*3>=0) {
                    for (int f = 0; f < 4; f++) {
                        if (src->gameBoard[r + (directions[j]*f)][c + (directions[j+1]*f)] == SP_FIAR_GAME_PLAYER_2_SYMBOL) {
                            score += 1;
                        } else if (src->gameBoard[r + directions[j]*f][c + directions[j+1]*f] == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
                            score -= 1;
                        }
                    }
                }
                if(score == 4){
                    return 30000;
                }else if(score == -4){
                    return -30000;
                }
                total_score += scores[score+3];
                score = 0;
            }
        }
    }
    return total_score;
}

