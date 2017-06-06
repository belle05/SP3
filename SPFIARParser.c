#ifndef SPFIARPARSER_H_
#define SPFIARPARSER_H_
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

/**
 * Checks if a specified string represents a valid integer. It is recommended
 * to use this function prior to calling the standard library function atoi.
 *
 * @return
 * true if the string represents a valid integer, and false otherwise.
 */

bool spParserIsInt(const char* str){
	long num=0;
	for(unsigned int i=0; i<sizeof(str); i++){
		if(isdigit(str[i])){
			num+=10*num+(long)str[i];
			if (num>=4294967295) {
				return false;
			}
		} else {
			return false;
		}
	}
	return true;
}

/**
 * Parses a specified line. If the line is a command which has an integer
 * argument then the argument is parsed and is saved in the field arg and the
 * field validArg is set to true. In any other case then 'validArg' is set to
 * false and the value 'arg' is undefined
 *
 * @return
 * A parsed line such that:
 *   cmd - contains the command type, if the line is invalid then this field is
 *         set to INVALID_LINE
 *   validArg - is set to true if the command is add_disc and the integer argument
 *              is valid
 *   arg      - the integer argument in case validArg is set to true
 */

SPCommand spParserPraseLine(const char* str) {
	SPCommand *myCommand;
	myCommand = (SPCommand*)malloc(sizeof(myCommand));
	if (str == NULL) {
		myCommand -> validArg = false;
		myCommand -> cmd = SP_INVALID_LINE;
	}
	if (checkIfNotOnlylWhiteSpaces == false) {
		myCommand -> cmd = SP_INVALID_LINE;
	}
	char * command;
	char * argument;
 	command = strtok (str," \t\v\f\r");
	arg = strtok (NULL," \t\v\f\r");
	if (!(command) || !( arg)) myCommand -> cmd = SP_INVALID_LINE;
	arg = strtok (NULL," \t\v\f\r");
	if (arg) myCommand -> cmd = SP_INVALID_LINE;
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
/*write get int from char that is int*/		
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



