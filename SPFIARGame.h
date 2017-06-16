#ifndef SPFIARGAME_H_
#define SPFIARGAME_H_
#include <stdbool.h>
#include "SPArrayList.h"
#include <stddef.h>

/**
 * SPFIARGame Summary:
 *
 * A container that represents a classic connect-4 game, a two players 6 by 7
 * board game (rows X columns). The container supports the following functions.
 *
 * spFiarGameCreate           - Creates a new game board
 * spFiarGameCopy             - Copies a game board
 * spFiarGameDestroy          - Frees all memory resources associated with a game
 * spFiarGameSetMove          - Sets a move on a game board
 * spFiarGameIsValidMove      - Checks if a move is valid
 * spFiarGameUndoPrevMove     - Undoes previous move made by the last player
 * spFiarGamePrintBoard       - Prints the current board
 * spFiarGameGetCurrentPlayer - Returns the current player
 *
 */

//Definitions
#define SP_FIAR_GAME_SPAN 4
#define SP_FIAR_GAME_N_ROWS 6
#define SP_FIAR_GAME_N_COLUMNS 7
#define SP_FIAR_GAME_PLAYER_1_SYMBOL 'X'
#define SP_FIAR_GAME_PLAYER_2_SYMBOL 'O'
#define SP_FIAR_GAME_TIE_SYMBOL '-'
#define SP_FIAR_GAME_EMPTY_ENTRY ' '

static const int scores[] = {-5,-2,-1,0,1,2,5};

typedef struct sp_fiar_game_t {
	char gameBoard[SP_FIAR_GAME_N_ROWS][SP_FIAR_GAME_N_COLUMNS];
	int tops[SP_FIAR_GAME_N_COLUMNS];
	char currentPlayer;
	int level;
	int historySize;
	SPArrayList *history;
	//You May add any fields you like
} SPFiarGame;

/**
 * Type used for returning error codes from game functions
 */
typedef enum sp_fiar_game_message_t {
	SP_FIAR_GAME_INVALID_MOVE,
	SP_FIAR_GAME_INVALID_ARGUMENT,
	SP_FIAR_GAME_NO_HISTORY,
	SP_FIAR_GAME_SUCCESS,
//You may add any message you like
} SP_FIAR_GAME_MESSAGE;

/* struct that defines a MINIMAXNODE */
typedef struct MiniMaxNode MiniMaxNode;

struct MiniMaxNode {
	SPFiarGame *myGame;
	int score;
	int minChildIndex;
	int maxChildIndex;
	int minChildScore;
	int maxChildScore;
	MiniMaxNode *childs[SP_FIAR_GAME_N_COLUMNS];
};


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
SPFiarGame* spFiarGameCreate(int historySize);

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
SPFiarGame* spFiarGameCopy(SPFiarGame* src);

/**
 * Frees all memory allocation associated with a given game. If src==NULL
 * the function does nothing.
 *
 * @param src - the source game
 */
void spFiarGameDestroy(SPFiarGame* src);

/**
 * Sets the next move in a given game by specifying column index. The
 * columns are 0-based and in the range [0,SP_FIAR_GAME_N_COLUMNS -1].
 *
 * @param src - The target game
 * @param col - The target column, the columns are 0-based
 * @return
 * SP_FIAR_GAME_INVALID_ARGUMENT - if src is NULL or col is out-of-range
 * SP_FIAR_GAME_INVALID_MOVE - if the given column is full.
 * SP_FIAR_GAME_SUCCESS - otherwise
 */
SP_FIAR_GAME_MESSAGE spFiarGameSetMove(SPFiarGame* src, int col);

/**
 * Checks if a disk can be put in the specified column.
 *
 * @param src - The source game
 * @param col - The specified column
 * @return
 * true  - if the a disc can be put in the target column
 * false - otherwise.
 */
bool spFiarGameIsValidMove(SPFiarGame* src, int col);

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
SP_FIAR_GAME_MESSAGE spFiarGameUndoPrevMove(SPFiarGame* src);


bool spFiarGameRemoveDisc(SPFiarGame* src, int col);
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
SP_FIAR_GAME_MESSAGE spFiarGamePrintBoard(SPFiarGame* src);

/**
 * Returns the current player of the specified game.
 * @param src - the source game
 * @return
 * SP_FIAR_GAME_PLAYER_1_SYMBOL - if it's player one's turn
 * SP_FIAR_GAME_PLAYER_2_SYMBOL - if it's player two's turn
 * SP_FIAR_GAME_EMPTY_ENTRY     - otherwise
 */
char spFiarGameGetCurrentPlayer(SPFiarGame* src);

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
char spFiarCheckWinner(SPFiarGame* src);

/**
* Checks if player has won the game.
* @param src - the source game
* @return
* true - if the specified player has won.
* false - otherwise.
*/
bool spFiarIsWinner(SPFiarGame* src, char player);

/**
* Checks if the game board is full.
* @param src - the source game.
* @param player - the player's simbole as char.
* @return
* true - if the specified game board is full.
* false - otherwise.
*/
bool spFiarIsTableFull(SPFiarGame* src);

/**
* Checks if player has got a winning col.
* @param src - the source game
* @param player - the player's simbole as char.
* @return
* true - if the specified player has won.
* false - otherwise.
*/
bool spFiarIsCol(SPFiarGame* src, char player);

/**
* Checks if player has got a winning row.
* @param src - the source game
* @param player - the player's simbole as char.
* @return
* true - if the specified player has won.
* false - otherwise.
*/
bool spFiarIsRow(SPFiarGame* src, char player);

/**
* Checks if player has got a winning diagonal.
* @param src - the source game
* @param player - the player's simbole as char.
* @return
* true - if the specified player has won.
* false - otherwise.
*/
bool spFiarIsDiag(SPFiarGame* src, char player);
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

void MiniMaxDelete(MiniMaxNode *myNode);

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
/** creates new tree (in the level depth) for a node, and update it's parameters as well
*@return:
*true, is succeeded
*false if node == NULL or if level<0
**/
bool createNewTreeFromNode(MiniMaxNode *myNode, int level);

/** This function moving you to a selected child of the node.
*It delets the node and it's tree except from the selected child sub tree.
*It also created new level at the bottum.
*@return
*the selected child node (with its tree).
*NULL if the index is out of range.
**/

MiniMaxNode* moveForward(MiniMaxNode *myNode, int index);

/**This function take the chosen node and returning the newNode with a new tree.
*@return:
*if the node is NULL returns NULL, if index out of range returns NULL, if the chosen child is NULL returns NULL.
**

void addLevel(MiniMaxNode *myNode);

** This function recursivly updates all nodes in the tree according to the level of the tree.
*@return
*false, if the level <0
*true, otherwise.
**

*bool updateMiniMaxRecursivlly(MiniMaxNode *myNode, int level);
**/
int calcBoardScore(SPFiarGame* src);

int singleScore(int score);

int calcBoardRows(SPFiarGame* src);

int calcBoardCols(SPFiarGame* src);

int calcBoardDiagonals(SPFiarGame* src);

#endif
