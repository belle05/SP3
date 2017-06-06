#ifndef SPMINIMAXNODE_H_
#define SPMINIMAXNODE_H_

int calcBoardScore(SPFiarGame* src,  char player1, char player2);

int singleScore(int score);

int calcBoadRows(SPFiarGame* src, char player1, char player2);

int calcBoadCols(SPFiarGame* src);

int calcBoadDiagonals(SPFiarGame* src);

#endif
