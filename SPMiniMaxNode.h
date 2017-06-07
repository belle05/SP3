#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

int calcBoardScore(SPFiarGame* src,  char player1, char player2);

int singleScore(int score);

int calcBoardRows(SPFiarGame* src, char player1, char player2);

int calcBoardCols(SPFiarGame* src);

int calcBoardDiagonals(SPFiarGame* src);

#endif
