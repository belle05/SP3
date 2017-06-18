#include "SPMainAux.h"
#include "SPFIARParser.h"

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
		printf("\nblankkkkkk\n");
	}
//	scanf("%s", charDifficulty);
	//printf("cahrDifficulty is %s\n",charDifficulty);
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
	int gameLevel = '\0';
	while (gameLevel == '\0') {
		gameLevel = printDifficulty();
		if (gameLevel == '\0') {
			return -1;
		}
		if (!checkNumRange7(gameLevel)){
			invalidLevel();
			gameLevel = '\0';
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

int proccesCommand(MiniMaxNode *node, SPCommand command) {
//TODO: figure out how to use game level
	printf("1");
	if (!(command.validArg)) {
		printf("2");
		invalidCommand();
	        return 0;
	}
	else if (command.cmd == SP_QUIT) {
		printf("3");
		return 8;
	}
    	else if (command.cmd == SP_RESTART){
		printf("4");
		printRestart();
	        return 9;
   	}
	else if (command.cmd == SP_SUGGEST_MOVE){
		printf("5");
	        suggestMove(node);
        	return 0;
   	}
    	else if(command.cmd == SP_UNDO_MOVE){
		printf("6");
		return 10;
	}
	else if (command.cmd==SP_ADD_DISC){
		printf("7");
		if (!checkNumRange7(command.arg)) {
			addDiscInvalid();
           		return 0;
        	}
		if (!spFiarGameIsValidMove(node -> myGame, command.arg-1)) {
			addDiscFull(command.arg);
		        return 0;
		}
//		spFiarGameSetMove(node -> myGame, command.arg-1);
		return command.arg;
	}
	return 0;
}

int userTurn(MiniMaxNode *node) {
	SPCommand command;
	char str[SP_MAX_LINE_LENGTH];
	int move = 0;
//	for (int i=0; i<SP_MAX_LINE_LENGTH; i++) {
//		str[i] = '\0';
//	}
	spFiarGamePrintBoard(node -> myGame);
	while (move == 0) {
		printf("\nmove is %d\n", move);
		printNextMove();
		fflush(stdin);
	        fgets(str, SP_MAX_LINE_LENGTH, stdin);
		sscanf(str, "%[^\n]s", str);
//		scanf(" %[^\n]", str);
//		printf("%s\n", str);
//		if (checkIfOnlylWhiteSpaces(str)) {
//			printf("\nonly whites!!!!");
//		}
//		printf("%s\n", str);
//        	scanf("%[^\n]s", str);
//		printf("lalala\n");
	        command = spParserPraseLine((char *)str);
		move = proccesCommand(node, command);
//		printf("move2 is %d\n", move);
	}
	return move;
}

int suggestMove(MiniMaxNode *node) {
	return node -> maxChildIndex;
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
	while (move !=8 || move!=9 || move !=10 ) {
		printCont();
                fflush(stdin);
                fgets(str, 1024, stdin);
		sscanf(str, "%[^ \n]s", str);
//                scanf("%[^\n]s", str);
		command = spParserPraseLine(str);
		move = proccesWinCommand(command);
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


MiniMaxNode* undoMove(MiniMaxNode *node, int gameLevel) {
	MiniMaxNode *miniMaxNode;
	SPFiarGame *newGame;
	newGame = spFiarGameCopy(node -> myGame);
	spFiarGameUndoPrevMove(newGame);
	miniMaxNode = nodeCreate(newGame);
	createNewTreeFromNode(miniMaxNode, gameLevel);
	return miniMaxNode;
}

int compTurn(MiniMaxNode *node) {
	int moveOptions = SP_FIAR_GAME_N_COLUMNS;
	bool moveMade = false;
	int move;
	while (!moveMade || moveOptions > 0) {
		move = node -> minChildIndex;
		if (!spFiarGameIsValidMove(node -> myGame, move)) {
			updateMiniMaxNode(node);
			moveOptions -= 1;
		} else {
			printf("\nComputer move will be %d", move);
			spFiarGameSetMove(node -> myGame, move);
			spFiarGamePrintBoard(node -> myGame);
			return move;
		}
	}
	return 10;
}

