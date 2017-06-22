#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include "SPFIARGame.h"
#include "SPArrayList.h"
#include "SPFIARParser.h"

/**
 * this function checks if the num is between 1-7
 * @param num
 * @return true if num is between 1-7 false if not
 */
bool checkNumRange7(int num);
/**
 * this function gets the difficulty level. continue to ask until the difficulty is valid, if gets quit she quits the program
 * @return int the dificulty level, NULL if exit
 */
int getGameDifficulty();
/**
 * this function gets a command and returns a number by the command type:
 *
 * @param game
 * @param command
 * @return:
 * 8 - exit pressed
 * 9 - restart pressed
 * 10 - undo move pressed
 * 1-7 - num of column
 * 0 - invalid move
 */
int proccesCommand(SPFiarGame *game, SPCommand command);
/**
 * this function first prints the board, then she keeps asking for commands until she stops: only when a valid move was made
 * she returns an int according to the function above
 * @param game
 * @return
 * 8 - exit pressed
 * 9 - restart pressed
 * 10 - undo move pressed
 * 1-7 - num of column
 */
int userTurn(SPFiarGame *game);
/**
 * this function does the suggested move from the function:
 * spMinimaxSuggestMove
 * and then prints the content of the suggested move print line
 * @param currentGame
 */
void suggestMove(SPFiarGame *currentGame);
/**
 * this function diils with the command after winning
 * @param command
 * @return
 * 8 - exit pressed
 * 9 - restart pressed
 * 10 - undo move pressed
 * 0 - not the above moves
 **/
int proccesWinCommand(SPCommand command);
/**
 * the function checks the simbol and prints the currect print line
 * then she asking for the use to enter one of the tree conmands quit, restart, undo
 * keep going until she gets one of those tree comands
 * @param simbol
 * @return
 * 8 - exit pressed
 * 9 - restart pressed
 * 10 - undo move pressed
 */
int  handleWinner(char simbol);
/**
 * this function undo the user turn and the comp turn
 * @param game
 * @return  the current game after the change
 */
SPFiarGame* undoMove(SPFiarGame *game);

//General Prints
int printDifficulty();
void printNextMove();
void printExit();
void printGameOverWin();
void printGameOverLose();
void printGameOverTie();
void printCont();
void printQuit();
void printRestart();
void printSuggestMove(int col);
void printUndoComp(int col);
void printUndoUser(int col);
void printCompNewDisc(int col);


//Error prints
void invalidLevel();
void invalidCommand();
void addDiscInvalid();
void addDiscFull(int col);
void errorUndo();
void errorGameOver();

#endif
