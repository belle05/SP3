#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_
#include <stddef.h>
#include "SPFIARGame.h"

/**we moved most functions to SPFIARGAME.h**/
/**
 * This functions update the scores of the tree of the root node given to her ( the tree of the node in the depth of the game level)
 * Then she does calculations on the data and gives you the best move according to minimax algorithm
 * @param myNode
 * @return the index of the best move
 */
int getBestMove(MiniMaxNode *myNode);

/**
 * this function updates the scores recursivly of all children in the tree of the root node.
 * @param myNode
 */
void updateScores(MiniMaxNode *myNode);

#endif
