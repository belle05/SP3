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
	if ((str == NULL)) { //|| (checkIfOnlylWhiteSpaces(str) == true)) {
		myCommand.arg = 0;
		myCommand.validArg = false;
		myCommand.cmd = SP_INVALID_LINE;
		return myCommand;
	}

	while (token != NULL || finishedArgs == false) {
		if (strcmp(token, "") != 0) {
			if (isCom) { 
				myCommand.cmd = checkForCommand(token);
				if (myCommand.cmd != SP_ADD_DISC){
					myCommand.validArg = true;
					finishedArgs = true;
				}
			} else {
				if (myCommand.cmd == SP_ADD_DISC){ //Flag that the command was add_disk
					if (spParserIsInt(token)) {
						myCommand.arg = atoi(token);
						myCommand.validArg = true; 
					} else {
						myCommand.cmd = SP_INVALID_LINE;
					}
					finishedArgs = true;
				} else  {
					myCommand.cmd = SP_INVALID_LINE;
					myCommand.validArg = false;
					finishedArgs = true;
				}
			}
			isCom = false;
		}
		token = strtok(NULL, parseChars);
	}
	if  (myCommand.cmd == SP_INVALID_LINE) {
		myCommand.cmd = SP_INVALID_LINE;
		myCommand.validArg = false;
	} else if (myCommand.cmd != SP_ADD_DISC){
		myCommand.arg = 0;
		myCommand.validArg = true;	
	}
	if (token != NULL && (strcmp(token, "\n") != 0)) {
		myCommand.arg = 0;
		myCommand.validArg = false;
	        myCommand.cmd = SP_INVALID_LINE;
        	return myCommand;
        }
	return myCommand;
}





SP_COMMAND checkForCommand(char *command) {
	if (command == NULL) {
		return SP_INVALID_LINE;
	}
	char *undo = "undo_move\0";
	char *add_disk = "add_disc\0";
	char *sp_suggest = "suggest_move\0";
	char *quit = "quit\0";
	char *restart = "restart_game\0";
	char *restart2 = "restart\0";
	if (strcmp(undo, command) == 0) {
		return SP_UNDO_MOVE;
	} else if (strcmp(add_disk, command) == 0) {
		return SP_ADD_DISC;
	} else if (strcmp(sp_suggest, command) == 0) {
		return SP_SUGGEST_MOVE;
	} else if (strcmp(quit, command) == 0) {
		return SP_QUIT;
	} else if ((strcmp(restart, command) == 0) || (strcmp(restart2, command) == 0)) {
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

