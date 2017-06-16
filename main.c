#include <stdio.h>
#include <stdbool.h>
#include "SPMainAux.h"
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"

int main() {
	bool newGame = true;
	char isWon = 'B';
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
			game -> currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
		}
		if (game -> currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
			if (isWon == 'B') {
				move = userTurn(miniMaxNode);
			}
			if (move == 8) {
				freeMem(miniMaxNode);
				break;
			} else if (move == 9) {
				freeMem(miniMaxNode);
				newGame = true;
			} else if (move == 10) {
				miniMaxNode = undoMove(miniMaxNode, gameLevel);
				round -= 2;
			} else if (isWon != 'B') {
				spFiarGameSetMove(game, move);
				miniMaxNode = moveForward(miniMaxNode, move);
				game -> currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
			}
		} else {
			move = miniMaxNode -> minChildIndex; 
			spFiarGameSetMove(game, move);
			miniMaxNode = moveForward(miniMaxNode, move);
			game -> currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
		}
		isWon = spFiarCheckWinner(game);
		if (isWon != 'B') {
			move = handleWinner(isWon);
		}
		round += 1;
	}
	return 0;
}
