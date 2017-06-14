#include "SPMainAux.h"

void printDifficulty() {
	printf("Please enter the difficulty level between [1-7]:\n");
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

