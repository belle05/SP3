#include <stdio.h>
#include <stdbool.h>
#include "SPMainAux.h"
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"

int main() {
	bool newGame = true;
	char isWon = '\0';
	int move = 0;
	int round = 0;
	int gameLevel = -1;
	SPFiarGame *game = NULL;
	MiniMaxNode *miniMaxNode = NULL;
	
	while(true){	
		if (newGame) {
			gameLevel = getGameDifficulty();
			if (gameLevel == -1) {
				break;
			}
			game = spFiarGameCreate(SP_ARRAY_MAX_HISTORY);
			miniMaxNode = nodeCreate(game);
			createNewTreeFromNode(miniMaxNode, gameLevel);
			newGame = false;
			round = 0;
		}
		if (miniMaxNode -> myGame -> currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
			if (isWon == '\0') {
				move = userTurn(miniMaxNode);
			}
			printf("\nmove is %d", move);
			if (move == 8) {
				freeMem(miniMaxNode);
				break;
			} else if (move == 9) {
				freeMem(miniMaxNode);
				newGame = true;
			} else if (move == 10) {
				miniMaxNode = undoMove(miniMaxNode, gameLevel);
				round -= 2;
			} else if (isWon == '\0') {
				spFiarGameSetMove(game, move-1);
				spFiarGamePrintBoard(miniMaxNode -> myGame);
				miniMaxNode = moveForward(miniMaxNode, move-1);
				miniMaxNode -> myGame -> currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
			}
		} else {
			move = miniMaxNode -> minChildIndex; 
			printf("\nComputer move will be %d", move);
			spFiarGameSetMove(game, move);
			spFiarGamePrintBoard(miniMaxNode -> myGame);
			miniMaxNode = moveForward(miniMaxNode, move);
			printf("node moved");
			game -> currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
		}
		if ((move != 8) && (move != 9)) {
			isWon = spFiarCheckWinner(miniMaxNode -> myGame);
		}
		printf("isWon is %c\n", isWon);
		if (isWon != '\0') {
			move = handleWinner(isWon);
		}
		round += 1;
	}
	return 0;
}
