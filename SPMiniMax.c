#include "SPMiniMax.h"
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
#include <stdio.h>
#include <stdlib.h>
int spMinimaxSuggestMove(SPFiarGame* currentGame,
                         unsigned int maxDepth){
    if (currentGame == NULL || maxDepth<=0) {
        return -1;
    }
    MiniMaxNode *miniMaxNode = NULL;
    miniMaxNode = nodeCreate(spFiarGameCopy(currentGame));
    createNewTreeFromNode(miniMaxNode, maxDepth);
    int move = getBestMove(miniMaxNode);
    printf("move=%d\n", move);
    MiniMaxDelete(miniMaxNode);
    //printf("move = %d\n",move);
    return move;

}