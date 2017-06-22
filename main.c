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
		} if (game -> currentPlayer == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
			if (isWon == '\0') {
				move = userTurn(game);
			} if (move == 8) {
				spFiarGameDestroy(game);
				printExit();
				exit(0);
			} else if (move == 9) {
				spFiarGameDestroy(game);
				newGame = true;
			} else if (move == 10) {
				game = undoMove(game);
				if(game == NULL) {
					spFiarGameDestroy(game);
					printQuit();
					exit(0);
				}
				round -= 2;
			} else if (isWon == '\0') {
				spFiarGameSetMove(game, move-1);
				game -> currentPlayer = SP_FIAR_GAME_PLAYER_2_SYMBOL;
			}
		} else {
			move = spMinimaxSuggestMove(game, gameLevel);
			printCompNewDisc(move);
			if (move == 3000) {
				printExit();
                                exit(0);
                        }
			spFiarGameSetMove(game, move);
			game -> currentPlayer = SP_FIAR_GAME_PLAYER_1_SYMBOL;
		} if ((move != 8) && (move != 9)) {
			isWon = spFiarCheckWinner(game);
		} if (isWon != '\0') {
			move = handleWinner(isWon);
		}
		round += 1;
	}
	return 0;
}
