#include "SPMainAux.h"
#include "SPFIARParser.h"
#include "SPMiniMax.h"

int  printDifficulty() {
	int difficulty;
	char charDifficulty[SP_MAX_LINE_LENGTH];
	for (int i = 0; i< SP_MAX_LINE_LENGTH; i++) {
		charDifficulty[i] = '\0';	
	}
	printf("Please enter the difficulty level between [1-7]:\n");
	fflush(stdin);
        fgets(charDifficulty, SP_MAX_LINE_LENGTH, stdin);
	sscanf(charDifficulty, "%[^ \n]s", charDifficulty);
	if (checkIfOnlylWhiteSpaces(charDifficulty)) {
	}
	if (spParserIsInt(charDifficulty)) {
		difficulty = getInt(charDifficulty);
		return difficulty;
	}
	else if (spParserPraseLine(charDifficulty).cmd == SP_QUIT) {
		return '\0';
	}
	else {
		return -2;
	}
}

bool checkNumRange7(int num){
	for (int i=1; i < 8; i++) {
		if (i==num) {
			return true;
		}
	}
	return false;
}

int getGameDifficulty() {
	int gameLevel = -1;
	while (gameLevel == -1) {
		gameLevel = printDifficulty();
		if (gameLevel == '\0') {
			return -1;
		}
		if (!checkNumRange7(gameLevel)){
			invalidLevel();
			gameLevel = -1;
		}
	}
	return gameLevel;
}


void printNextMove() {
	printf("Please make the next move:\n");
}

void printGameOverWin() {
	printf("Game over: you win\n");
}

void printGameOverLose() {
	printf("Game over: computer wins\n");
}
void printGameOverTie() {
	printf("Game over: it's a tie\n");
}

void printCont() {
	printf("Please enter 'quit' to exit or 'restart' to start a new game!\n");
}

void printSuggestMove(int col) {
	printf("Suggested move: drop a disc to column %d\n",col+1);
}

void printUndoComp(int col) {
	printf("Remove disc: remove computer's disc at column %d\n",col+1);
}

void printUndoUser(int col) {
	printf("Remove disc: remove user's disc at column %d\n",col+1);
}

void printCompNewDisc(int col) {
	printf("Computer move: add disc to column %d\n",col+1);
}

void printQuit() {
	printf("Exiting...\n\n");
}

void printRestart() {
	printf("Game restarted!\n");
}

void invalidLevel() {
	printf("Error: invalid level (should be between 1 to 7)\n");
}

void invalidCommand() {
	printf("Error: invalid command\n");
}

void addDiscInvalid() {
	printf("Error: column number must be in range 1-7\n");
}

void addDiscFull(int col) {
	printf("Error: column %d is full\n",col);
}

void errorUndo() {
	printf("Error: cannot undo previous move!\n");
}

void errorGameOver() {
	printf("Error: the game is over\n");
}
void printExit() {
	printf("Exiting...\n\n");
}


int proccesCommand(SPFiarGame *game, SPCommand command) {
	if (!(command.validArg)) {
		invalidCommand();
	        return 0;
	}
	else if (command.cmd == SP_QUIT) {
		return 8;
	}
    	else if (command.cmd == SP_RESTART){
		printRestart();
	        return 9;
   	}
	else if (command.cmd == SP_SUGGEST_MOVE){
	        suggestMove(game);
        	return 0;
   	}
    	else if(command.cmd == SP_UNDO_MOVE){
		return 10;
	}
	else if (command.cmd==SP_ADD_DISC){
		if (!checkNumRange7(command.arg)) {
			addDiscInvalid();
           		return 0;
        	}
		if (!spFiarGameIsValidMove(game, command.arg-1)) {
			addDiscFull(command.arg);
		        return 0;
		}
		return command.arg;
	}
	return 0;
}

int userTurn(SPFiarGame *game) {
	SPCommand command;
	char str[SP_MAX_LINE_LENGTH];
	int move = -1;
	spFiarGamePrintBoard(game);
	while (move <= 0) {
		if (move == -1) {
			printNextMove();
			move = 0;
		}
		fflush(stdin);
	        fgets(str, SP_MAX_LINE_LENGTH, stdin);
		sscanf(str, "%[^\n]s", str);
	        command = spParserPraseLine((char *)str);
		move = proccesCommand(game, command);
	}
	return move;
}

void suggestMove(SPFiarGame *currentGame) {
	int move;
	move = spMinimaxSuggestMove(currentGame, currentGame->level);
	printSuggestMove(move);
}



int  handleWinner(char simbol) {
	SPCommand command;
	char str[1024];
	int move = 0;
	if (simbol == 'X') {
		printGameOverWin();
	}
	else if (simbol == 'O') {
		printGameOverLose();
	}
	else if (simbol == '-') {
		printGameOverTie();
	}			
	while (move !=8 && move!=9 && move !=10 ) {
		printCont();
		fflush(stdin);
                fgets(str, SP_MAX_LINE_LENGTH, stdin);
                sscanf(str, "%[^\n]s", str);
		command = spParserPraseLine(str);
		move = proccesWinCommand(command);
		if (move !=8 && move!=9 && move !=10) {
			printf("Error: the game is over\n");
		}
	}
	return move;
}

int proccesWinCommand(SPCommand command){
        if (command.cmd == SP_QUIT) {
                return 8;
        }
        else if (command.cmd == SP_RESTART){
                printRestart();
                return 9;
        }
        else if(command.cmd == SP_UNDO_MOVE){
                        return 10;
        }
        else {
		return 0;
        }
}


SPFiarGame* undoMove(SPFiarGame *game) {
	SP_FIAR_GAME_MESSAGE undoResult = spFiarGameUndoPrevMove(game);
	if (!(undoResult == SP_FIAR_GAME_SUCCESS)) {
		errorUndo();
		if (undoResult == SP_FIAR_GAME_NO_HISTORY) {
			return NULL;
		}
	}
	undoResult = spFiarGameUndoPrevMove(game);
	if (!(undoResult == SP_FIAR_GAME_SUCCESS)) {
		errorUndo();
		if (undoResult == SP_FIAR_GAME_NO_HISTORY) {
			return NULL;
		}
	}
	return game;
}
