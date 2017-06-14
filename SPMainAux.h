#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_

//Validity and command proccessing
bool checkNumRange7(int num);
int getGameDifficulty();
bool proccesComand(SPFiarGame* currentGame, SPCommand command, unsigned int maxDepth);

//General Prints
void printDifficulty();
void printNextMove();
void printGameOverWin();
void printGameOverLose();
void printGameOverTie();
void printCont();
void printQuit();
void printRestart();

//Error prints
void invalidLevel();
void invalidCommand();
void addDiscInvalid()
void addDiscFull(int col);
void errorUndo()
void errorGameOver()

#endif
