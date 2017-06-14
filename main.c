#include <stdio.h>
#include <stdbool.h>
#include "SPMainAux.h"
#include "SPMiniMaxNode.h"
#include "SPFIARGame.h"
#include "SPMiniMax.h"

int main() {
	bool newGame = True;
	int round = 0;
	int gameLevel = NULL;
	int player = SP_FIAR_GAME_PLAYER_1_SYMBOL;
	SPFiarGame *game = NULL;
	while(true){
		if (newGame) {
			gameLevel = getGameDifficulty();
		}

	}
	return 0;
}
