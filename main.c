#include <stdio.h>
#include <stdbool.h>
#include "SPMainAux.h"
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"
#include <stdlib.h>

int main() {
	bool newGame = true;
	char isWon = '\0';
	int move = 0;
	int round = 0;
	int gameLevel = -1;
	SPFiarGame *game = NULL;

	while(true){	
		if (newGame) {
			gameLevel = getGameDifficulty();
			if (gameLevel == -1) {
				printExit();
				exit(0);
			}
			game = spFiarGameCreate(SP_ARRAY_MAX_HISTORY);
			if (game == NULL) {
				printExit();
                                exit(0);
			}
			game->level = gameLevel;
			newGame = false;
			round = 0;
		}
		if (game -> currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
			if (isWon == '\0') {
				move = userTurn(game);
			}
//			printf("\nmove is %d", move);
			if (move == 8) {
				//free(miniMaxNode);
//				MiniMaxDelete(miniMaxNode);
//				printf("before destroing game");
				spFiarGameDestroy(game);
//				printf("after destroing game");
				printExit();
				exit(0);
			} else if (move == 9) {
				spFiarGameDestroy(game);
				newGame = true;
			} else if (move == 10) {
				game = undoMove(game);
				round -= 2;
			} else if (isWon == '\0') {
				spFiarGameSetMove(game, move-1);
				//spFiarGamePrintBoard(game);
//				miniMaxNode = moveForward(miniMaxNode, move-1);
				game -> currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
			}
		} else {
//			move = miniMaxNode -> minChildIndex; 
//			printf("\nComputer move will be %d", move);
//			spFiarGameSetMove(game, move);
//			spFiarGamePrintBoard(miniMaxNode -> myGame);
//			move = compTurn(miniMaxNode);
			move = spMinimaxSuggestMove(game, gameLevel);
			printCompNewDisc(move);
			if (move == 3000) {
				printExit();
                                exit(0);
                        }
			spFiarGameSetMove(game, move);
			game -> currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;

//			if (move == 10) {
//				printf("ERROR! COMP MOVE CANT BE MADE");
//			} else {
//				miniMaxNode = moveForward(miniMaxNode, move);
//				printf("node moved");
//				game -> currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
//			}
		}
		if ((move != 8) && (move != 9)) {
//			printf("checking winer from main\n");
			isWon = spFiarCheckWinner(game);
		}
//		printf("isWon is %c\n", isWon);
		if (isWon != '\0') {
//			printf("found winner score: %d\n",calcBoardScore2(game));
			move = handleWinner(isWon);
		}
		round += 1;
	}
	return 0;
}
