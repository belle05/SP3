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
bool checkIfOnlylWhiteSpaces(const char* str) {
	int chr = 0;
	if (str[chr] == ' ')
		chr = 1;
	while (str[chr]) {
		if (!(str[chr] == ' '))
			return false;
		chr++;
	}
	return true;
}

SPCommand spParserPraseLine(char* str) {
	printf("a");
	SPCommand *myCommand;
	int size = 0;
	bool isNull = false;
	while(isNull) {
		if (str[size] != '\0') {
			size +=1;
		} else {
			isNull = true;
		}
	}
	myCommand = (SPCommand*)malloc(sizeof(myCommand));
	printf("b");
	if (str == NULL) {
		myCommand -> validArg = false;
		myCommand -> cmd = SP_INVALID_LINE;
	}
	if (checkIfOnlylWhiteSpaces(str) == true) {
		myCommand -> cmd = SP_INVALID_LINE;
	}
	char newstr[1024];
	for (int i=0; i<size; i++) {
		newstr[i] = '\0';
	}
	strcpy(newstr, str);
	char *command;
	char *argument;
 	command = strtok (newstr," \t\v\f\r");
	argument = strtok (NULL," \t\v\f\r");
	if (!(command) || !( argument)) {
		myCommand -> cmd = SP_INVALID_LINE;
	}
	argument = strtok (NULL," \t\v\f\r");
	if (strcmp( argument, "\n") == 0) {
		argument = strtok (NULL," \t\v\f\r");
		if (argument) myCommand -> cmd = SP_INVALID_LINE;
	}
	else if (strcmp( argument, "\n") != 0 && argument != NULL) {
		myCommand -> cmd = SP_INVALID_LINE;
	}
	if (myCommand -> cmd == SP_INVALID_LINE) {
                myCommand -> validArg = false;
                myCommand -> arg = 0;
                return *myCommand;
        }
	if ((checkForCommand(command) == SP_ADD_DISC) && spParserIsInt(argument) ) {
		myCommand -> cmd = SP_ADD_DISC;
		myCommand -> validArg = true;
		myCommand -> arg = getInt(argument);
	}
	else {
		if ((checkForCommand(command) == SP_ADD_DISC) && spParserIsInt(argument) == false) myCommand -> cmd = SP_INVALID_LINE;
		else myCommand -> cmd = checkForCommand(command);
		myCommand -> validArg = false;
		myCommand -> arg = 0;
	}
	return *myCommand;	
}
SP_COMMAND checkForCommand(const char* command) {
	if (command == NULL) {
		return SP_INVALID_LINE;
	}
	char undo[9];
	char add_disk[8];
	char sp_suggest[12];
	char quit[4];
	char restart[7];
	strcpy(undo, "undo_move");
	strcpy(add_disk, "add_disk");
	strcpy(sp_suggest, "suggest_move") ;
	strcpy(quit,"quit");
	strcpy(restart,"restart");
	if (strcmp(undo,command) == 0) return SP_UNDO_MOVE;
	else if (strcmp(add_disk,command) == 0) return SP_ADD_DISC;
	else if (strcmp(sp_suggest,command) == 0) return SP_SUGGEST_MOVE;
	else if (strcmp(quit,command) == 0) return SP_QUIT;
	else if (strcmp(restart,command) == 0) return SP_RESTART;
	else return SP_INVALID_LINE;
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
        for(unsigned int i=0; i<sizeof(str); i++){
                if (isspace(str[i]) == false) {
                        notOnlylWhiteSpaces = true;
                        break;
                }
        }
	return notOnlylWhiteSpaces;
}



