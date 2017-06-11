#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

/* struct that defines a MINIMAXNODE */
typedef struct MiniMaxNode {
	SPFiarGame *myGame;
	MiniMaxNode childs[SP_FIAR_GAME_N_COLUMNS];
	int score;
	int minChildIndex;
	int maxChildIndex;
	int minChildScore;
	int maxChildScore;
}MiniMaxNode;

/** creates an empty node.
* sets the game to be the user argument, the indexes if min/maxChild to be -2,
* sets the score to be the ##########, and sets the min/max child score to be the score of the new node.
* sets all the children of the new node to be NULL.
*@return
*the node that was created
*if the allocation is not succedd returns NULL
**/

MiniMaxNode* nodeCreate(SPFiarGame *game);

/** created a new node with the same parameters as the argument node.
*@return
*the copyNode as a MiniMaxNode
*NULL, if the allocation did not succeed.
**/

MiniMaxNode* copyNode(MiniMaxNode *myNode);

/** This function delets all node recursivelly from the node down the tree.
*It also free all the node and the nodes under it memory.
*If the node is NULL does nothing.
**/

MiniMaxMassage MiniMaxDelete(MiniMaxNode *myNode);

/** Checks if the node is a leaf.
*@return 
*if the node is NULL returns false.
*if all childrens are NULL returns true.
*otherwize returns false.
**/

bool ifLeaf(MiniMaxNode *myNode);

/** This function updates the node parameters.
*It updates the max child score by the highest score of its children,
*It updates the min child score by the lowest score.
*It it has the same score as other child and this is the maximum/munimum,
*it takes the lowest index.
*@return
*false if the node is NULL
*true otherwize.
**/

bool updateMiniMaxNode(MiniMaxNode *myNode);

/** Creates new tree from the node and the level of the game.
* Recursivly creates new nodes under the node it recivied in the depth of the level.
*It also update the score by the children score.
*@return
*true is she succedded
*flase if the level <0
**/

bool createNodesForChilds(MiniMaxNode *myNode);

/** creates new children for the node with the same game of the node.
*@return
*false, if the node == NULL or if its not a leaf.
*true, otherwise.
**/

bool createNodesForChilds(MiniMaxNode *myNode);

/** This function moving you to a selected child of the node.
*It delets the node and it's tree except from the selected child sub tree.
*It also created new level at the bottum.
*@return
*the selected child node (with its tree).
*NULL if the index is out of range.
**/

MiniMaxNode* moveForward(MiniMaxNode *myNode, int index);

/**This function adds level at the buttom of a tree
*if the node is NULL does nothing.
**/

void addLevel(MiniMaxNode *myNode);

/** This function recursivly updates all nodes in the tree according to the level of the tree.
*@return
*false, if the level <0
*true, otherwise.
**/

bool updateMiniMaxRecursivlly(MiniMaxNode *myNode, int level);

int calcBoardScore(SPFiarGame* src,  char player1, char player2);

int singleScore(int score);

int calcBoardRows(SPFiarGame* src, char player1, char player2);

int calcBoardCols(SPFiarGame* src);

int calcBoardDiagonals(SPFiarGame* src);

#endif
