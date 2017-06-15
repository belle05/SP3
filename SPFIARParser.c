#include "SPFIARParser.h"
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

bool spParserIsInt(const char* str){
	 long num=0;
	        bool firstNumberAfter0 = false;
	        bool negative = false;
	        for(unsigned int i=0; i<sizeof(str); i++){
	                if (i == 0 && str[0] == '-') {
	                        negative = true;
	                }
	                else if(isdigit(str[i])){
	                        if (((long)str[i] == 0) && firstNumberAfter0 == false) {
	                                continue;
	                        }
	                        else if (((long)str[i] != 0) && firstNumberAfter0 == false) {
	                                firstNumberAfter0 = true;
	                                num+=10*num+(long)str[i];
	                        }
	                        else {
	                                num+=10*num+(long)str[i];
	                        }
	                        if (num>=2147483647) {
	                                return false;
	                        }
	                } else {
	                        return false;
	                }
	        }
	        return true;
}

SPCommand spParserPraseLine(const char* str) {
	SPCommand *myCommand;
	myCommand = (SPCommand*)malloc(sizeof(myCommand));
	if (str == NULL) {
		myCommand -> validArg = false;
		myCommand -> cmd = SP_INVALID_LINE;
	}
	if (checkIfNotOnlylWhiteSpaces(str) == false) {
		myCommand -> cmd = SP_INVALID_LINE;
	}
	char* newstr[1024];
	for (unsigned int i=0; i<sizeof(newstr); i++) {
		newstr[i] = '\0';
	}
	strcpy(newstr, str);
	char * command;
	char * argument;
 	command = strtok (newstr," \t\v\f\r");
	arg = strtok (NULL," \t\v\f\r");
	if (!(command) || !( arg)) myCommand -> cmd = SP_INVALID_LINE;
	arg = strtok (NULL," \t\v\f\r");
	if (arg == '\n') {
		arg = strtok (NULL," \t\v\f\r");
		if (arg) myCommand -> cmd = SP_INVALID_LINE;
	}
	else if (arg != '\n' && arg != NULL)  myCommand -> cmd = SP_INVALID_LINE;
	if (myCommand -> cmd == SP_INVALID_LINE) {
                myCommand -> validArg = false;
                myCommand -> arg = 0;
                return myCommand;
        }
	if ((checkForCommand(command) == SP_ADD_DISC) && SPParserIsInt(arg) ) {
		myCommand -> cmd = SP_ADD_DISC;
		myCommand -> validArg = true;
		myCommand -> arg = getInt(argument);
	}
	else {
		if ((checkForCommand(command) == SP_ADD_DISC) && SPParserIsInt(arg) == false) myCommand -> cmd = SP_INVALID_LINE;
		else myCommand -> cmd = checkForCommand(command);
		myCommand -> validArg = false;
		myCommand -> arg = 0;
	}
	return myCommand;	
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



