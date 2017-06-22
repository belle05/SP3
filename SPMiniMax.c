#include "SPMiniMax.h"
#include "SPFIARGame.h"
#include "SPMiniMaxNode.h"
#include <stdio.h>
#include <stdlib.h>
int spMinimaxSuggestMove(SPFiarGame* currentGame,
                         unsigned int maxDepth){
    if (currentGame == NULL || maxDepth<=0) {
        return -1;
    }
    MiniMaxNode *miniMaxNode = NULL;
    miniMaxNode = nodeCreate(spFiarGameCopy(currentGame));
	if (miniMaxNode == NULL) {
		return 3000;
	}
    if(createNewTreeFromNode(miniMaxNode, maxDepth) == false) {
		return 3000;
	}
    int move = getBestMove(miniMaxNode);
    MiniMaxDelete(miniMaxNode);
    return move;

}
