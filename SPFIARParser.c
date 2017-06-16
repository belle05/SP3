#include "SPFIARParser.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool spParserIsInt(char* str) {
	int chr = 0;
	if (str[chr] == '-')
		chr = 1;
	while (str[chr]) {
		if (!('0' <= str[chr] && str[chr] <= '9'))
			return false;
		chr++;
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
	SPCommand *myCommand;
	myCommand = (SPCommand*)malloc(sizeof(myCommand));
	if (str == NULL) {
		myCommand -> validArg = false;
		myCommand -> cmd = SP_INVALID_LINE;
	}
	if (checkIfOnlylWhiteSpaces(str) == true) {
		myCommand -> cmd = SP_INVALID_LINE;
	}
	char newstr[1024];
	for (unsigned int i=0; i<sizeof(newstr); i++) {
		newstr[i] = '\0';
	}
	strcpy(newstr, str);
	char *command;
	char *argument;
 	command = strtok (newstr," \t\v\f\r");
	argument = strtok (NULL," \t\v\f\r");
	if (!(command) || !( argument)) myCommand -> cmd = SP_INVALID_LINE;
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
	 int num=0;
	 bool firstNumberAfter0 = false;
	 bool negative = false;
	 for(unsigned int i=0; i<sizeof(argument); i++){
	     if (i == 0 && argument[0] == '-') {
	    	 negative = true;
	     }
	     else {
	         if (((int)argument[i] == 0) && firstNumberAfter0 == false) {
	        	 continue;
	         }
	         else if (((int)argument[i] != 0) && firstNumberAfter0 == false) {
	             firstNumberAfter0 = true;
	             num+=10*num+(int)argument[i];
	         }
	         else {
	             num+=10*num+(int)argument[i];
	         }
	     }
	 }
	 if (negative) {
		 return num*-1;
	 }
	 else {
		 return num;
	 }

}

bool checkIfNotOnlyWhiteSpaces(const char* str) {
	bool notOnlylWhiteSpaces = false;
        for(unsigned int i=0; i<sizeof(str); i++){
                if (isspace(str[i]) == false) {
                        notOnlylWhiteSpaces = true;
                        break;
                }
        }
	return notOnlylWhiteSpaces;
}



