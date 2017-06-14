#include "SPMainAux.h"

char *

void printDifficulty() {
	int difficulty;
	printf("Please enter the difficulty level between [1-7]:\n");
	scanf("%d", difficulty);
	return difficulty;
}

bool checkNumRange7(int num){
	for (i=1; i < 8; i++) {
		if (i==num) {
			return true;
		}
	}
	return false;
}

int getGameDifficulty() {
	int gameLevel = NULL;
	while (gameLevel == NULL) {
		gameLevel = printDifficulty();
		if (!checkNumRange7(gameLevel)){
			invalidLevel();
			gameLevel = NULL;
		}
	}
	return gameLevel;
}


void printNextMove() {
	printf("Please make the next move:\n");
}

void printGameOverWin() {
	printf("Game over: you win\n");
	printCont();
}

void printGameOverLose() {
	printf("Game over: computer wins\n");
	printCont();
}

void printGameOverTie() {
	printf("Game over: it's a tie\n");
	printCont();
}

void printCont() {
	printf("Please enter 'quit' to exit or 'restart' to start a new game!\n");
}

void pringSuggestMove(int col) {
	printf("Suggested move: drop a disc to column %d\n",col+1);
}

void printUndoComp(int col1) {
	printf("Remove disc: remove computer's disc at column %d\n",col1+1);
}

void printUndoUser(int col2) {
	printf("Remove disc: remove user's disc at column %d\n",col2+1);
}

void printCompNewDisc(int col) {
	printf("Computer move: add disc to column %d\n",col+1);
}

void printQuit() {
	printf("Exiting...\n");
}

void printRestart() {
	printf("Game restarted!\n");
}

void invalidLevel() {
	printf("Error: invalid level (should be between 1 to 7)\n");
}

void invalidCommand() {
	printf("Error: invalid command\n");
	return 0;
}

void addDiscInvalid() {
	printf("Error: column number must be in range 1-7\n");
}

void addDiscFull(int col) {
	printf("Error: column %d is full\n",col+1);
}

void errorUndo() {
	printf("Error: cannot undo previous move!\n");
}

void errorGameOver() {
	printf("Error: the game is over\n");
}

bool proccesComand(SPFiarGame* currentGame, SPCommand command, unsigned int maxDepth){
	bool user_wins = false;
	if (!command.validArg) {
		invalidCommand();
	        return 0;
	}
	else if (command.cmd == SP_QUIT) {
		quitGame(currentGame);
		return 1;
	}
    	else if (command.cmd == SP_RESTART){
        	restartGame(currentGame);
	        return 1;
   	}
	else if (command.cmd == SP_SUGGEST_MOVE){
	        suggestMove(currentGame, maxDepth);
        	return 0;
   	}
    	else if(command.cmd == SP_UNDO_MOVE){
        	if(undoMove(currentGame))
      			return 1;
		return 0;
	}
	else if (command.cmd==SP_ADD_DISC){
		if (!checkNumRange7) {
			addDiscInvalid();
           		return 0;
        	}
		if (!spFiarGameIsValidMove(currentGame,command.arg-1)) {
			addDiscFull(command.arg);
		        return 0;
		}
		spFiarGameSetMove(currentGame,command.arg-1);
		//TODO: decide how to manage winner scenario
		if (spFiarCheckWinner(curr_game) == SP_FIAR_GAME_PLAYER_1_SYMBOL) {
			user_wins = true;
		return 1;
	}
	return 0;
}
