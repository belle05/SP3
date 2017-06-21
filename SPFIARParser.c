#include "SPFIARParser.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>



bool spParserIsInt(char* str) {
	long num = 0;
	int size =0;
	bool isNull = false;
	int argument = 0;
	bool firstNumberAfter0 = false;

	while(!isNull) {
		if (str[size] != '\0') {
			size +=1 ;
		} else {
			isNull = true;
		}
	}
	for(int i=0; i < size; i++){
		if (i == 0 && str[0] == '-') {
			continue;
	        }
	        else if(isdigit(str[i])){
			argument = str[i] - '0';
			if ((argument == 0) && firstNumberAfter0 == false) {
				continue;
	                }
	                else if ((argument != 0) && firstNumberAfter0 == false) {
				firstNumberAfter0 = true;
				num = (10*num)+argument;
                        }
                        else {
				num=(10*num)+argument;
	                }
			if (num >= 2147483647) {
				return false;
			}
		}
	        else {
			return false;
	        }
	}
	return true;
}
bool checkIfOnlylWhiteSpaces(char* str) {
	int chr = 0;
	if (str[chr] == ' ')
		chr = 1;
	while (str[chr]>0) {
		if (!(str[chr] == ' '))
			return false;
		chr++;
	}
	return true;
}

/*
SPCommand spParserPraseLine(char* str) {
	printf("a");
	SPCommand myCommand;
	int size = 0;
	bool isNull = false;
	while(!isNull) {
		if (str[size] != '\0') {
			size +=1;
		} else {
			isNull = true;
		}
	}
	char newstr[size];
//	myCommand = (SPCommand *)malloc(sizeof(SPCommand));
	printf("b");
	if ((str == NULL) || (checkIfOnlylWhiteSpaces(str) == true)) {
		myCommand.arg = 0;
		myCommand.validArg = false;
		myCommand.cmd = SP_INVALID_LINE;
		return myCommand;
	}
	for (int i=0; i<size; i++) {
		newstr[i] = '\0';
	}
	strcpy(newstr, str);
	char *command;
	char *argument;
 	command = strtok (newstr," \t\v\f\r");
	argument = strtok (NULL," \t\v\f\r");
	if (!(command) || !( argument)) {
		myCommand.cmd = SP_INVALID_LINE;
	}
	argument = strtok (NULL," \t\v\f\r");
	if (strcmp( argument, "\n") == 0) {
		argument = strtok (NULL," \t\v\f\r");
		if (argument) myCommand.cmd = SP_INVALID_LINE;
	}
	else if (strcmp( argument, "\n") != 0 && argument != NULL) {
		myCommand.cmd = SP_INVALID_LINE;
	}
	if ((checkForCommand(command) == SP_ADD_DISC) && spParserIsInt(argument) ) {
		myCommand.cmd = SP_ADD_DISC;
		myCommand.validArg = true;
		myCommand.arg = getInt(argument);
	}
	else {
		if ((checkForCommand(command) == SP_ADD_DISC) && spParserIsInt(argument) == false) myCommand.cmd = SP_INVALID_LINE;
		else myCommand.cmd = checkForCommand(command);
		myCommand.validArg = false;
		myCommand.arg = 0;
	}
	return myCommand;	
}

*/




SPCommand spParserPraseLine(char* str) {
	char *token = NULL;
	char *parseChars = " \t\r\n";;
	SPCommand myCommand;
	char local_str[SP_MAX_LINE_LENGTH];
	bool isCom = true;
	bool finishedArgs = false;
	strcpy(local_str, str);
	myCommand.validArg = true;
	token = strtok(local_str, parseChars);
//	printf("\nBoom");
//	if (checkIfOnlylWhiteSpaces(str) == true) {
//		printf("\nClap");
//	}
	if ((str == NULL)) { //|| (checkIfOnlylWhiteSpaces(str) == true)) {
//		printf("\ninvalid");
		myCommand.arg = 0;
		myCommand.validArg = false;
		myCommand.cmd = SP_INVALID_LINE;
		return myCommand;
	}


	while (token != NULL || finishedArgs == false) {
//		printf("token is %s\n",token);
		if (strcmp(token, "") != 0) {
			if (isCom) { 
				myCommand.cmd = checkForCommand(token);
				isCom = false;
				if (myCommand.cmd != SP_ADD_DISC){
					finishedArgs = true;
				}
			} else {
				//token = strtok(NULL, parseChars);
				if (myCommand.cmd == SP_ADD_DISC){ //Flag that the command was add_disk
					if (spParserIsInt(token)) {
						myCommand.arg = atoi(token);
						myCommand.validArg = true; 
					} else {
//						printf("valid command not valid arg\n");
						myCommand.cmd = SP_INVALID_LINE;
					}
					finishedArgs = true;
				} else  {
//					printf("found invalid command\n");
					myCommand.cmd = SP_INVALID_LINE;
					myCommand.validArg = false;
					finishedArgs = true;
				}
			//	} else {
			//		printf("not add disk and not invalid\n");
			//		myCommand.arg = 0;
			//		myCommand.validArg = true;
			//		finishedArgs = true;
			//	}
			}
		}
		token = strtok(NULL, parseChars);
	}
	if  (myCommand.cmd == SP_INVALID_LINE) {
		myCommand.cmd = SP_INVALID_LINE;
		myCommand.validArg = false;
	} else if (myCommand.cmd != SP_ADD_DISC){
//		printf("found different command from add_disc");
		myCommand.arg = 0;
		myCommand.validArg = true;	
	}
	if (token != NULL && (strcmp(token, "\n") != 0)) {
//		printf("\ninvalid");
		myCommand.arg = 0;
		myCommand.validArg = false;
        myCommand.cmd = SP_INVALID_LINE;
        return myCommand;
        }
	if (myCommand.validArg) {
//		printf("myCommand.cmd is %d, myCommand.arg is %d and valid is true\n", myCommand.cmd, myCommand.arg);
	} else {
//		printf("myCommand.cmd is %d, myCommand.arg is %d and valid is false\n", myCommand.cmd, myCommand.arg);
	}
//	printf("finished parser command\n");
	return myCommand;
}





SP_COMMAND checkForCommand(char *command) {
//	printf("\ncommand is %s\n", command);
	if (command == NULL) {
		return SP_INVALID_LINE;
	}
	char *undo = "undo_move\0";
	char *add_disk = "add_disc\0";
	char *sp_suggest = "suggest_move\0";
	char *quit = "quit\0";
	char *restart = "restart\0";
//	strcpy(undo, "undo_move");
//	strcpy(add_disk, "add_disk");
//	strcpy(sp_suggest, "suggest_move") ;
//	strcpy(quit,"quit");
//	strcpy(restart,"restart");
//	int a, b, c;
//	a = strcmp(undo, command);
//	b = strcmp(add_disk, command);
//	c = strcmp(sp_suggest, command);
//	printf("\na=%d, b=%d, c=%d\n", a, b, c);
	if (strcmp(undo, command) == 0) {
		return SP_UNDO_MOVE;
	} else if (strcmp(add_disk, command) == 0) {
		return SP_ADD_DISC;
	} else if (strcmp(sp_suggest, command) == 0) {
		return SP_SUGGEST_MOVE;
	} else if (strcmp(quit, command) == 0) {
//		printf("found quit");
		return SP_QUIT;
	} else if (strcmp(restart, command) == 0) {
		return SP_RESTART;
	} else {
		return SP_INVALID_LINE;
	}
}

int getInt(char* argument) {
	int argumentI;
	argumentI = atoi(argument);
	return argumentI;
}

bool checkIfNotOnlyWhiteSpaces(const char* str) {
	bool notOnlylWhiteSpaces = false;
	int size=0;
	bool isNull=false;
	while(!isNull) {
		if (str[size] != '\0') {
			size+=1;
		} else {
			isNull = true;
		}
	}
        for(int i=0; i<size; i++){
                if (isspace(str[i]) == false) {
                        notOnlylWhiteSpaces = true;
                        break;
                }
        }
	return notOnlylWhiteSpaces;
}



