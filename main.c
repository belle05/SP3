#include <stdio.h>
#include <stdbool.h>
#include "SPMainAux.h"
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"

int main() {
	bool newGame = true;
	bool isWon = false;
	bool success = false;
	int move = 0;
	int round = 0;
	int gameLevel = NULL;
	int player = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	int chosenPath = 0;
	char* input[1024];
	for (unsigned int i=0; i<1024; i++) input[i] ='\0';
	SPFiarGame *game = NULL;
	MiniMaxNode *miniMaxNode = NULL;
	SPCommand command;
	SP_FIAR_GAME_MESSAGE message;
	
	while(true){	
		if (newGame) {
			gameLevel = getGameDifficulty();
			if (gameLevel == -1) {
				break;
			}
			game = spFiarGameCreate(SP_ARRAY_MAX_HISTORY);
			miniMaxNode = nodeCreate(game);
			success = createNewTreeFromNode(miniMaxNode, gameLevel);
			newGame = false;
		}
		if (player == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
			move = userTurn(game, gameLevel);
			if (move == 8) {
				freeMem(miniMaxNode);
				break;
			} else if (move == 9) {
				freeMem(miniMaxNode);
				newGame = true;
			} else {
				printf("\nERROR ERROR ERROR\n");
				break;
			}
		} else {
			move = miniMaxNode -> minChildIndex; 
			message = spFiarGameSetMove(game, move);
		}
		miniMaxNode = moveForward(MiniMaxNode *myNode, move);
		message = spFiarCheckWinner(game);
	}
	return 0;
}
