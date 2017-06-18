#ifndef SPMAINAUX_H_
#define SPMAINAUX_H_
#include <stdbool.h>
#include <stdio.h>
#include <stddef.h>
#include "SPFIARGame.h"
#include "SPArrayList.h"
#include "SPFIARParser.h"

//Validity and command proccessing
bool checkNumRange7(int num);
int getGameDifficulty();
int proccesCommand(MiniMaxNode *node, SPCommand command);
int userTurn(MiniMaxNode *node);
int suggestMove(MiniMaxNode *node);
void freeMem(MiniMaxNode *node);
int proccesWinCommand(SPCommand command);
int  handleWinner(char simbol);
MiniMaxNode* undoMove(MiniMaxNode *node, int gameLevel);
int compTurn(MiniMaxNode *node);

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
void addDiscInvalid();
void addDiscFull(int col);
void errorUndo();
void errorGameOver();

#endif
