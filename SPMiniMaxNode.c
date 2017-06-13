#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

static const int scores[] = {-5,-2,-1,0,1,2,5};

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
	/* TODO- update score*/
	myNode -> score = 65984328792;
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
	SPFIARGame *copyGame;
	copyGame = spFiarGameCopy(*(myNode -> myGame));
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
	if (isLeaf(myNode)) {
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
	if (allNULL == true) return true;
	else return false;
}



bool updateMiniMaxNode(MiniMaxNode *myNode) {
	if (myNode == NULL) {
			return false;
	}
	for (unsigned i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
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
	bool success = False;

	if (level <0) {
		return false;
	}
	else if (level == 0) {
		return true;
	}
	else if (isLeaf(myNode)) {
		success = createNodesForChilds(myNode);
		for (unsigned i = 0; i<=level; i++) {
			if (success) {
				success = createNewTreeFromNode(myNode -> childs[i], level-1);
			}
		}
		updateMiniMaxNode(myNode);
		return success;
	}
}

bool createNodesForChilds(MiniMaxNode *myNode) {
	if (myNode == NULL) {
		return false;
	}
	else if (isLeaf(myNode)){
		for (unsigned i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
				SPFIARGame *copyGame;
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
	MiniMaxNode *copiedNode;
	if (index < 0 || index >= SP_FIAR_GAME_N_COLUMNS) {
		return NULL;
	}
	copiedNode = copyNode(*(myNode -> childs[i]));
	miniMaxDelete(*myNode);
	addLevel(*copiedNode);
	updateMiniMaxRecursivelly(*copiedNode, copiedNode -> myGame -> level)
	return copyNode;
}

void addLevel(MiniMaxNode *myNode) {
	if (!myNode) {
		return;
	}
	else if (isLeaf(myNode)) {
		createNodesForChilds(myNode);
		return;
	}
	else {
		for (unsigned i = 0; i<SP_FIAR_GAME_N_COLUMNS;i++) {
			addLevel(*myNode);
		}
		return;
	}
}
bool updateMiniMaxRecursivlly(MiniMaxNode *myNode, int level) {
	if (level <0) {
			return false;
	}
	else if (level == 0) {
		return true;
	}
	else if (isLeaf(myNode)) {
		for (unsigned i = 0; i<=level; i++) {
			updateMiniMaxRecursivlly(myNode -> childs[i], level-1);
		}
		updateMiniMaxNode(myNode);
		return true;
		}
}
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
	return calcBoardRows(src) +\
		calcBoardCols(src) +\
		calcBoardDiagonals(src)
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
int calcBoardRows(SPFiarGame* src, char player1, char player2){
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
int calcBoardCols(SPFiarGame* src, char player1, char player2){
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
int calcBoardDiagonals(SPFiarGame* src, char player1, char player2){
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
