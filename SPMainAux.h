#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

//Validity and command proccessing
bool checkNumRange7(int num);
int getGameDifficulty();
int proccesComand(SPFiarGame* currentGame, SPCommand command, int gameLevel);
bool userTurn(MiniMaxNode *node, int gameLevel);
int suggestMove(MiniMaxNode *node);

//General Prints
void printDifficulty();
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
