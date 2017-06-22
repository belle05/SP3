#include <stdio.h>
#include <stdlib.h>
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"

MiniMaxNode* nodeCreate(SPFiarGame *game) {
	MiniMaxNode *myNode;
	myNode = calloc(1, sizeof(MiniMaxNode));
	if (myNode == NULL) {
			printf("Error: nodeCreate has failed\n");
			return NULL;
		}
	myNode -> myGame = game;
	for (unsigned i=0; i<SP_FIAR_GAME_N_COLUMNS; i++) {
		myNode -> childs[i] = NULL;
	}
	myNode -> score = calcBoardScore(game);
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

bool MiniMaxDelete(MiniMaxNode *myNode) {
	if (myNode == NULL) {
		return false;
	}
    for (int i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
        if (myNode->childs[i] != NULL){
        MiniMaxDelete(myNode->childs[i]);
    }
    }
	if (myNode -> myGame != NULL) {
        spFiarGameDestroy(myNode -> myGame);
	}
	free(myNode);
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
		if ((myNode -> childs[i] -> maxChildScore) < (myNode -> minChildScore)) {
			myNode -> minChildScore = myNode -> childs[i] -> maxChildScore;
			myNode -> minChildIndex = i;
		}
	}
	return true;
}

bool createNewTreeFromNode(MiniMaxNode *myNode, int level) {
	if (level <0) {
		return false;
	}
	else if (level == 0) {
		return true;
	}
	if (myNode == NULL) {
		 return false;
	}
    if(spFiarCheckWinner(myNode->myGame)==0) {
		SPFiarGame *newGame;
		for (int i = 0; i < SP_FIAR_GAME_N_COLUMNS; i++) {
			if (spFiarGameIsValidMove(myNode->myGame, i)) {
				newGame = spFiarGameCopy(myNode->myGame);
				if (newGame == NULL) {
					return false;
				}
				spFiarGameSetMove(newGame, i);
				myNode->childs[i] = nodeCreate(newGame);
				if (myNode->childs[i] == NULL) {
					return false;
				}
				if (newGame->currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
					newGame->currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
				} else {
					newGame->currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
				}
				createNewTreeFromNode(myNode->childs[i], level - 1);
			}
		}
	}
	return true;
}

MiniMaxNode* moveForward(MiniMaxNode *myNode, int index) {
	if (index < 0 || index >= SP_FIAR_GAME_N_COLUMNS) {
		return NULL;
	}
	if (myNode == NULL) {
		 return NULL;
	}
	createNewTreeFromNode(myNode, myNode -> myGame -> level);
	return myNode;
}

int singleScore(int score){
    if(score == -4){
        return 30000;
    }
    if(score == 4){
        return -30000;
    }
	return scores[score+3];
}

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

int calcBoardScore(SPFiarGame* src) {
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

