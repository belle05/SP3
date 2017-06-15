#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_
#include <stddef.h>

//Validity and command proccessing
bool checkNumRange7(int num);
int getGameDifficulty();
int proccesComand(SPFiarGame* currentGame, SPCommand command, int gameLevel);
int userTurn(MiniMaxNode *node, int gameLevel);
int suggestMove(MiniMaxNode *node);
bool freeMem(MiniMaxNode *node);
int proccesComandWin(SPCommand command);
int  handleWinner(char simbol);
MiniMaxNode* undoMove(MiniMaxNode *node);

//General Prints
int printDifficulty();
void printNextMove();
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
void addDiscInvalid()
void addDiscFull(int col);
void errorUndo()
void errorGameOver()

#endif
